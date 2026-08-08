// mir.cpp  —  the only hard-coded binary
// Everything else is discovered or refused at runtime.

#include "mir.hpp"
#include <iostream>

namespace mir {

// --- resolve / load helpers ---

std::string Mir::resolve_plugin(const std::string& role, const Json& /*settings*/) {
    // TODO: real settings lookup
    // settings["plugins"]["mainloop"] = "plugins/console_mainloop.so"
    // for bootstrap we hard-wire console path only as temporary
    if (role == "mainloop") return "plugins/console_mainloop/libconsole_mainloop.so";
    return {};
}

template<typename T>
std::unique_ptr<T> Mir::load_role(const std::string& role,
                                  T* (*factory)(PluginApi*),
                                  const Json& settings)
{
    auto path = resolve_plugin(role, settings);
    if (path.empty()) return nullptr;

    LibHandle h = load_lib(path);
    if (!h) return nullptr;

    auto get_api = reinterpret_cast<PluginApi*(*)()>(get_sym(h, "mir_plugin_api"));
    if (!get_api) { unload_lib(h); return nullptr; }

    PluginApi* api = get_api();
    if (!api || !factory(api)) { unload_lib(h); return nullptr; }

    // ownership stays with Mir; handle kept alive for process lifetime
    return std::unique_ptr<T>(factory(api));
}

bool Mir::boot(const Json& settings) {
    // 1. Main loop (console first → later glfw / pixelbuf / headless)
    loop = load_role<MainLoop>("mainloop",
        [](PluginApi* a){ return a->create_mainloop ? a->create_mainloop() : nullptr; },
        settings);

    // 2. AI station (Grok / Claude / local / none)
    ai = load_role<AiStation>("ai",
        [](PluginApi* a){ return a->create_ai ? a->create_ai() : nullptr; },
        settings);

    // 3. Local state engine
    state = load_role<StateEngine>("state",
        [](PluginApi* a){ return a->create_state ? a->create_state() : nullptr; },
        settings);

    // Mir itself is always present – the human PEBCAK
    return true;   // even if some plugins failed, Mir still runs
}

int Mir::run() {
    if (!loop) {
        std::cout << "[Mir] no mainloop plugin – sitting in PEBCAK mode\n";
        return 0;
    }

    loop->enter();
    Tick t{0.016};
    while (loop->tick(t)) {
        // Mir (the human) decides what to do this frame
        if (ai) {
            Json observation = state ? state->snapshot() : Json{};
            Json decision    = ai->ask(observation);
            if (state)
                state->apply(decision);
        }
        // … IO, rendering live inside the loaded mainloop
    }
    loop->exit();
    return 0;
}

} // namespace mir

// -------------------------------------------------
// entry point – the only hard-coded “DLL”
// -------------------------------------------------
int main(int /*argc*/, char** /*argv*/) {
    mir::Json settings; // TODO: settings_read(argc, argv)
    mir::Mir mir;
    if (!mir.boot(settings))
        return 1;
    return mir.run();
}

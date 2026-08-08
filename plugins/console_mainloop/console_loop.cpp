// Console MainLoop plugin — ASAP IO target
// cmd terminal only. No graphics yet. Mouse/key secondary later.

#include "../../core/stations.hpp"
#include <iostream>
#include <string>

namespace mir {
namespace plugins {

class ConsoleMainLoop : public MainLoop {
    bool running_ = false;
public:
    void enter() override {
        running_ = true;
        std::cout << "[console] MainLoop entered. Type 'q' + enter to quit.\n";
        std::cout << "[console] PEBCAK mode ready.\n";
    }

    bool tick(Tick& t) override {
        std::cout << "> " << std::flush;
        std::string line;
        if (!std::getline(std::cin, line)) {
            running_ = false;
            return false;
        }
        if (line == "q" || line == "quit" || line == "exit") {
            running_ = false;
            return false;
        }
        if (!line.empty())
            std::cout << "[console] cmd: " << line << "\n";

        t.dt = 0.016;
        return running_;
    }

    void exit() override {
        std::cout << "[console] MainLoop exit.\n";
        running_ = false;
    }
};

} // namespace plugins
} // namespace mir

// ---- plugin export ----
extern "C" mir::PluginApi* mir_plugin_api() {
    static mir::PluginApi api = {
        "console_mainloop",
        "0.1.0",
        /*create_mainloop*/ []() -> mir::MainLoop* {
            return new mir::plugins::ConsoleMainLoop();
        },
        /*create_ai*/       nullptr,
        /*create_state*/    nullptr
    };
    return &api;
}

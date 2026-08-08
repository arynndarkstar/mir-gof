#pragma once
// The three stations — pure interfaces. No implementation here.
// Plugins supply concrete factories via PluginApi.

#include "types.hpp"

namespace mir {

// -------------------------------------------------
// 1. MAIN LOOP STATION  (IO / entry / exit)
// -------------------------------------------------
class MainLoop {
public:
    virtual ~MainLoop() = default;
    virtual void enter() = 0;
    virtual bool tick(Tick&) = 0;          // return false → exit
    virtual void exit() = 0;
};

// -------------------------------------------------
// 2. AI STATION  (provider loader)
// -------------------------------------------------
class AiStation {
public:
    virtual ~AiStation() = default;
    virtual void configure(const Json& cfg) = 0;
    virtual Json ask(const Json& prompt) = 0;
};

// -------------------------------------------------
// 3. LOCAL STATE ENGINE
// -------------------------------------------------
class StateEngine {
public:
    virtual ~StateEngine() = default;
    virtual void load(const Json& bootstrap) = 0;
    virtual Json snapshot() = 0;
    virtual void apply(const Json& delta) = 0;
};

// -------------------------------------------------
// Plugin descriptor (what a hot-loaded DLL must export)
// -------------------------------------------------
struct PluginApi {
    const char* name;
    const char* version;
    // factory functions – one of these will be non-null
    MainLoop*    (*create_mainloop)();
    AiStation*   (*create_ai)();
    StateEngine* (*create_state)();
};

// Required export from every plugin shared library:
// extern "C" PluginApi* mir_plugin_api();

} // namespace mir

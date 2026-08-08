#pragma once
// Mir — the PEBCAK human operator shell
// Only hard-coded binary. Everything else discovered or refused at runtime.

#include "stations.hpp"
#include "platform/dynlib.hpp"
#include <memory>
#include <string>

namespace mir {

class Mir {
    std::unique_ptr<MainLoop>    loop;
    std::unique_ptr<AiStation>   ai;
    std::unique_ptr<StateEngine> state;

    // never hard-code DLL names
    std::string resolve_plugin(const std::string& role, const Json& settings);

    template<typename T>
    std::unique_ptr<T> load_role(const std::string& role,
                                 T* (*factory)(PluginApi*),
                                 const Json& settings);

public:
    bool boot(const Json& settings);
    int  run();
};

} // namespace mir

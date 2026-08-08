#pragma once
// mir core types — minimal, no hard deps

#include <string>
#include <memory>
#include <functional>
#include <optional>
#include <cstdint>

namespace mir {

struct Tick {
    double dt = 0.016;
    // later: input events, frame id, wall time
};

// Thin Json placeholder. Replace with nlohmann::json or custom later.
// For now keeps core free of external headers.
struct Json {
    // intentional empty shell — plugins own real parsing
};

using LibHandle = void*;

} // namespace mir

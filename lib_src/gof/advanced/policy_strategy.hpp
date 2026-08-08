#pragma once
// Advanced: Policy-based Strategy (compile-time Strategy)
//
// Origin / lineage:
//   - GoF Strategy = runtime interchangeable algorithms
//   - Policy-based design popularised by Andrei Alexandrescu,
//     *Modern C++ Design* (2001) and the Loki library
//   - Modern comparison: oopscenities.net Strategy vs Policy-Based Design
//
// MIR use : compile-time selectable render backends, tick policies,
//           freestanding builds that cannot afford virtual dispatch.

#include "../common/crtp.hpp"
#include <utility>

namespace mir::gof::advanced {

template <typename Policy>
class PolicyHost : public Policy {
public:
    using Policy::Policy;

    template <typename... Args>
    decltype(auto) execute(Args&&... args) {
        return static_cast<Policy*>(this)->execute(std::forward<Args>(args)...);
    }
};

template <typename... Policies>
class MultiPolicyHost : public Policies... {
public:
    MultiPolicyHost() = default;
};

} // namespace mir::gof::advanced

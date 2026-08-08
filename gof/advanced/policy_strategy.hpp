#pragma once
// Advanced: Policy-based Strategy
// Problem : classic Strategy uses runtime polymorphism; when the set of
//           algorithms is known at compile time, policies give zero-overhead.
// Solution: the host is a template parameterized by one or more policy classes.
//           Policies supply the algorithm via static or non-virtual calls.
// MIR use : compile-time selectable render backends, tick policies, allocator
//           policies, logging policies.

#include "../common/crtp.hpp"

namespace mir::gof::advanced {

// Host that mixes in a Policy
template <typename Policy>
class PolicyHost : public Policy {
public:
    using Policy::Policy;   // inherit constructors if any

    // convenience: run the policy’s primary operation
    template <typename... Args>
    auto execute(Args&&... args) {
        return static_cast<Policy*>(this)->execute(std::forward<Args>(args)...);
    }
};

// Example policy shape (clients write their own)
// struct MyRenderPolicy {
//     void execute(PixelBuffer& buf) { /* ... */ }
// };
// using Renderer = PolicyHost<MyRenderPolicy>;

} // namespace mir::gof::advanced

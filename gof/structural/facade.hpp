#pragma once
// Facade — raw form
// Problem : a subsystem is complex; clients need a simple, unified entry point.
// Solution: a single façade class that delegates to the subsystem’s internal classes.
// MIR use : platform window + pixel buffer + input + sound as one “GraphicStation”
//           façade; plugin loading subsystem; AI provider + session management.

#include <memory>
#include <utility>

namespace mir::gof {

// Minimal illustrative façade skeleton.
// Real façades are written per subsystem; this header documents the intent
// and provides a tiny example of the shape.

template <typename SubsystemA, typename SubsystemB>
class Facade {
    std::unique_ptr<SubsystemA> a_;
    std::unique_ptr<SubsystemB> b_;
public:
    Facade(std::unique_ptr<SubsystemA> a, std::unique_ptr<SubsystemB> b)
        : a_(std::move(a)), b_(std::move(b)) {}

    // High-level operations that orchestrate the subsystems
    void operation() {
        if (a_) a_->do_work();
        if (b_) b_->do_work();
    }

    SubsystemA* a() noexcept { return a_.get(); }
    SubsystemB* b() noexcept { return b_.get(); }
};

} // namespace mir::gof

#pragma once
// Advanced: CRTP State Machine
// Problem : classic State uses virtual dispatch; closed compile-time sets can be static.
// Solution: CRTP host + state types; static or thin dispatch without vtable cost.
// Origin  : GoF State + CRTP (Coplien); common in game/embedded machines.
// MIR use : modal input, graphic focus, AI conversation phases (fixed set).

#include "../common/crtp.hpp"

namespace mir::gof::advanced {

template <typename Machine>
class CrtpState {
public:
    virtual ~CrtpState() = default;
    virtual void on_enter(Machine&) {}
    virtual void on_exit(Machine&)  {}
    virtual void handle(Machine&) = 0;
};

template <typename Machine>
class CrtpStateHost {
    CrtpState<Machine>* current_ = nullptr;
public:
    void change(CrtpState<Machine>* next) {
        if (current_) current_->on_exit(static_cast<Machine&>(*this));
        current_ = next;
        if (current_) current_->on_enter(static_cast<Machine&>(*this));
    }

    void handle() {
        if (current_) current_->handle(static_cast<Machine&>(*this));
    }
};

} // namespace mir::gof::advanced

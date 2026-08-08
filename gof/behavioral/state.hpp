#pragma once
// State — raw form (modern C++)
// Problem : an object must change its behaviour when its internal state changes.
// Solution: represent states as objects; the context delegates to the current state.
// MIR use : StateEngine station, modal input handling, AI conversation modes,
//           graphic window focus / interaction modes.

#include <memory>
#include <utility>

namespace mir::gof {

template <typename Context>
class State {
public:
    virtual ~State() = default;
    virtual void enter(Context& ctx) {}
    virtual void exit(Context& ctx)  {}
    virtual void handle(Context& ctx) = 0;
};

template <typename Context>
class StateContext {
    std::unique_ptr<State<Context>> current_;
public:
    void change_state(std::unique_ptr<State<Context>> next) {
        if (current_) current_->exit(static_cast<Context&>(*this));
        current_ = std::move(next);
        if (current_) current_->enter(static_cast<Context&>(*this));
    }

    void handle() {
        if (current_) current_->handle(static_cast<Context&>(*this));
    }

    [[nodiscard]] bool has_state() const noexcept {
        return static_cast<bool>(current_);
    }

protected:
    State<Context>* current_state() noexcept { return current_.get(); }
};

} // namespace mir::gof

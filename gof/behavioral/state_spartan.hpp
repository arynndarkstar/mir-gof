#pragma once
// State — spartan form
// No unique_ptr. Caller owns state objects (static / arena / explicit lifetime).
// Suitable for real-time loops and freestanding environments.

namespace mir::gof::spartan {

template <typename Context>
class State {
public:
    virtual ~State() = default;
    virtual void enter(Context&) {}
    virtual void exit(Context&)  {}
    virtual void handle(Context&) = 0;
};

template <typename Context>
class StateContext {
    State<Context>* current_ = nullptr;   // non-owning
public:
    void change_state(State<Context>* next) {
        if (current_) current_->exit(static_cast<Context&>(*this));
        current_ = next;
        if (current_) current_->enter(static_cast<Context&>(*this));
    }

    void handle() {
        if (current_) current_->handle(static_cast<Context&>(*this));
    }

    bool has_state() const { return current_ != nullptr; }

protected:
    State<Context>* current_state() noexcept { return current_; }
};

} // namespace mir::gof::spartan

#pragma once
// ScopeGuard — spartan form
// No exceptions, no std::function, no type traits.
// Suitable for freestanding / embedded / game-engine cores.

namespace mir::gof::idiom::spartan {

template <typename F>
class ScopeGuard {
    F f_;
    bool active_;
public:
    explicit ScopeGuard(F f) : f_(f), active_(true) {}

    ~ScopeGuard() {
        if (active_) f_();
    }

    void dismiss() { active_ = false; }

    // no copy
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

    // move is possible but kept simple
    ScopeGuard(ScopeGuard&& o) : f_(o.f_), active_(o.active_) {
        o.active_ = false;
    }
};

template <typename F>
ScopeGuard<F> make_scope_guard(F f) {
    return ScopeGuard<F>(f);
}

} // namespace mir::gof::idiom::spartan

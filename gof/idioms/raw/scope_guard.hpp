#pragma once
// ScopeGuard / ScopeExit — modern raw form
// RAII for arbitrary cleanup. Exception-safe.

#include <utility>
#include <type_traits>

namespace mir::gof::idiom {

template <typename F>
class ScopeGuard {
    F f_;
    bool active_ = true;
public:
    explicit ScopeGuard(F&& f) noexcept(std::is_nothrow_move_constructible_v<F>)
        : f_(std::forward<F>(f)) {}

    ScopeGuard(ScopeGuard&& other) noexcept(std::is_nothrow_move_constructible_v<F>)
        : f_(std::move(other.f_)), active_(other.active_) {
        other.active_ = false;
    }

    ~ScopeGuard() noexcept {
        if (active_) f_();
    }

    void dismiss() noexcept { active_ = false; }

    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;
};

template <typename F>
[[nodiscard]] ScopeGuard<std::decay_t<F>> make_scope_guard(F&& f) {
    return ScopeGuard<std::decay_t<F>>(std::forward<F>(f));
}

} // namespace mir::gof::idiom

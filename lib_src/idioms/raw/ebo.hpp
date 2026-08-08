#pragma once
// Empty Base Optimization (EBO) helper — raw form
// Problem : empty policy / trait classes still cost a byte if stored as members.
// Solution: inherit from them; EBO collapses the empty base.
// MIR use : policy-based hosts, compressed pair style storage.

namespace mir::gof::idiom {

template <typename T, typename Tag = void>
struct EboHolder : private T {
    EboHolder() = default;
    explicit EboHolder(const T& t) : T(t) {}
    explicit EboHolder(T&& t) : T(std::move(t)) {}

    T&       get()       noexcept { return static_cast<T&>(*this); }
    const T& get() const noexcept { return static_cast<const T&>(*this); }
};

} // namespace mir::gof::idiom

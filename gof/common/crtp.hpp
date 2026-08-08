#pragma once
// Spartan + Raw friendly CRTP base
// Usage: class Derived : public mir::gof::Crtp<Derived> { ... };

namespace mir::gof {

template <typename Derived>
class Crtp {
protected:
    constexpr Derived&       self()       noexcept { return static_cast<Derived&>(*this); }
    constexpr const Derived& self() const noexcept { return static_cast<const Derived&>(*this); }
};

} // namespace mir::gof

#pragma once
// Proxy — spartan form
// Non-owning real subject. Lazy or access-control proxy without heap.

namespace mir::gof::spartan {

template <typename Subject>
class Proxy : public Subject {
protected:
    Subject* real_ = nullptr;
public:
    explicit Proxy(Subject* s = nullptr) : real_(s) {}

    void set_real(Subject* s) noexcept { real_ = s; }
    Subject* real() noexcept { return real_; }
    const Subject* real() const noexcept { return real_; }
    bool has_real() const noexcept { return real_ != nullptr; }
};

} // namespace mir::gof::spartan

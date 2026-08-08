#pragma once
// Bridge — spartan form
// Non-owning implementor pointer. No unique_ptr, no exceptions.

namespace mir::gof::spartan {

template <typename Implementor>
class Bridge {
    Implementor* impl_ = nullptr;
public:
    explicit Bridge(Implementor* i = nullptr) : impl_(i) {}

    void set_implementor(Implementor* i) noexcept { impl_ = i; }
    Implementor* implementor() noexcept { return impl_; }
    const Implementor* implementor() const noexcept { return impl_; }

protected:
    Implementor& impl() { return *impl_; }
};

} // namespace mir::gof::spartan

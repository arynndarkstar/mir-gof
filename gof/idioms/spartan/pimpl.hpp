#pragma once
// Pimpl — spartan form
// Raw owning pointer; no unique_ptr, no exceptions.
// Caller must ensure proper destruction order.

namespace mir::gof::idiom::spartan {

template <typename T>
class Pimpl {
    T* impl_ = nullptr;
public:
    Pimpl() : impl_(new T) {}
    explicit Pimpl(T* p) : impl_(p) {}

    ~Pimpl() { delete impl_; }

    // move only
    Pimpl(Pimpl&& o) noexcept : impl_(o.impl_) { o.impl_ = nullptr; }
    Pimpl& operator=(Pimpl&& o) noexcept {
        if (this != &o) {
            delete impl_;
            impl_ = o.impl_;
            o.impl_ = nullptr;
        }
        return *this;
    }

    Pimpl(const Pimpl&) = delete;
    Pimpl& operator=(const Pimpl&) = delete;

    T*       operator->()       noexcept { return impl_; }
    const T* operator->() const noexcept { return impl_; }
    T&       operator*()        noexcept { return *impl_; }
    const T& operator*()  const noexcept { return *impl_; }

    T* get() noexcept { return impl_; }
};

} // namespace mir::gof::idiom::spartan

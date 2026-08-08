#pragma once
// Pimpl (Pointer to Implementation) — raw form
// Problem : header exposure of private members increases compile-time coupling
//           and binary size; changing private details forces client recompiles.
// Solution: hide implementation behind an opaque pointer; header only declares
//           the public interface.
// MIR use : stations, platform window / pixel-buffer classes, AI provider wrappers.

#include <memory>
#include <utility>

namespace mir::gof::idiom {

// CRTP-friendly Pimpl helper
template <typename T>
class Pimpl {
    std::unique_ptr<T> impl_;
public:
    Pimpl() : impl_(std::make_unique<T>()) {}
    explicit Pimpl(std::unique_ptr<T> p) : impl_(std::move(p)) {}

    T*       operator->()       noexcept { return impl_.get(); }
    const T* operator->() const noexcept { return impl_.get(); }
    T&       operator*()        noexcept { return *impl_; }
    const T& operator*()  const noexcept { return *impl_; }

    T*       get()       noexcept { return impl_.get(); }
    const T* get() const noexcept { return impl_.get(); }

    explicit operator bool() const noexcept { return static_cast<bool>(impl_); }
};

} // namespace mir::gof::idiom

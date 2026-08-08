#pragma once
// Bridge — raw form
// Problem : an abstraction and its implementation should be able to vary independently.
// Solution: put the implementation behind an interface; the abstraction holds a
//           reference to it (composition over inheritance).
// MIR use : window abstraction vs platform implementation (X11 / Win32 / Wayland),
//           pixel-buffer abstraction vs software / GPU backends.

#include <memory>
#include <utility>

namespace mir::gof {

template <typename Implementor>
class Bridge {
    std::unique_ptr<Implementor> impl_;
public:
    explicit Bridge(std::unique_ptr<Implementor> i) : impl_(std::move(i)) {}

    void set_implementor(std::unique_ptr<Implementor> i) {
        impl_ = std::move(i);
    }

    Implementor* implementor() noexcept { return impl_.get(); }
    const Implementor* implementor() const noexcept { return impl_.get(); }

protected:
    Implementor& impl() { return *impl_; }
};

} // namespace mir::gof

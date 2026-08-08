#pragma once
// Decorator — raw form
// Problem : responsibilities should be added to objects dynamically without subclassing.
// Solution: wrap the component with a decorator that implements the same interface
//           and forwards calls, adding behaviour before / after.
// MIR use : layered pixel-buffer effects, logging / metrics wrappers around stations,
//           input filters, AI response post-processors.

#include <memory>
#include <utility>

namespace mir::gof {

template <typename Component>
class Decorator : public Component {
protected:
    std::unique_ptr<Component> wrappee_;
public:
    explicit Decorator(std::unique_ptr<Component> c) : wrappee_(std::move(c)) {}

    Component* wrappee() noexcept { return wrappee_.get(); }
    const Component* wrappee() const noexcept { return wrappee_.get(); }
};

} // namespace mir::gof

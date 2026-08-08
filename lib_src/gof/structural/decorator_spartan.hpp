#pragma once
// Decorator — spartan form
// Non-owning wrappee. Caller owns the chain of lifetime.

namespace mir::gof::spartan {

template <typename Component>
class Decorator : public Component {
protected:
    Component* wrappee_ = nullptr;
public:
    explicit Decorator(Component* c = nullptr) : wrappee_(c) {}

    Component* wrappee() noexcept { return wrappee_; }
    const Component* wrappee() const noexcept { return wrappee_; }
};

} // namespace mir::gof::spartan

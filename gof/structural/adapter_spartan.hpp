#pragma once
// Adapter — spartan form
// Object adapter only. Non-owning pointer to adaptee.

namespace mir::gof::spartan {

template <typename... Args>
class Target {
public:
    virtual ~Target() = default;
    virtual void request(Args... args) = 0;
};

template <typename Adaptee, typename... Args>
class ObjectAdapter : public Target<Args...> {
    Adaptee* adaptee_ = nullptr;   // non-owning
public:
    explicit ObjectAdapter(Adaptee* a) : adaptee_(a) {}

    void request(Args... args) override {
        if (adaptee_) adaptee_->specific_request(args...);
    }

    Adaptee* adaptee() noexcept { return adaptee_; }
};

} // namespace mir::gof::spartan

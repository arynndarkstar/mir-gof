#pragma once
// Adapter — raw form
// Problem : an existing class has an interface that does not match what the client needs.
// Solution: wrap the adaptee with a class that translates calls into the target interface.
// MIR use : pixel-buffer backends (software / OpenGL / Vulkan / platform window buffers),
//           different window systems, audio output devices, input device APIs.

#include <memory>
#include <utility>

namespace mir::gof {

// Target interface the client expects
template <typename... Args>
class Target {
public:
    virtual ~Target() = default;
    virtual void request(Args... args) = 0;
};

// Class Adapter (inheritance) — when multiple inheritance is acceptable
template <typename Adaptee, typename... Args>
class ClassAdapter : public Target<Args...>, private Adaptee {
public:
    void request(Args... args) override {
        // translate and forward — specialise in derived or override
        this->specific_request(std::forward<Args>(args)...);
    }
};

// Object Adapter (composition) — preferred in modern C++
template <typename Adaptee, typename... Args>
class ObjectAdapter : public Target<Args...> {
    std::unique_ptr<Adaptee> adaptee_;
public:
    explicit ObjectAdapter(std::unique_ptr<Adaptee> a) : adaptee_(std::move(a)) {}

    void request(Args... args) override {
        if (adaptee_) adaptee_->specific_request(std::forward<Args>(args)...);
    }

    Adaptee* adaptee() noexcept { return adaptee_.get(); }
};

} // namespace mir::gof

#pragma once
// Proxy — raw form
// Problem : control access to an object (lazy init, access control, remote, logging…).
// Solution: a surrogate that implements the same interface and delegates to the real subject.
// MIR use : lazy-loaded plugins, remote AI providers, read-only views of StateEngine,
//           logging proxies around stations.

#include <memory>
#include <utility>

namespace mir::gof {

template <typename Subject>
class Proxy : public Subject {
protected:
    std::unique_ptr<Subject> real_;
public:
    explicit Proxy(std::unique_ptr<Subject> s = nullptr) : real_(std::move(s)) {}

    void set_real(std::unique_ptr<Subject> s) { real_ = std::move(s); }
    Subject* real() noexcept { return real_.get(); }
    const Subject* real() const noexcept { return real_.get(); }

    [[nodiscard]] bool has_real() const noexcept { return static_cast<bool>(real_); }
};

} // namespace mir::gof

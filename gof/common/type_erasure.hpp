#pragma once
// Type Erasure helpers — raw form
// Small, reusable type-erasure shells used by advanced patterns and by MIR
// when a closed set of implementations is not known at compile time.
//
// Provides a minimal “any callable / any strategy” style without pulling
// in std::function (which can be heavy and exception-prone).

#include <memory>
#include <utility>
#include <type_traits>

namespace mir::gof {

// ---------- Type-erased nullary / unary callable ----------
template <typename Sig>
class AnyCallable;   // primary undefined

template <typename R, typename... Args>
class AnyCallable<R(Args...)> {
    struct Concept {
        virtual ~Concept() = default;
        virtual R invoke(Args...) = 0;
        virtual std::unique_ptr<Concept> clone() const = 0;
    };

    template <typename F>
    struct Model : Concept {
        F f;
        explicit Model(F&& fn) : f(std::forward<F>(fn)) {}
        R invoke(Args... args) override { return f(std::forward<Args>(args)...); }
        std::unique_ptr<Concept> clone() const override {
            return std::make_unique<Model<F>>(f);
        }
    };

    std::unique_ptr<Concept> self_;

public:
    AnyCallable() = default;

    template <typename F,
              typename = std::enable_if_t<!std::is_same_v<std::decay_t<F>, AnyCallable>>>
    AnyCallable(F&& f) : self_(std::make_unique<Model<std::decay_t<F>>>(std::forward<F>(f))) {}

    AnyCallable(const AnyCallable& o) : self_(o.self_ ? o.self_->clone() : nullptr) {}
    AnyCallable& operator=(const AnyCallable& o) {
        if (this != &o) self_ = o.self_ ? o.self_->clone() : nullptr;
        return *this;
    }

    AnyCallable(AnyCallable&&) noexcept = default;
    AnyCallable& operator=(AnyCallable&&) noexcept = default;

    explicit operator bool() const noexcept { return static_cast<bool>(self_); }

    R operator()(Args... args) const {
        return self_->invoke(std::forward<Args>(args)...);
    }
};

// ---------- Small type-erased Strategy shell ----------
// Value-semantic Strategy that can hold any callable matching void(Context&)
template <typename Context>
class AnyStrategy {
    AnyCallable<void(Context&)> impl_;
public:
    AnyStrategy() = default;

    template <typename F>
    AnyStrategy(F&& f) : impl_(std::forward<F>(f)) {}

    void execute(Context& ctx) {
        if (impl_) impl_(ctx);
    }

    explicit operator bool() const noexcept { return static_cast<bool>(impl_); }
};

} // namespace mir::gof

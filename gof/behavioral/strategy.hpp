#pragma once
// Strategy — raw form (modern C++20+)
// MIR primary uses: AI providers, render backends, input maps, tick policies.
//
// Classic polymorphic Strategy + host.
// Prefer type-erased or CRTP variants from advanced/ when the set of
// strategies is closed or you need value semantics.

#include <memory>
#include <utility>

namespace mir::gof {

template <typename Context>
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void execute(Context& ctx) = 0;
};

template <typename Context>
class StrategyHost {
    std::unique_ptr<Strategy<Context>> strategy_;
public:
    void set_strategy(std::unique_ptr<Strategy<Context>> s) {
        strategy_ = std::move(s);
    }

    void run(Context& ctx) {
        if (strategy_) strategy_->execute(ctx);
    }

    [[nodiscard]] bool has_strategy() const noexcept {
        return static_cast<bool>(strategy_);
    }
};

} // namespace mir::gof

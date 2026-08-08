#pragma once
// Classic Strategy — raw form (modern C++)
// Used by MIR for AI providers, render backends, input maps, etc.

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
};

} // namespace mir::gof

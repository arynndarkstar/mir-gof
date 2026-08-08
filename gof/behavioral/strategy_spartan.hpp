#pragma once
// Strategy — spartan form
// No virtuals if you can avoid them; here we keep a pure interface
// but strip everything else. Suitable for freestanding / embedded cores.
// Caller owns the strategy lifetime (raw pointer / static storage).

namespace mir::gof::spartan {

template <typename Context>
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual void execute(Context& ctx) = 0;
};

template <typename Context>
class StrategyHost {
    Strategy<Context>* strategy_ = nullptr;   // non-owning
public:
    void set_strategy(Strategy<Context>* s) noexcept { strategy_ = s; }

    void run(Context& ctx) {
        if (strategy_) strategy_->execute(ctx);
    }

    bool has_strategy() const noexcept { return strategy_ != nullptr; }
};

} // namespace mir::gof::spartan

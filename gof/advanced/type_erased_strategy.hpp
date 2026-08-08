#pragma once
// Advanced: Type-Erased Strategy
// Value-semantic, no virtual base required at the call site.
// Combines the classic Strategy intent with type erasure so clients
// can store heterogeneous strategies in a vector or pass them by value.
//
// Prefer this over the classic polymorphic Strategy when:
//   - the set of strategies is open / plugin-loaded
//   - you want value semantics and move-only friendliness
//   - you are already in the “raw” modern track

#include "../common/type_erasure.hpp"
#include "../behavioral/strategy.hpp"   // for conceptual compatibility

namespace mir::gof::advanced {

template <typename Context>
using TypeErasedStrategy = AnyStrategy<Context>;

// Host that stores the type-erased strategy by value
template <typename Context>
class TypeErasedStrategyHost {
    TypeErasedStrategy<Context> strategy_;
public:
    void set_strategy(TypeErasedStrategy<Context> s) {
        strategy_ = std::move(s);
    }

    template <typename F>
    void set_strategy(F&& f) {
        strategy_ = TypeErasedStrategy<Context>(std::forward<F>(f));
    }

    void run(Context& ctx) {
        if (strategy_) strategy_.execute(ctx);
    }

    [[nodiscard]] bool has_strategy() const noexcept {
        return static_cast<bool>(strategy_);
    }
};

} // namespace mir::gof::advanced

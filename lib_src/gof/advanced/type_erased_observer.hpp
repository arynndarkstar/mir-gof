#pragma once
// Advanced: Type-Erased Observer
// Problem : classic Observer requires a common base; heterogeneous listeners
//           force either a fat interface or many observer types.
// Solution: type-erase the notification callable so any callable matching
//           void(const Event&) can be stored and notified.
// Origin  : GoF Observer + modern type-erasure (external polymorphism).
// MIR use : input events, state-delta bus, plugin lifecycle signals.

#include "../common/type_erasure.hpp"
#include <vector>
#include <utility>

namespace mir::gof::advanced {

template <typename Event>
class TypeErasedObserverBus {
    std::vector<AnyCallable<void(const Event&)>> listeners_;
public:
    template <typename F>
    void subscribe(F&& f) {
        listeners_.emplace_back(std::forward<F>(f));
    }

    void notify(const Event& e) {
        for (auto& l : listeners_)
            if (l) l(e);
    }

    [[nodiscard]] std::size_t size() const noexcept { return listeners_.size(); }
    void clear() { listeners_.clear(); }
};

} // namespace mir::gof::advanced

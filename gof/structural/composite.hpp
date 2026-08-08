#pragma once
// Composite — raw form
// Problem : clients need to treat individual objects and groups of objects uniformly.
// Solution: both leaves and composites implement the same component interface;
//           composites contain children.
// MIR use : scene graph / UI widget trees, nested command groups, hierarchical
//           state machines, plugin trees.

#include <memory>
#include <vector>
#include <utility>
#include <algorithm>

namespace mir::gof {

template <typename Component>
class Composite : public Component {
    std::vector<std::unique_ptr<Component>> children_;
public:
    void add(std::unique_ptr<Component> c) {
        if (c) children_.push_back(std::move(c));
    }

    void remove(Component* c) {
        children_.erase(
            std::remove_if(children_.begin(), children_.end(),
                [c](const std::unique_ptr<Component>& p) { return p.get() == c; }),
            children_.end());
    }

    // Forward operation to all children
    template <typename Op>
    void for_each(Op op) {
        for (auto& c : children_) if (c) op(*c);
    }

    [[nodiscard]] std::size_t size() const noexcept { return children_.size(); }
    Component* child(std::size_t i) noexcept {
        return i < children_.size() ? children_[i].get() : nullptr;
    }
};

} // namespace mir::gof

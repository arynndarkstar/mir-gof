#pragma once
// Composite — spartan form
// Fixed-capacity children array. No vector, no unique_ptr.

namespace mir::gof::spartan {

template <typename Component, std::size_t MaxChildren = 16>
class Composite : public Component {
    Component* children_[MaxChildren] = {};
    std::size_t size_ = 0;
public:
    bool add(Component* c) {
        if (!c || size_ >= MaxChildren) return false;
        children_[size_++] = c;
        return true;
    }

    void clear() { size_ = 0; }

    template <typename Op>
    void for_each(Op op) {
        for (std::size_t i = 0; i < size_; ++i)
            if (children_[i]) op(*children_[i]);
    }

    std::size_t size() const { return size_; }
    Component* child(std::size_t i) noexcept {
        return i < size_ ? children_[i] : nullptr;
    }
};

} // namespace mir::gof::spartan

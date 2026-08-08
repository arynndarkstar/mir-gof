#pragma once
// Memento — raw form
// Problem : capture and restore an object’s internal state without violating encapsulation.
// Solution: the originator creates a memento that stores a snapshot; a caretaker holds it.
// MIR use : Command undo, StateEngine snapshots, graphic view undo, configuration rollback.

#include <memory>
#include <vector>
#include <utility>

namespace mir::gof {

// Opaque snapshot — only the Originator knows how to interpret it
class Memento {
public:
    virtual ~Memento() = default;
};

template <typename StateData>
class ConcreteMemento : public Memento {
    StateData data_;
public:
    explicit ConcreteMemento(StateData d) : data_(std::move(d)) {}
    const StateData& state() const noexcept { return data_; }
};

// Originator interface
template <typename StateData>
class Originator {
public:
    virtual ~Originator() = default;
    virtual std::unique_ptr<Memento> create_memento() const = 0;
    virtual void restore(const Memento& m) = 0;
};

// Caretaker — holds history of mementos
class Caretaker {
    std::vector<std::unique_ptr<Memento>> history_;
public:
    void push(std::unique_ptr<Memento> m) {
        if (m) history_.push_back(std::move(m));
    }

    std::unique_ptr<Memento> pop() {
        if (history_.empty()) return nullptr;
        auto m = std::move(history_.back());
        history_.pop_back();
        return m;
    }

    [[nodiscard]] std::size_t size() const noexcept { return history_.size(); }
    void clear() { history_.clear(); }
};

} // namespace mir::gof

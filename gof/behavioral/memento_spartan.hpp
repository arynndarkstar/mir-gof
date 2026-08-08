#pragma once
// Memento — spartan form
// Fixed-capacity caretaker, no unique_ptr. Caller manages memento lifetime.

namespace mir::gof::spartan {

class Memento {
public:
    virtual ~Memento() = default;
};

template <typename StateData>
class ConcreteMemento : public Memento {
    StateData data_;
public:
    explicit ConcreteMemento(StateData d) : data_(d) {}
    const StateData& state() const { return data_; }
};

template <typename StateData>
class Originator {
public:
    virtual ~Originator() = default;
    virtual Memento* create_memento() const = 0;   // owning; caller deletes
    virtual void restore(const Memento& m) = 0;
};

template <std::size_t N = 32>
class Caretaker {
    Memento* history_[N] = {};
    std::size_t size_ = 0;
public:
    bool push(Memento* m) {
        if (!m || size_ >= N) return false;
        history_[size_++] = m;
        return true;
    }

    Memento* pop() {
        if (size_ == 0) return nullptr;
        Memento* m = history_[--size_];
        history_[size_] = nullptr;
        return m;
    }

    std::size_t size() const { return size_; }
    void clear() { size_ = 0; }
};

} // namespace mir::gof::spartan

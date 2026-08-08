#pragma once
// Command — spartan form
// No unique_ptr, no vector. Fixed-size history or caller-managed stack.
// Intended for constrained runtimes.

namespace mir::gof::spartan {

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() {}
};

// Simple invoker with fixed capacity history
template <std::size_t N = 32>
class Invoker {
    Command* history_[N] = {};
    std::size_t size_ = 0;
public:
    // non-owning; caller keeps the Command alive for the lifetime of the history entry
    bool execute(Command* cmd) {
        if (!cmd || size_ >= N) return false;
        cmd->execute();
        history_[size_++] = cmd;
        return true;
    }

    bool undo_last() {
        if (size_ == 0) return false;
        history_[--size_]->undo();
        history_[size_] = nullptr;
        return true;
    }

    std::size_t history_size() const { return size_; }
    void clear() { size_ = 0; }
};

} // namespace mir::gof::spartan

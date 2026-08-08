#pragma once
// Command — raw form
// MIR uses: operator decisions, menu actions, later undo via Memento.
//
// Classic Command + invoker. Supports both owning and non-owning storage.

#include <memory>
#include <vector>
#include <utility>

namespace mir::gof {

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    // optional undo hook — leave empty if not needed
    virtual void undo() {}
};

class Invoker {
    std::vector<std::unique_ptr<Command>> history_;
public:
    void execute(std::unique_ptr<Command> cmd) {
        if (!cmd) return;
        cmd->execute();
        history_.push_back(std::move(cmd));
    }

    void undo_last() {
        if (history_.empty()) return;
        history_.back()->undo();
        history_.pop_back();
    }

    [[nodiscard]] std::size_t history_size() const noexcept {
        return history_.size();
    }

    void clear_history() { history_.clear(); }
};

// Simple lambda-backed command (C++20)
template <typename ExecuteFn, typename UndoFn = void (*)()>
class LambdaCommand : public Command {
    ExecuteFn exec_;
    UndoFn    undo_;
public:
    LambdaCommand(ExecuteFn e, UndoFn u = []{})
        : exec_(std::move(e)), undo_(std::move(u)) {}

    void execute() override { exec_(); }
    void undo()    override { undo_(); }
};

} // namespace mir::gof

#pragma once
// Advanced: Command + Memento merger
// Problem : commands need reliable undo/redo that captures real state, not just inverse operations.
// Solution: each Command stores a Memento of the originator before mutation;
//           undo restores the memento.
// MIR use : operator actions that mutate StateEngine or graphic view state.

#include "../behavioral/command.hpp"
#include "../behavioral/memento.hpp"
#include <memory>
#include <utility>
#include <functional>

namespace mir::gof::advanced {

// A command that automatically snapshots the originator before execute()
template <typename OriginatorT>
class MementoCommand : public Command {
    OriginatorT& originator_;
    std::unique_ptr<Memento> before_;
    // the actual work
    std::function<void()> action_;
public:
    template <typename F>
    MementoCommand(OriginatorT& o, F&& action)
        : originator_(o), action_(std::forward<F>(action)) {}

    void execute() override {
        before_ = originator_.create_memento();
        action_();
    }

    void undo() override {
        if (before_) originator_.restore(*before_);
    }
};

// Convenience factory
template <typename OriginatorT, typename F>
std::unique_ptr<Command> make_memento_command(OriginatorT& o, F&& action) {
    return std::make_unique<MementoCommand<OriginatorT>>(o, std::forward<F>(action));
}

} // namespace mir::gof::advanced

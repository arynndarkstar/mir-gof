#pragma once
// Mediator — raw form
// Problem : many objects communicate directly, creating a dense web of dependencies.
// Solution: centralise communication in a mediator; colleagues talk only to it.
// MIR use : coordinating MainLoop / AiStation / StateEngine / graphic station,
//           input routing between multiple widgets, plugin event bus.

#include <memory>
#include <utility>

namespace mir::gof {

template <typename Event>
class Mediator;

template <typename Event>
class Colleague {
protected:
    Mediator<Event>* mediator_ = nullptr;
public:
    virtual ~Colleague() = default;
    void set_mediator(Mediator<Event>* m) noexcept { mediator_ = m; }
    virtual void receive(const Event& e) = 0;

protected:
    void send(const Event& e);
};

template <typename Event>
class Mediator {
public:
    virtual ~Mediator() = default;
    virtual void notify(Colleague<Event>* sender, const Event& e) = 0;
};

template <typename Event>
void Colleague<Event>::send(const Event& e) {
    if (mediator_) mediator_->notify(this, e);
}

} // namespace mir::gof

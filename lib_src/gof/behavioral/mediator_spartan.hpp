#pragma once
// Mediator — spartan form
// Non-owning mediator pointer on colleagues.

namespace mir::gof::spartan {

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

} // namespace mir::gof::spartan

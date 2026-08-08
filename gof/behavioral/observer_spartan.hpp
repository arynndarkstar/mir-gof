#pragma once
// Observer — spartan form
// Fixed-capacity or singly-linked list. No vector, no unique_ptr.
// Suitable for real-time / embedded loops.

namespace mir::gof::spartan {

template <typename Event>
class Observer {
public:
    virtual ~Observer() = default;
    virtual void on_notify(const Event& e) = 0;
    Observer* next = nullptr;   // intrusive link
};

template <typename Event>
class Subject {
    Observer<Event>* head_ = nullptr;
public:
    void attach(Observer<Event>* o) {
        if (!o) return;
        o->next = head_;
        head_ = o;
    }

    void detach(Observer<Event>* o) {
        if (!o) return;
        Observer<Event>** pp = &head_;
        while (*pp) {
            if (*pp == o) {
                *pp = o->next;
                o->next = nullptr;
                return;
            }
            pp = &((*pp)->next);
        }
    }

    void notify(const Event& e) {
        for (Observer<Event>* o = head_; o; o = o->next)
            o->on_notify(e);
    }
};

} // namespace mir::gof::spartan

#pragma once
// Observer — raw form (modern C++)
// MIR uses: input events, state-delta notifications, plugin lifecycle signals.
//
// Subject holds a list of observers; notification is synchronous.
// For high-frequency or async needs prefer a type-erased or lock-free variant
// from advanced/.

#include <vector>
#include <memory>
#include <algorithm>
#include <utility>

namespace mir::gof {

template <typename Event>
class Observer {
public:
    virtual ~Observer() = default;
    virtual void on_notify(const Event& e) = 0;
};

template <typename Event>
class Subject {
    std::vector<Observer<Event>*> observers_;   // non-owning by default
public:
    void attach(Observer<Event>* o) {
        if (o) observers_.push_back(o);
    }

    void detach(Observer<Event>* o) {
        observers_.erase(std::remove(observers_.begin(), observers_.end(), o),
                         observers_.end());
    }

    void notify(const Event& e) {
        // copy the list so observers can detach during notification
        auto snapshot = observers_;
        for (auto* o : snapshot) {
            if (o) o->on_notify(e);
        }
    }

    [[nodiscard]] std::size_t observer_count() const noexcept {
        return observers_.size();
    }
};

// Owning variant (useful when observers are short-lived)
template <typename Event>
class OwningSubject {
    std::vector<std::unique_ptr<Observer<Event>>> observers_;
public:
    void attach(std::unique_ptr<Observer<Event>> o) {
        if (o) observers_.push_back(std::move(o));
    }

    void notify(const Event& e) {
        for (auto& o : observers_) {
            if (o) o->on_notify(e);
        }
    }
};

} // namespace mir::gof

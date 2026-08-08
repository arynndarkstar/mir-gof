#pragma once
// Iterator — raw form
// Problem : traverse an aggregate without exposing its internal structure.
// Solution: provide an iterator interface that knows how to walk the collection.
// MIR use : walking plugin lists, event queues, scene-graph nodes, command history.

#include <cstddef>

namespace mir::gof {

template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool is_done() const = 0;
    virtual T& current() = 0;
};

// Simple random-access aggregate helper
template <typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual Iterator<T>* create_iterator() = 0;   // owning
    virtual std::size_t count() const = 0;
    virtual T& get(std::size_t i) = 0;
};

} // namespace mir::gof

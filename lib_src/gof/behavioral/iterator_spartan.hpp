#pragma once
// Iterator — spartan form
// Same conceptual interface; no ownership helpers.

namespace mir::gof::spartan {

template <typename T>
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool is_done() const = 0;
    virtual T& current() = 0;
};

template <typename T>
class Aggregate {
public:
    virtual ~Aggregate() = default;
    virtual Iterator<T>* create_iterator() = 0;
    virtual std::size_t count() const = 0;
    virtual T& get(std::size_t i) = 0;
};

} // namespace mir::gof::spartan

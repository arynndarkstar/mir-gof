#pragma once
// Prototype — raw form
// Problem : creating objects by class name / type is rigid; cloning an existing
//           configured instance is often cheaper and more flexible.
// Solution: define a clone() operation; clients request new objects by copying
//           a prototype.
// MIR use : cloning configured AI sessions, window / pixel-buffer descriptors,
//           plugin configuration snapshots.

#include <memory>
#include <utility>

namespace mir::gof {

template <typename T>
class Prototype {
public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<T> clone() const = 0;
};

// Simple concrete helper
template <typename T>
class Cloneable : public Prototype<T> {
public:
    std::unique_ptr<T> clone() const override {
        return std::make_unique<T>(static_cast<const T&>(*this));
    }
};

} // namespace mir::gof

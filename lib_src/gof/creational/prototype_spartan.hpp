#pragma once
// Prototype — spartan form
// clone() returns raw owning pointer; caller deletes.

namespace mir::gof::spartan {

template <typename T>
class Prototype {
public:
    virtual ~Prototype() = default;
    virtual T* clone() const = 0;   // owning; caller deletes
};

} // namespace mir::gof::spartan

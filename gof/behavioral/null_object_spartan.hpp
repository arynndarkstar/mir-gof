#pragma once
// Null Object — spartan form
// Pure marker + helper. Concrete null types are written per interface.

namespace mir::gof::spartan {

template <typename Interface>
class NullObject : public Interface {
    // Concrete null classes inherit and implement no-op methods.
};

template <typename Interface>
Interface* or_null(Interface* p, Interface* null_instance) {
    return p ? p : null_instance;
}

} // namespace mir::gof::spartan

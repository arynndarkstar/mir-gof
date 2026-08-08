#pragma once
// Null Object — raw form
// Problem : client code is littered with null checks for optional collaborators.
// Solution: provide a do-nothing implementation of the interface; clients always have a valid object.
// MIR use : missing plugins (no AI station loaded), optional render backends,
//           absent input devices, empty event handlers.

#include <memory>

namespace mir::gof {

// Generic Null Object base — specialise or inherit for concrete interfaces
template <typename Interface>
class NullObject : public Interface {
    // Default: all virtuals of Interface should be overridden to no-ops
    // in the concrete null type. This base exists mainly as a tag / marker.
};

// Helper: always returns a usable (possibly null) instance
template <typename Interface>
std::shared_ptr<Interface> or_null(std::shared_ptr<Interface> p,
                                   std::shared_ptr<Interface> null_instance) {
    return p ? p : null_instance;
}

template <typename Interface>
Interface* or_null(Interface* p, Interface* null_instance) {
    return p ? p : null_instance;
}

} // namespace mir::gof

#pragma once
// Visitor — raw form
// Problem : you need to add new operations to a stable set of classes without
//           modifying those classes.
// Solution: the visitor declares a visit() for each concrete element; elements
//           accept the visitor and call back the appropriate visit overload.
// MIR use : serialising / pretty-printing plugin trees, applying operations
//           across a scene graph, collecting metrics from heterogeneous stations.

namespace mir::gof {

template <typename ConcreteVisitor>
class Element {
public:
    virtual ~Element() = default;
    virtual void accept(ConcreteVisitor& v) = 0;
};

template <typename ElementA, typename ElementB>
class Visitor2 {
public:
    virtual ~Visitor2() = default;
    virtual void visit(ElementA& a) = 0;
    virtual void visit(ElementB& b) = 0;
};

} // namespace mir::gof

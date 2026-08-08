#pragma once
// Factory Method + Abstract Factory — spartan form
// No unique_ptr, no exceptions, no string. Caller supplies storage or
// receives a raw owning pointer that it is responsible for deleting.
// Designed for constrained / freestanding environments.

namespace mir::gof::spartan {

template <typename Product>
class FactoryMethod {
public:
    virtual ~FactoryMethod() = default;
    // returns owning pointer; caller must delete
    virtual Product* create() = 0;
};

template <typename Product, typename Concrete>
class ConcreteFactory : public FactoryMethod<Product> {
public:
    Product* create() override { return new Concrete(); }
};

// Three-product abstract factory (MIR station shape)
template <typename ProductA, typename ProductB, typename ProductC>
class AbstractFactory3 {
public:
    virtual ~AbstractFactory3() = default;
    virtual ProductA* create_a() = 0;
    virtual ProductB* create_b() = 0;
    virtual ProductC* create_c() = 0;
};

} // namespace mir::gof::spartan

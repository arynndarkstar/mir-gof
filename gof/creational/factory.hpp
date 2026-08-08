#pragma once
// Factory Method + Abstract Factory — raw form
// Tailored for MIR plugin stations and any “create by role / by type tag” needs.
//
// - FactoryMethod: single product family, virtual create()
// - AbstractFactory: family of related products (MainLoop / AiStation / StateEngine style)

#include <memory>
#include <string_view>
#include <utility>

namespace mir::gof {

// ---------- Factory Method ----------
template <typename Product>
class FactoryMethod {
public:
    virtual ~FactoryMethod() = default;
    virtual std::unique_ptr<Product> create() = 0;
};

// Simple concrete helper
template <typename Product, typename Concrete>
class ConcreteFactory : public FactoryMethod<Product> {
public:
    std::unique_ptr<Product> create() override {
        return std::make_unique<Concrete>();
    }
};

// ---------- Abstract Factory ----------
// Example product set that mirrors MIR stations.
// Replace or extend the product types as needed.

template <typename ProductA, typename ProductB, typename ProductC = void>
class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;
    virtual std::unique_ptr<ProductA> create_a() = 0;
    virtual std::unique_ptr<ProductB> create_b() = 0;
    // ProductC is optional; specialise or ignore when void
};

// Convenience for three-product families (MIR stations)
template <typename ProductA, typename ProductB, typename ProductC>
class AbstractFactory3 {
public:
    virtual ~AbstractFactory3() = default;
    virtual std::unique_ptr<ProductA> create_a() = 0;
    virtual std::unique_ptr<ProductB> create_b() = 0;
    virtual std::unique_ptr<ProductC> create_c() = 0;
};

// Named / keyed factory (string or type-tag driven)
template <typename Product>
class KeyedFactory {
public:
    virtual ~KeyedFactory() = default;
    virtual std::unique_ptr<Product> create(std::string_view key) = 0;
};

} // namespace mir::gof

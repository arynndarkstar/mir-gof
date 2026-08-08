#pragma once
// Builder — raw form
// Problem : constructing a complex object requires many steps / optional parts;
//           telescoping constructors become unreadable.
// Solution: separate the construction process from the final representation.
//           A Director can reuse the same construction steps for different builders.
// MIR use : bootstrap / settings construction, plugin configuration objects,
//           complex pixel-buffer / window descriptors, AI request payloads.

#include <memory>
#include <utility>

namespace mir::gof {

template <typename Product>
class Builder {
public:
    virtual ~Builder() = default;
    virtual void reset() = 0;
    virtual void build_part_a() {}
    virtual void build_part_b() {}
    virtual void build_part_c() {}
    virtual std::unique_ptr<Product> get_result() = 0;
};

template <typename Product>
class Director {
public:
    void construct(Builder<Product>& b) {
        b.reset();
        b.build_part_a();
        b.build_part_b();
        b.build_part_c();
    }

    // Variant construction sequences can be added as needed
    void construct_minimal(Builder<Product>& b) {
        b.reset();
        b.build_part_a();
    }
};

} // namespace mir::gof

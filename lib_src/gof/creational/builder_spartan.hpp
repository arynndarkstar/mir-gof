#pragma once
// Builder — spartan form
// No unique_ptr. Director drives a non-owning builder; product is returned raw.

namespace mir::gof::spartan {

template <typename Product>
class Builder {
public:
    virtual ~Builder() = default;
    virtual void reset() = 0;
    virtual void build_part_a() {}
    virtual void build_part_b() {}
    virtual void build_part_c() {}
    virtual Product* get_result() = 0;   // owning; caller deletes
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

    void construct_minimal(Builder<Product>& b) {
        b.reset();
        b.build_part_a();
    }
};

} // namespace mir::gof::spartan

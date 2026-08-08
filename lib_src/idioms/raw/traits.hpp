#pragma once
// Traits — raw form (minimal skeleton)
// Problem : algorithms need type-dependent properties without hard-coding types.
// Solution: a traits class template specialised per type.
// MIR use : pixel-format traits, station capability traits, allocator traits later.

namespace mir::gof::idiom {

template <typename T>
struct Traits {
    // using value_type = …;
    // static constexpr bool is_stateless = …;
};

} // namespace mir::gof::idiom

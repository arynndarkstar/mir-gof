#pragma once
// Copy-and-swap — raw form
// Problem : strong exception guarantee for assignment is hard to get right by hand.
// Solution: implement operator= in terms of a non-throwing swap + copy-construction
//           of the right-hand side (pass by value).
// MIR use : any value-semantic type that manages resources (buffers, configs).

#include <utility>

namespace mir::gof::idiom {

// Usage sketch:
// class T {
// public:
//     T& operator=(T other) noexcept {
//         using std::swap;
//         swap(*this, other);
//         return *this;
//     }
//     friend void swap(T& a, T& b) noexcept { /* member-wise swap */ }
// };

struct CopyAndSwapTag {};

} // namespace mir::gof::idiom

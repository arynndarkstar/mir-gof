#pragma once
// Non-copyable / Move-only — spartan form

namespace mir::gof::idiom::spartan {

struct NonCopyable {
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
protected:
    ~NonCopyable() = default;
};

struct MoveOnly {
    MoveOnly() = default;
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;
    MoveOnly(MoveOnly&&) = default;
    MoveOnly& operator=(MoveOnly&&) = default;
protected:
    ~MoveOnly() = default;
};

} // namespace mir::gof::idiom::spartan

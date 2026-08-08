#pragma once
// Non-copyable / Move-only helpers — raw form
// Problem : some types must not be copied (unique ownership, OS handles, …).
// Solution: explicitly delete copy operations; optionally default move.
// MIR use : stations that own plugins, pixel-buffer owners, dynlib handles.

namespace mir::gof::idiom {

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
    MoveOnly(MoveOnly&&) noexcept = default;
    MoveOnly& operator=(MoveOnly&&) noexcept = default;
protected:
    ~MoveOnly() = default;
};

} // namespace mir::gof::idiom

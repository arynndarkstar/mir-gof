#pragma once
// Object Pool — spartan form
// Fixed-capacity free list. No vector, no std::function factory.

namespace mir::gof::spartan {

template <typename T, std::size_t N = 32>
class ObjectPool {
    T* free_[N] = {};
    std::size_t count_ = 0;
public:
    bool release(T* p) {
        if (!p || count_ >= N) return false;
        free_[count_++] = p;
        return true;
    }

    T* acquire() {
        if (count_ == 0) return nullptr;
        return free_[--count_];
    }

    std::size_t available() const { return count_; }
    void clear() { count_ = 0; }
};

} // namespace mir::gof::spartan

#pragma once
// Object Pool — raw form
// Problem : repeatedly creating and destroying expensive objects is costly.
// Solution: keep a pool of reusable instances; clients acquire / release.
// MIR use : pixel buffers, AI session handles, network connections, sound voices.

#include <vector>
#include <memory>
#include <utility>
#include <functional>

namespace mir::gof {

template <typename T>
class ObjectPool {
    std::vector<std::unique_ptr<T>> free_;
    std::function<std::unique_ptr<T>()> factory_;
public:
    explicit ObjectPool(std::function<std::unique_ptr<T>()> factory)
        : factory_(std::move(factory)) {}

    // Acquire an object (creates one if pool empty)
    std::unique_ptr<T> acquire() {
        if (!free_.empty()) {
            auto p = std::move(free_.back());
            free_.pop_back();
            return p;
        }
        return factory_ ? factory_() : nullptr;
    }

    // Return an object to the pool
    void release(std::unique_ptr<T> p) {
        if (p) free_.push_back(std::move(p));
    }

    [[nodiscard]] std::size_t available() const noexcept { return free_.size(); }

    void clear() { free_.clear(); }
};

} // namespace mir::gof

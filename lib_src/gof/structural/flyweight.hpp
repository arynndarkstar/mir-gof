#pragma once
// Flyweight — raw form
// Problem : large numbers of fine-grained objects share intrinsic state;
//           storing that state in every instance wastes memory.
// Solution: factor shared (intrinsic) state into a flyweight; extrinsic state
//           is supplied by the client on each operation.
// MIR use : glyph / character caches, particle systems, tile maps,
//           shared AI prompt templates, repeated pixel-buffer formats.

#include <memory>
#include <unordered_map>
#include <string>
#include <utility>

namespace mir::gof {

template <typename Intrinsic, typename Extrinsic>
class Flyweight {
public:
    virtual ~Flyweight() = default;
    virtual void operation(const Extrinsic& extrinsic) = 0;
    virtual const Intrinsic& intrinsic() const = 0;
};

template <typename Intrinsic, typename Extrinsic, typename Key = std::string>
class FlyweightFactory {
    std::unordered_map<Key, std::unique_ptr<Flyweight<Intrinsic, Extrinsic>>> pool_;
public:
    template <typename Creator>
    Flyweight<Intrinsic, Extrinsic>* get(const Key& key, Creator creator) {
        auto it = pool_.find(key);
        if (it != pool_.end()) return it->second.get();
        auto fw = creator();
        auto* raw = fw.get();
        pool_[key] = std::move(fw);
        return raw;
    }

    [[nodiscard]] std::size_t size() const noexcept { return pool_.size(); }
    void clear() { pool_.clear(); }
};

} // namespace mir::gof

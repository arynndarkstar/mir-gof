#pragma once
// Facade — spartan form
// Non-owning references / pointers to subsystems.

namespace mir::gof::spartan {

template <typename SubsystemA, typename SubsystemB>
class Facade {
    SubsystemA* a_ = nullptr;
    SubsystemB* b_ = nullptr;
public:
    Facade(SubsystemA* a, SubsystemB* b) : a_(a), b_(b) {}

    void operation() {
        if (a_) a_->do_work();
        if (b_) b_->do_work();
    }

    SubsystemA* a() noexcept { return a_; }
    SubsystemB* b() noexcept { return b_; }
};

} // namespace mir::gof::spartan

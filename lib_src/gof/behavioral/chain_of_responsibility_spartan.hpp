#pragma once
// Chain of Responsibility — spartan form
// Intrusive next pointer. No unique_ptr.

namespace mir::gof::spartan {

template <typename Request>
class Handler {
    Handler* next_ = nullptr;
public:
    virtual ~Handler() = default;

    void set_next(Handler* n) noexcept { next_ = n; }
    Handler* next() noexcept { return next_; }

    virtual bool handle(Request& req) {
        if (next_) return next_->handle(req);
        return false;
    }
};

} // namespace mir::gof::spartan

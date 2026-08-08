#pragma once
// Chain of Responsibility — raw form
// Problem : multiple objects may handle a request; the sender should not know which.
// Solution: pass the request along a chain of handlers until one processes it.
// MIR use : input event routing, plugin command dispatch, error / log handling chains.

#include <memory>
#include <utility>

namespace mir::gof {

template <typename Request>
class Handler {
    std::unique_ptr<Handler> next_;
public:
    virtual ~Handler() = default;

    void set_next(std::unique_ptr<Handler> n) { next_ = std::move(n); }
    Handler* next() noexcept { return next_.get(); }

    // returns true if handled
    virtual bool handle(Request& req) {
        if (next_) return next_->handle(req);
        return false;
    }
};

} // namespace mir::gof

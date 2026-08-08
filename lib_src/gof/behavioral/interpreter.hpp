#pragma once
// Interpreter — raw form
// Problem : a simple language / grammar needs to be evaluated.
// Solution: represent grammar rules as classes in a composite hierarchy;
//           an interpret() operation evaluates a context.
// MIR use : simple command-line expression evaluation, config DSL,
//           lightweight query language over StateEngine snapshots.

#include <memory>
#include <string>
#include <utility>

namespace mir::gof {

template <typename Context>
class AbstractExpression {
public:
    virtual ~AbstractExpression() = default;
    virtual void interpret(Context& ctx) = 0;
};

template <typename Context>
class TerminalExpression : public AbstractExpression<Context> {
};

template <typename Context>
class NonTerminalExpression : public AbstractExpression<Context> {
protected:
    std::unique_ptr<AbstractExpression<Context>> left_;
    std::unique_ptr<AbstractExpression<Context>> right_;
public:
    NonTerminalExpression(std::unique_ptr<AbstractExpression<Context>> l,
                          std::unique_ptr<AbstractExpression<Context>> r)
        : left_(std::move(l)), right_(std::move(r)) {}
};

} // namespace mir::gof

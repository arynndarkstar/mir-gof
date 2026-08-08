#pragma once
// Template Method — raw form
// Problem : an algorithm’s structure is fixed but some steps vary.
// Solution: define the skeleton in a base class; subclasses override the
//           primitive / hook steps.
// MIR use : MainLoop tick skeleton, plugin load sequence, AI request pipeline,
//           bootstrap / shutdown sequences.

namespace mir::gof {

class TemplateMethod {
public:
    virtual ~TemplateMethod() = default;

    // the invariant algorithm skeleton
    void run() {
        before();
        step1();
        step2();
        step3();
        after();
    }

protected:
    virtual void before() {}
    virtual void step1() = 0;
    virtual void step2() = 0;
    virtual void step3() {}
    virtual void after() {}
};

} // namespace mir::gof

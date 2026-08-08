#pragma once
// Template Method — spartan form
// Identical shape to raw; no heap, no std. Suitable as-is for freestanding.

namespace mir::gof::spartan {

class TemplateMethod {
public:
    virtual ~TemplateMethod() = default;

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

} // namespace mir::gof::spartan

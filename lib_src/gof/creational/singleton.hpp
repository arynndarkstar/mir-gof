#pragma once
// Singleton — raw form (use sparingly)
// Problem : exactly one instance of a class is required, with global access.
// Solution: private constructor + static instance accessor.
// MIR note : MIR prefers discovery / settings over classic Singleton.
//            Provided for completeness and for non-MIR utility objects
//            (loggers, metrics sinks) where a single instance is truly desired.
//            Prefer Meyers' Singleton (function-local static) for thread-safe
//            lazy init in modern C++.

namespace mir::gof {

template <typename T>
class Singleton {
public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static T& instance() {
        static T inst;          // Meyers' Singleton — thread-safe since C++11
        return inst;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;
};

} // namespace mir::gof

// posix dynamic loader (linux / macos)
#include "dynlib.hpp"
#include <dlfcn.h>
#include <iostream>

namespace mir {

LibHandle load_lib(const std::string& path) {
    void* h = dlopen(path.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (!h) {
        std::cerr << "[dynlib] dlopen failed: " << dlerror() << "\n";
    }
    return h;
}

void* get_sym(LibHandle h, const std::string& name) {
    if (!h) return nullptr;
    void* s = dlsym(h, name.c_str());
    if (!s) {
        std::cerr << "[dynlib] dlsym failed: " << dlerror() << "\n";
    }
    return s;
}

void unload_lib(LibHandle h) {
    if (h) dlclose(h);
}

} // namespace mir

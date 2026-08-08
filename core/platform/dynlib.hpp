#pragma once
// platform abstraction for dynamic loading
// implementation lives in .cpp per OS (win32 / posix)

#include <string>
#include "../types.hpp"

namespace mir {

LibHandle load_lib(const std::string& path);
void*     get_sym(LibHandle, const std::string& name);
void      unload_lib(LibHandle);

} // namespace mir

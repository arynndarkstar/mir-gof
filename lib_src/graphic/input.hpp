#pragma once
// Shared input snapshot for MainLoop plugins.
// Later can feed Observer bus / Command queue.

namespace mir {
namespace graphic {

struct KeyMods {
    bool shift = false;
    bool ctrl  = false;
    bool alt   = false;
};

struct InputSnapshot {
    int  mouse_x = 0;
    int  mouse_y = 0;
    bool mouse_l = false;
    bool mouse_r = false;
    bool mouse_m = false;
    int  wheel   = 0;
    int  key_code = 0;
    bool key_down = false;
    KeyMods mods;
    bool quit_requested = false;
};

} // namespace graphic
} // namespace mir

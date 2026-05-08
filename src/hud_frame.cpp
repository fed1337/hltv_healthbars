#include "stdafx.h"

void hook_hud_frame(const double time) {
    Tick(); // update the round timer
    CLIENT.HUD_Frame(time);
}

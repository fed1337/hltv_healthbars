#include "stdafx.h"

SCREENINFO g_ScreenInfo;

void LoadTimerIcon() {
    char path[MAX_PATH];
    _snprintf(path, sizeof(path), "%stimer.png", g_szPluginPath);
    path[MAX_PATH - 1] = '\0';

    if (CHelpers::bFileExists(path)) {
        // Use your existing LOAD_TEXTURE macro
        LOAD_TEXTURE(g_HUD_Vars.timer_icon, path);

        if (g_HUD_Vars.timer_icon.texID == 0) {
            CONPRINTF("Failed to load timer texture at %s", path);
        }
    } else {
        CONPRINTF("Timer icon not found at %s", path);
    }
}

auto Hook_HUD_VidInit() -> int {
    // update screen width&height
    g_ScreenInfo.iSize = sizeof(g_ScreenInfo);
    ENGINE.pfnGetScreenInfo(&g_ScreenInfo);

    // reload fonts on next redraw
    g_bReinitializeFonts = true;
    LoadTimerIcon();
    const int ret = CLIENT.HUD_VidInit();
    InitializeSprites();
    return ret;
}

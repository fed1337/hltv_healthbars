#include "stdafx.h"

SCREENINFO g_ScreenInfo;

auto Hook_HUD_VidInit() -> int {
    // update screen width&height
    g_ScreenInfo.iSize = sizeof(g_ScreenInfo);
    ENGINE.pfnGetScreenInfo(&g_ScreenInfo);

    // reload fonts on next redraw
    g_bReinitializeFonts = true;

    return CLIENT.HUD_VidInit();
}

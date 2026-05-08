#include "stdafx.h"

void ReinitializeFonts();

auto Hook_HUD_Redraw(float flArg, int iArg) -> int;

extern CHealthBars *hud;
extern CTopBar *topbar;
extern bool g_bReinitializeFonts;

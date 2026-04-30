#include "stdafx.h"

void ReinitializeFonts();

int Hook_HUD_Redraw(float flArg, int iArg);

extern CHealthBars* hud;
extern CTopBar* topbar;
extern bool g_bReinitializeFonts;
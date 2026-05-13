#include "stdafx.h"

CTopBar *topbar = new CTopBar();
CHealthBars *healthbars = new CHealthBars();
CScoreboard *scoreboard = new CScoreboard();

void ReinitializeFonts() {
    g_fontGeneral.InitText();
    g_fontHealthBar.InitText();
    g_fontRoundTimer.InitText();
    g_fontTeamScore.InitText();
    g_fontTeamNames.InitText();
    g_fontClanScore.InitText();
    g_bReinitializeFonts = false;

    CONPRINTF("Fonts initialized \r\n");
}

bool g_bReinitializeFonts = true;
auto Hook_HUD_Redraw(float flArg, int iArg) -> int {
    if (g_bReinitializeFonts) {
        ReinitializeFonts();
    }

    if (CConVars::getConVarFloat("draw_topbar") == 1.F) {
        CTopBar::Draw();
    }

    if (CConVars::getConVarFloat("draw_healthbars") == 1.F) {
        CHealthBars::Draw();
    }

    return CLIENT.HUD_Redraw(flArg, iArg);
}

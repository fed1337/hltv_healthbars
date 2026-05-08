#include "stdafx.h"

#pragma once

// globals related to what is shown on the hud
// updated from usermessages or commands
struct hud_globals_s {
    int iRoundTime;
    int iTeamScores[2];
    char *szClanNames[2];
    int iClanScores[2];
    bool bBombPlanted;

    hud_texture_s team1_flag;
    hud_texture_s team2_flag;
};

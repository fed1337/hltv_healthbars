#include "stdafx.h"

CTopBar::CTopBar() = default;

void CTopBar::Draw() {
    drawBackground();
    drawRoundTimer(g_HUD_Vars.iRoundTime);
    drawTeam1(g_HUD_Vars.szClanNames[0]);
    drawTeam2(g_HUD_Vars.szClanNames[1]);
    drawTeam1Score(g_HUD_Vars.iTeamScores[0], CConVars::getConVarFloat("team_1_score"));
    drawTeam2Score(g_HUD_Vars.iTeamScores[1], CConVars::getConVarFloat("team_2_score"));
    drawTeam1Flag(g_HUD_Vars.team1_flag);
    drawTeam2Flag(g_HUD_Vars.team2_flag);
}

void CTopBar::drawRoundTimer(int time) {
    if (CConVars::getConVarFloat("enable_roundtimer") != 1) return;

    char szRoundTime[32];
    sprintf(szRoundTime, "%d:%02d", time / 60, time % 60);

    int centerX = g_Positions.roundTimer_pos.x;
    int centerY = g_Positions.roundTimer_pos.y - 18;
    int gap = 54;

    int iconX = centerX - gap;

    if (g_HUD_Vars.bBombPlanted) {
        CHelpers::drawSprite(iconX, g_Positions.roundTimer_pos.y - 6, (char *) "c4", false, nullptr, 168, 24, 4);
        g_fontRoundTimer.Print(g_Positions.roundTimer_pos.x, g_Positions.roundTimer_pos.y, 168, 24, 4, 255,
                               FL_CENTER_X | FL_BACKDROP, 0, szRoundTime);
    } else {
        if (g_HUD_Vars.timer_icon.texID != 0) {
            DrawTexture(g_HUD_Vars.timer_icon, iconX, centerY, 255, FL_NONE);
        }
        g_fontRoundTimer.Print(g_Positions.roundTimer_pos.x, g_Positions.roundTimer_pos.y, 255, 255, 255, 255,
                               FL_CENTER_X | FL_BACKDROP, 0, szRoundTime);
    }
}

void CTopBar::drawTeam1(char *szTeam) {
    if (szTeam != nullptr) {
        g_fontTeamNames.Print(g_Positions.team_1_name_pos.x, g_Positions.team_1_name_pos.y, 255, 255, 255, 255,
                              FL_CENTER_X | FL_BACKDROP, 0, szTeam);
    }
}
void CTopBar::drawTeam2(char *szTeam) {
    if (szTeam != nullptr) {
        g_fontTeamNames.Print(g_Positions.team_2_name_pos.x, g_Positions.team_2_name_pos.y, 255, 255, 255, 255,
                              FL_CENTER_X | FL_BACKDROP, 0, szTeam);
    }
}

void CTopBar::drawTeam1Score(int teamScore, int clanScore) {
    char szTeamScore[16];
    char szClanScore[16];
    sprintf(szClanScore, "%d", clanScore);
    sprintf(szTeamScore, "%d", teamScore);

    g_fontClanScore.Print(g_Positions.team_1_clanScore_pos.x, g_Positions.team_1_clanScore_pos.y, 255, 255, 255, 255,
                          FL_CENTER_X | FL_BACKDROP, 0, szClanScore);
    g_fontTeamScore.Print(g_Positions.team_1_teamScore_pos.x, g_Positions.team_1_teamScore_pos.y, 255, 255, 255, 255,
                          FL_CENTER_X | FL_BACKDROP, 0, szTeamScore);
}
void CTopBar::drawTeam2Score(int teamScore, int clanScore) {
    char szTeamScore[16];
    char szClanScore[16];
    sprintf(szClanScore, "%d", clanScore);
    sprintf(szTeamScore, "%d", teamScore);

    g_fontClanScore.Print(g_Positions.team_2_clanScore_pos.x, g_Positions.team_2_clanScore_pos.y, 255, 255, 255, 255,
                          FL_CENTER_X | FL_BACKDROP, 0, szClanScore);
    g_fontTeamScore.Print(g_Positions.team_2_teamScore_pos.x, g_Positions.team_2_teamScore_pos.y, 255, 255, 255, 255,
                          FL_CENTER_X | FL_BACKDROP, 0, szTeamScore);
}
void CTopBar::drawTeam1Flag(hud_texture_s flag) {
    if (flag.texID != 0) {
        DrawTexture(flag, g_Positions.flag_1_pos.x, g_Positions.flag_1_pos.y, 255.F, FL_NONE);
    }
}
void CTopBar::drawTeam2Flag(hud_texture_s flag) {
    if (flag.texID != 0) {
        DrawTexture(flag, g_Positions.flag_2_pos.x, g_Positions.flag_2_pos.y, 255.F, FL_NONE);
    }
}
void CTopBar::drawBackground() {
    fillrgba(g_Positions.topbar_pos.x, g_Positions.topbar_pos.y, (int) CConVars::getConVarFloat("topbar_width"),
             (int) CConVars::getConVarFloat("topbar_height"), 0, 0, 0, 128);
}

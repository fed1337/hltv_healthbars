#include "stdafx.h"

scoreboard_entry_s g_ScoreboardData[SCOREBOARD_MAX_INDEX + 1];

namespace {

    struct score_row_s {
        int slot;
        char name[64];
        int frags;
        int headshots;
        int deaths;
        int ping;
    };

    int compare_by_nickname(const void *a, const void *b) {
        const auto *ra = static_cast<const score_row_s *>(a);
        const auto *rb = static_cast<const score_row_s *>(b);
        return _stricmp(ra->name, rb->name);
    }

    void draw_team_block(int panelLeft, int topY, char *teamTitle, score_row_s *rows, int rowCount, int titleR,
                         int titleG, int titleB) {
        const int rowH = static_cast<int>(CConVars::getConVarFloat("general_font_size")) + 4;
        const int hdrR = 255;
        const int hdrG = 140;
        const int hdrB = 0;

        int y = topY;
        g_fontGeneral.Print(panelLeft, y, titleR, titleG, titleB, 255, FL_NONE, 0, teamTitle);
        y += rowH;

        g_fontGeneral.Print(panelLeft + 200, y, hdrR, hdrG, hdrB, 255, FL_RIGHT, 0, (char *) "Frags");
        g_fontGeneral.Print(panelLeft + 260, y, hdrR, hdrG, hdrB, 255, FL_RIGHT, 0, (char *) "HS");
        g_fontGeneral.Print(panelLeft + 320, y, hdrR, hdrG, hdrB, 255, FL_RIGHT, 0, (char *) "Death");
        g_fontGeneral.Print(panelLeft + 380, y, hdrR, hdrG, hdrB, 255, FL_RIGHT, 0, (char *) "Ping");
        y += rowH;

        for (int i = 0; i < rowCount; i++) {
            score_row_s *r = &rows[i];
            g_fontGeneral.Print(panelLeft, y, 220, 220, 220, 255, FL_NONE, 0, r->name);

            char buf[32];
            sprintf(buf, "%d", r->frags);
            g_fontGeneral.Print(panelLeft + 200, y, 255, 255, 255, 255, FL_RIGHT, 0, buf);

            sprintf(buf, "%d", r->headshots);
            g_fontGeneral.Print(panelLeft + 260, y, 255, 255, 255, 255, FL_RIGHT, 0, buf);

            sprintf(buf, "%d", r->deaths);
            g_fontGeneral.Print(panelLeft + 320, y, 255, 255, 255, 255, FL_RIGHT, 0, buf);

            sprintf(buf, "%d", r->ping);
            g_fontGeneral.Print(panelLeft + 380, y, 255, 255, 255, 255, FL_RIGHT, 0, buf);

            y += rowH;
        }
    }

} // namespace

CScoreboard::CScoreboard() : bIsVisible(false) {}

void CScoreboard::setVisible(bool value) { bIsVisible = value; }

void CScoreboard::Draw() {
    g_ScreenInfo.iSize = sizeof(g_ScreenInfo);
    ENGINE.pfnGetScreenInfo(&g_ScreenInfo);

    if (g_ScreenInfo.iWidth <= 0 || g_ScreenInfo.iHeight <= 0) {
        return;
    }

    score_row_s team1[SCOREBOARD_MAX_INDEX];
    score_row_s team2[SCOREBOARD_MAX_INDEX];
    int n1 = 0;
    int n2 = 0;

    for (int i = 1; i <= SCOREBOARD_MAX_INDEX; i++) {
        hud_player_info_t pi{};
        ENGINE.pfnGetPlayerInfo(i, &pi);
        if (pi.name == nullptr || pi.name[0] == 0) {
            continue;
        }
        if (pi.spectator != 0) {
            continue;
        }

        char *rawModel = CHelpers::szGetPlayerModel(i);
        int team = CHelpers::iGetTeam(rawModel);
        if (team == 0) {
            int tid = g_ScoreboardData[i].teamId;
            if (tid == 1) {
                team = 1;
            } else if (tid == 2 || tid == 3) {
                team = 2;
            }
        }
        if (team != 1 && team != 2) {
            continue;
        }

        char stripped[64];
        StripTags(stripped, pi.name);

        score_row_s row{};
        row.slot = i;
        strncpy(row.name, stripped, sizeof(row.name) - 1);
        row.name[sizeof(row.name) - 1] = 0;

        row.frags = g_ScoreboardData[i].frags;
        row.headshots = g_ScoreboardData[i].headshots;
        row.deaths = g_ScoreboardData[i].deaths;
        row.ping = static_cast<int>(pi.ping);

        if (team == 1) {
            team1[n1++] = row;
        } else {
            team2[n2++] = row;
        }
    }

    if (n1 == 0 && n2 == 0) {
        return;
    }

    if (n1 > 1) {
        qsort(team1, n1, sizeof(score_row_s), compare_by_nickname);
    }
    if (n2 > 1) {
        qsort(team2, n2, sizeof(score_row_s), compare_by_nickname);
    }

    const int rowH = static_cast<int>(CConVars::getConVarFloat("general_font_size")) + 4;
    const int headerRows = 2;
    const int maxRows = (n1 > n2) ? n1 : n2;
    const int blockH = ((headerRows + maxRows) * rowH) + 16;
    const int panelW = 400;
    const int gap = 24;
    const int totalW = (panelW * 2) + gap;

    const int cx = g_ScreenInfo.iWidth / 2;
    const int cy = g_ScreenInfo.iHeight / 2;

    const int leftT = cx - (totalW / 2);
    const int leftCT = leftT + panelW + gap;
    const int topY = cy - (blockH / 2);

    fillrgba(static_cast<GLfloat>(leftT - 16), static_cast<GLfloat>(topY - 12), totalW + 32, blockH + 24, 0, 0, 0, 200);

    char *nameT = CConVars::getConVarString("team_1_name");
    char *nameCT = CConVars::getConVarString("team_2_name");
    if (nameT == nullptr) {
        nameT = (char *) "Terrorists";
    }
    if (nameCT == nullptr) {
        nameCT = (char *) "Counter-Terrorists";
    }

    draw_team_block(leftT, topY, nameT, team1, n1, 255, 120, 40);
    draw_team_block(leftCT, topY, nameCT, team2, n2, 160, 200, 255);
}

#include "stdafx.h"

class CTopBar {
public:
    CTopBar();
    static void Draw();

private:
    int x;
    int y;
    int width;
    int height;
    static void drawRoundTimer(int time);
    static void drawTeam1(char *szTeam);
    static void drawTeam2(char *szTeam);
    static void drawTeam1Score(int teamScore, int clanScore);
    static void drawTeam2Score(int teamScore, int clanScore);
    static void drawTeam1Flag(hud_texture_s flag);
    static void drawTeam2Flag(hud_texture_s flag);
    static void drawBackground();
};

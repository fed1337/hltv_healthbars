#include "stdafx.h"

class CTopBar
{
public:
	CTopBar();
	void Draw();
private:
	int x;
	int y;
	int width;
	int height;
	void drawRoundTimer(int time);
	void drawTeam1(char* szTeam);
	void drawTeam2(char* szTeam);
	void drawTeam1Score(int teamScore, int clanScore);
	void drawTeam2Score(int teamScore, int clanScore);
	void drawTeam1Flag(hud_texture_s flag);
	void drawTeam2Flag(hud_texture_s flag);
	void drawSponsor(hud_texture_s flag);
	void drawBackground();
};
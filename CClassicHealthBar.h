#include "stdafx.h"

class CClassicHealthBar : CHealthBar
{
public:
	CClassicHealthBar(int x, int y, int width, int height, playerInfo_s info)
		: CHealthBar(x, y, width, height, info) { };
	void Draw();
private:
	void DrawHPBar();
	void DrawRightBar();
	void DrawHP();
	void DrawPlayerName();
	void DrawWeapon();
	void DrawSequence();
	void DrawBackground();
};
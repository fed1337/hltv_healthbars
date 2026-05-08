#include "stdafx.h"

class CCSPHealthBar final : CHealthBar {
public:
    CCSPHealthBar(int x, int y, int width, int height, playerInfo_s info) : CHealthBar(x, y, width, height, info) {}
    void Draw() override;

private:
    void DrawHPBar() override;
    void DrawRightBar();
    void DrawHP() override;
    void DrawPlayerName() override;
    void DrawWeapon() override;
    void DrawSequence() override;
    void DrawBackground() override;
};

#include "stdafx.h"

class CClassicHealthBar final : public CHealthBar {
public:
    CClassicHealthBar(int x, int y, int width, int height, playerInfo_s info) : CHealthBar(x, y, width, height, info) {}
    void Draw() override;

private:
    void DrawHPBar() override;
    void DrawHP() override;
    void DrawPlayerName() override;
    void DrawWeapon(BarColors color, bool isDoingAction) override;
    void DrawBackground() override;
    int healthWidth;
};

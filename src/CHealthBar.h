#include "stdafx.h"

// Move shared UI structs to the base class
struct BarColors {
    int r, g, b, a;
};

class CHealthBar {
public:
    CHealthBar(int x, int y, int width, int height, playerInfo_s info) :
        x(x), y(y), width(width), height(height), info(info), healthWidth(0) {}
    virtual ~CHealthBar() = default;
    virtual void Draw() = 0;

protected:
    int x, y, width, height;
    int healthWidth;
    playerInfo_s info;
    virtual void DrawHPBar() = 0;
    virtual void DrawHP() = 0;
    virtual void DrawPlayerName() = 0;
    virtual void DrawBackground() = 0;
    virtual void DrawWeapon(BarColors dye, bool isDoingAction) = 0;
};

#include "stdafx.h"

class CHealthBar {
public:
    CHealthBar(int x, int y, int width, int height, playerInfo_s info) {
        this->x = x;
        this->y = y;

        this->width = width;
        this->height = height;

        this->info = info;
    }

    virtual ~CHealthBar() = default;

    virtual void Draw() = 0;

protected:
    int x;
    int y;
    int width;
    int height;
    int healthWidth{0};
    playerInfo_s info;

private:
    virtual void DrawHPBar() = 0;
    virtual void DrawHP() = 0;
    virtual void DrawPlayerName() = 0;
    virtual void DrawWeapon() = 0;
    virtual void DrawSequence() = 0;
    virtual void DrawBackground() = 0;
};

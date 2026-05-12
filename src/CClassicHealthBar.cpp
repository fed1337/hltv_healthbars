#include "stdafx.h"

const BarColors COLOR_T = {168, 24, 4, 192};
const BarColors COLOR_CT = {4, 24, 168, 192};
const BarColors COLOR_BG = {0, 0, 0, 128};
const BarColors COLOR_ACTION = {255, 128, 0, 255};

const int HP_SECTION_WIDTH = 42;
const int ACCENT_WIDTH = 8;
const int SPRITE_GAP = 28;

void CClassicHealthBar::Draw() {
    DrawBackground();
    DrawHPBar();

    BarColors activeColor = {255, 255, 255, 255}; // Default White
    bool isDoingAction = false;

    if (info.sequence == SEQUENCE_RELOAD || info.sequence == SEQUENCE_ARM_C4) {
        activeColor = COLOR_ACTION;
        isDoingAction = true;
    };

    DrawWeapon(activeColor, isDoingAction);
    DrawHP();
    DrawPlayerName();
}

void CClassicHealthBar::DrawHPBar() {
    auto percentage = static_cast<float>(info.hp);
    if (info.hp > 100) {
        percentage = 100;
    }
    if (info.hp < 0) {
        percentage = 0;
    }
    percentage /= 100.F;

    // Bar width is total width minus the reserved HP section
    this->healthWidth = static_cast<int>(percentage * (this->width - static_cast<float>(HP_SECTION_WIDTH)));

    if (info.team == 1) { // T: Fills Left -> Right
        fillrgba(this->x + HP_SECTION_WIDTH, this->y, healthWidth, this->height, COLOR_T.r, COLOR_T.g, COLOR_T.b,
                 COLOR_T.a);
    } else { // CT: Fills Right -> Left
        fillrgba(this->x + (this->width - HP_SECTION_WIDTH - healthWidth), this->y, healthWidth, this->height,
                 COLOR_CT.r, COLOR_CT.g, COLOR_CT.b, COLOR_CT.a);
    }
}

void CClassicHealthBar::DrawHP() {
    int centerX = (info.team == 1) ? (this->x + (HP_SECTION_WIDTH / 2) + 4)
                                   : (this->x + this->width - (HP_SECTION_WIDTH / 2) - 4);

    if (info.hp > 0) {
        char szHealth[16];
        sprintf(szHealth, "%d", info.hp);
        float yOffset = static_cast<float>(this->y) + (static_cast<float>(this->height) / 2.0F) +
                        CConVars::getConVarFloat("healthbar_font_yoffset");
        g_fontHealthBar.Print(centerX, static_cast<int>(yOffset), 255, 255, 255, 255,
                              FL_CENTER_X | FL_CENTER_Y | FL_BACKDROP, 0, szHealth);
    } else {
        int centerY = this->y + (this->height / 2);
        CHelpers::drawSprite(centerX, centerY, (char *) "smallskull", false, nullptr, 255, 255, 255);
    }
}

void CClassicHealthBar::DrawPlayerName() {
    char buffer[64];
    StripTags(buffer, info.szName);
    float yOffset = this->y + (this->height / 2) + CConVars::getConVarFloat("healthbar_font_yoffset");

    if (info.team == 1) {
        g_fontHealthBar.Print(this->x + HP_SECTION_WIDTH + ACCENT_WIDTH, (int) yOffset, 255, 255, 255, 255,
                              FL_CENTER_Y | FL_BACKDROP, 124, buffer);
    } else {
        g_fontHealthBar.Print(this->x + this->width - HP_SECTION_WIDTH - ACCENT_WIDTH, (int) yOffset, 255, 255, 255,
                              255, FL_RIGHT | FL_CENTER_Y | FL_BACKDROP, 124, buffer);
    }
}

void CClassicHealthBar::DrawWeapon(BarColors color, bool isDoingAction) {
    if (info.hp <= 0) {
        return;
    }

    bool isHoldingC4 = (strcmp(info.szWeapon, "c4") == 0);
    color = {255, 255, 255, 255};

    if (info.sequence == SEQUENCE_RELOAD || info.sequence == SEQUENCE_ARM_C4) {
        color = COLOR_ACTION;
    }
    if (info.team == 1) { // T: Left side
        CHelpers::drawSprite(this->x + this->width + SPRITE_GAP, this->y + (this->height / 2), info.szWeapon, false,
                             nullptr, color.r, color.g, color.b);
        if (info.kitbomb && !isHoldingC4) {
            CHelpers::drawSprite(this->x + this->width + SPRITE_GAP + 42, this->y + (this->height / 2), (char *) "c4",
                                 false, nullptr, 255, 255, 255);
        }
    } else { // CT: Right side
        CHelpers::drawSprite(this->x - SPRITE_GAP, this->y + (this->height / 2), info.szWeapon, true, nullptr, color.r,
                             color.g, color.b);
        if (info.kitbomb) {
            CHelpers::drawSprite(this->x - SPRITE_GAP - 42, this->y + (this->height / 2), (char *) "defuser", true,
                                 nullptr, 255, 255, 255);
        }
    }
}

void CClassicHealthBar::DrawBackground() {
    if (info.team == 1) {
        // Vertical Accent Bar
        fillrgba(this->x, this->y, ACCENT_WIDTH, this->height, COLOR_T.r, COLOR_T.g, COLOR_T.b, 255);
        // HP BG (The black box behind numbers)
        fillrgba(this->x + ACCENT_WIDTH, this->y, HP_SECTION_WIDTH - ACCENT_WIDTH, this->height, 0, 0, 0, 192);
        // Main Bar BG
        fillrgba(this->x + HP_SECTION_WIDTH, this->y, this->width - HP_SECTION_WIDTH, this->height, COLOR_BG.r,
                 COLOR_BG.g, COLOR_BG.b, COLOR_BG.a);
        // Border
        // drawBox(this->x, this->y, this->width, this->height, 1, COLOR_T.r, COLOR_T.g, COLOR_T.b, 255);
    } else {
        // Vertical Accent Bar
        fillrgba(this->x + this->width - ACCENT_WIDTH, this->y, ACCENT_WIDTH, this->height, COLOR_CT.r, COLOR_CT.g,
                 COLOR_CT.b, 255);
        // HP BG
        fillrgba(this->x + this->width - HP_SECTION_WIDTH, this->y, HP_SECTION_WIDTH - ACCENT_WIDTH, this->height, 0, 0,
                 0, 192);
        // Main Bar BG
        fillrgba(this->x, this->y, this->width - HP_SECTION_WIDTH, this->height, COLOR_BG.r, COLOR_BG.g, COLOR_BG.b,
                 COLOR_BG.a);
        // Border
        // drawBox(this->x, this->y, this->width, this->height, 1, COLOR_CT.r, COLOR_CT.g, COLOR_CT.b, 255);
    }
}

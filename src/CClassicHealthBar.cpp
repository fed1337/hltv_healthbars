#include "stdafx.h"

void CClassicHealthBar::Draw() {
    DrawHPBar();
    DrawBackground();
    DrawHP();
    DrawPlayerName();
    DrawWeapon();
}

void CClassicHealthBar::DrawHPBar() {
    // % filled, adjust 0-100
    auto percentage = static_cast<float>(info.hp);
    if (info.hp > 100) {
        percentage = 100;
    }
    if (info.hp < 0) {
        percentage = 0;
    }
    percentage /= 100.F;

    this->healthWidth = static_cast<int>(percentage * (this->width - 32)); // ***

    if (info.team == 2) // CT, i.e. right
    {
        if (info.sequence == SEQUENCE_RELOAD) {
            fillrgba(this->x + this->width - 32, this->y, 32, this->height, 204, 204, 204, 128);
        } else {
            fillrgba(this->x + this->width - 32, this->y, 32, this->height, 48, 48, 255, 255);
        }

        fillrgba(this->x + this->width - 32 - healthWidth, this->y, healthWidth, this->height, 48, 48, 255, 192);
    } else { // T, i.e. left

        if (info.sequence == SEQUENCE_RELOAD) {
            fillrgba(this->x, this->y, 32, this->height, 204, 204, 204, 128);
        } else {
            fillrgba(this->x, this->y, 32, this->height, 255, 0, 48, 255);
        }

        fillrgba(this->x + 32, this->y, healthWidth, this->height, 255, 0, 48, 192);
    }

    // gloss
    fillrgba(this->x, this->y, this->width, this->height / 2, 255, 255, 255, 50);
}

void CClassicHealthBar::DrawHP() {
    char szHealth[16];
    sprintf(szHealth, "%d", info.hp);

    if (this->info.team == 2) // right
    {
        if (CConVars::getConVarFloat("healthbar_use_engine_font") == 1.F) {
            CEngineFont::Print(this->x + this->width - 16, this->y + (this->height / 2), 255, 255, 255,
                               FL_CENTER_X | FL_CENTER_Y, 0, szHealth);
        } else {
            g_fontHealthBar.Print(this->x + this->width - 16,
                                  this->y + (this->height / 2) + CConVars::getConVarFloat("healthbar_font_yoffset"),
                                  255, 255, 255, 255, FL_CENTER_X | FL_CENTER_Y | FL_BACKDROP, 0, szHealth);
        }
    } else if (this->info.team == 1) // left
    {
        if (CConVars::getConVarFloat("healthbar_use_engine_font") == 1.F) {
            CEngineFont::Print(this->x + 16, this->y + (this->height / 2), 255, 255, 255, FL_CENTER_X | FL_CENTER_Y, 0,
                               szHealth);
        } else {
            g_fontHealthBar.Print(this->x + 16,
                                  this->y + (this->height / 2) + CConVars::getConVarFloat("healthbar_font_yoffset"),
                                  255, 255, 255, 255, FL_CENTER_X | FL_CENTER_Y | FL_BACKDROP, 0, szHealth);
        }
    }
}

void CClassicHealthBar::DrawPlayerName() {
    char buffer[64];
    StripTags(buffer, info.szName);

    if (this->info.team == 2) // i.e right
    {
        if (CConVars::getConVarFloat("healthbar_use_engine_font") == 1.F) {
            CEngineFont::Print(this->x + this->width - 36, this->y + (this->height / 2), 255, 255, 255,
                               FL_RIGHT | FL_CENTER_Y, 126, buffer);
        } else {
            g_fontHealthBar.Print(this->x + this->width - 36,
                                  this->y + (this->height / 2) + CConVars::getConVarFloat("healthbar_font_yoffset"),
                                  255, 255, 255, 255, FL_RIGHT | FL_CENTER_Y, 126, buffer);
        }
    } else if (this->info.team == 1) {
        if (CConVars::getConVarFloat("healthbar_use_engine_font") == 1.F) {
            CEngineFont::Print(this->x + 36, this->y + (this->height / 2), 255, 255, 255, FL_CENTER_Y, 126, buffer);
        } else {
            g_fontHealthBar.Print(this->x + 36,
                                  this->y + (this->height / 2) + CConVars::getConVarFloat("healthbar_font_yoffset"),
                                  255, 255, 255, 255, FL_CENTER_Y, 126, buffer);
        }
    }
}

void CClassicHealthBar::DrawWeapon() {
    if (info.hp == 0) {
        return;
    }

    int spacing = 0;

    if (info.team == 2 && info.kitbomb) {
        if (static_cast<int>(strcmp(info.szWeapon, "c4") != 0) !=
            0) // don't draw two c4s if the player is both carrying and having the c4 selected
        {
            CHelpers::drawSprite(this->x - 26, this->y + (this->height / 2), "defuser", false, nullptr);
            spacing = 42;
        }
    } else if (info.team == 1 && info.kitbomb) {
        float scale = 0.75F;
        glScalef(scale, scale, 1.F);
        CHelpers::drawSprite((this->x + this->width + 22) * 1 / scale, (this->y + (this->height / 2)) * 1 / scale,
                             "c4", false, nullptr);
        glLoadIdentity();
        spacing = 36;
    }

    if (this->info.team == 2) // right
    {
        CHelpers::drawSprite(this->x - 30 - spacing, this->y + (this->height / 2), info.szWeapon, true, nullptr);
    } else if (this->info.team == 1) {
        CHelpers::drawSprite(this->x + this->width + 30 + spacing, this->y + (this->height / 2), info.szWeapon, false,
                             nullptr);
    }
}

void CClassicHealthBar::DrawSequence() {}

void CClassicHealthBar::DrawBackground() {
    // only draw the background where the HP bar isn't drawn as to not mess up the opacity
    if (this->info.team == 2) // right
    {
        fillrgba(this->x, this->y, this->width - 32 - this->healthWidth, this->height, 0, 0, 0, 160);
    } else if (this->info.team == 1) {
        fillrgba(this->x + 32 + this->healthWidth, this->y, this->width - 32 - this->healthWidth, this->height, 0, 0, 0,
                 160);
    }

    // border
    drawBox(this->x, this->y, this->width, this->height, 1, 0, 0, 0, 255);
}

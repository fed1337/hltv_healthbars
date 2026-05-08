#include "stdafx.h"

// never got a reply if it was ok ripping off their layout, not done

void CCSPHealthBar::Draw() {
    DrawHPBar();
    // DrawSequence();
    DrawWeapon();
    DrawBackground(); // note: healthwidth is calculated in drawHPBar

    DrawHP();
    DrawPlayerName();
}

void CCSPHealthBar::DrawHPBar() {
    // antal % som �r ifyllt. justera till 0-100
    auto percentage = static_cast<float>(info.hp);
    if (info.hp > 100) {
        percentage = 100;
    }
    if (info.hp < 0) {
        percentage = 0;
    }
    percentage /= 100.F;

    this->healthWidth = static_cast<int>(percentage * (this->width - 4 - 30)); // ***

    if (info.team == 1) // T, dvs h�ger
    {
        // TODO
    } else { // CT, dvs v�nster

        fillrgba(this->x + 4 + 30, this->y, this->healthWidth, this->height, 0x1a, 0x8b, 0xd3, 168);

        // if (info.sequence == SEQUENCE_RELOAD)
        //   fillrgba(this->x + 4, this->y, 30, this->height, 0xFF, 0x99, 0x0, 200);
        // else
        //   fillrgba(this->x + 4, this->y, 30, this->height, 0,  0, 0, 200);

        // ifyllda hp:n
        // fillrgba(this->x + 30 + 4, this->y, this->healthWidth, this->height,  0x1a, 0x8b, 0xd3, 168);
    }

    // gloss
    // fillrgba(this->x, this->y, this->width, this->height / 2, 255, 255, 255, 62);
}
void CCSPHealthBar::DrawHP() {
    char szHealth[16];
    sprintf(szHealth, "%d", info.hp);

    if (this->info.team == 1) // h�ger
    {
        g_fontHealthBar.Print(this->x + this->width - 16, this->y + 22, 255, 255, 255, 255, FL_CENTER_X | FL_BACKDROP,
                              0, szHealth);
    } else if (this->info.team == 2) {
        g_fontHealthBar.Print(this->x + 16, this->y + 22, 255, 255, 255, 255, FL_CENTER_X | FL_BACKDROP, 0, szHealth);
    }
}
void CCSPHealthBar::DrawSequence() {
    // Not used, sequence is drawn in DrawHPBar above as a change of color

    int length = 0;
    int height = 0;

    if (info.sequence == 0) {
        return;
    }
    if (info.sequence == SEQUENCE_RELOAD) {
        g_fontHealthBar.Print(this->x + 200, this->y + 20, 255, 255, 255, 255, FL_RIGHT, 0, "Reloading");
    } else if (info.sequence == SEQUENCE_ARM_C4) {
        g_fontHealthBar.Print(this->x + 200, this->y + 20, 255, 255, 255, 255, FL_RIGHT, 0, "Planting");
    }
}
void CCSPHealthBar::DrawPlayerName() {
    char buffer[64];
    StripTags(buffer, info.szName);

    if (this->info.team == 1) // h�ger
    {
        if (CConVars::getConVarFloat("healthbar_use_engine_font") == 1.F) {
            CEngineFont::Print(this->x + this->width - 36, this->y + 22, 255, 255, 255, FL_RIGHT | FL_BACKDROP, 124,
                               buffer);
        } else {
            g_fontHealthBar.Print(this->x + this->width - 36, this->y + 22, 255, 255, 255, 255, FL_RIGHT | FL_BACKDROP,
                                  124, buffer);
        }
    } else if (this->info.team == 2) {
        if (CConVars::getConVarFloat("healthbar_use_engine_font") == 1.F) {
            CEngineFont::Print(this->x + 36, this->y + 22, 255, 255, 255, FL_BACKDROP, 124, buffer);
        } else {
            g_fontHealthBar.Print(this->x + 36, this->y + 22, 255, 255, 255, 255, FL_BACKDROP, 124, buffer);
        }
    }
}
void CCSPHealthBar::DrawWeapon() {
    if (info.hp == 0) {
        return;
    }

    int spacing = 0;

    if (info.team == 1 && info.kitbomb) {
        if (static_cast<int>(strcmp(info.szWeapon, "c4") != 0) !=
            0) // don't draw two c4s if the player is both carrying and having the c4 selected
        {
            CHelpers::drawSprite(this->x - 26, this->y + (this->height / 2), "c4", false, nullptr);
            spacing = 42;
        }
    } else if (info.team == 2 && info.kitbomb) {
        float scale = 0.75F;
        glScalef(scale, scale, 1.F);
        CHelpers::drawSprite((this->x + this->width + 26) * 1 / scale, (this->y + (this->height / 2)) * 1 / scale,
                             "defuser", false, nullptr);
        glLoadIdentity();
        spacing = 36;
    }

    if (this->info.team == 1) // h�ger
    {
        CHelpers::drawSprite(this->x - 26 - spacing, this->y + (this->height / 2), info.szWeapon, true, nullptr);
    } else if (this->info.team == 2) {
        CHelpers::drawSprite(this->x + this->width + 26 + spacing, this->y + (this->height / 2), info.szWeapon, false,
                             nullptr);
    }
}

void CCSPHealthBar::DrawBackground() {
    // skilj p� v�nster, h�ger

    // kant & plupp till v�nster
    fillrgba(this->x, this->y, 4, this->height, 0x1a, 0x8b, 0xd3, 168);
    fillrgba(this->x + 4, this->y, 30, this->height, 0, 0, 0, 200);

    // rita bara ut bakgrunden d�r det inte finns en bar
    fillrgba(this->x + 4 + 30 + this->healthWidth, this->y, this->width - 4 - 30 - this->healthWidth, this->height, 0,
             0, 0, 52);

    // border
    drawBox(this->x, this->y, this->width, this->height, 1, 0x1a, 0x8b, 0xd3, 168);
}

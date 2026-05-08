#include "stdafx.h"

int currentTick;
int previousTick;
int elapsedTicks;

void Tick() {
    previousTick = currentTick;
    currentTick = GetTickCount();

    int difference = currentTick - previousTick;

    elapsedTicks += difference;

    if (elapsedTicks >= 1000) {
        if (g_HUD_Vars.iRoundTime > 0) {
            g_HUD_Vars.iRoundTime--;
        } else {
            g_HUD_Vars.iRoundTime = 0;
        }

        elapsedTicks = 0;
    }
}

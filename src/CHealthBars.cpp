#include "stdafx.h"

void CHealthBars::Draw() {
    if ((g_Positions.iArrPosCT == nullptr) || (g_Positions.iArrPosT == nullptr)) {
        return;
    }

    int addedT = 0;
    int addedCT = 0;

    // Max players in GoldSrc is 32, but index 0 is world, so 1-32.
    for (int i = 1; i <= 32; i++) {
        cl_entity_s *ent = ENGINE.GetEntityByIndex(i);

        if (!CHelpers::bIsValidEnt(ent)) {
            continue;
        }

        // Populate player info
        playerInfo_s info = {}; // Initialize to zero

        info.szName = CHelpers::szGetPlayerName(i);
        info.szModel = CHelpers::szGetPlayerModel(i);
        info.szWeapon = CHelpers::szGetWeaponName(ent->curstate.weaponmodel);

        // Null checks
        if (info.szName == nullptr) {
            info.szName = "unknown";
        }
        if (info.szModel == nullptr) {
            info.szModel = "unknown";
        }
        if (info.szWeapon == nullptr) {
            info.szWeapon = "unknown";
        }

        info.team = CHelpers::iGetTeam(info.szModel);
        info.hp = CHelpers::iGetPlayerHP(i);
        info.sequence = CHelpers::iTranslateSequence(ent->curstate.sequence);
        info.kitbomb = CHelpers::bHasKitOrBomb(ent);

        // Position and Draw
        if (info.team == 1 && addedT < 5) {
            CClassicHealthBar card(g_Positions.iArrPosT[addedT].x, g_Positions.iArrPosT[addedT].y, 192, 32, info);
            card.Draw();
            addedT++;
        } else if (info.team == 2 && addedCT < 5) {
            CClassicHealthBar card(g_Positions.iArrPosCT[addedCT].x, g_Positions.iArrPosCT[addedCT].y, 192, 32, info);
            card.Draw();
            addedCT++;
        }
    }
}

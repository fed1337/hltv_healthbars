#include "stdafx.h"

void CHealthBars::Draw() {
    int addedT = 0;
    int addedCT = 0;

    if (g_Positions.iArrPosCT == nullptr || g_Positions.iArrPosT == nullptr) {
        return;
    }

    for (int i = 0; i < 33; i++) {
        cl_entity_s *ent = ENGINE.GetEntityByIndex(i);

        if (!CHelpers::bIsValidEnt(ent)) {
            continue;
        }

        playerInfo_s info;
        info.szWeapon = CHelpers::szGetWeaponName(ent->curstate.weaponmodel);
        if (info.szWeapon == nullptr) {
            info.szWeapon = "unknown";
        }
        info.szModel = CHelpers::szGetPlayerModel(i);
        if (info.szModel == nullptr) {
            info.szModel = "unknown";
        }
        info.szName = CHelpers::szGetPlayerName(i);
        if (info.szName == nullptr) {
            info.szName = "unknown";
        }
        info.team = CHelpers::iGetTeam(info.szModel);
        info.hp = CHelpers::iGetPlayerHP(i); // HLTV only
        info.sequence = CHelpers::iTranslateSequence(ent->curstate.sequence);
        info.kitbomb = CHelpers::bHasKitOrBomb(ent);

        if (info.team == 1 && addedT < 5) // t
        {
            CClassicHealthBar card(g_Positions.iArrPosT[addedT].x, g_Positions.iArrPosT[addedT].y, 162, 30, info);

            card.Draw();
            addedT++;
        } else if (info.team == 2 && addedCT < 5) // ct
        {
            CClassicHealthBar card(g_Positions.iArrPosCT[addedCT].x, g_Positions.iArrPosCT[addedCT].y, 162, 30, info);

            card.Draw();
            addedCT++;
        }
    }
}

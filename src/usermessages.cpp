#include "stdafx.h"

// the complete struct is probably in the SDK somewhere, bleh
struct UserMessageList_s {
    int whatisthis;
    int idonteven;
    char pszFuncName[16];
    UserMessageList_s *pNext;
    pfnUserMsgHook pfnUserMessage;
};

// inspired by stev3s post on addCommand hooking
pfnUserMsgHook HookUserMsg(char *szMsgName, void *pfnUserMessage) {
    UserMessageList_s *pList = *(UserMessageList_s **) ((DWORD) g_hHW_DLL + g_dwUserMessages);
    while (pList != nullptr) {
        if (strcmp(pList->pszFuncName, szMsgName) == 0) {
            pfnUserMsgHook ret = pList->pfnUserMessage;
            pList->pfnUserMessage = static_cast<pfnUserMsgHook>(pfnUserMessage);
            return ret;
        }
        pList = pList->pNext;
    }
    return nullptr;
}

void DumpUserMessages() {
    UserMessageList_s *pList = *(UserMessageList_s **) ((DWORD) g_hHW_DLL + 0x1AFF74);
    CONPRINT("UserMsg list:\r\n");
    while (pList != nullptr) {
        CONPRINTF("%s (Located at: %X \r\n", pList->pszFuncName, pList->pfnUserMessage);
        pList = pList->pNext;
    }
}

// === Hooked usermessages below ===
// Team score is updated
pfnUserMsgHook oTeamScore;
auto TeamScore(const char *szMsgName, int iSize, void *pbuf) -> int {
    BEGIN_READ(pbuf, iSize);
    char *teamName = READ_STRING();
    int score = READ_BYTE();

    if (strcmp(teamName, "TERRORIST") == 0) {
        g_HUD_Vars.iTeamScores[0] = score;
    } else if (strcmp(teamName, "CT") == 0) {
        g_HUD_Vars.iTeamScores[1] = score;
    }

    return oTeamScore(szMsgName, iSize, pbuf);
}

// Round time is updated
pfnUserMsgHook oRoundTime;
auto RoundTime(const char *szMsgName, int iSize, void *pbuf) -> int {
    BEGIN_READ(pbuf, iSize);
    int time = READ_SHORT();

    // Uppdate round time
    g_HUD_Vars.iRoundTime = time;
    // Do not clear bBombPlanted here: RoundTime repeats for the whole round; clearing it made the top bar alternate
    // between DrawTexture and pfnSPR_Draw, which broke sprite rendering for the rest of the HUD redraw.

    return oRoundTime(szMsgName, iSize, pbuf);
}

// Centered text
pfnUserMsgHook oTextMsg;
auto TextMsg(const char *szMsgName, int iSize, void *pbuf) -> int {
    BEGIN_READ(pbuf, iSize);
    int destinationType = READ_BYTE();
    char *message = READ_STRING();
    if (strcmp(message, "#Bomb_Planted") == 0) {
        g_HUD_Vars.bBombPlanted = true;
        g_HUD_Vars.iRoundTime = CConVars::getConVarFloat("c4timer");
    } else if (strcmp(message, "#Bomb_Defused") == 0 || strcmp(message, "#Target_Bombed") == 0 ||
               strcmp(message, "#CTs_Win") == 0 || strcmp(message, "#Terrorists_Win") == 0 ||
               strcmp(message, "#Round_Draw") == 0 || strcmp(message, "#Game_Commencing") == 0) {
        g_HUD_Vars.bBombPlanted = false;
    }

    return oTextMsg(szMsgName, iSize, pbuf);
}

pfnUserMsgHook oScoreInfo;
auto try_scoreinfo(void *pbuf, int iSize, int skipBytes, int *playerID, int *frags, int *deaths, int *classID,
                   int *teamID) -> bool {
    BEGIN_READ(pbuf, iSize);
    for (int s = 0; s < skipBytes; s++) {
        READ_BYTE();
    }
    *playerID = READ_BYTE();
    *frags = READ_SHORT();
    *deaths = READ_SHORT();
    *classID = READ_SHORT();
    *teamID = READ_SHORT();
    return READ_OK() != 0 && *playerID >= 1 && *playerID <= SCOREBOARD_MAX_INDEX;
}

// HL/CS ScoreInfo: byte index + 4 shorts (see halflife dlls/player.cpp). Some paths pass an extra leading byte
// (e.g. iSize 10); try skip 0/1 so reads stay aligned with the game scoreboard.
auto ScoreInfo(const char *szMsgName, int iSize, void *pbuf) -> int {
    int playerID = 0;
    int frags = 0;
    int deaths = 0;
    int classID = 0;
    int teamID = 0;
    bool ok = false;

    if (iSize >= 9) {
        for (int skip = 0; skip <= 1 && !ok; skip++) {
            if (try_scoreinfo(pbuf, iSize, skip, &playerID, &frags, &deaths, &classID, &teamID)) {
                ok = true;
            }
        }
    }

    if (ok) {
        if (frags == 0 && deaths == 0) {
            g_ScoreboardData[playerID].headshots = 0;
        }

        g_ScoreboardData[playerID].id = playerID;
        g_ScoreboardData[playerID].frags = frags;
        g_ScoreboardData[playerID].score = frags;
        g_ScoreboardData[playerID].deaths = deaths;
        g_ScoreboardData[playerID].teamId = teamID;
        (void) classID;
    }

    return oScoreInfo(szMsgName, iSize, pbuf);
}

pfnUserMsgHook oDeathMsg;
auto DeathMsg(const char *szMsgName, int iSize, void *pbuf) -> int {
    BEGIN_READ(pbuf, iSize);

    int KillerID = READ_BYTE();
    int VictimID = READ_BYTE();
    int IsHeadshot = READ_BYTE();
    char *TruncatedWeaponName = READ_STRING();
    (void) VictimID;
    (void) TruncatedWeaponName;

    if (KillerID >= 1 && KillerID <= SCOREBOARD_MAX_INDEX && KillerID != VictimID && IsHeadshot == 1) {
        g_ScoreboardData[KillerID].headshots++;
    }

    return oDeathMsg(szMsgName, iSize, pbuf);
}

void HookUserMessages() {
    oScoreInfo = HookUserMsg("ScoreInfo", ScoreInfo);
    oTeamScore = HookUserMsg("TeamScore", TeamScore);
    oRoundTime = HookUserMsg("RoundTime", RoundTime);
    oTextMsg = HookUserMsg("TextMsg", TextMsg);
    oDeathMsg = HookUserMsg("DeathMsg", DeathMsg);
}

void UnhookUserMessages() {
    HookUserMsg("ScoreInfo", oScoreInfo);
    HookUserMsg("TeamScore", oTeamScore);
    HookUserMsg("RoundTime", oRoundTime);
    HookUserMsg("TextMsg", oTextMsg);
    HookUserMsg("DeathMsg", oDeathMsg);
}

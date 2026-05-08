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
auto TeamScore(const char *szMsgName, int iSize, pfnUserMsgHook *pBuf) -> int {
    BEGIN_READ(pBuf, iSize);
    char *teamName = READ_STRING();
    int score = READ_BYTE();

    if (strcmp(teamName, "TERRORIST") == 0) {
        g_HUD_Vars.iTeamScores[0] = score;
    } else if (strcmp(teamName, "CT") == 0) {
        g_HUD_Vars.iTeamScores[1] = score;
    }

    return oTeamScore(szMsgName, iSize, pBuf);
}

// Round time is updated
pfnUserMsgHook oRoundTime;
auto RoundTime(const char *szMsgName, int iSize, pfnUserMsgHook *pBuf) -> int {
    BEGIN_READ(pBuf, iSize);
    int time = READ_SHORT();

    // Uppdate round time
    g_HUD_Vars.iRoundTime = time;
    g_HUD_Vars.bBombPlanted =
            false; // the Bomb_Planted TextMsg is only ever sent after RoundTime messages, no need to reset it elsewhere

    return oRoundTime(szMsgName, iSize, pBuf);
}

// Centered text
pfnUserMsgHook oTextMsg;
auto TextMsg(const char *szMsgName, int iSize, pfnUserMsgHook *pBuf) -> int {
    BEGIN_READ(pBuf, iSize);
    int destinationType = READ_BYTE();
    char *message = READ_STRING();
    if (strcmp(message, "#Bomb_Planted") == 0) {
        g_HUD_Vars.bBombPlanted = true;
        g_HUD_Vars.iRoundTime = CConVars::getConVarFloat("c4timer");
    }

    return oTextMsg(szMsgName, iSize, pBuf);
}

// TODO add the following two to the overlay
pfnUserMsgHook oScoreInfo;
auto ScoreInfo(const char *szMsgName, int iSize, pfnUserMsgHook *pBuf) -> int {
    BEGIN_READ(pBuf, iSize);
    int playerID = READ_BYTE();
    int frags = READ_BYTE();
    int deaths = READ_BYTE();
    int classID = READ_BYTE();
    int teamID = READ_BYTE();

    // reset the manual counters
    if (frags == 0) {
        g_ScoreboardData[playerID].frags = 0;
        g_ScoreboardData[playerID].headshots = 0;
    }


    g_ScoreboardData[playerID].score = frags;
    g_ScoreboardData[playerID].deaths = deaths;

    return oScoreInfo(szMsgName, iSize, pBuf);
}

pfnUserMsgHook oDeathMsg;
auto DeathMsg(const char *szMsgName, int iSize, pfnUserMsgHook *pBuf) -> int {
    BEGIN_READ(pBuf, iSize);

    int KillerID = READ_BYTE();
    int VictimID = READ_BYTE();
    int IsHeadshot = READ_BYTE();
    char *TruncatedWeaponName = READ_STRING();

    g_ScoreboardData[KillerID].frags++;

    if (IsHeadshot == 1) {
        g_ScoreboardData[KillerID].headshots++;
    }


    return oDeathMsg(szMsgName, iSize, pBuf);
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

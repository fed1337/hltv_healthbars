#include "stdafx.h"

// This is a near exact copy of CCommands

void CConVars::addConVar(char *szConVar, char *szValue, char *szDescription) {
    char *szPrefixedConVar = new char[64];
    sprintf(szPrefixedConVar, "%s_%s", PLUGIN_PREFIX, szConVar);

    ENGINE.pfnRegisterVariable(szPrefixedConVar, szValue, 0);

    auto *cvar = new conVarInfo_s();
    cvar->szConVar = szPrefixedConVar;
    cvar->szDescription = szDescription;

    if (head == nullptr) {
        head = cvar;
        return;
    }

    conVarInfo_s *current = head;

    while (current->pNext != nullptr) {
        current = current->pNext;
    }

    current->pNext = cvar;
}

auto CConVars::getConVarFloat(char *szConVar) -> float {
    char szPrefixedConVar[64];
    sprintf(szPrefixedConVar, "%s_%s", PLUGIN_PREFIX, szConVar);
    return ENGINE.pfnGetCvarFloat(szPrefixedConVar);
}
auto CConVars::getConVarString(char *szConVar) -> char * {
    char szPrefixedConVar[64];
    sprintf(szPrefixedConVar, "%s_%s", PLUGIN_PREFIX, szConVar);
    return ENGINE.pfnGetCvarString(szPrefixedConVar);
}
void CConVars::setValue(char *szConVar, float value) {
    char szPrefixedConVar[64];
    sprintf(szPrefixedConVar, "%s_%s", PLUGIN_PREFIX, szConVar);
    ENGINE.Cvar_SetValue(szPrefixedConVar, value);
}

void CConVars::printHelp() {
    conVarInfo_s *current = head;

    CONPRINTF("========================\r\n");
    while (current != nullptr) {
        CONPRINTF("%s \"%s\" - %s\n", current->szConVar, ENGINE.pfnGetCvarString(current->szConVar),
                  current->szDescription);

        current = current->pNext;
    }
    CONPRINTF("========================\r\n");
}

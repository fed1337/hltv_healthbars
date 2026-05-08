#include "stdafx.h"

void CCommands::addCommand(char *szCommand, char *szDescription, void *pfnCommand) {
    auto *szPrefixedCommand = new char[64];
    sprintf(szPrefixedCommand, "%s_%s", PLUGIN_PREFIX, szCommand);

    ENGINE.pfnAddCommand(szPrefixedCommand, static_cast<void (*)()>(pfnCommand));

    auto *cmd = new commandInfo_s();
    cmd->szCommand = szPrefixedCommand;
    cmd->szDescription = szDescription;

    if (head == nullptr) {
        head = cmd;
        return;
    }

    commandInfo_s *current = head;

    while (current->pNext != nullptr) {
        current = current->pNext;
    }

    current->pNext = cmd;
}

void CCommands::printHelp() {
    commandInfo_s *current = head;

    CONPRINTF("========================\r\n");
    while (current != nullptr) {
        CONPRINTF("%s - %s\n", current->szCommand, current->szDescription);

        current = current->pNext;
    }
    CONPRINTF("========================\r\n");
}

// Not even the actual size, but it's linked so w/e
struct node_s {
    node_s *pNext;
    char *szCommand;
    void *pfnCommand;
    // more stuff here
};

auto CCommands::hookCommand(char *szCommand, void *pfnCommand) -> void * {
    node_s *pList = *(node_s **) ((DWORD) g_hHW_DLL + g_dwCommandList);

    while (pList != nullptr) {
        if (strcmp(pList->szCommand, szCommand) == 0) {
            void *ret = pList->pfnCommand;
            pList->pfnCommand = pfnCommand;
            return ret;
        }
        pList = pList->pNext;
    }

    return nullptr;
}

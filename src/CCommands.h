#include "stdafx.h"

// just keeps track of added commands for printing a listing in console
// EDITED to work with XOR'd strings
using pfnCommand = int (*)(void);

struct commandInfo_s {
    commandInfo_s *pNext;
    char *szCommand;
    char *szDescription;
};

class CCommands {
public:
    CCommands() {}
    void addCommand(char *szCommand, char *szDescription, void *pfnCommand);
    void printHelp();
    static auto hookCommand(char *szCommand, void *pfnCommand) -> void *;

private:
    commandInfo_s *head{nullptr};
};

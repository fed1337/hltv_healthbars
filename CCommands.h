#include "stdafx.h"

// just keeps track of added commands for printing a listing in console
// EDITED to work with XOR'd strings
typedef int (*pfnCommand)(void);

struct commandInfo_s
{
	commandInfo_s* pNext;
	char* szCommand;
	char* szDescription;
};

class CCommands
{
public:
	CCommands()
		: head(NULL) { };
	void addCommand(char* szCommand, char* szDescription, void* pfnCommand);
	void printHelp();
	void* hookCommand(char* szCommand, void* pfnCommand);
private:
	commandInfo_s* head;
};
#include "stdafx.h"

void CCommands::addCommand(char* szCommand, char* szDescription, void* pfnCommand)
{

	char* szPrefixedCommand = new char[64];
	sprintf(szPrefixedCommand, "%s_%s", PLUGIN_PREFIX, szCommand);

	ENGINE.pfnAddCommand(szPrefixedCommand, (void (*)(void))pfnCommand);

	commandInfo_s* cmd = new commandInfo_s();
	cmd->szCommand = szPrefixedCommand;
	cmd->szDescription = szDescription;

	if (!head)
	{
		head = cmd;
		return;
	}

	commandInfo_s* current = head;

	while (current->pNext)
		current = current->pNext;

	current->pNext = cmd;
}

void CCommands::printHelp()
{
	commandInfo_s* current = head;

	CONPRINTF("========================\r\n");
	while (current)
	{
		CONPRINTF("%s - %s\n", current->szCommand, current->szDescription);

		current = current->pNext;
	}
	CONPRINTF("========================\r\n");
}

// Not even the actual size, but it's linked so w/e
struct node_s
{
	node_s* pNext;
	char* szCommand;
	void* pfnCommand;
	// more stuff here
};

void* CCommands::hookCommand(char* szCommand, void* pfnCommand)
{
	node_s* pList = *(node_s**)((DWORD)g_hHW_DLL + g_dwCommandList);
	
	while (pList)
	{	
		if (!strcmp(pList->szCommand, szCommand))
		{
			void* ret = pList->pfnCommand;
			pList->pfnCommand = pfnCommand;
			return ret;
		} 
		pList = pList->pNext;
	}

	return 0;
}
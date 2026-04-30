#include "stdafx.h"

// same but with cvars

struct conVarInfo_s
{
	conVarInfo_s* pNext;
	char* szConVar;
	char* szDescription;
};

class CConVars
{
public:
	CConVars()
		: head(NULL) { };
	void addConVar(char* szConVar, char* szValue, char* szDescription);
	float getConVarFloat(char* szConVar);
	char* getConVarString(char* szConVar);
	void setValue(char* szConVar, float value);
	void printHelp();
private:
	conVarInfo_s* head;
};
#include "stdafx.h"

// same but with cvars

struct conVarInfo_s {
    conVarInfo_s *pNext;
    char *szConVar;
    char *szDescription;
};

class CConVars {
public:
    CConVars() {}
    void addConVar(char *szConVar, char *szValue, char *szDescription);
    static auto getConVarFloat(char *szConVar) -> float;
    static auto getConVarString(char *szConVar) -> char *;
    static void setValue(char *szConVar, float value);
    void printHelp();

private:
    conVarInfo_s *head{nullptr};
};

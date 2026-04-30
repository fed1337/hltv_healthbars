#include "stdafx.h"

#pragma once

template <class T> void swap ( T& a, T& b )
{
  T c(a); 
  a = b; 
  b = c;
}

struct dim_s
{
	int width;
	int height;
};

class CHelpers
{
public:
	// Getting player data
	static bool bHasKitOrBomb(cl_entity_s* ent);
	static int iGetPlayerHP(int index);
	static bool bIsValidEnt(cl_entity_s *ent);
	static int iGetTeam(char* model);
	static char* szGetWeaponName(int weaponmodel);
	static int iTranslateSequence(int sequence); //
	static char* szGetPlayerModel(int playerNum);
	static char* szGetPlayerName(int playerNum);
	// Drawing
	static void drawConsoleStringCentered(int x, int y, char* szMsg);
	static void drawConsoleStringRightAligned(int x, int y, char* szMsg);
	static void drawSprite(int x, int y, char* szWeapon, bool reversed, dim_s* dim);
	// Misc
	static bool bFileExists(char* szFileName);
	static bool bDirectoryExists(char* szDirectory);
	static BOOL DumpMemory(void* dwAddress, int size, char* szFileName);
	static void* LoadFileIntoMemory(char* szFileName);
private:
};

enum Sequence
{ 
	SEQUENCE_SHOOT=1,
	SEQUENCE_RELOAD=2,
	SEQUENCE_DIE=3,
	SEQUENCE_THROW=4,
	SEQUENCE_ARM_C4=5 
}; 
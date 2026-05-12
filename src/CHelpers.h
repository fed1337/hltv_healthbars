#include "stdafx.h"

#pragma once

template<class T>
void swap(T &a, T &b) noexcept {
    T c(a);
    a = b;
    b = c;
}

struct dim_s {
    int width;
    int height;
};

class CHelpers {
public:
    // Getting player data
    static auto bHasKitOrBomb(cl_entity_s *ent) -> bool;
    static auto iGetPlayerHP(int index) -> int;
    static auto bIsValidEnt(cl_entity_s *ent) -> bool;
    static auto iGetTeam(char *model) -> int;
    static auto szGetWeaponName(int weaponmodel) -> char *;
    static auto iTranslateSequence(int sequence) -> int; //
    static auto szGetPlayerModel(int playerNum) -> char *;
    static auto szGetPlayerName(int playerNum) -> char *;
    // Drawing
    static void drawConsoleStringCentered(int x, int y, char *szMsg);
    static void drawConsoleStringRightAligned(int x, int y, char *szMsg);
    static void drawSprite(int x, int y, char *szWeapon, bool reversed, dim_s *dim, int r, int g, int b);
    // Misc
    static auto bFileExists(char *szFileName) -> bool;
    static auto bDirectoryExists(char *szDirectory) -> bool;
    static auto DumpMemory(void *dwAddress, int size, char *szFileName) -> BOOL;
    static auto LoadFileIntoMemory(const char *szFileName) -> void *;
};

enum Sequence { SEQUENCE_SHOOT = 1, SEQUENCE_RELOAD = 2, SEQUENCE_DIE = 3, SEQUENCE_THROW = 4, SEQUENCE_ARM_C4 = 5 };

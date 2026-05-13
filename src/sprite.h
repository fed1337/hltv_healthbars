#include "stdafx.h"

struct sprite_data_s {
    char szSpriteName[64];
    int iRes;
    char szSpriteFile[64];
    wrect_t rc;
    HSPRITE hspr; // not read from file
};

extern int g_iSpriteCount;

void LoadSprites();
void InitializeSprites();
auto GetSpriteIndex(char *szSpriteName) -> int;

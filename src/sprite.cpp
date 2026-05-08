#include "stdafx.h"

int g_iSpriteCount = 0;

void LoadSprites() {
    using namespace std;

    char spritePath[MAX_PATH];
    sprintf(spritePath, "%s%s", g_szPluginPath, "sprites.txt");

    if (!CHelpers::bFileExists(spritePath)) {
        CONPRINTF("Couldn't find sprites.txt. \r\n");
        return;
    }

    ifstream ifs;

    int lines = 0;
    g_iSpriteCount = 0;

    ifs.open(spritePath);

    if (!ifs.is_open()) {
        printf("Couldn't open file sprites.txt\r\n");
        return;
    }

    while (ifs.good()) {
        char c = ifs.get();
        if (c == '\n') {
            lines++;
        }
    }
    lines++;

    g_iSpriteCount = lines;

    ifs.close();

    g_Sprites = new sprite_data_s[lines];

    FILE *fp = fopen(spritePath, "r");

    int i = 0;
    while ((feof(fp) == 0) && i < lines) {
        fscanf(fp, "%s", g_Sprites[i].szSpriteName);
        fscanf(fp, "%d", &g_Sprites[i].iRes);

        fscanf(fp, "%s", g_Sprites[i].szSpriteFile);

        fscanf(fp, "%d %d %d %d", &g_Sprites[i].rc.left, &g_Sprites[i].rc.right, &g_Sprites[i].rc.top,
               &g_Sprites[i].rc.bottom);

        /*CONPRINTF("== Sprite loaded ==\r\n");

        CONPRINTF("%s %d %s %d %d %d %d\r\n",
            g_Sprites[i].szSpriteName,
            g_Sprites[i].iRes,
            g_Sprites[i].szSpriteFile,
            g_Sprites[i].rc.left,
            g_Sprites[i].rc.right,
            g_Sprites[i].rc.top,
            g_Sprites[i].rc.bottom);

        CONPRINTF("===================\r\n");*/

        i++;
    }
}

void InitializeSprites() {
    if (g_Sprites == nullptr) {
        CONPRINTF("Could not initialize sprites, null pointer \r\n");
        return;
    }
    for (int i = 0; i < g_iSpriteCount; i++) {
        char buffer[64];
        sprintf(buffer, "sprites/%s.spr", g_Sprites[i].szSpriteFile);
        g_Sprites[i].hspr = ENGINE.pfnSPR_Load(buffer);
    }
    CONPRINTF("Sprites initialized \r\n");
}


auto GetSpriteIndex(char *szSpriteName) -> int {
    for (int i = 0; i < g_iSpriteCount; i++) {
        if (g_Sprites[i].iRes == 640 && (strstr(g_Sprites[i].szSpriteName, szSpriteName) != nullptr))
        // note: these don't have the path and .spr added
        {
            return i;
        }
    }

    return -1;
}

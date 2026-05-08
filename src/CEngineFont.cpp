#include "stdafx.h"

void CEngineFont::Print(int x, int y, int r, int g, int b, BYTE flags, int maxlen, char *string) {
    int drawlen = 0;
    int cheight = 0;

    ENGINE.pfnDrawConsoleStringLen(string, &drawlen, &cheight);

    y -= cheight; // x & y coordinates specify the bottom, not top

    char buffer[256];
    strcpy(buffer, string);

    while (maxlen != 0 && drawlen > 0 && drawlen > maxlen) {
        buffer[strlen(buffer) - 1] = '\0';
        ENGINE.pfnDrawConsoleStringLen(buffer, &drawlen, &cheight);
    }

    if ((flags & FL_CENTER_X) != 0) {
        x -= (drawlen / 2);
    }
    if ((flags & FL_CENTER_Y) != 0) {
        y += cheight / 2;
    }
    if ((flags & FL_RIGHT) != 0) {
        x -= drawlen;
    }

    ENGINE.pfnDrawSetTextColor(r / 255.F, g / 255.F, b / 255.F);
    ENGINE.pfnDrawConsoleString(x, y, buffer);
}

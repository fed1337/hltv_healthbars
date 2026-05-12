#ifndef CFONT_H
#define CFONT_H

#include <windows.h>
#include "../external/stb/stb_truetype.h"

// Alignment and Style Flags
#define FL_NONE 0
#define FL_OUTLINE (1 << 0)
#define FL_BACKDROP (1 << 1)
#define FL_CENTER_X (1 << 2)
#define FL_CENTER_Y (1 << 3)
#define FL_RIGHT (1 << 4)

class CFont {
public:
    CFont();
    CFont(char *i_name, int i_size, int i_weight = 700);

    void InitText();
    void SetFont(char *szFont);
    void SetSize(int iSize);
    void SetWeight(int i_weight);

    void Print(int x, int y, int r, int g, int b, int a, BYTE flags, int maxlen, char *string, ...);

private:
    void Render(float x, float y, int r, int g, int b, int a, char *string);

    char name[64];
    int size;
    int weight;
    unsigned int textureID;
    stbtt_bakedchar cdata[96]; // ASCII 32..126
    float cheight;
    float cwidth[256];
};

// Global HUD Font Instances
extern CFont g_fontGeneral;
extern CFont g_fontHealthBar;
extern CFont g_fontRoundTimer;
extern CFont g_fontTeamScore;
extern CFont g_fontTeamNames;
extern CFont g_fontClanScore;

#endif // CFONT_H

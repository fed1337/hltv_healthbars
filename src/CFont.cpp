#include "stdafx.h"
#include "CFont.h"
#include <vector>

#define STB_TRUETYPE_IMPLEMENTATION
#include "../external/stb/stb_truetype.h"

#pragma warning(disable : 4244)
#pragma warning(disable : 4996)

CFont::CFont() {
    strncpy(name, "Verdana", 63);
    size = 12;
    weight = 700;
    textureID = 0;
}

CFont::CFont(char *i_name, int i_size, int i_weight) {
    strncpy(name, i_name, 63);
    size = i_size;
    weight = i_weight;
    textureID = 0;
}

void CFont::SetFont(char *szFont) { strncpy(name, szFont, 63); }
void CFont::SetSize(int iSize) { this->size = iSize; }
void CFont::SetWeight(int i_weight) { this->weight = i_weight; }

void CFont::InitText() {
    HDC hDC = CreateCompatibleDC(nullptr);
    if (!hDC) return;

    HFONT hFont = CreateFontA(size, 0, 0, 0, weight, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_ONLY_PRECIS,
                              CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, name);

    if (!hFont) {
        DeleteDC(hDC);
        return;
    }

    SelectObject(hDC, hFont);
    DWORD fontSize = GetFontData(hDC, 0, 0, nullptr, 0);
    if (fontSize == GDI_ERROR) {
        DeleteObject(hFont);
        DeleteDC(hDC);
        return;
    }

    std::vector<unsigned char> fontBuffer(fontSize);
    GetFontData(hDC, 0, 0, fontBuffer.data(), fontSize);
    DeleteObject(hFont);
    DeleteDC(hDC);

    unsigned char t_bitmap[512 * 512];
    stbtt_BakeFontBitmap(fontBuffer.data(), 0, (float) size, t_bitmap, 512, 512, 32, 96, cdata);

    if (textureID != 0) glDeleteTextures(1, &textureID);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, t_bitmap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    cheight = (float) size;
    for (int i = 0; i < 256; i++) {
        cwidth[i] = (i >= 32 && i < 128) ? cdata[i - 32].xadvance : 0.0f;
    }
}

void CFont::Print(int x, int y, int r, int g, int b, int a, BYTE flags, int maxlen, char *string, ...) {
    if (!string || !textureID) return;

    char strText[256];
    va_list args;
    va_start(args, string);
    vsprintf(strText, string, args);
    va_end(args);

    float drawlen = 0;
    for (char *p = strText; *p; p++) {
        drawlen += cwidth[(unsigned char) *p];
        if (maxlen > 0 && drawlen >= maxlen) {
            *p = 0;
            break;
        }
    }

    float fx = (float) x;
    float fy = (float) y;

    if (flags & FL_CENTER_X) fx -= (drawlen / 2.0F);
    if (flags & FL_RIGHT) fx -= drawlen;
    if (flags & FL_CENTER_Y) fy += (cheight / 2.0F);

    // 1. Save all attributes (Blending, Alpha Test, Textures, etc.)
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    // 2. Save the current texture bound by the engine
    GLint last_texture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);

    // 3. Setup our specific environment
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glDisable(GL_ALPHA_TEST); // Usually needed for font textures

    // Shadow / Outline
    if (flags & FL_OUTLINE) {
        Render(fx - 1, fy, 0, 0, 0, a, strText);
        Render(fx + 1, fy, 0, 0, 0, a, strText);
        Render(fx, fy - 1, 0, 0, 0, a, strText);
        Render(fx, fy + 1, 0, 0, 0, a, strText);
    }

    if (flags & FL_BACKDROP) {
        Render(fx + 1, fy + 1, 0, 0, 0, a, strText);
    }

    // Main text
    Render(fx, fy, r, g, b, a, strText);

    // 4. RESTORE: Put the engine's texture back
    glBindTexture(GL_TEXTURE_2D, last_texture);

    // 5. RESTORE: Put all flags/colors back
    glPopAttrib();
}

void CFont::Render(float x, float y, int r, int g, int b, int a, char *string) {
    glColor4ub(r, g, b, a);
    glBegin(GL_QUADS);
    for (int i = 0; string[i]; i++) {
        unsigned char c = (unsigned char) string[i];
        if (c >= 32 && c < 128) {
            stbtt_aligned_quad q;
            stbtt_GetBakedQuad(cdata, 512, 512, c - 32, &x, &y, &q, 1);
            glTexCoord2f(q.s0, q.t0);
            glVertex2f(q.x0, q.y0);
            glTexCoord2f(q.s1, q.t0);
            glVertex2f(q.x1, q.y0);
            glTexCoord2f(q.s1, q.t1);
            glVertex2f(q.x1, q.y1);
            glTexCoord2f(q.s0, q.t1);
            glVertex2f(q.x0, q.y1);
        }
    }
    glEnd();
}

CFont g_fontGeneral("Verdana", 24);
CFont g_fontHealthBar("Verdana", 16);
CFont g_fontRoundTimer("Verdana", 24);
CFont g_fontTeamScore("Verdana", 16);
CFont g_fontTeamNames("Verdana", 32);
CFont g_fontClanScore("Verdana", 32);

#include "stdafx.h"

using pfn_glDeleteTextures = void(WINAPI *)(GLsizei n, const GLuint *textures);
pfn_glDeleteTextures original = nullptr;

void WINAPI Hook_glDeleteTextures(GLsizei n, const GLuint *textures) {
    for (int i = 0; i < n; i++) {
        CONPRINTF("Freeing texture %d\r\n", textures[i]);
    }
    original(n, textures);
}

void Hook() {
    g_pClient->HUD_Frame = hook_hud_frame;
    g_pClient->HUD_Redraw = Hook_HUD_Redraw;
    g_pClient->HUD_VidInit = Hook_HUD_VidInit;

    auto *offset = (DWORD *) ((DWORD) g_hHW_DLL + g_dw_glDeleteTextures);
    original = (pfn_glDeleteTextures) *offset;
    *offset = (DWORD) &Hook_glDeleteTextures;
}

void Unhook() {
    g_pClient->HUD_Frame = CLIENT.HUD_Frame;
    g_pClient->HUD_Redraw = CLIENT.HUD_Redraw;
    g_pClient->HUD_VidInit = CLIENT.HUD_VidInit;

    *(DWORD *) ((DWORD) g_hHW_DLL + g_dw_glDeleteTextures) = (DWORD) original;
}

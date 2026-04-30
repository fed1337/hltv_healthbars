#include "stdafx.h"

typedef void (WINAPI *pfn_glDeleteTextures)(GLsizei n, const GLuint* textures);
pfn_glDeleteTextures original = NULL;

void WINAPI Hook_glDeleteTextures(GLsizei n, const GLuint* textures)
{
	for (int i = 0; i < n; i++)
	{
		CONPRINTF("Freeing texture %d\r\n", textures[i]);
	}
	return original(n, textures);
}

void Hook()
{
	g_pClient->HUD_Frame = Hook_HUD_Frame;
	g_pClient->HUD_Redraw = Hook_HUD_Redraw;
	g_pClient->HUD_VidInit = Hook_HUD_VidInit;

	DWORD* offset = (DWORD*)((DWORD)g_hHW_DLL + g_dw_glDeleteTextures); 
	original = (pfn_glDeleteTextures)*offset;
	*offset = (DWORD)&Hook_glDeleteTextures;
}

void Unhook()
{
	g_pClient->HUD_Frame = CLIENT.HUD_Frame;
	g_pClient->HUD_Redraw = CLIENT.HUD_Redraw;
	g_pClient->HUD_VidInit = CLIENT.HUD_VidInit;

	*(DWORD*)((DWORD)g_hHW_DLL + g_dw_glDeleteTextures) = (DWORD)original;
}
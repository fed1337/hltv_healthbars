#include "stdafx.h"

extern DWORD g_dwHLTV;
extern DWORD g_dwCommandList;
extern DWORD g_dwUserMessages;
extern DWORD g_dwEngine;
extern DWORD g_dwClient;
extern DWORD g_dwStudio;
extern DWORD g_dwInterface;
extern DWORD g_dw_glDeleteTextures;

extern HANDLE g_hHW_DLL;
extern HANDLE g_hClient;

extern cl_enginefuncs_s g_oEngine;
extern cl_enginefuncs_s *g_pEngine;

extern cl_clientfuncs_s g_oClient;
extern cl_clientfuncs_s *g_pClient;

extern engine_studio_api_s *g_pStudio;
extern r_studio_interface_s *g_pInterface;

extern hud_globals_s g_HUD_Vars;
extern char g_szPluginPath[MAX_PATH];

extern sprite_data_s *g_Sprites;

extern char **g_pszPlayerNames;

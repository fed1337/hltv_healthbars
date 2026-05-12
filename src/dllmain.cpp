// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

// HLTV HUD
// Sk�ll
// http://www.gamedeception.net/threads/22277-Healthbars?p=163659#post163659


// === Globals ===
// Offsets
DWORD g_dwHLTV = 0x12B334; // client.dll (start of info arr)
DWORD g_dwCommandList = 0x326A48; // -|
DWORD g_dwUserMessages = 0x1AFF74; //  | (list head)
DWORD g_dwEngine = 0x166A98; // |
DWORD g_dwClient = 0x11FE320; //  | - hw.dll
DWORD g_dwStudio = 0x1829B8; // |
DWORD g_dwInterface = 0x182A7C; // -|
// OpenGL table
DWORD g_dw_glDeleteTextures = 0xA5DC2C; // hw.dll

HANDLE g_hHW_DLL = nullptr;
HANDLE g_hClient = nullptr;

cl_enginefuncs_s g_oEngine;
cl_enginefuncs_s *g_pEngine;

cl_clientfuncs_s g_oClient;
cl_clientfuncs_s *g_pClient;

engine_studio_api_s *g_pStudio;
r_studio_interface_s *g_pInterface;

hud_globals_s g_HUD_Vars;
char g_szPluginPath[MAX_PATH];
sprite_data_s *g_Sprites = nullptr;
char **g_pszPlayerNames = nullptr;

void InitializeHack();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(InitializeHack), nullptr, 0, nullptr);
            break;
        case DLL_THREAD_ATTACH:
            break;
        case DLL_THREAD_DETACH:
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

void InitializeHack() {
    do {
        g_hHW_DLL = GetModuleHandleA("hw.dll");
        g_hClient = GetModuleHandleA("client.dll");
        Sleep(10);
    } while (g_hHW_DLL == nullptr);

    // get the Counter-Strike path
    char szPath[256];
    int len = static_cast<int>(GetModuleFileNameA(nullptr, szPath, sizeof(szPath)));
    szPath[len - 6] = 0; // remove "hl.exe"
    sprintf(g_szPluginPath, "%shltv_healthbars\\", szPath);

    // struct pointers
    g_pEngine = (cl_enginefuncs_s *) ((DWORD) g_hHW_DLL + g_dwEngine);
    g_pClient = (cl_clientfuncs_s *) ((DWORD) g_hHW_DLL + g_dwClient);
    g_pStudio = (engine_studio_api_s *) ((DWORD) g_hHW_DLL + g_dwStudio);
    g_pInterface = (r_studio_interface_s *) ((DWORD) g_hHW_DLL + g_dwInterface);


    // copies for later calling the original functions from our hooked ones
    memcpy(&g_oEngine, g_pEngine, sizeof(g_oEngine));
    memcpy(&g_oClient, g_pClient, sizeof(g_oClient));

    // HLTV variables & positions
    // not sure if properly intialized, hence
    ZeroMemory(&g_HUD_Vars, sizeof(g_HUD_Vars));
    ZeroMemory(&g_Positions, sizeof(g_Positions));
    ZeroMemory(&g_ScoreboardData, sizeof(g_ScoreboardData));

    // names are later copied every now and then for use with the strip tag function
    g_pszPlayerNames = new char *[32];
    for (int i = 0; i < 32; i++) {
        g_pszPlayerNames[i] = new char[64];
    }

    CONPRINTF(
            "\r\n================================================\r\nHLTV Health Bars Overlay v1.1.0\r\n"
            "https://github.com/fed1337/hltv_healthbars\r\nFor help, type hltv_help\r\n"
            "================================================\r\n\r\n");

    Hook(); // client functions
    HookUserMessages();
    RegisterCommands();
    LoadSprites();

    // TODO check if files actually exist
    if (!CHelpers::bDirectoryExists(g_szPluginPath)) {
        CONPRINTF("** WARNING ** The plugin directory could not be found:\r\n");
        CONPRINTF("\"%s\"", g_szPluginPath);
    }
}

// dicks
#define CLIENT g_oClient
#define ENGINE g_oEngine
#define STUDIO g_pStudio
#define INTERFACE g_pInterface
#define CONPRINT(pszMsg) g_pEngine->Con_Printf(pszMsg)
#define CONPRINTF(fmt, ...) g_pEngine->Con_Printf(fmt, __VA_ARGS__)
#define ARGC g_pEngine->Cmd_Argc()
#define ARGV g_pEngine->Cmd_Argv

#define PLUGIN_PREFIX "hltv"

#define CRYPTPRINT decrypt_conprintf

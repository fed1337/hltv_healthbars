#include "stdafx.h"

auto commands = new CCommands();
auto cvars = new CConVars();

// Lists all commands & convars that we've registered
void PrintHelp() {
    CONPRINTF("Commands:\r\n");
    commands->printHelp();
    CONPRINTF("Cvars:\r\n");
    cvars->printHelp();
}

// reload everything not accessed directly through a cvar
void cmd_HUD_Reload() {
    delete g_Positions.iArrPosCT;
    delete g_Positions.iArrPosT;

    g_Positions.iArrPosCT = new pos_s[5];
    g_Positions.iArrPosT = new pos_s[5];

    g_Positions.team_1_name_pos.x = static_cast<int>(CConVars::getConVarFloat("team_1_name_xpos"));
    g_Positions.team_1_name_pos.y = static_cast<int>(CConVars::getConVarFloat("team_1_name_ypos"));

    g_Positions.team_2_name_pos.x = static_cast<int>(CConVars::getConVarFloat("team_2_name_xpos"));
    g_Positions.team_2_name_pos.y = static_cast<int>(CConVars::getConVarFloat("team_2_name_ypos"));

    g_Positions.topbar_pos.x = static_cast<int>(CConVars::getConVarFloat("topbar_xpos"));
    g_Positions.topbar_pos.y = static_cast<int>(CConVars::getConVarFloat("topbar_ypos"));

    g_Positions.flag_1_pos.x = static_cast<int>(CConVars::getConVarFloat("flag_1_xpos"));
    g_Positions.flag_1_pos.y = static_cast<int>(CConVars::getConVarFloat("flag_1_ypos"));

    g_Positions.flag_2_pos.x = static_cast<int>(CConVars::getConVarFloat("flag_2_xpos"));
    g_Positions.flag_2_pos.y = static_cast<int>(CConVars::getConVarFloat("flag_2_ypos"));

    g_Positions.roundTimer_pos.x = static_cast<int>(CConVars::getConVarFloat("roundtimer_xpos"));
    g_Positions.roundTimer_pos.y = static_cast<int>(CConVars::getConVarFloat("roundtimer_ypos"));

    g_Positions.team_1_clanScore_pos.x = static_cast<int>(CConVars::getConVarFloat("team_1_clanscore_xpos"));
    g_Positions.team_1_clanScore_pos.y = static_cast<int>(CConVars::getConVarFloat("team_1_clanscore_ypos"));

    g_Positions.team_2_clanScore_pos.x = static_cast<int>(CConVars::getConVarFloat("team_2_clanscore_xpos"));
    g_Positions.team_2_clanScore_pos.y = static_cast<int>(CConVars::getConVarFloat("team_2_clanscore_ypos"));

    g_Positions.team_1_teamScore_pos.x = static_cast<int>(CConVars::getConVarFloat("team_1_teamscore_xpos"));
    g_Positions.team_1_teamScore_pos.y = static_cast<int>(CConVars::getConVarFloat("team_1_teamscore_ypos"));

    g_Positions.team_2_teamScore_pos.x = static_cast<int>(CConVars::getConVarFloat("team_2_teamscore_xpos"));
    g_Positions.team_2_teamScore_pos.y = static_cast<int>(CConVars::getConVarFloat("team_2_teamscore_ypos"));


    char buffer[64];
    for (int i = 0; i < 5; i++) {
        sprintf(buffer, "ct_%d_xpos", i + 1);
        g_Positions.iArrPosCT[i].x = static_cast<int>(CConVars::getConVarFloat(buffer));

        sprintf(buffer, "ct_%d_ypos", i + 1);
        g_Positions.iArrPosCT[i].y = static_cast<int>(CConVars::getConVarFloat(buffer));

        sprintf(buffer, "t_%d_xpos", i + 1);
        g_Positions.iArrPosT[i].x = static_cast<int>(CConVars::getConVarFloat(buffer));

        sprintf(buffer, "t_%d_ypos", i + 1);
        g_Positions.iArrPosT[i].y = static_cast<int>(CConVars::getConVarFloat(buffer));
    }

    g_HUD_Vars.szClanNames[0] = CConVars::getConVarString("team_1_name");
    g_HUD_Vars.szClanNames[1] = CConVars::getConVarString("team_2_name");

    g_fontGeneral.SetFont(CConVars::getConVarString("general_font"));
    g_fontGeneral.SetSize(static_cast<int>(CConVars::getConVarFloat("general_font_size")));

    g_fontHealthBar.SetFont(CConVars::getConVarString("healthbar_font"));
    g_fontHealthBar.SetSize(static_cast<int>(CConVars::getConVarFloat("healthbar_font_size")));

    g_fontRoundTimer.SetFont(CConVars::getConVarString("roundtimer_font"));
    g_fontRoundTimer.SetSize(static_cast<int>(CConVars::getConVarFloat("roundtimer_font_size")));

    g_fontTeamScore.SetFont(CConVars::getConVarString("teamscore_font"));
    g_fontTeamScore.SetSize(static_cast<int>(CConVars::getConVarFloat("teamscore_font_size")));

    g_fontTeamNames.SetFont(CConVars::getConVarString("teamnames_font"));
    g_fontTeamNames.SetSize(static_cast<int>(CConVars::getConVarFloat("teamnames_font_size")));

    g_fontClanScore.SetFont(CConVars::getConVarString("clanscore_font"));
    g_fontClanScore.SetSize(static_cast<int>(CConVars::getConVarFloat("clanscore_font_size")));


    ReinitializeFonts();
    InitializeSprites();

    CONPRINTF("HUD reloaded.\r\n");
}

// increment/decrement cvar, helpers for setting the scores
void cmd_Increment() {
    if (ARGC != 2) {
        CONPRINTF("Usage %s <ConVar>\r\n", ARGV(0));
        return;
    }
    ENGINE.Cvar_SetValue(ARGV(1), ENGINE.pfnGetCvarFloat(ARGV(1)) + 1);
}
void cmd_Decrement() {
    if (ARGC != 2) {
        CONPRINTF("Usage %s <ConVar>\r\n", ARGV(0));
        return;
    }
    ENGINE.Cvar_SetValue(ARGV(1), ENGINE.pfnGetCvarFloat(ARGV(1)) - 1);
}
// toggle cvar 0/1
void cmd_Toggle() {
    if (ARGC != 2) {
        CONPRINTF("Usage %s <ConVar>\r\n", ARGV(0));
        return;
    }
    ENGINE.Cvar_SetValue(ARGV(1), static_cast<float>(static_cast<int>(ENGINE.pfnGetCvarFloat(ARGV(1))) ^ 1));
}

void Set_Team1_Flag() {
    char flagPath[MAX_PATH];

    // Construct the path: <plugin_path>/flags/<input>.png
    // Using _snprintf to ensure we never exceed MAX_PATH
    _snprintf(flagPath, sizeof(flagPath), "%sflags/%s.png", g_szPluginPath, ARGV(1));
    flagPath[MAX_PATH - 1] = '\0'; // Manual null-termination safety

    if (CHelpers::bFileExists(flagPath)) {
        unsigned int oldTexture = g_HUD_Vars.team1_flag.texID;

        // Load the new texture
        unsigned int newTexture = LOAD_TEXTURE(g_HUD_Vars.team1_flag, flagPath);

        // Only delete the old texture if the new one loaded successfully
        if (newTexture != 0) {
            g_HUD_Vars.team1_flag.texID = newTexture;
            if (oldTexture != 0) {
                glDeleteTextures(1, &oldTexture);
            }
        }
    } else {
        CONPRINTF("Error - Flag file '%s' not found", flagPath);
    }
}

void Set_Team2_Flag() {
    char flagPath[MAX_PATH];
    _snprintf(flagPath, sizeof(flagPath), "%sflags/%s.png", g_szPluginPath, ARGV(1));
    flagPath[MAX_PATH - 1] = '\0';

    if (CHelpers::bFileExists(flagPath)) {
        unsigned int oldTexture = g_HUD_Vars.team2_flag.texID;

        // Load the new texture
        unsigned int newTexture = LOAD_TEXTURE(g_HUD_Vars.team2_flag, flagPath);

        // Only delete the old texture if the new one loaded successfully
        if (newTexture != 0) {
            g_HUD_Vars.team2_flag.texID = newTexture;
            if (oldTexture != 0) {
                glDeleteTextures(1, &oldTexture);
            }
        }
    } else {
        CONPRINTF("Error - Flag file '%s' not found", flagPath);
    }
}

// switch the scores around
// positions swapped through the cfg
void cmd_Swap() {
    float score1 = CConVars::getConVarFloat("team_1_score");
    float score2 = CConVars::getConVarFloat("team_2_score");
    CConVars::setValue("team_1_score", score2);
    CConVars::setValue("team_2_score", score1);

    swap(g_HUD_Vars.iClanScores[0], g_HUD_Vars.iClanScores[1]);
    swap(g_HUD_Vars.szClanNames[0], g_HUD_Vars.szClanNames[1]);
    swap(g_HUD_Vars.team1_flag, g_HUD_Vars.team2_flag);

    CONPRINTF("Teams swapped.\r\n");
}

// adds a substr to be stripped
void cmd_StripTag() {
    if (ARGC != 2) {
        CONPRINTF("Usage %s <String>\r\n", ARGV(0));
        return;
    }
    AddTag(ARGV(1));
    CONPRINTF("Tag added\r\n");
}
// clears tags, restores names
void cmd_ClearTags() {
    ClearTags();
    CONPRINTF("All tags cleared\r\n");
}

// just added this to prevent others and myself from getting tempted by game invites or to otherwise wander off to
// VAC-servers
void Hook_Connect() { CONPRINTF("**Use the plugin-specific command to connect**\r\n"); }

// Display available fonts
char fontBuffer[128];
int CALLBACK EnumFontFamiliesExProc(ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, int FontType, LPARAM lParam) {
    if ((strcmp(fontBuffer, reinterpret_cast<char *>(lpelfe->elfFullName)) == 0) || lpelfe->elfFullName[0] == '@') {
        return 1;
    }

    CONPRINTF("%s\n", lpelfe->elfFullName);
    sprintf(fontBuffer, reinterpret_cast<char *>(lpelfe->elfFullName));
    return 1;
}
void PrintAvailableFonts() {
    CONPRINTF("Available fonts (use them exactly as they appear on each line)\r\n");

    ZeroMemory(&fontBuffer, sizeof(fontBuffer));

    HDC hDC = GetDC(nullptr);

    LOGFONT lf = {0, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, 0};
    EnumFontFamiliesEx(hDC, &lf, reinterpret_cast<FONTENUMPROC>(EnumFontFamiliesExProc), 0, 0);
    ReleaseDC(nullptr, hDC);
}

void Debug() {
    CONPRINTF("unhooking\n");
    UnhookUserMessages();
}

void RegisterCommands() {
    // Fonts
    cvars->addConVar("healthbar_font_yoffset", "0", "font vertical offset");
    cvars->addConVar("healthbar_use_engine_font", "1", "use engine font or not");
    cvars->addConVar("general_font", "Verdana", "font");
    cvars->addConVar("healthbar_font", "Verdana", "font");
    cvars->addConVar("roundtimer_font", "Verdana", "font");
    cvars->addConVar("teamscore_font", "Verdana", "font");
    cvars->addConVar("teamnames_font", "Verdana", "font");
    cvars->addConVar("clanscore_font", "Verdana", "font");

    // Sizes
    cvars->addConVar("general_font_size", "22", "font size");
    cvars->addConVar("healthbar_font_size", "18", "font size");
    cvars->addConVar("roundtimer_font_size", "22", "font size");
    cvars->addConVar("teamscore_font_size", "26", "font size");
    cvars->addConVar("teamnames_font_size", "38", "font size");
    cvars->addConVar("clanscore_font_size", "26", "font size");

    commands->addCommand("debug_cmd", "debug", Debug);
    cvars->addConVar("debug_cvar", "debug", "debug");

    // Rename connect => dj_connect, let connect display a message
    void *pfnConnect = CCommands::hookCommand("connect", Hook_Connect);
    commands->addCommand("connect", "Renamed connect command", pfnConnect);

    commands->addCommand("help", "Displays this help", PrintHelp);
    commands->addCommand("reload", "Reloads HUD settings from ConVars", cmd_HUD_Reload);

    commands->addCommand("strip_tag", "Strips specified tag from all player names", cmd_StripTag);
    commands->addCommand("strip_clear_tags", "Clear any added tags", cmd_ClearTags);
    commands->addCommand("swap", "Swaps teams around", cmd_Swap);

    commands->addCommand("increment", "Increment specified cvar", cmd_Increment);
    commands->addCommand("decrement", "Decrement specified cvar", cmd_Decrement);
    commands->addCommand("toggle", "Toggle specified cvar between 0/1", cmd_Toggle);

    commands->addCommand("print_available_fonts", "Print installed fonts", PrintAvailableFonts);

    cvars->addConVar("c4timer", "30", "Set to equal the server's mp_c4timer");

    cvars->addConVar("enable_roundtimer", "1",
                     "Enable/disable separate roundtimer (bomb notification is shown anyway)");
    cvars->addConVar("draw_topbar", "0", "Enable/disable drawing the top bar");
    cvars->addConVar("draw_healthbars", "0", "Enable/disable drawing health bars");
    cvars->addConVar("draw_scoreboard", "0", "Enable/disable drawing the scoreboard");

    commands->addCommand("set_team_1_flag", "Set Team 1 flag", Set_Team1_Flag);
    commands->addCommand("set_team_2_flag", "Set Team 2 flag", Set_Team2_Flag);

    // team names
    cvars->addConVar("team_1_name", "Team 1", "Team 1 name");
    cvars->addConVar("team_2_name", "Team 2", "Team 2 name");

    // team scores (not the T/CT, but the clans or whatchamacallit)
    cvars->addConVar("team_1_score", "0", "Team 1 team score");
    cvars->addConVar("team_2_score", "0", "Team 2 team score");

    // positions
    cvars->addConVar("team_1_name_xpos", "0", "team 1 name position");
    cvars->addConVar("team_1_name_ypos", "0", "team 1 name position");

    cvars->addConVar("team_2_name_xpos", "0", "team 2 name position");
    cvars->addConVar("team_2_name_ypos", "0", "team 2 name position");

    cvars->addConVar("topbar_xpos", "0", "topbar position");
    cvars->addConVar("topbar_ypos", "0", "topbar position");
    cvars->addConVar("topbar_width", "0", "topbar width");
    cvars->addConVar("topbar_height", "0", "topbar height");

    cvars->addConVar("flag_1_xpos", "0", "flag position");
    cvars->addConVar("flag_1_ypos", "0", "flag position");
    cvars->addConVar("flag_2_xpos", "0", "flag position");
    cvars->addConVar("flag_2_ypos", "0", "flag position");

    cvars->addConVar("roundtimer_xpos", "0", "round timer position");
    cvars->addConVar("roundtimer_ypos", "0", "round timer position");

    cvars->addConVar("team_1_clanscore_xpos", "0", "clan score position");
    cvars->addConVar("team_1_clanscore_ypos", "0", "clan score position");

    cvars->addConVar("team_2_clanscore_xpos", "0", "clan score position");
    cvars->addConVar("team_2_clanscore_ypos", "0", "clan score position");

    cvars->addConVar("team_1_teamscore_xpos", "0", "team score position");
    cvars->addConVar("team_1_teamscore_ypos", "0", "team score position");

    cvars->addConVar("team_2_teamscore_xpos", "0", "team score position");
    cvars->addConVar("team_2_teamscore_ypos", "0", "team score position");

    // HP bar positions
    for (int i = 0; i < 5; i++) {
        char *temp = new char[64];
        sprintf(temp, "ct_%d_xpos", i + 1);
        cvars->addConVar(temp, "0", "Health bar position");

        temp = new char[64];
        sprintf(temp, "ct_%d_ypos", i + 1);
        cvars->addConVar(temp, "0", "Health bar position");

        temp = new char[64];
        sprintf(temp, "t_%d_xpos", i + 1);
        cvars->addConVar(temp, "0", "Health bar position");

        temp = new char[64];
        sprintf(temp, "t_%d_ypos", i + 1);
        cvars->addConVar(temp, "0", "Health bar position");
    }
}

// stdafx.h: include file for standard system include files,
// or project-specific include files that are used frequently but are changed infrequently

#pragma once

#include "targetver.h"

// Windows Header Files:
#include <windows.h>
#include <algorithm>

// http://www.gamedeception.net/threads/22277-Healthbars?p=163659#post163659
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <cassert>
#include <cstdint>
#include <iostream>

// Half-Life SDK
#include <mathlib.h>
#include <wrect.h>
#include <cl_dll.h>
#include <cdll_int.h>
#include <cl_entity.h>
#include <com_model.h>
#include <ref_params.h>
#include <triangleapi.h>
#include <r_studioint.h>
#include <usercmd.h>
#include <cvardef.h>
#include <con_nprint.h>
#include <net_api.h>
#include <hltv.h>
#include <event_api.h>

// Panels
// #pragma comment(lib, "vgui.lib")
// #include <VGUI_Font.h>
// #include <VGUI_TextPanel.h>
// #include <VGUI_BorderLayout.h>

// OGL
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment(lib, "OpenGL32.lib")

// PNG => OGL texture
#include "loadpng.h"
#include "../external/lodepng/lodepng.h"

// F�r anti-aliased, anv�nds ej
// #define FTGL_LIBRARY_STATIC
// #include <FTGL/ftgl.h>
// #pragma comment(lib, "ftgl_static.lib")
// #pragma comment(lib, "freetype248ST.lib")

// The project
#include "striptags.h"
#include "sprite.h"
#include "Drawing.h"
#include "textures.h"
#include "hudglobals.h"
#include "parsemsg.h"
#include "usermessages.h"
#include "clientfuncs.h"
#include "snabbmakaroner.h"
#include "CHelpers.h"
#include "CCommands.h"
#include "CConVars.h"
#include "CTopBar.h"
#include "CHealthBars.h"
#include "CHealthBar.h"
#include "CClassicHealthBar.h"
#include "CCSPHealthBar.h"
#include "CScoreboard.h"
#include "dllmain.h"
#include "hook.h"
#include "positions.h"
#include "commands.h"
#include "roundtimer.h"
#include "hud_vidinit.h"
#include "hud_frame.h"
#include "hud_redraw.h"

#include "CEngineFont.h"
#include "CFont.h"

#pragma warning(disable : 4244 4996)

#include "stdafx.h"

bool CHelpers::bHasKitOrBomb(cl_entity_s* ent)
{
	return (ent->curstate.body == 1);
}

int CHelpers::iGetPlayerHP(int index)
{
	DWORD dwAddy = (DWORD)((DWORD)index * (DWORD)0x68 + (DWORD)g_hClient + g_dwHLTV);

	return *(int*)dwAddy;
}

bool CHelpers::bIsValidEnt(cl_entity_s *ent) 
{
 return (ent 
	 && !(ent->curstate.effects & EF_NODRAW) 
	 && ent->player 
	 //&& !ent->curstate.spectator
	 && !(ent->curstate.messagenum < g_oEngine.GetLocalPlayer()->curstate.messagenum));
} 

char* CHelpers::szGetPlayerModel(int playerNum)
{
	return (char*)ENGINE.PlayerInfo_ValueForKey(playerNum, "model");
}
char* CHelpers::szGetPlayerName(int playerNum)
{
	return (char*)ENGINE.PlayerInfo_ValueForKey(playerNum, "name");
}

// c&p from this tutorial by boecke, also credited P47R!CK & Sruh.
// http://www.gamedeception.net/threads/5594-Weapon-ESP
char* CHelpers::szGetWeaponName(int weaponmodel)
{
	static char weapon[50];
	weapon[0]=0;

	model_s* mdl = STUDIO->GetModelByIndex( weaponmodel );
	if( !mdl ){ return weapon; }

	char* name = mdl->name; if( !name ) { return weapon; }
	int len = strlen(name); if( len>48 || len<10){ return weapon; }

	strcpy(weapon,name+9); len -=9;
	if(len>4)weapon[len-4]=(char)0;

	return weapon;
}
int CHelpers::iGetTeam(char* model)
{
	if (strstr(model, "arc")	||
		strstr(model, "gue")	||
		strstr(model, "lee")		||
		strstr(model, "ter"))
		return 1;

	else if (strstr(model, "gig")	||
		strstr(model, "gsg")		||
		strstr(model, "sas")		||
		strstr(model, "urb")		||
		strstr(model, "vip"))
		return 2;

	return 0;
}

// also posted by boecke,
// credited people P47R!CK & Sruh
// http://www.gamedeception.net/threads/5572-Sequence-ESP
int iArrSequenceInfo[] = {
0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   
0, 1, 2, 0, 1, 2, 0, 1, 2, 0,  
1, 2, 0, 1, 1, 2, 0, 1, 1, 2,  
0, 1, 2, 0, 1, 2, 0, 1, 2, 0,  
1, 2, 0, 1, 2, 0, 1, 2, 0, 1,  
2, 0, 1, 2, 0, 0, 0, 4, 0, 4, 
0, 5, 0, 5, 0, 0, 1, 1, 2, 0, 
1, 1, 2, 0, 1, 0, 1, 0, 1, 2, 
0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3}; 
int CHelpers::iTranslateSequence(int sequence)
{
	return iArrSequenceInfo[sequence];
}

void CHelpers::drawConsoleStringCentered(int x, int y, char* szMsg)
{
	int length = 0;
	int height = 0;
	ENGINE.pfnDrawConsoleStringLen(szMsg, &length, &height);
	ENGINE.pfnDrawConsoleString(x - length / 2, y, szMsg);
}
void CHelpers::drawConsoleStringRightAligned(int x, int y, char* szMsg)
{
	int length = 0;
	int height = 0;
	ENGINE.pfnDrawConsoleStringLen(szMsg, &length, &height);
	ENGINE.pfnDrawConsoleString(x - length, y, szMsg);
}

bool CHelpers::bFileExists(char* szFileName)
{
	FILE *fp = fopen(szFileName,"r");
	if (fp) 
	{
		fclose(fp);
		return true;
	}
	return false;
}

bool CHelpers::bDirectoryExists(char* szDirectory)
{
	return (GetFileAttributesA(szDirectory) != INVALID_FILE_ATTRIBUTES);
}

void CHelpers::drawSprite(int x, int y, char* szWeapon, bool reversed, dim_s* dim)
{
	char buffer[256];

	if (strstr(szWeapon, "nade"))
	{ 
		sprintf(buffer,"d_grenade");	
	}
	else if (strstr(szWeapon,"c4"))
	{ 
		sprintf(buffer,"c4"); 
	}
	else if (strstr(szWeapon, "defuser"))
	{
		sprintf(buffer, "defuser");
	}
	else if (strstr(szWeapon,"mp5"))
	{ 
		sprintf(buffer,"d_mp5navy");	
	}
	else if (strstr(szWeapon,"shield"))
	{ 
		sprintf(buffer,"d_skull"); 
	}
	else 
	{ 
		sprintf(buffer, "d_%s",szWeapon); 
	}

	int index = 0;
	index = GetSpriteIndex(buffer); 

	if (index != -1)
	{			
		if (reversed)
		{
			glScalef(-1.f, 1.f, 1.f);
			x *= -1; // should probably do this with some GL thing
		}

		ENGINE.pfnSPR_Set(g_Sprites[index].hspr, 255, 255, 255);
		int width = g_Sprites[index].rc.right - g_Sprites[index].rc.left;
		int height = g_Sprites[index].rc.bottom - g_Sprites[index].rc.top;
		ENGINE.pfnSPR_DrawAdditive(0, x - width / 2, y - height / 2, &(g_Sprites[index].rc));

		if (dim != 0)
		{
			dim->width = ENGINE.pfnSPR_Width(g_Sprites[index].hspr, 0);
			dim->height = ENGINE.pfnSPR_Height(g_Sprites[index].hspr, 0);
		}

		glLoadIdentity();
	}
}

BOOL CHelpers::DumpMemory(void* dwAddress, int size, char* szFileName)
{
	using namespace std;
	ofstream ofs;

	ofs.open(szFileName, ios_base::binary);

	if (!ofs.is_open())
		return FALSE;

	ofs.write((const char*)dwAddress, size);

	ofs.close();
	return TRUE;
}

void* CHelpers::LoadFileIntoMemory(char* szFileName)
{
	using namespace std;

	ifstream ifs;
	ifs.open(szFileName, ios::in | ios_base::binary | ios::ate);

	if (!ifs.is_open())
		return 0;

	int size = (int)ifs.tellg();
	char* buffer = new char[size];

	ifs.seekg (0, ios::beg);
	ifs.read(buffer, size);

	ifs.close();
	return buffer;
}
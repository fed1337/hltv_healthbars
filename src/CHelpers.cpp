#include "stdafx.h"

auto CHelpers::bHasKitOrBomb(cl_entity_s *ent) -> bool { return (ent->curstate.body == 1); }

auto CHelpers::iGetPlayerHP(int index) -> int {
    auto dwAddy = ((static_cast<DWORD>(index) * static_cast<DWORD>(0x68)) + (DWORD) g_hClient + g_dwHLTV);

    return *(int *) dwAddy;
}

auto CHelpers::bIsValidEnt(cl_entity_s *ent) -> bool {
    return ((ent != nullptr) && ((ent->curstate.effects & EF_NODRAW) == 0) &&
            (ent->player != 0)
            //&& !ent->curstate.spectator
            && !(ent->curstate.messagenum < g_oEngine.GetLocalPlayer()->curstate.messagenum));
}

auto CHelpers::szGetPlayerModel(int playerNum) -> char * {
    return const_cast<char *>(ENGINE.PlayerInfo_ValueForKey(playerNum, "model"));
}
auto CHelpers::szGetPlayerName(int playerNum) -> char * {
    return const_cast<char *>(ENGINE.PlayerInfo_ValueForKey(playerNum, "name"));
}

// c&p from this tutorial by boecke, also credited P47R!CK & Sruh.
// http://www.gamedeception.net/threads/5594-Weapon-ESP
auto CHelpers::szGetWeaponName(int weaponmodel) -> char * {
    static char weapon[50];
    weapon[0] = 0;

    model_s *mdl = STUDIO->GetModelByIndex(weaponmodel);
    if (mdl == nullptr) {
        return weapon;
    }

    char *name = mdl->name;
    if (name == nullptr) {
        return weapon;
    }
    int len = strlen(name);
    if (len > 48 || len < 10) {
        return weapon;
    }

    strcpy(weapon, name + 9);
    len -= 9;
    if (len > 4) {
        weapon[len - 4] = static_cast<char>(0);
    }

    return weapon;
}
auto CHelpers::iGetTeam(char *model) -> int {
    if ((strstr(model, "arc") != nullptr) || (strstr(model, "gue") != nullptr) || (strstr(model, "lee") != nullptr) ||
        (strstr(model, "ter") != nullptr)) {
        return 1;
    }
    if ((strstr(model, "gig") != nullptr) || (strstr(model, "gsg") != nullptr) || (strstr(model, "sas") != nullptr) ||
        (strstr(model, "urb") != nullptr) || (strstr(model, "vip") != nullptr)) {
        return 2;
    }

    return 0;
}

// also posted by boecke,
// credited people P47R!CK & Sruh
// http://www.gamedeception.net/threads/5572-Sequence-ESP
int iArrSequenceInfo[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 1, 2,
                          0, 1, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0,
                          1, 2, 0, 0, 0, 4, 0, 4, 0, 5, 0, 5, 0, 0, 1, 1, 2, 0, 1, 1, 2, 0, 1, 0, 1, 0,
                          1, 2, 0, 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
auto CHelpers::iTranslateSequence(int sequence) -> int { return iArrSequenceInfo[sequence]; }

void CHelpers::drawConsoleStringCentered(int x, int y, char *szMsg) {
    int length = 0;
    int height = 0;
    ENGINE.pfnDrawConsoleStringLen(szMsg, &length, &height);
    ENGINE.pfnDrawConsoleString(x - (length / 2), y, szMsg);
}
void CHelpers::drawConsoleStringRightAligned(int x, int y, char *szMsg) {
    int length = 0;
    int height = 0;
    ENGINE.pfnDrawConsoleStringLen(szMsg, &length, &height);
    ENGINE.pfnDrawConsoleString(x - length, y, szMsg);
}

auto CHelpers::bFileExists(char *szFileName) -> bool {
    FILE *fp = fopen(szFileName, "r");
    if (fp != nullptr) {
        fclose(fp);
        return true;
    }
    return false;
}

auto CHelpers::bDirectoryExists(char *szDirectory) -> bool {
    return (GetFileAttributesA(szDirectory) != INVALID_FILE_ATTRIBUTES);
}

void CHelpers::drawSprite(int x, int y, char *szWeapon, bool reversed, dim_s *dim) {
    char buffer[256];

    if (strstr(szWeapon, "nade") != nullptr) {
        sprintf(buffer, "d_grenade");
    } else if (strstr(szWeapon, "c4") != nullptr) {
        sprintf(buffer, "c4");
    } else if (strstr(szWeapon, "defuser") != nullptr) {
        sprintf(buffer, "defuser");
    } else if (strstr(szWeapon, "mp5") != nullptr) {
        sprintf(buffer, "d_mp5navy");
    } else if (strstr(szWeapon, "shield") != nullptr) {
        sprintf(buffer, "d_skull");
    } else {
        sprintf(buffer, "d_%s", szWeapon);
    }

    int index = 0;
    index = GetSpriteIndex(buffer);

    if (index != -1) {
        if (reversed) {
            glScalef(-1.F, 1.F, 1.F);
            x *= -1; // should probably do this with some GL thing
        }

        ENGINE.pfnSPR_Set(g_Sprites[index].hspr, 255, 255, 255);
        int width = g_Sprites[index].rc.right - g_Sprites[index].rc.left;
        int height = g_Sprites[index].rc.bottom - g_Sprites[index].rc.top;
        ENGINE.pfnSPR_DrawAdditive(0, x - (width / 2), y - (height / 2), &(g_Sprites[index].rc));

        if (dim != nullptr) {
            dim->width = ENGINE.pfnSPR_Width(g_Sprites[index].hspr, 0);
            dim->height = ENGINE.pfnSPR_Height(g_Sprites[index].hspr, 0);
        }

        glLoadIdentity();
    }
}

auto CHelpers::DumpMemory(void *dwAddress, int size, char *szFileName) -> BOOL {
    using namespace std;
    ofstream ofs;

    ofs.open(szFileName, ios_base::binary);

    if (!ofs.is_open()) {
        return FALSE;
    }

    ofs.write(static_cast<const char *>(dwAddress), size);

    ofs.close();
    return TRUE;
}

auto CHelpers::LoadFileIntoMemory(const char *szFileName) -> void * {
    using namespace std;

    ifstream ifs;
    ifs.open(szFileName, ios::in | ios_base::binary | ios::ate);

    if (!ifs.is_open()) {
        return nullptr;
    }

    int size = (int) ifs.tellg();
    char *buffer = new char[size];

    ifs.seekg(0, ios::beg);
    ifs.read(buffer, size);

    ifs.close();
    return buffer;
}

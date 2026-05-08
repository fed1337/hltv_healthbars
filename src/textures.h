#include "stdafx.h"

struct hud_texture_s {
    unsigned int texID;
    int width;
    int height;
};

auto LoadTexture(char *file, int *width, int *height) -> unsigned int;
void DrawTexture(hud_texture_s texture, int x, int y, float alpha, int flags);

#define LOAD_TEXTURE(texture, filename) texture.texID = LoadTexture(filename, &(texture).width, &(texture).height)
#define DELETE_TEXTURE(texture)                            \
    unsigned int oldTextureId_ #texture = (texture).texID; \
    glDeleteTextures(1, &oldTextureId_ #texture);
#define DBG_PRINT_TEXTURE(texture) \
    g_oEngine.Con_Printf("%s (id %u): %dx%d\r\n", #texture, (texture).texID, (texture).width, (texture).height);

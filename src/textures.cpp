#include "stdafx.h"

auto LoadTexture(char *file, int *width, int *height) -> unsigned int { return load_png_texture(file, width, height); }

// unbind texture? i'unno lol
void DrawTexture(hud_texture_s texture, int x, int y, float alpha, int flags) {
    if ((flags & FL_CENTER_X) != 0) {
        x -= texture.width / 2;
    }
    if ((flags & FL_CENTER_Y) != 0) {
        y -= texture.height / 2;
    }
    if ((flags & FL_RIGHT) != 0) {
        x -= texture.width;
    }

    glBindTexture(GL_TEXTURE_2D, texture.texID);

    glColor4f(1.0, 1.0, 1.0, static_cast<GLfloat>(alpha));

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0.F);
    glVertex2f(x, y);
    glTexCoord2f(1.F, 0.0);
    glVertex2f(x + texture.width, y);
    glTexCoord2f(1.F, 1.F);
    glVertex2f(x + texture.width, y + texture.height);
    glTexCoord2f(0.F, 1.F);
    glVertex2f(x, y + texture.height);
    glEnd();
}

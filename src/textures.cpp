#include "stdafx.h"

auto LoadTexture(char *file, int *width, int *height) -> unsigned int { return load_png_texture(file, width, height); }

// unbind texture? i'unno lol
void DrawTexture(hud_texture_s texture, int x, int y, float alpha, int flags) {
    if (texture.texID == 0) return;

    // Use a local copy for calculations to keep the logic clean
    auto fx = (float) x;
    auto fy = (float) y;
    auto fw = (float) texture.width;
    auto fh = (float) texture.height;

    if ((flags & FL_CENTER_X) != 0) fx -= fw / 2.0F;
    if ((flags & FL_CENTER_Y) != 0) fy -= fh / 2.0F;
    if ((flags & FL_RIGHT) != 0) fx -= fw;

    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture.texID);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // If alpha is 0-255, we need to normalize it for glColor4f, ensure alpha is 0.0-1.0
    if (alpha > 1) {
        alpha /= 255.0;
    } else {
        alpha = 0;
    }
    glColor4f(1.0F, 1.0F, 1.0F, alpha);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0F, 0.0F);
    glVertex2f(fx, fy);
    glTexCoord2f(1.0F, 0.0F);
    glVertex2f(fx + fw, fy);
    glTexCoord2f(1.0F, 1.0F);
    glVertex2f(fx + fw, fy + fh);
    glTexCoord2f(0.0F, 1.0F);
    glVertex2f(fx, fy + fh);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0); // Explicitly unbind
    glPopAttrib(); // Restore engine's blending, color, etc.
}

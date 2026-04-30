#include "stdafx.h"

unsigned int LoadTexture(char* file, int* width, int *height)
{
	return Load_PNG_Texture(file, width, height);
}

// unbind texture? i'unno lol
void DrawTexture(hud_texture_s texture, int x, int y, float alpha, int flags)
{
	if (flags & FL_CENTER_X)
		x -= texture.width / 2;
	if (flags & FL_CENTER_Y)
		y -= texture.height / 2;
	if (flags & FL_RIGHT)
		x -= texture.width;

	glBindTexture(GL_TEXTURE_2D, texture.texID);

	glColor4f(1.0, 1.0, 1.0, (GLfloat)alpha);

	glBegin(GL_QUADS);
	glTexCoord2f(0, 0.f); glVertex2f(x, y);
	glTexCoord2f(1.f,0.0); glVertex2f(x + texture.width, y);
	glTexCoord2f(1.f,1.f); glVertex2f(x + texture.width, y + texture.height);
	glTexCoord2f(0.f,1.f); glVertex2f(x, y + texture.height);
	glEnd();
}
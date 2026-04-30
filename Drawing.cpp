#include "stdafx.h"

// C&P
// posted by sp0rky here:
// http://www.gamedeception.net/threads/6711-fillrgba

void fillrgba(GLfloat x, GLfloat y, int w, int h, UCHAR r, UCHAR g, UCHAR b, UCHAR a)
{
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(r,g,b,a);
	  glBegin(GL_QUADS);
	    glVertex2f(x,y);
		glVertex2f(x+w,y);
		glVertex2f(x+w,y+h);
		glVertex2f(x,y+h);
	  glEnd();
	glDisable(GL_BLEND);

	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void drawBox(GLfloat x, GLfloat y, int w, int h, int thickness, UCHAR r, UCHAR g, UCHAR b, UCHAR a)
{
	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(r,g,b,a);
	glLineWidth(thickness);
	  glBegin(GL_LINES);
	    glVertex2f(x-thickness,y-thickness);
		glVertex2f(x+w,y-thickness);

		glVertex2f(x+w+thickness,y-thickness);
		glVertex2f(x+w+thickness,y+h+thickness);

		glVertex2f(x+w,y+h);
		glVertex2f(x-thickness,y+h);

		glVertex2f(x,y+h);
		glVertex2f(x,y);
	  glEnd();
	glDisable(GL_BLEND);

	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}
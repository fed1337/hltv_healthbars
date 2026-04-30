// This:

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
/*
	This font class was created by Azorbix for Game-Deception (http://www.game-deception.com).
	Original print style created by Jeff Molofee (http://nehe.gamedev.net)
	
	Credits:
		Azorbix (for making it) [http://zox.game-deception.com]
		Crusader (Help with original glPrint function) [http://crusader.game-deception.com]
		LanceVorgin (Help with character lengths) [http://lvgl.game-deception.com]
		Xnient (Many improvements to fontclass) [http://zox.game-deception.com]

	This code may not be reproduced anywhere without concent from Xnient or Azorbix.
	If you are going to use this code in any program, please credit the names above.
	
	Dont be a RIPPER!
*/
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//

#include "stdafx.h"

#pragma warning( disable: 4244 )

// FIX cleanup

CFont::CFont() 
{  
	strcpy(name, "Verdana Bold "); 
	size = 12; 
} 

CFont::CFont(char *i_name, int i_size) 
{ 
	strcpy(name, i_name); 
	size = i_size; 
}

void CFont::SetFont(char* szFont)
{
	strcpy(name, szFont); 
}
void CFont::SetSize(int iSize)
{
	this->size = iSize;
}

void CFont::InitText() 
{ 
	HDC hDC; 
	HFONT hFont; 
	HFONT hOldFont; 

	hDC = wglGetCurrentDC(); 
	g_FontListID = glGenLists(256); 

	hFont=CreateFont(size, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, // FW_DONTCARE => FW_BOLD
      		OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, 
      		DEFAULT_PITCH|FF_DONTCARE, name); // PROOF_QUALITY => ANTIALIASED_QUALITY

	hOldFont = (HFONT)SelectObject(hDC, hFont); 
    
	wglUseFontBitmapsA (hDC, 0, 255, g_FontListID);
	for(int i=0; i < 255; i++) 
	{ 
		SIZE s; 
		char line[2] = { (char)i, 0 }; //credits to LanceVorgin 
		GetTextExtentPoint(hDC, line, 1, &s); 
		cwidth[i] = s.cx; 
		cheight = s.cy; 
	} 
	SelectObject(hDC, hOldFont); 
	DeleteObject(hFont); 
} 

void CFont::Print(int x, int y, int r, int g, int b, int a, BYTE flags, int maxlen, char *string, ...) 
{ 
	if (strlen(string) == 0)
		return;

	glDisable(GL_TEXTURE_2D); 

	char strText[256];							 
	va_list	argumentPtr; 

	va_start(argumentPtr, string);				 
	vsprintf(strText, string, argumentPtr);			 
	va_end(argumentPtr); 

	int drawlen = 0; 
	for(char *p = strText; *p; p++) 
	{ 
		drawlen += cwidth[*p]; 
		if (maxlen != 0 && drawlen >= maxlen) // max length
		{
			*p = 0;
			break;
		}
	} 
	 
	if(flags & FL_CENTER_X) { x -= (drawlen / 2); } 
	if(flags & FL_CENTER_Y) { y += cheight / 2; }
	if(flags & FL_RIGHT) { x -= drawlen; }

	// fix
	if (x < 1)
		x = 1;
	if (y < 1)
		y = 1;

	if(flags & FL_OUTLINE)
	{
		//Render(x,	y-1,	0, 0, 0, 200, strText); //comment these 4 if you experience slowness
		//Render(x,	y+1,	0, 0, 0, 200, strText); //"""""""
		//Render(x-1, y,		0, 0, 0, 200, strText); //"""""""
		//Render(x+1, y,		0, 0, 0, 200, strText); //"""""""

		Render(x-1, y-1,	0, 0, 0, 100, strText); // 200 => 100
		Render(x+1, y-1,	0, 0, 0, 100, strText);
		Render(x-1, y+1,	0, 0, 0, 100, strText);
		Render(x+1, y+1,0, 0, 0, 100, strText);

	} 

	if(flags & FL_BACKDROP)
	{
		
		Render(x,y+1,	0, 0, 0, 255, strText); //comment these 4 if you experience slowness
		Render(x,y+1,	0, 0, 0, 255, strText); //"""""""
		Render(x+1, y,		0, 0, 0, 255, strText); //"""""""
		Render(x+1, y,		0, 0, 0, 255, strText); //"""""""

		Render(x+1,y+1,	0, 0, 0, 255, strText);
		Render(x,y+1,	0, 0, 0, 255, strText);
		Render(x+1,y+1,	0, 0, 0, 255, strText);
		Render(x,y+1,	0, 0, 0, 255, strText);
	} 

	Render(x, y, r, g, b, a, strText);		//draw normally 
	 
	glEnable(GL_TEXTURE_2D); 
}  

void CFont::Render(int x, int y, int r, int g, int b, int a, char *string) 
{ 
	int i=0; 
	while(x < 0)	//prevent rendering from failing 
	{ 
		x += cwidth[string[i]]; 
		i++; if(!string[i]) { return; } 
	} 

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4ub(r, g, b, a); 

	glRasterPos2i(x, y); 

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
	glPushAttrib(GL_LIST_BIT);							 
		glListBase(g_FontListID);						 
		glCallLists(strlen(string) - i, GL_UNSIGNED_BYTE, string + i); 
	glPopAttrib();	 
} 

//
CFont g_fontGeneral("Verdana",22);
CFont g_fontHealthBar("Verdana",18); 
CFont g_fontRoundTimer("Verdana",22);
CFont g_fontTeamScore("Verdana",26);
CFont g_fontTeamNames("Verdana",38); 
CFont g_fontClanScore("Verdana",26);
//
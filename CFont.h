#include "stdafx.h"

// Azorbix GL font class, see CFont.cpp

#define FL_NONE	0 
#define FL_OUTLINE	2 
#define FL_BACKDROP	4 
#define FL_CENTER_X	8 
#define FL_CENTER_Y 16
#define FL_RIGHT 32
#define FL_ALL	255 

class CFont 
{ 
public: 
	CFont(); 
	CFont(char*, int); 
	void Print(int x, int y, int r, int g, int b, int a, BYTE flags, int maxlen, char *szbuf, ...); 
	void InitText();    
	void SetFont(char* szFont);
	void SetSize(int iSize);
private: 
	void	Render(int x, int y, int r, int g, int b, int a, char *string); 
	short	cheight; 
	short	cwidth[255]; 
	char   name[20]; 
	int   size; 
	UINT   g_FontListID; 
}; 

// Fonts
extern CFont g_fontGeneral;
extern CFont g_fontHealthBar;  
extern CFont g_fontRoundTimer;  
extern CFont g_fontTeamScore;
extern CFont g_fontTeamNames;  
extern CFont g_fontClanScore;
extern CFont g_fontRoundTimer; 
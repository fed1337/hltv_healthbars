#include "stdafx.h"

HDC     hDC=NULL;                   // Private GDI Device Context
HGLRC       hRC=NULL;                   // Permanent Rendering Context
HWND        hWnd=NULL;                  // Holds Our Window Handle
HINSTANCE   hInstance;                  // Holds The Instance Of The Application

GLuint  base;                           // Base Display List For The Font Set
GLfloat cnt1;                           // 1st Counter Used To Move Text & For Coloring
GLfloat cnt2;                           // 2nd Counter Used To Move Text & For Coloring
 
bool    keys[256];                      // Array Used For The Keyboard Routine
bool    active=TRUE;                        // Window Active Flag Set To TRUE By Default
bool    fullscreen=TRUE;                    // Fullscreen Flag Set To Fullscreen Mode By Default
 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);       // Declaration For WndProc

GLvoid BuildFont(GLvoid)                    // Build Our Bitmap Font
{
    HFONT   font;                       // Windows Font ID
    HFONT   oldfont;                    // Used For Good House Keeping
 
    base = glGenLists(96);                  // Storage For 96 Characters ( NEW )

	font = CreateFont(-24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_TT_PRECIS, 	
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE|DEFAULT_PITCH, L"Verdana");
    
	hDC = wglGetCurrentDC();

	oldfont = (HFONT)SelectObject(hDC, font);       // Selects The Font We Want
    wglUseFontBitmaps(hDC, 32, 96, base);           // Builds 96 Characters Starting At Character 32
    SelectObject(hDC, oldfont);             // Selects The Font We Want
    DeleteObject(font);                 // Delete The Font
}

GLvoid KillFont(GLvoid)                     // Delete The Font List
{
    glDeleteLists(base, 96);                // Delete All 96 Characters ( NEW )
}

GLvoid glPrint(const char *fmt, ...)                // Custom GL "Print" Routine
{
	char        text[256];              // Holds Our String
	va_list     ap;                 // Pointer To List Of Arguments

	if (fmt == NULL)                    // If There's No Text
		return;                     // Do Nothing

	va_start(ap, fmt);                  // Parses The String For Variables
    vsprintf(text, fmt, ap);                // And Converts Symbols To Actual Numbers
	va_end(ap);                     // Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits     ( NEW )
	glListBase(base - 32);                  // Sets The Base Character to 32    ( NEW )

    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text  ( NEW )
    glPopAttrib();                      // Pops The Display List Bits   ( NEW )
}
#ifndef _ZODIAC_H

#include "message.h"
#include "z340.h"

//program
#define PROG_NAME	"Zodiac Code Decipher"
#define PROG_VER	"v1.0"

//language
#define LANG_DIR	"language"
#define LANG_ENG	"eng"
#define LANG_SPA	"spa"
#define LANG_GER	"ger"

//position and size for the cipher and plain text displays, 
//used to calculate #lines for display and click position
#define CIPHER_X	202
#define CIPHER_Y	32
#define PLAIN_X		426
#define PLAIN_Y		32
#define TEXT_WIDTH  223
#define TEXT_HEIGHT 208
#define CHAR_WIDTH  7
#define CHAR_HEIGHT 12

//macros
#define IS_BETWEEN(X,Y,Z) (X>=Y && X<=Z)
#define IN_RECT(X,Y,L,T,W,H) (IS_BETWEEN(X,L,L+W) && IS_BETWEEN(Y,T,T+H))

//cipher/key data & files
Message message; //cipher & main key
Message undo_message; //undo key
char szCipherName[1024], szKeyName[1024], szGraphName[1024]; //filenames
char *szCipherBase, *szKeyBase; //file basenames
int bMsgLoaded=false, bMapLoaded=false, bUndo=false;
const char *szCipher=NULL, *szPlain=NULL; //strings for display
int iCipherLength=0, iSymbols=0; 

//GUI data
char szTitle[512], szText[1024], szExeDir[1024];
int iCurSymbol=-1, iCurPat=-1, iTextSel=-1; //selections
int iCharWidth=CHAR_WIDTH, iCharHeight=CHAR_HEIGHT; //font size
float iCharSize=1.0; //font size multiplier
int iLineChars=17, iLines, iDispLines; //text line data
int iScrollPos, iMaxScroll; //scrollbar

//solver data
SOLVEINFO siSolveInfo;
int iUseGraphs=USE_BI+USE_TRI+USE_TETRA+USE_PENTA;
int iPriority, iLang, iBestScore=0;

//Win32 object handles
HWND		hMainWnd, hCipher=NULL, hPlain=NULL, hScroll=NULL;
HPEN 		hRedPen, hGreenPen, hBluePen;
HDC 		hCipherDC=NULL, hPlainDC=NULL;
HFONT		hTextFont=NULL;
HMENU		hMainMenu;
HINSTANCE	hInst;
HANDLE		hSolveThread=NULL;

//open/save file filter
char szFileFilter[]=
	{"Text Files (*.txt)\0" "*.txt;\0"
	 "All Files (*.*)\0" "*.*\0\0"};
	 
//callback functions for hillclimber
inline void disp_all()  {SendMessage(hMainWnd,WM_COMMAND,UDM_DISPALL,0);}
inline void disp_info() {SendMessage(hMainWnd,WM_COMMAND,UDM_DISPINFO,0);}
inline DWORD GetTime()	{return GetTickCount();}

#endif


#ifndef DefSmallWindow
#define DefSmallWindow
#include "SDL.h"
#include "WINDOW.h"
class CSmallWindow
{
	char Active;
	char Result;
	int X1;
	int Y1;
	int X2;
	int Y2;
	int LinesNum;
	int ButtonNum;
	char Reading;
	char*HeadingText;
	char*ConstText[4];
	char*ReadText;
	CMenuButton*TabBut[2];
	void React(int X, int Y);//reakcja na przyci˜ni©cie klawisza myszki
	void Read();//wczytuje znaki z klawiatury
	void CheckButtons(int X, int Y);//sprawdzenie przycisk¢w przy naci˜ni©ciu myszki
	void Action(int ActNum);
	SDL_Rect Bar(int x1, int y1, int x2, int y2);
public:
	CSmallWindow();
	void DrawSmallWin(SDL_Renderer * renderer);
	char Work();//obsluga myszki

	CSmallWindow(int X1, int Y1, int X2, int Y2, char*HeadingText, char**ConstText,
		char Reading, int ButtonNum, SDL_Renderer * renderer, char*FirstButtonText=nullptr,
		char*SecondButtonText = nullptr);
	int GetReadTextLength();
	char GetReadText(char*ReadText);
	~CSmallWindow();
};
#endif


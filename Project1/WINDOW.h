#ifndef DefWindow
#define DefWindow
#include "SDL.h"
#include "SDL_TTF.h"
#include "button.h"
class CWindow
{
	SDL_Window *window;
	SDL_Renderer *renderer=NULL;
	int WinNum;
	char Active;
	char Result;
	int NumOfElem;//ilo˜† element¢w
	enum TMode { move, link, block };
	TMode Mode;
	//CElement*TabElem[MaxNumOfElem];
	CButton*TabBut[16];
	char*StandardPath;
	//void*ImageTab[NumberOfImages];
	void DoText(int Number, char*Text = NULL);
	//void React(int X, int Y);//reakcja na przyci˜ni©cie klawisza myszki
	//void CheckButtons(int X, int Y);//sprawdzenie przycisk¢w przy naci˜ni©ciu myszki
	//void CheckElements(int X, int Y);//sprawdzenie element¢w przy naci˜ni©ciu myszki
	//char DragElement(int ImageNum, int ElemNum);
	void DrawWin(char Mode);
	void DrawBasket(int X, int Y);
	SDL_Rect Bar(int x1, int y1, int x2, int y2);
	void Action(int ActNum);
	//char Load(char*Path = NULL);
	void New();
	void Previous();
	void Next();
	//char Save(char*Path = NULL);
	void Exit();
	//void Info();
	//void MoveOrLink();
	//void NewElement(int ElemNum);
	//void LinkElem(CElement*FirstElem, int X1, int Y1, CElement*NextElem, int X2, int Y2);
	//void DeleteElem(int ElemNum);
	//void Error(int ErrorNum);
public:
	char Work();//praca u¾ytkownika w oknie
	CWindow();
	CWindow(int Number, char IsPrev, char IsNext, char NewPossib, char IsNew);
	~CWindow();
};
#endif
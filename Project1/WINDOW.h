#pragma once
#ifndef DefWindow
#define DefWindow
#include "SDL.h"
#include "SDL_TTF.h"
#include "button.h"
#include "MENUBUT.H"
#include "MODEBUT.H"
#include "ELEMENT.h"
#include "CONSTANTS.h"
#include "CONSTBUS.h"
#include "INBUS.H"
#include "and.h"
#include "or.h"
#include "not.h"
#include "nand.h"
#include "nor.h"
#include "xor.h"
#include "output.h"
#include "wire.h"

class CWindow
{
	SDL_Window *window;
	int WinNum;
	char Active;
	char Result;
	int NumOfElem;//ilo˜† element¢w
	enum TMode { move, link, block };
	TMode Mode;
	CElement*TabElem[MaxNumOfElem];
	CButton*TabBut[16];
	SDL_Renderer *renderer = NULL;
	char*StandardPath;
	SDL_Texture* Message = NULL;
	SDL_Surface* surfaceMessage = NULL;
	TTF_Font* font = NULL;
	//void*ImageTab[NumberOfImages];
	void DoText(int Number, char*Text = NULL);
	//void React(int X, int Y);//reakcja na przyci˜ni©cie klawisza myszki
	void CheckButtons(int X, int Y);//sprawdzenie przycisk¢w przy naci˜ni©ciu myszki
	void CheckElements(int X, int Y);//sprawdzenie element¢w przy naci˜ni©ciu myszki
	char DragElement(int ImageNum, int ElemNum);
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
	void MoveOrLink();
	void NewElement(int ElemNum);
	//void LinkElem(CElement*FirstElem, int X1, int Y1, CElement*NextElem, int X2, int Y2);
	void DeleteElem(int ElemNum);
	//void Error(int ErrorNum);
public:
	void Control();
	void Redraw();
	char Work();//praca u¾ytkownika w oknie
	CWindow();
	CWindow(int Number, char IsPrev, char IsNext, char NewPossib, char IsNew);
	~CWindow();
};
#endif
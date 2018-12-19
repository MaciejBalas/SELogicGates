#ifndef DefWire
#define DefWire

#include "element.h"
#include "junction.h"

class CWire :public CElement
{
	int JunctionNum;
	CJunction*TabJunction[MaxJunctionNum];
	int BreakpointsNum;
	int TabBreakpoints[MaxBreakpointsNum][2];
	//SDL_Renderer *renderer = NULL;
	char FormatJunctions(CElement**TabElem, int NumOfElem);
	char FormatLine(int i, CElement**TabElem, int NumOfElem);
	char Check(CElement**TabElem, int NumOfElem);
public:
	void passOnRenderer();
	void DrawElem(SDL_Color Colour = { 0,0,0 });
	TOutput GetOutput(int AskElemNum, int MaxNum);
	int IsYourArea(int X, int Y);
	char IsElemNext(CElement*Element);
	int IsOnBoard();
	void ClickElement(int X, int Y);
	char LinkNextElem(CElement*NextElem, int X, int Y);
	char LinkPrevElem(CElement*PrevElem, int X, int Y);
	TElementType ElementType();
	void MoveBeg(int X, int Y);//przesuwanie pocz¥tku
	void MoveEnd(int X, int Y);//przesuwanie koäca
	char Autoformat(CElement**TabElem, int NumOfElem);
	char DelNextElem(CElement*DelElem);
	int DeleteConnections(CElement**TabElem, int NumOfElem, char Main);
	char SaveElement(CElement**TabElem, int NumOfElem, FILE*File, char Phase);
	char LoadElement(CElement**TabElem, int NumOfElem, FILE*File, char Phase);
	CWire(int X, int Y, SDL_Renderer *renderer, SDL_Color Colour = { 0,0,0 }, char FromJunction = 0, CElement*PrevWire = NULL);
	~CWire();
};

#endif
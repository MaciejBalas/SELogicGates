#ifndef DefInBus
#define DefInBus

#include "CONSTANTS.h"
#include "SMALLBUT.h"
#include "element.h"
#include "junction.h"

class CInBus:public CElement
{
	CSmallButton*Button[2];
	char Name;
	bool Visible;
	int JunctionNum;
	CJunction*TabJunction[MaxBusJunctionNum];
 public:
	void DrawElem(SDL_Color Colour = { 0,0,0 });
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void Change();
	SDL_Renderer *renderer = NULL;
	char LinkNextElem(CElement*NextElem,int X,int Y);
	char LinkPrevElem(CElement*PrevElem,int X,int Y);
	TElementType ElementType();
	char DelNextElem(CElement*DelElem);
	char SaveElement(CElement**TabElem,int NumOfElem,FILE*File,char Phase);
	char LoadElement(CElement**TabElem,int NumOfElem,FILE*File,char Phase);
	void ClickElement();
	CInBus(int X,int Y, char Name, SDL_Renderer *renderer);
	~CInBus();
};

#endif
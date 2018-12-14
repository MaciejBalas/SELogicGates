#ifndef DefConstBus
#define DefConstBus

#include "element.h"
#include "junction.h"

class CConstBus :public CElement
{
	int JunctionNum;
	SDL_Renderer *renderer = NULL;
	CJunction*TabJunction[MaxBusJunctionNum];
public:
	void DrawElem(SDL_Color Colour = {0,0,0});
	TOutput GetOutput(int AskElemNum, int MaxNum);
	void ClickElement();
	char LinkNextElem(CElement*NextElem, int X, int Y);
	char LinkPrevElem(CElement*PrevElem, int X, int Y);
	TElementType ElementType();
	char DelNextElem(CElement*DelElem);
	char SaveElement(CElement**TabElem, int NumOfElem, FILE*File, char Phase);
	char LoadElement(CElement**TabElem, int NumOfElem, FILE*File, char Phase);
	CConstBus(int X, int Y, int Type, SDL_Renderer *renderer);
	~CConstBus();
};

#endif
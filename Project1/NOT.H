#ifndef DefNot
#define DefNot

#include "element.h"

class CNot :public CElement
{
public:
	void DrawElem(SDL_Color Colour = { 0, 0, 0 });
	TOutput GetOutput(int AskElemNum, int MaxNum);
	void ClickElement(int X, int Y);
	char LinkPrevElem(CElement*PrevElem, int X, int Y);
	TElementType ElementType();
	SDL_Renderer *renderer = NULL;
	CNot(int X, int Y, SDL_Color Colour, SDL_Renderer *renderer);
};

#endif
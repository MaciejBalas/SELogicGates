#ifndef DefNor
#define DefNor

#include "element.h"

class CNor :public CElement
{
public:
	void DrawElem(SDL_Color Colour = { 0, 0, 0 });
	TOutput GetOutput(int AskElemNum, int MaxNum);
	void ClickElement(int X, int Y);
	TElementType ElementType();
	//SDL_Renderer *renderer = NULL;
	CNor(int X, int Y, SDL_Color Colour, SDL_Renderer *renderer );
};

#endif
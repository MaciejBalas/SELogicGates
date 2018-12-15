#ifndef DefOr
#define DefOr

#include "element.h"

class COr :public CElement
{
public:
	void DrawElem(SDL_Color Colour = { 0, 0, 0 });
	TOutput GetOutput(int AskElemNum, int MaxNum);
	void ClickElement();
	SDL_Renderer *renderer = NULL;
	TElementType ElementType();
	COr(int X, int Y, SDL_Color Colour, SDL_Renderer *renderer);
};

#endif
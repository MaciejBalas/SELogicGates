#ifndef DefNand
#define DefNand

#include "element.h"

class CNand :public CElement
{
public:
	void passOnRenderer();
	void DrawElem(SDL_Color Colour = { 0, 0, 0 });
	TOutput GetOutput(int AskElemNum, int MaxNum);
	void ClickElement(int X, int Y);
	TElementType ElementType();
	//SDL_Renderer *renderer = NULL;
	CNand(int X, int Y, SDL_Color Colour, SDL_Renderer *renderer);
};

#endif
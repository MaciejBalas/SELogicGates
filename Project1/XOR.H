#ifndef DefXor
#define DefXor

#include "element.h"

class CXor :public CElement
{
public:
	void DrawElem(SDL_Color Colour = { 0, 0, 0 });
	TOutput GetOutput(int AskElemNum, int MaxNum);
	void ClickElement(int X, int Y);
	//SDL_Renderer *renderer = NULL;
	TElementType ElementType();
	CXor(int X, int Y, SDL_Color Colour, SDL_Renderer *renderer);
};

#endif
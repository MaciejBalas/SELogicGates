#ifndef DefOutput
#define DefOutput

#include "element.h"

class COutput :public CElement
{
	//SDL_Renderer *renderer = NULL;
public:
	void passOnRenderer();
	void DrawElem(SDL_Color Colour = { 0,0,0 });
	TOutput GetOutput(int AskElemNum, int MaxNum);
	void ClickElement(int X, int Y);
	char LinkNextElem(CElement*NextElem, int X, int Y);
	TElementType ElementType();
	int IsOnBoard();
	COutput(int X, int Y, SDL_Renderer *renderer, SDL_Color Colour = { 0,0,0 });
};

#endif
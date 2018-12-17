#ifndef DefAnd
#define DefAnd

#include "element.h"

class CAnd :public CElement
{
public:
	void passOnRenderer();
	void DrawElem(SDL_Color Colour = { 0, 0, 0 });
	TOutput GetOutput(int AskElemNum, int MaxNum);
	void ClickElement(int X, int Y);
	TElementType ElementType();
	//SDL_Renderer *renderer = NULL;
	CAnd(int X, int Y, SDL_Color FrameColour, SDL_Renderer *renderer);
};

#endif
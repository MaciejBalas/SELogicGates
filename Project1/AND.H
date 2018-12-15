#ifndef DefAnd
#define DefAnd

#include "element.h"

class CAnd :public CElement
{
public:
	void DrawElem(SDL_Color Colour = { 0, 0, 0 });
	TOutput GetOutput(int AskElemNum, int MaxNum);
	void ClickElement();
	TElementType ElementType();
	SDL_Renderer *renderer = NULL;
	CAnd(int X, int Y, SDL_Color FrameColour, SDL_Renderer *renderer);
};

#endif
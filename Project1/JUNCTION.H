#ifndef DefJunction
#define DefJunction

#include "element.h"

class CJunction:public CElement
{
 public:
	 SDL_Renderer *renderer = NULL;
	char Move(int X,int Y,CElement**TabElem,int NumOfElem);
	void DrawElem(SDL_Color Colour = { 0,0,0 });
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void ClickElement(int X, int Y);
	char LinkNextElem(CElement*NextElem,int X,int Y);
	char LinkPrevElem(CElement*PrevElem,int X,int Y);
	TElementType ElementType();
	CJunction(int X,int Y,  SDL_Renderer *renderer, SDL_Color Colour = { 0,0,0 });
	char DelNextElem(CElement*DelElem);
	int DeleteConnections(CElement**TabElem,int NumOfElem,char Main=1);
	void draw_circle(SDL_Point center, int radius, SDL_Color color);
};

#endif
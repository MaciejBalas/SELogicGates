#ifndef DefNot
#define DefNot

#include "element.h"

class CNot:public CElement
{
 public:
	void DrawElem(int Colour=0);
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void ClickElement();
	char LinkPrevElem(CElement*PrevElem,int X,int Y);
	TElementType ElementType();
	CNot(int X,int Y,int Colour=0);
};

#endif
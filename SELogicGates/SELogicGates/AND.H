#ifndef DefAnd
#define DefAnd

#include "element.h"

class CAnd:public CElement
{
 public:
	void DrawElem(int Colour=0);
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void ClickElement();
	TElementType ElementType();
	CAnd(int X,int Y,int Colour=0);
};

#endif
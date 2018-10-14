#ifndef DefOr
#define DefOr

#include "element.h"

class COr:public CElement
{
 public:
	void DrawElem(int Colour=0);
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void ClickElement();
	TElementType ElementType();
	COr(int X,int Y,int Colour=0);
};

#endif
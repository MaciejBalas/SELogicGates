#ifndef DefNand
#define DefNand

#include "element.h"

class CNand:public CElement
{
 public:
	void DrawElem(int Colour=0);
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void ClickElement();
	TElementType ElementType();
	CNand(int X,int Y,int Colour=0);
};

#endif
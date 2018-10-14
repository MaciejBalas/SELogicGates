#ifndef DefXor
#define DefXor

#include "element.h"

class CXor:public CElement
{
 public:
	void DrawElem(int Colour=0);
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void ClickElement();
	TElementType ElementType();
	CXor(int X,int Y,int Colour=0);
};

#endif
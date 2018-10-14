#ifndef DefOutput
#define DefOutput

#include "element.h"

class COutput:public CElement
{
 public:
	void DrawElem(int Colour=0);
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void ClickElement();
	char LinkNextElem(CElement*NextElem,int X,int Y);
	TElementType ElementType();
	int IsOnBoard();
	COutput(int X,int Y,int Colour=0);
};

#endif
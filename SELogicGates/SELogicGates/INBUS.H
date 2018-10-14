#ifndef DefInBus
#define DefInBus

#include "gate.h"
#include "menubut.h"
#include "element.h"
#include "junction.h"

class CInBus:public CElement
{
	CMenuButton*Button[2];
	char Name;
	enum {true,false}Visible;
	int JunctionNum;
	CJunction*TabJunction[MaxBusJunctionNum];
 public:
	void DrawElem(int Colour=0);
	TOutput GetOutput(int AskElemNum,int MaxNum) ;
	void Change();
	void ClickElement();
	char LinkNextElem(CElement*NextElem,int X,int Y);
	char LinkPrevElem(CElement*PrevElem,int X,int Y);
	TElementType ElementType();
	char DelNextElem(CElement*DelElem);
	char SaveElement(CElement**TabElem,int NumOfElem,FILE*File,char Phase);
	char LoadElement(CElement**TabElem,int NumOfElem,FILE*File,char Phase);
	CInBus(int X,int Y,char Name);
	~CInBus();
};

#endif
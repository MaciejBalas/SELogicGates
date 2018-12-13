#ifndef DefElement
#define DefElement
#include <stdio.h>
class CElement
{
protected:
	int X1;
	int Y1;
	int X2;
	int Y2;
	int OutNum;
	int InNum;
	enum TOutput { low = 0, high = 1, error = -1 };
	enum TMovable { yes, no };
	TOutput Output;
	TMovable Movable;
	CElement*TabNextElem[1];
	CElement*TabPrevElem[2];
	int IsAreaFree(CElement**TabElem, int NumOfElem);
public:
	virtual void DrawElem(int Colour = 0) = 0;
	virtual TOutput GetOutput(int AskElemNum, int MaxNum) = 0;
	virtual char Move(int X, int Y, CElement**TabElem, int NumOfElem);
	virtual void MoveBeg(int X, int Y);
	virtual void MoveEnd(int X, int Y);
	virtual int IsOnBoard();
	virtual int IsYourArea(int X, int Y);
	char IsElemPrev(CElement*Element);
	virtual char IsElemNext(CElement*Element);
	int GetXCorner(char Right = 0);
	int GetYCorner(char Down = 0);
	virtual void ClickElement() = 0;
	virtual TElementType ElementType() = 0;
	virtual char LinkNextElem(CElement*NextElem, int X, int Y);
	virtual char LinkPrevElem(CElement*PrevElem, int X, int Y);
	virtual char DelNextElem(CElement*DelElem);
	virtual char DelPrevElem(CElement*DelElem);
	virtual char Autoformat(CElement**TabElem, int NumOfElem);
	virtual int DeleteConnections(CElement**TabElem, int NumOfElem, char Main = 1);
	virtual char SaveElement(CElement**TabElem, int NumOfElem,
		FILE*File, char Phase);
	virtual char LoadElement(CElement**TabElem, int NumOfElem,
		FILE*File, char Phase);
	virtual ~CElement();
};
#endif
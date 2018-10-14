#include "and.h"

CAnd::CAnd(int X,int Y,int Colour)
{
	X1=X;
	Y1=Y;
	X2=X+25;
	Y2=Y+25;
	InNum=2;
	OutNum=1;
	for(int i=0;i<InNum;i++)
		TabPrevElem[i]=NULL;
	for(i=0;i<OutNum;i++)
		TabNextElem[i]=NULL;
	Output=error;
	Movable=yes;
}

void CAnd::DrawElem(int Colour)
{
	if(Colour==0)
	{
		switch(Output)
		{
			case low:Colour=LowColour;break;
			case high:Colour=HighColour;break;
			case error:Colour=ErrorColour;break;
		}
	}
	setcolor(Colour);
	line(X1+8,Y1+7,X1+8,Y1+22);//pionowa linia
	line(X1+3,Y1+12,X1+8,Y1+12);//wej˜cie g¢rne
	line(X1+3,Y1+17,X1+8,Y1+17);//wej˜cie dolne
	arc(X1+8,Y1+14,270,90,8);//ˆuk
	line(X1+17,Y1+14,X1+24,Y1+14);//wyj˜cie
}

TOutput CAnd::GetOutput(int AskElemNum,int MaxNum)
{
	if(AskElemNum==MaxNum) return Output;
		//rekurencja wpadˆa w p©tl© sprz©¾enia zwrotnego
	if(Output==error) Output=high;
	TOutput Value=high;
	for(int i=0;i<InNum;i++)
	{
		if(TabPrevElem[i]==NULL)
			Output=error;
		else
		{
			TOutput TmpValue=TabPrevElem[i]->GetOutput(AskElemNum+1,MaxNum);
			if(TmpValue==error)
				Output=error;
			else Value*=TmpValue;
		}
	}
	if(Output!=error) Output=Value;
	return Output;
}

TElementType CAnd::ElementType()
{
	return and;
}

void CAnd::ClickElement()
{}

#include "junction.h"
#include "CONSTANTS.h" 

CJunction::CJunction(int X,int Y, SDL_Renderer *renderer, SDL_Color Colour)
{
	X1=X2=X;
	Y1=Y2=Y;
	InNum=1;
	OutNum=1;
	int i;
	for( i=0;i<InNum;i++)
		TabPrevElem[i]=NULL;
	for(i=0;i<OutNum;i++)
		TabNextElem[i]=NULL;
	Output=error;
	Movable=yes;
	this->renderer = renderer;
}

void CJunction::DrawElem(SDL_Color Colour)
{
	if (Colour.r == 0 && Colour.g == 0 && Colour.b == 0) {
		switch (Output)
		{
		case low:Colour = LowColour; break;
		case high:Colour = HighColour; break;
		case error:Colour = ErrorColour; break;
		}
	}
	//setcolor(Colour);
	//setfillstyle(1,Colour);
	//pieslice(X1,Y1,0,360,2);
	draw_circle(renderer,SDL_Point{ X1, Y1 }, 2, Colour);
}


TOutput CJunction::GetOutput(int AskElemNum,int MaxNum)
{
	Output=TabPrevElem[0]->GetOutput(0,0);
	return Output;
}

char CJunction::Move(int X,int Y,CElement**TabElem,int NumOfElem)
{
	int X1Prev=X1;
	int Y1Prev=Y1;
	int X2Prev=X2;
	int Y2Prev=Y2;
	for(int i=0;i<OutNum;i++)
		if(TabNextElem[i]!=NULL)
		{
			int TmpX=TabNextElem[i]->GetXCorner();
			int TmpY=TabNextElem[i]->GetYCorner();
			if(TabNextElem[i]->IsOnBoard())
				TabNextElem[i]->DrawElem(BackgroundColour);
					//poˆ¥czenie zniknie, je¾eli byˆo narysowane
				TabNextElem[i]->MoveBeg(X,Y);
			if(!TabNextElem[i]->Autoformat(TabElem,NumOfElem)) return 0;
		}
	X2=X2-X1+X;
	Y2=Y2-Y1+Y;
	X1=X;
	Y1=Y;
	return 1;
}

TElementType CJunction::ElementType()
{
	return _junction;
}

void CJunction::ClickElement(int X, int Y)
{}

char CJunction::LinkNextElem(CElement*NextElem,int X,int Y)
{
	if(NextElem->ElementType()!=_wire) return 0;
		//w©zeˆ mo¾e by† poˆ¥czony tylko z drutem
	char OK=0;
	int i;
	for(i=0;i<OutNum;i++)
		if(TabNextElem[i]==NULL)
		{
			OK=1;
			break;
		}
	if(OK==0) return 0;//istniej¥ ju¾ elementy nast©pny
	TabNextElem[i]=NextElem;
	NextElem->MoveBeg(X1,Y1);
	return 1;
}

char CJunction::LinkPrevElem(CElement*PrevElem,int X,int Y)
{
	if(TabPrevElem[0]!=NULL) return 0;
	TabPrevElem[0]=PrevElem;
	return 1;
}

char CJunction::DelNextElem(CElement*DelElem)
{
	for(int i=0;i<OutNum;i++)
		if(TabNextElem[i]==DelElem)
		{
			TabNextElem[i]=NULL;
			for(int j=0;j<OutNum;j++)
				if(TabNextElem[j]!=NULL) return 1;//element zostaˆ usuni©ty,
																					//ale nie jest ostatni
			return 2;//nie ma ju¾ wi©cej element¢w nast©pnych
		}
	return 0;
}

int CJunction::DeleteConnections(CElement**TabElem,int NumOfElem,char Main)
{
	int DelElemNum=0;//w©zeˆ nie jest zawarty w generalnej tabeli element¢w
	for(int i=0;i<OutNum;i++)
		if(TabNextElem[i]!=NULL)
		{
			DelElemNum+=TabNextElem[i]->DeleteConnections(TabElem,NumOfElem,0);
			delete TabNextElem[i];
			TabNextElem[i]=NULL;
		}
	this->DrawElem(BackgroundColour);//znikni©cie elementu
	return DelElemNum;
}



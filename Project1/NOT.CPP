#include "not.h"
//#include "gate.h"

CNot::CNot(int X, int Y, SDL_Color Colour, SDL_Renderer *renderer)
{
	X1 = X;
	Y1 = Y;
	X2 = X + 25;
	Y2 = Y + 25;
	InNum = 1;
	OutNum = 1;
	for (int i = 0; i<InNum; i++)
		TabPrevElem[i] = NULL;
	for (int i = 0; i<OutNum; i++)
		TabNextElem[i] = NULL;
	Output = error;
	Movable = yes;
	this->renderer = renderer;
}

void CNot::DrawElem(SDL_Color Colour)
{
	if (Colour.r == 0 && Colour.g == 0 && Colour.b == 0)
	{
		switch (Output)
		{
		case low:Colour = LowColour; break;
		case high:Colour = HighColour; break;
		case error:Colour = ErrorColour; break;
		}
	}
	SDL_SetRenderDrawColor(renderer, Colour.r, Colour.g, Colour.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, X1 + 8, Y1 + 7, X1 + 8, Y1 + 22);//linia z lewej
	SDL_RenderDrawLine(renderer, X1 + 3, Y1 + 14, X1 + 8, Y1 + 14);//wej˜cie
	SDL_RenderDrawLine(renderer, X1 + 8, Y1 + 7, X1 + 17, Y1 + 14);//linia z g¢ry
	SDL_RenderDrawLine(renderer, X1 + 8, Y1 + 22, X1 + 17, Y1 + 14);//linia z doˆu
	draw_circle(renderer, SDL_Point{ X1 + 19, Y1 + 14 }, 2,Colour);//negacja
	SDL_RenderDrawLine(renderer, X1 + 21, Y1 + 14, X1 + 24, Y1 + 14);//wyj˜cie
}

TOutput CNot::GetOutput(int AskElemNum, int MaxNum)
{
	if (AskElemNum == MaxNum) return Output;
	//rekurencja wpadˆa w p©tl© sprz©¾enia zwrotnego
	if (TabPrevElem[0] == NULL)//bramka jednowej˜ciowa
	{
		Output = error;
		return Output;
	}
	TOutput TmpValue = TabPrevElem[0]->GetOutput(AskElemNum + 1, MaxNum);
	if (TmpValue == high) Output = low;
	else if (TmpValue == low) Output = high;
	else Output = error;
	return Output;
}

TElementType CNot::ElementType()
{
	return _not;
}

void CNot::ClickElement(int X, int Y)
{}

char CNot::LinkPrevElem(CElement*PrevElem, int X, int Y)
{
	if (PrevElem->ElementType() != _wire) return 0;
	//bramka mo¾e by† poˆ¥czona tylko z drutem
	X -= X1;
	Y -= Y1;//zmienne X i Y okre˜laj¥ wzgl©dne poˆo¾enie
	if (TabPrevElem[0] != NULL) return 0;
	TabPrevElem[0] = PrevElem;
	PrevElem->MoveEnd(X1 + 3, Y1 + 14);
	return 1;
}

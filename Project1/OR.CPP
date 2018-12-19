#include "or.h"
#include <iostream>
//#include "gate.h"

COr::COr(int X, int Y, SDL_Color Colour, SDL_Renderer *renderer)
{
	X1 = X;
	Y1 = Y;
	X2 = X + 25;
	Y2 = Y + 25;
	InNum = 2;
	OutNum = 1;
	for (int i = 0; i<InNum; i++)
		TabPrevElem[i] = NULL;
	for (int i = 0; i<OutNum; i++)
		TabNextElem[i] = NULL;
	Output = error;
	Movable = yes;
	this->renderer = renderer;
}
void COr::passOnRenderer() {

}
void COr::DrawElem(SDL_Color Colour)
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
	draw_arc(renderer, X1 + 8, Y1 + 14, 10, 9, Colour);//ˆuk z lewej
	SDL_RenderDrawLine(renderer, X1 + 3, Y1 + 12, X1 + 10, Y1 + 12);//we g.
	SDL_RenderDrawLine(renderer, X1 + 3, Y1 + 17, X1 + 10, Y1 + 17);//we d.
	draw_arc(renderer, X1 + 6, Y1 + 14, 5, 10, Colour);//ˆuk z prawej
	SDL_RenderDrawLine(renderer, X1 + 21, Y1 + 14, X1 + 24, Y1 + 14);//wyj˜cie
}

TOutput COr::GetOutput(int AskElemNum, int MaxNum)
{
	if (AskElemNum == MaxNum) return Output;
	//rekurencja wpadˆa w p©tl© sprz©¾enia zwrotnego
	if (Output == error)	Output = low;//warto˜† wyj˜ciowa
	TOutput Value = low;
	for (int i = 0; i<InNum; i++)
	{
		if (TabPrevElem[i] == NULL)
			Output = error;
		else
		{
			TOutput TmpValue = TabPrevElem[i]->GetOutput(AskElemNum + 1, MaxNum);
			if (TmpValue == error)
				Output = error;
			//else Value += TmpValue;
			//if (Value>1) Value = 1;
			else if (Value || TmpValue){
				Value = high;
			}
			else{
				Value = low;
			}
		}
	}
	if (Output != error) Output = Value;

	std::cout << "OR gate output is " << Output << std::endl;
	return Output;
}

TElementType COr::ElementType()
{
	return _or;
}

void COr::ClickElement(int X, int Y)
{}

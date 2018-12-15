#include "nand.h"
//#include "gate.h"

CNand::CNand(int X, int Y, SDL_Color Colour, SDL_Renderer *renderer)
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

void CNand::DrawElem(SDL_Color Colour)
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
	SDL_RenderDrawLine(renderer,X1 + 8, Y1 + 7, X1 + 8, Y1 + 22);
	SDL_RenderDrawLine(renderer, X1 + 3, Y1 + 12, X1 + 8, Y1 + 12);
	SDL_RenderDrawLine(renderer, X1 + 3, Y1 + 17, X1 + 8, Y1 + 17);
	draw_arc(renderer, X1 + 8, Y1 + 14, 270, 90, Colour);
	draw_circle(renderer, SDL_Point{ X1 + 18, Y1 + 14 }, 2, Colour);
	SDL_RenderDrawLine(renderer, X1 + 21, Y1 + 14, X1 + 24, Y1 + 14);
}

TOutput CNand::GetOutput(int AskElemNum, int MaxNum)
{
	if (AskElemNum == MaxNum) return Output;
	//rekurencja wpadˆa w p©tl© sprz©¾enia zwrotnego
	if (Output == error) Output = high;
	TOutput Value = high;
	for (int i = 0; i<InNum; i++)
	{
		if (TabPrevElem[i] == NULL)
			Output = error;
		else
		{
			TOutput TmpValue = TabPrevElem[i]->GetOutput(AskElemNum + 1, MaxNum);
			if (TmpValue == error)
				Output = error;
			//else Value *= TmpValue;
			else if (Value && TmpValue){
				Value = high;
			}
			else { Value = low; }
		}
	}
	if (Value == low) Value = high;
	else Value = low;
	if (Output != error) Output = Value;
	return Output;
}

TElementType CNand::ElementType()
{
	return _nand;
}

void CNand::ClickElement(int X, int Y)
{}

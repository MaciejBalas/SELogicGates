#include "modebut.h"
//#include "gate.h"
#include "and.h"
#include "or.h"
#include "not.h"
#include "nand.h"
#include "nor.h"
#include "xor.h"
#include "output.h"
#include "wire.h"

CModeButton::CModeButton(TElementType ButtonType, int X1, int Y1, int X2, int Y2,SDL_Renderer *renderer)
{
	this->renderer = renderer;
	this->X1 = X1;
	this->X2 = X2;
	this->Y1 = Y1;
	this->Y2 = Y2;
	DrawingColour = SDL_Color{0,0,0};
	ButtonColour = SDL_Color{ 255, 0, 0 };
	Insert = false;
	Active = true;
	ButtonElement = NULL;
	switch (ButtonType)
	{
	case _and:ButtonElement = new CAnd(X1, Y1, DrawingColour,renderer); break;
	case _or:ButtonElement = new COr(X1, Y1, DrawingColour, renderer); break;
	case _not:ButtonElement = new CNot(X1, Y1, DrawingColour, renderer); break;
	case _nor:ButtonElement = new CNor(X1, Y1, DrawingColour, renderer); break;
	case _nand:ButtonElement = new CNand(X1, Y1, DrawingColour, renderer); break;
	case _xor:ButtonElement = new CXor(X1, Y1, DrawingColour, renderer); break;
	case _output:ButtonElement = new COutput(X1, Y1, DrawingColour); break;
	case _wire:ButtonElement = new CWire(X1, Y1, DrawingColour); break;
	};
}

CModeButton::~CModeButton()
{
	delete ButtonElement;
}

void CModeButton::DrawButton()
{

	SDL_SetRenderDrawColor(renderer, DrawingColour.r, DrawingColour.g, DrawingColour.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, X1, Y1, X2, Y1);
	SDL_RenderDrawLine(renderer, X2, Y1, X2, Y2);
	SDL_RenderDrawLine(renderer, X2, Y2, X1, Y2);
	SDL_RenderDrawLine(renderer, X1, Y2, X1, Y1);
	//setfillstyle(1, ButtonColour);
	//bar(X1 + 1, Y1 + 1, X2 - 1, Y2 - 1);
	SDL_Rect rekt = { X1 + 1, Y1 + 1, X2 - 1 - X1 + 1, Y2 - 1 - Y1 + 1 };
	SDL_RenderDrawRect(renderer, &rekt);
	ButtonElement->DrawElem(DrawingColour);
}

void CModeButton::ChangeText(char*Text)
{}

int CModeButton::ClickButton()
{
	if (Active == true) return 1;
	return 0;
}

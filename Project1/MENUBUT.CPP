#include "menubut.h"
#include <stdio.h>
#include "SDL.h"



CMenuButton::CMenuButton(const char text[], int X1,int Y1,int X2,int Y2, SDL_Renderer *renderer)
{

	Insert=false;
	Active=true;
	this->X1=X1;
	this->X2=X2;
	this->Y1=Y1;
	this->Y2=Y2;
	ButtonText=NULL;
	//ButtonText=strdup(text);

	this->renderer = renderer;
	drawRect.x = X1;
	drawRect.y = Y1;
	drawRect.w = X2 - X1;
	drawRect.h = Y2 - Y1;
	this->renderer = renderer;

};

CMenuButton::~CMenuButton()
{
	delete ButtonText;
}

void CMenuButton::DrawButton()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &drawRect);
	SDL_RenderPresent(renderer);

}

void CMenuButton::ChangeText(char*Text)
{
	delete ButtonText;
	ButtonText=NULL;
//	ButtonText=strdup(Text);
	this->DrawButton();
}

int CMenuButton::ClickButton()
{

	return 0;//nic nie robi†
}

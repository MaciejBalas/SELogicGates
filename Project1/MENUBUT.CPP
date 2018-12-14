#include "menubut.h"
#include <stdio.h>
#include "SDL.h"
#include "SDL_ttf.h"



CMenuButton::CMenuButton(const char text[], int X1,int Y1,int X2,int Y2, SDL_Renderer *renderer)
{

	Insert=false;
	Active=true;
	this->X1=X1;
	this->X2=X2;
	this->Y1=Y1;
	this->Y2=Y2;
	ButtonText=NULL;
	this->ButtonText = text;

	this->renderer = renderer;
	drawRect.x = X1;
	drawRect.y = Y1;
	drawRect.w = X2 - X1;
	drawRect.h = Y2 - Y1;

};

CMenuButton::~CMenuButton()
{
	delete ButtonText;
}

void CMenuButton::DrawButton()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &drawRect);
	SDL_RenderPresent(renderer);

	TTF_Font* font = TTF_OpenFont("arial.ttf", 10); //this opens a font style and sets a size
	SDL_Color White = { 0, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, ButtonText, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
	int texW, texH;
	SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
	SDL_Rect Message_rect;
	Message_rect.x = this->X1+15;
	Message_rect.y = this->Y1+3;
	Message_rect.w = texW;
	Message_rect.h = texH;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
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

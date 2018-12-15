#include "output.h"

COutput::COutput(int X, int Y, SDL_Renderer *renderer, SDL_Color Colour)
{
	X1 = X;
	Y1 = Y;
	X2 = X + 25;
	Y2 = Y + 25;
	InNum = 1;
	OutNum = 0;
	TabPrevElem[0] = NULL;
	Output = high;
	Movable = yes;
	this->renderer = renderer;
}

void COutput::DrawElem(SDL_Color Colour)
{
	char Text1[2] = "?";
	TTF_Font* font = TTF_OpenFont("arial.ttf", 10); //this opens a font style and sets a size
	SDL_Color White = { 0, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, Text1, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
	int texW, texH;
	SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
	SDL_Rect Message_rect;
	Message_rect.x = X1 + 17;
	Message_rect.y = Y1 + 5;
	Message_rect.w = texW;
	Message_rect.h = texH;
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
	
	char Text2[2] = "0";
	SDL_Surface* surfaceMessage1 = TTF_RenderText_Solid(font, Text2, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message1 = SDL_CreateTextureFromSurface(renderer, surfaceMessage1); //now you can convert it into a texture
	int texW1, texH1;
	SDL_QueryTexture(Message1, NULL, NULL, &texW1, &texH1);
	SDL_RenderCopy(renderer, Message1, NULL, &Message_rect);

	char Text3[2] = "1";
	SDL_Surface* surfaceMessage3 = TTF_RenderText_Solid(font, Text3, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message3 = SDL_CreateTextureFromSurface(renderer, surfaceMessage3); //now you can convert it into a texture
	int texW3, texH3;
	SDL_QueryTexture(Message3, NULL, NULL, &texW3, &texH3);
	SDL_RenderCopy(renderer, Message3, NULL, &Message_rect);

	
	//zmazanie napisu
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
	SDL_RenderDrawLine(renderer, X1+1, Y1+8, X1 + 10, Y1 + 13);
	SDL_RenderDrawLine(renderer, X1 + 10, Y1 + 13, X1 + 1, Y1 + 18);
	char Text[2];
	switch (Output)
	{
	case low:Text[0] = '0'; break;
	case high:Text[0] = '1'; break;
	case error:Text[0] = '?'; break;
	}
	Text[1] = '\0';

	SDL_Surface* surfaceMessage4 = TTF_RenderText_Solid(font, Text, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message4 = SDL_CreateTextureFromSurface(renderer, surfaceMessage4); //now you can convert it into a texture
	int texW4, texH4;
	SDL_QueryTexture(Message4, NULL, NULL, &texW4, &texH4);
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_RenderPresent(renderer);
}

TOutput COutput::GetOutput(int AskElemNum, int MaxNum)
{
	if (TabPrevElem[0] == NULL) Output = error;
	else Output = TabPrevElem[0]->GetOutput(AskElemNum + 1, MaxNum);
	return Output;
}

TElementType COutput::ElementType()
{
	return _output;
}

void COutput::ClickElement()
{}

int COutput::IsOnBoard()
{
	if (X1<611 || Y1<61 || Y2>440) return 0;
	X1 = 611;
	X2 = X1 + 25;//autoformatowanie
	return 1;
}

char COutput::LinkNextElem(CElement*NextElem, int X, int Y)
{
	return 0;
}

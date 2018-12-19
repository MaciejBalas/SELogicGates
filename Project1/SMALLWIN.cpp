#define _CRT_SECURE_NO_WARNINGS
#include "SMALLWIN.h"
#include <string.h>
#include "SDL.h"
#include "SDL_ttf.h"

CSmallWindow::CSmallWindow()
{
}


CSmallWindow::~CSmallWindow()
{
}

CSmallWindow::CSmallWindow(int X1, int Y1, int X2, int Y2, char*HeadingText, char**ConstText,
	char Reading, int ButtonNum, SDL_Renderer * renderer, char*FirstButtonText,
	char*SecondButtonText)
{
	Active = 1;
	this->X1 = X1;
	this->Y1 = Y1;
	this->HeadingText = HeadingText;
	int i;
	this->renderer = renderer;
/*	for (i = 0; i<4; i++)
		if (ConstText[i] == nullptr) break;
		else this->ConstText[i] = ConstText[i];
		LinesNum = i;
		if (LinesNum>4) LinesNum = 4;
		if (X2 == 0)	this->X2 = X1 + 200;
		else this->X2 = X2;
		if (Y2 == 0)	this->Y2 = Y1 + LinesNum * 15 + 80;
		else this->Y2 = Y2;
		if (Reading) this->Y2 += 20;
		ReadText = nullptr;
		this->Reading = Reading;
		this->ButtonNum = ButtonNum;
		char*Text = nullptr;
		if (FirstButtonText == nullptr)
			Text = _strdup("OK");
		else
			Text = _strdup(FirstButtonText);
		if (ButtonNum == 2)
		{
			TabBut[0] = new CMenuButton(Text, this->X1 + 15, this->Y2 - 30,
				(int)((this->X1 + this->X2) / 2 - 10), this->Y2 - 15, renderer);
			delete Text;
			if (SecondButtonText == NULL)
				Text = _strdup("Cancel");
			else
				Text = _strdup(SecondButtonText);
			TabBut[1] = new CMenuButton(Text, (int)((this->X1 + this->X2) / 2 + 10),
				this->Y2 - 30, this->X2 - 15, this->Y2 - 15, renderer);
		}
		else
			TabBut[0] = new CMenuButton(Text, this->X1 + 15, this->Y2 - 30,
				this->X2 - 15, this->Y2 - 15, renderer);
		delete Text;*/
}
/*
CSmallWindow::~CSmallWindow()
{
	if (ReadText != NULL)
		delete ReadText;
	for (int i = 0; i < ButtonNum; i++)
		delete TabBut[i];
}*/

/*char CSmallWindow::Work()
{
	struct REGPACK reg;
	DrawSmallWin();
	reg.r_ax = 0x1;
	intr(0x33, &reg);//wˆ¥czenie
	if (kbhit())
		do
		{
			getch();
		} while (kbhit());
		do
		{
			if (kbhit())
				Read();
			reg.r_ax = 0x3;
			intr(0x33, &reg);
			if (reg.r_bx & 1) React(reg.r_cx, reg.r_dx);
		} while (Active);
		reg.r_ax = 0x2;
		intr(0x33, &reg);//wyˆ¥czenie
		return Result;
}*/

/*void CSmallWindow::React(int X, int Y)
{
	struct REGPACK reg;
	CheckButtons(X, Y);
	do
	{
		reg.r_ax = 0x3;
		intr(0x33, &reg);
	} while (reg.r_bx & 1);//blokada-nic si© nie dzieje, gdy klawisz myszy
										//zostaˆ wci˜ni©ty na pustym polu
}*/


/*void CSmallWindow::Read()
{
	REGPACK reg;
	char TmpText[15];
	int Length;
	if (Reading)
	{
		Length = strlen(ReadText);
		strcpy(TmpText, ReadText);
	}
	else Length = 0;
	TmpText[Length] = getch();
	if ((int)TmpText[Length] == Enter)
	{
		if (Reading&&ReadText == NULL) return;
		Result = 1;
		Active = 0;
		return;//naci˜ni©ty przycisk OK
	}
	if ((int)TmpText[Length] == Esc)
	{
		Result = 0;
		Active = 0;
		return;//naci˜ni©ty przycisk Cancel
	}
	if (!Reading) return;//dalej jest obsluga pola do wprowadzania napisu
	reg.r_ax = 0x2;
	intr(0x33, &reg);//schowanie kursora
	setfillstyle(1, BackgroundColour);
	bar(X1 + 50, Y2 - 55, X1 + 150, Y2 - 40);//pole do odczytu
	TmpText[Length + 1] = '\x0';
	if ((int)TmpText[Length] == BackSpace && Length > 0)
	{
		TmpText[Length - 1] = '\x0';
		Length -= 2;
	}//zmazanie ostatniego znaku
	else
	{
		if (Length >= 8)
		{
			TmpText[Length] = '\x0';
			Length--;
		}
		else
			if (!(((int)TmpText[Length] >= (int)'0' && (int)TmpText[Length] <= '9') ||
				((int)TmpText[Length] >= (int)'A' && (int)TmpText[Length] <= 'Z') ||
				((int)TmpText[Length] >= (int)'a' && (int)TmpText[Length] <= 'z')))
			{
				TmpText[Length] = '\x0';
				Length--;
			}
	}
	outtextxy(X1 + 55, Y2 - 50, TmpText);
	reg.r_ax = 0x1;
	intr(0x33, &reg);//pokazanie kursora
	Length++;
	if (ReadText != NULL) delete ReadText;
	if (strlen(TmpText) == 0)
	{
		ReadText = NULL;
		return;
	}
	ReadText = strdup(TmpText);
}*/


int CSmallWindow::GetReadTextLength()
{
	return strlen(ReadText) + 1;
}

char CSmallWindow::GetReadText(char*ReadText)
{
	if (ReadText == NULL) return 0;
	strcpy(ReadText, this->ReadText);
	return 1;
}

void CSmallWindow::CheckButtons(int X, int Y)
{
	for (int i = 0; i < ButtonNum; i++)
		if (TabBut[i]->IsYourArea(X, Y))
			if (TabBut[i]->ClickButton())
				Action(i);
}

void CSmallWindow::DrawSmallWin()
{
	SDL_CreateWindow("smallwin", 0, 0, 320, 320, 0);
	SDL_SetRenderDrawColor(renderer, 128, 128, 128, SDL_ALPHA_OPAQUE);
	TTF_Font* font = TTF_OpenFont("arial.ttf", 10); //this opens a font style and sets a size
	SDL_Color White = { 255, 255, 255 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, HeadingText, White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture
	SDL_RenderDrawLine(renderer,X1, Y1, X1, Y2);
	SDL_RenderDrawLine(renderer,X1, Y2, X2, Y2);
	SDL_RenderDrawLine(renderer, X2, Y2, X2, Y1);
	SDL_RenderDrawLine(renderer, X2, Y1, X1, Y1);
	SDL_RenderFillRect(renderer, &Bar(X1, Y1, X2, Y2));
/*	no idea what is happening here
bar(X1 + 1, Y1 + 1, X2 - 1, Y1 + 20);
	setcolor(HeadingTextColour);
	outtextxy((int)(X1 + X2) / 2 - (strlen(HeadingText) / 2) * 9, Y1 + 8, HeadingText);
	setfillstyle(1, FrameColour);
	bar(X1 + 1, Y1 + 21, X2 - 1, Y2 - 1);//szare pole
	setfillstyle(1, CustomTextColour);
	setcolor(CustomTextColour);*/

	/*
	for (int i = 0; i < LinesNum; i++)
	{
		char*Text = ConstText[i];
		outtextxy(X1 + 15, Y1 + 30 + i * 15, Text);
	}
	if (Reading)
	{
		setfillstyle(1, BackgroundColour);
		bar(X1 + 50, Y2 - 55, X1 + 150, Y2 - 40);//pole do odczytu
		setcolor(LineColour);
		line(X1 + 49, Y2 - 56, X1 + 49, Y2 - 39);
		line(X1 + 49, Y2 - 39, X1 + 151, Y2 - 39);
		line(X1 + 151, Y2 - 39, X1 + 151, Y2 - 56);
		line(X1 + 151, Y2 - 56, X1 + 49, Y2 - 56);
	}
	*/
	for (int i = 0; i < ButtonNum; i++)
		TabBut[i]->DrawButton();
}

void CSmallWindow::Action(int ActNum)
{
	switch (ActNum)
	{
	case 0:if (ReadText == NULL && Reading) return;
		Result = 1; Active = 0; break;//naci˜ni©ty przycisk OK
	case 1:Result = 0; Active = 0; break;//naci˜ni©ty przycisk Cancel
	}
}
SDL_Rect CSmallWindow::Bar(int x1, int y1, int x2, int y2) {
	SDL_Rect bar;
	bar.x = x1;
	bar.y = y1;
	bar.w = x2 - x1;
	bar.h = y2 - y1;
	return bar;
}

#include "BUTTON.h"

CButton::CButton()
{
}


CButton::~CButton()
{
}

int CButton::IsYourArea(int X, int Y)
{
	if (X>X1&&X<X2&&Y>Y1&&Y<Y2) return 1;
	return 0;
}

void CButton::ChangeInsertMode(int TurnOff)
{
	//gdy zmienna TurnOff=1, to przycisk automatycznie jest puszczany
	//jest to zabezpieczenie przy szybkim "klikaniu" myszk¥
	if (Insert == false && TurnOff == 0)
	{
		Insert = true;
		DrawingColour = { 255, 0, 0 };  //12 red
	}
	else
	{
		Insert = false;
		DrawingColour = { 0, 255, 0 };  //16 green
	}
	DrawButton();
}

void CButton::SetActivity(bool Active)
{
	this->Active = Active;
	if (Active == true) DrawingColour = { 1, 1, 1 };
	else DrawingColour = { 0, 0, 255 }; //8 blue
	this->DrawButton();
}
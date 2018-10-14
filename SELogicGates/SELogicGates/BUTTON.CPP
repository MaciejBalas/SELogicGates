#include "button.h"
#include "gate.h"

CButton::~CButton()
{}

int CButton::IsYourArea(int X,int Y)
{
	if(X>X1&&X<X2&&Y>Y1&&Y<Y2) return 1;
	return 0;
}

void CButton::ChangeInsertMode(int TurnOff)
{
	//gdy zmienna TurnOff=1, to przycisk automatycznie jest puszczany
	//jest to zabezpieczenie przy szybkim "klikaniu" myszk¥
	if(Insert==false&&TurnOff==0)
	{
		Insert=true;
		DrawingColour=InsertTextColour;
	}
	else
	{
		Insert=false;
		DrawingColour=CustomTextColour;
	}
	DrawButton();
}

void CButton::SetActivity(TActive Active)
{
	this->Active=Active;
	if(Active==on) DrawingColour=16;
	else DrawingColour=8;
	this->DrawButton();
}

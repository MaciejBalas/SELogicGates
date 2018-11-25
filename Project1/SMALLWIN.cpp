#include "SMALLWIN.h"
#include <string.h>


CSmallWindow::CSmallWindow()
{
}


CSmallWindow::~CSmallWindow()
{
}

CSmallWindow::CSmallWindow(int X1, int Y1, int X2, int Y2, char*HeadingText,
	char**ConstText, char Reading, int ButtonNum,
	char*FirstButtonText, char*SecondButtonText)
{
	Active = 1;
	this->X1 = X1;
	this->Y1 = Y1;
	this->HeadingText = HeadingText;
	int i;
	for (i = 0; i<4; i++)
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
		/*if (ButtonNum == 2)
		{
			TabBut[0] = new CMenuButton(Text, this->X1 + 15, this->Y2 - 30,
				(int)((this->X1 + this->X2) / 2 - 10), this->Y2 - 15);
			delete Text;
			if (SecondButtonText == NULL)
				Text = strdup("Cancel");
			else
				Text = strdup(SecondButtonText);
			TabBut[1] = new CMenuButton(Text, (int)((this->X1 + this->X2) / 2 + 10),
				this->Y2 - 30, this->X2 - 15, this->Y2 - 15);
		}
		else
			TabBut[0] = new CMenuButton(Text, this->X1 + 15, this->Y2 - 30,
				this->X2 - 15, this->Y2 - 15);*/
		delete Text;
}
#ifndef DefButton
#define DefButton
#include "SDL.h"
class CButton
{
protected:
	int X1;
	int Y1;
	int X2;
	int Y2;
	int ButtonColour;
	SDL_Color DrawingColour;
	enum TInsert { _true, _false };
	enum TActive { off, on };
	TInsert Insert;
	TActive Active;
public:
	CButton();
	~CButton();
	virtual void DrawButton() = 0;
	void ChangeInsertMode(int TurnOff = 0);
	void ActiveMode(TActive Active);
	virtual void ChangeText(char*) = 0;
	int IsYourArea(int X, int Y);
	virtual int ClickButton() = 0;
	void SetActivity(TActive Active);
};
#endif

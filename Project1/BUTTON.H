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
	SDL_Color ButtonColour;
	SDL_Color DrawingColour;
	bool Insert;
	bool Active;
	SDL_Rect drawRect;

public:
	CButton();
	~CButton();
	virtual void DrawButton() = 0;
	void ChangeInsertMode(int TurnOff = 0);
	void ActiveMode(bool Active);
	virtual void ChangeText(char*) = 0;
	virtual void ChangeText(const char*) = 0;

	int IsYourArea(int X, int Y);
	virtual int ClickButton() = 0;
	void SetActivity(bool Active);
};
#endif

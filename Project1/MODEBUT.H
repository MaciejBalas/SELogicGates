#ifndef DefModeBut
#define DefModeBut

#include "button.h"
#include "element.h"

class CModeButton :public CButton
{
	CElement*ButtonElement;
public:
	void DrawButton();
	void ChangeText(char*);
	int ClickButton();
	void ChangeText(const char*);
	SDL_Renderer *renderer = NULL;
	CModeButton(TElementType ButtonType, int X1, int Y1, int X2, int Y2, SDL_Renderer *renderer);
	~CModeButton();
};

#endif
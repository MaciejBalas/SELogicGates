#ifndef SmallBut
#define SmallBut



#include "button.h"
#include <stdio.h>

class CSmallButton:public CButton
{
	const char*ButtonText;

	
 public:
	void DrawButton();
	void ChangeText(char*Text);
	int ClickButton();
	SDL_Renderer *renderer = NULL;
	CSmallButton(const char *text,int X1,int Y1,int X2,int Y2, SDL_Renderer *renderer);
	~CSmallButton();
};

#endif
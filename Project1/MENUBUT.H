#ifndef DefMenuBut
#define DefMenuBut



#include "button.h"
#include <stdio.h>

class CMenuButton:public CButton
{
	const char*ButtonText;
	
 public:
	void DrawButton();
	void ChangeText(const char Text[]);
	int ClickButton();
	SDL_Renderer *renderer = NULL;
	void ChangeText(char*) ;
	CMenuButton(const char text[],int X1,int Y1,int X2,int Y2, SDL_Renderer *renderer);
	~CMenuButton();
};

#endif
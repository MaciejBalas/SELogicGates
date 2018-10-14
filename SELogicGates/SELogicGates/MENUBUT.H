#ifndef DefMenuBut
#define DefMenuBut

#include "gate.h"
#include "button.h"

class CMenuButton:public CButton
{
	char*ButtonText;
 public:
	void DrawButton();
	void ChangeText(char*Text);
	int ClickButton();
	CMenuButton(char*Text,int X1,int Y1,int X2,int Y2);
	~CMenuButton();
};

#endif
#ifndef DefModeBut
#define DefModeBut

#include "button.h"
#include "element.h"

class CModeButton:public CButton
{
	CElement*ButtonElement;
 public:
	void DrawButton();
	void ChangeText(char*);
	int ClickButton();
	CModeButton(TElementType ButtonType,int X1,int Y1,int X2, int Y2);
	~CModeButton();
};

#endif
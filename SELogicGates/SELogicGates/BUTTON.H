#ifndef DefButton
#define DefButton

class CButton
{
 protected:
	int X1;
	int Y1;
	int X2;
	int Y2;
	int ButtonColour;
	int DrawingColour;
	enum TInsert{true,false};
	enum TActive{off,on};
	TInsert Insert;
	TActive Active;
 public:
	virtual void DrawButton()=0;
	void ChangeInsertMode(int TurnOff=0);
	void ActiveMode(TActive Active);
	virtual void ChangeText(char*)=0;
	int IsYourArea(int X,int Y);
	virtual int ClickButton()=0;
	void SetActivity(TActive Active);
	virtual ~CButton();
};

#endif
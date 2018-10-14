#ifndef DefSmallWindow
#define DefSmallWindow

#include "element.h"
#include "menubut.h"

class CSmallWindow
{
	char Active;
	char Result;
	int X1;
	int Y1;
	int X2;
	int Y2;
	int LinesNum;
	int ButtonNum;
	char Reading;
	char*HeadingText;
	char*ConstText[MaxSmallWinLinesNum];
	char*ReadText;
	CMenuButton*TabBut[2];
	void React(int X,int Y);//reakcja na przyci˜ni©cie klawisza myszki
	void Read();//wczytuje znaki z klawiatury
	void CheckButtons(int X,int Y);//sprawdzenie przycisk¢w przy naci˜ni©ciu myszki
	void DrawSmallWin();
	void Action(int ActNum);
 public:
	char Work();//obsluga myszki
	CSmallWindow(int X1,int Y1,int X2, int Y2,char*HeadingText,char**ConstText,
							 char Reading,int ButtonNum,char*FirstButtonText=NULL,
							 char*SecondButtonText=NULL);
	int GetReadTextLength();
	char GetReadText(char*ReadText);
	~CSmallWindow();
};

#endif
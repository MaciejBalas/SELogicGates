#include <dos.h>
#include <string.h>
#include <conio.h>
#include <stdio.h>
#include <graphics.h>
#include <alloc.h>

#define MenuButNum 7
#define ButNum 14
#define HighColour 4
#define LowColour 1
#define ErrorColour 2
#define NumberOfInBuses 6

enum TElementType{and,or,not,nor,nand,xor,output,wire,junction,inbus,cbus};
/*class CWindow;
class CElement;
class CButton;
class CMenuButton;*/

//Funkcje dodatkowe
void InitGraph(char *path="f:/borlandc/bgi")
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver,&gmode,path);//"c:/borlandc/bgi");
	errorcode=graphresult();
	if(errorcode)
	{
		gotoxy(23,8);
		printf("Graphic's error has appeared!");
		gotoxy(12,10);
		printf("While running this programm please write an access path");
		gotoxy(27,12);
		printf("to a file \"egavga.bgi\".");
		gotoxy(25,20);
		printf("Press any key to continue...");
		getch();
	}
}

int CheckMouse()
{
	struct REGPACK reg;
	reg.r_ax=0x0;
	intr(0x33,&reg);
	if(reg.r_ax==0)
	{
		printf("\n\n\t\tError!!!\n\n\tMouse not installed!!!");
		return 0;
	}
	return 1;
}

main()
{
	clrscr();
	if(!CheckMouse()) return 0;
	InitGraph();
	int WinNum=1;
	CWindow FirstWindow(WinNum);
	return 0;
}
#include "gate.h"
#include "window.h"
#include "smallwin.h"

//Funkcje dodatkowe
void InitGraph(char *Path)
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver,&gmode,Path);
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

void Control()
{
	int CurrentWinNum=0;//numer aktualnie otwartego okna
	int TotalWinNum=1;//ilo˜† wszystkich otwartych okien
	char NewPossib=1;//flaga m¢wi¥ca, czy mo¾e powsta† nowe okno
	char IsNew=1;//flaga m¢wi¥ca, czy okno jest nowe
	char IsPrev;//flaga m¢wi¥ca, czy istnieje okno wcze˜niejsze
	char IsNext;//flaga m¢wi¥ca, czy istnieje okno nast©pne
	int TabWin[MaxWinNum];//tablica flag m¢wi¥cych, czy okno istnieje
	for(int i=0;i<MaxWinNum;i++) TabWin[i]=0;
	TabWin[0]=1;
	do
	{
		IsPrev=0;
		IsNext=0;
		for(i=0;i<CurrentWinNum;i++)
			if(TabWin[i]==1)
			{
				IsPrev=1;
				break;
			}
		for(i=CurrentWinNum+1;i<MaxWinNum;i++)
			if(TabWin[i]==1)
			{
				IsNext=1;
				break;
			}
		CWindow*Window=new CWindow(CurrentWinNum+1,IsPrev,IsNext,NewPossib,IsNew);
		IsNew=0;
		char WinResult=Window->Work();
		if(WinResult==0)//okno zostaje zamkni©te
		{
			TabWin[CurrentWinNum]=0;
			TotalWinNum--;
			if(NewPossib==0) NewPossib=1;
				//skasowane zostaˆo jakie˜ okno, wi©c mo¾na utworzy† nowe okno
			for(i=CurrentWinNum+1;i<MaxWinNum;i++)
				if(TabWin[i]==1)
				{
					CurrentWinNum=i;
					break;
				}
			if(i>=MaxWinNum)//nie zostaˆo znalezione nast©pne otwarte okno
				for(i=CurrentWinNum-1;i>=0;i--)
					if(TabWin[i]==1)
					{
						CurrentWinNum=i;
						break;
					}
			if(i<0) TotalWinNum=0;//okno zamkni©te byˆo ostatnie
		}
		else
		if(WinResult==-1)//wy˜wietlone ma by† okno poprzednie
		{
			for(i=CurrentWinNum-1;i>=0;i--)
				if(TabWin[i]==1) break;
			CurrentWinNum=i;
			if(i<0) TotalWinNum=0;//wyst¥piˆ bˆ¥d
		}
		else
		if(WinResult==1)//wy˜wietlone ma by† okno nast©pne
		{
			for(i=CurrentWinNum+1;i<MaxWinNum;i++)
				if(TabWin[i]==1) break;
			CurrentWinNum=i;
			if(i>=MaxWinNum) TotalWinNum=0;//wyst¥piˆ bˆ¥d
		}
		else
		if(WinResult==2)//ma powsta† nowe okno
		{
			for(i=0;i<MaxWinNum;i++)
				if(TabWin[i]==0) break;
			CurrentWinNum=i;
			TabWin[CurrentWinNum]=1;
			TotalWinNum++;
			if(i>=MaxWinNum) TotalWinNum=0;//wyst¥piˆ bˆ¥d
			if(i==MaxWinNum-1) NewPossib=0;
			IsNew=1;//kolejne okno b©dzie nowym oknem
		}
		delete Window;
	}while(TotalWinNum>0);
}

char ConfirmQuit()
{
	char*TabText[3];
	TabText[0]=new char[40];
	TabText[1]=new char[40];
	strcpy(TabText[0],"You have closed the last window...");
	for(int i=0;i<5;i++) TabText[1][i]=' ';
	TabText[1][i]='\x0';
	strcat(TabText[1],"Do you really want to quit?");
	TabText[2]=NULL;
	CSmallWindow*Window=new CSmallWindow(155,130,470,0,"Confirm",
																			 TabText,0,2,"Yes","No");
	char Result=Window->Work();
	delete Window;
	delete TabText[0];
	delete TabText[1];
	REGPACK reg;
	reg.r_ax=0x2;
	intr(0x33,&reg);//schowanie kursora
	setfillstyle(1,BackgroundColour);
	bar(155,130,470,300);//zamalowanie okienka
	reg.r_ax=0x1;
	intr(0x33,&reg);//pokazanie kursora
	return Result;
}

void FirstInfo()
{
	setfillstyle(1,BackgroundColour);
	setcolor(FrameColour);
	bar(1,1,639,479);
	char*TabText[2];
	TabText[0]=new char[40];
	for(int i=0;i<4;i++) TabText[0][i]=' ';
	TabText[0][i]='\x0';
	strcat(TabText[0],"LOGIC CIRCUITS 1.0");
	TabText[1]=NULL;
	CSmallWindow*Window=new CSmallWindow(195,130,430,0,"Information",
																			 TabText,0,1);
	Window->Work();
	delete Window;
	delete TabText[0];
}

main()
{
	clrscr();
	if(!CheckMouse()) return 0;
	InitGraph();
	FirstInfo();
	do
	{
		Control();
	}while(!ConfirmQuit());
	closegraph();
	return 0;
}
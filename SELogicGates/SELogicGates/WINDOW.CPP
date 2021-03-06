#include "window.h"
#include "smallwin.h"
#include "constbus.h"
#include "inbus.h"
#include "menubut.h"
#include "modebut.h"
#include "gate.h"
#include "and.h"
#include "or.h"
#include "not.h"
#include "nand.h"
#include "nor.h"
#include "xor.h"
#include "output.h"
#include "wire.h"

CWindow::CWindow(int Number,char IsPrev,char IsNext,char NewPossib,char IsNew)
{
  setactivepage(1);
	Active=1;
	Result=1;
	NumOfElem=NumberOfInBuses+2;//szyny wej�ciowe
	WinNum=Number;
	Mode=move;
	StandardPath=NULL;
	for(int i=0;i<NumberOfInBuses+2;i++)
		TabElem[i]=NULL;
	TabElem[0]=new CConstBus(145,447,0);
	TabElem[1]=new CConstBus(145,462,1);
	TabElem[2]=new CInBus(41,45,'a');
	TabElem[3]=new CInBus(56,45,'b');
	TabElem[4]=new CInBus(71,45,'c');
	TabElem[5]=new CInBus(86,45,'d');
	TabElem[6]=new CInBus(101,45,'e');
	TabElem[7]=new CInBus(116,45,'f');
	for(i=0;i<ButNum;i++)
		TabBut[i]=NULL;
	TabBut[0]=new CMenuButton("Load",30,22,90,39);
	TabBut[1]=new CMenuButton("New",100,22,160,39);
	if(!NewPossib) TabBut[1]->SetActivity(0);
	TabBut[2]=new CMenuButton("Prev",170,22,230,39);
	if(!IsPrev) TabBut[2]->SetActivity(0);
	TabBut[3]=new CMenuButton("Next",240,22,300,39);
	if(!IsNext) TabBut[3]->SetActivity(0);
	TabBut[4]=new CMenuButton("Save",310,22,370,39);
	TabBut[5]=new CMenuButton("Save As",380,22,440,39);
	TabBut[6]=new CMenuButton("Close",450,22,510,39);
	TabBut[7]=new CMenuButton("Info",520,22,580,39);
	TabBut[8]=new CMenuButton("Move",170,42,370,59);
		//stworzenie przycisk�w menu
	unsigned ImageSize=imagesize(2,61,28,90);//rozmiar jest sta�y
	for(i=0;i<ButNum-MenuButNum;i++) ImageTab[i]=new [ImageSize];
	TabBut[MenuButNum]=new CModeButton(and,2,61,28,90);
	TabBut[MenuButNum]->DrawButton();
	getimage(2,61,28,90,ImageTab[0]);
	TabBut[MenuButNum+1]=new CModeButton(or,2,101,28,130);
	TabBut[MenuButNum+1]->DrawButton();
	getimage(2,101,28,130,ImageTab[1]);
	TabBut[MenuButNum+2]=new CModeButton(not,2,141,28,170);
	TabBut[MenuButNum+2]->DrawButton();
	getimage(2,141,28,170,ImageTab[2]);
	TabBut[MenuButNum+3]=new CModeButton(nand,2,181,28,210);
	TabBut[MenuButNum+3]->DrawButton();
	getimage(2,181,28,210,ImageTab[3]);
	TabBut[MenuButNum+4]=new CModeButton(nor,2,221,28,250);
	TabBut[MenuButNum+4]->DrawButton();
	getimage(2,221,28,250,ImageTab[4]);
	TabBut[MenuButNum+5]=new CModeButton(xor,2,261,28,290);
	TabBut[MenuButNum+5]->DrawButton();
	getimage(2,261,28,290,ImageTab[5]);
	TabBut[MenuButNum+6]=new CModeButton(output,2,301,28,330);
	TabBut[MenuButNum+6]->DrawButton();
	getimage(2,301,28,330,ImageTab[6]);
	setfillstyle(1,FrameColour);
	ImageSize=imagesize(100,155,168,170);
	ImageTab[NumberOfImages-1]=new [ImageSize];
	bar(100,155,168,170);
	outtextxy(107,160,"Linking");
	getimage(100,155,168,170,ImageTab[NumberOfImages-1]);
		//ikona ��czenia element�w jest ostatnia w tablicy
	for(i=0;i<ButNum-MenuButNum;i++)
	{
		putimage(0,0,ImageTab[i],4);
		getimage(0,0,26,29,ImageTab[i]);
	}//negacja ikon element�w
	putimage(0,0,ImageTab[NumberOfImages-1],4);
	getimage(0,0,68,15,ImageTab[NumberOfImages-1]);
	setactivepage(0);
	if(!IsNew)
	{
		char Path[15];
		strcpy(Path,"win");
		DoText(WinNum,Path);
		strcat(Path,".tmp");
		if(Load(Path)!=1) Error(0);
		if(unlink(Path)==-1) Error(0);
		for(int i=0;i<NumOfElem;i++)
			TabElem[i]->GetOutput(0,NumOfElem);
	}//gdy okno nie jest nowe, to zostanie odtworzony jego poprzedni stan
	if(!IsPrev&&!IsNext&&IsNew) DrawWin(1);
		//jest to pierwsze otwierane okno
	else DrawWin(0);//narysowanie tylko element�w zmieniaj�cych si�
}

CWindow::~CWindow()
{
	for(int i=0;i<NumOfElem;i++)
		delete TabElem[i];
	for(i=0;i<=MenuButNum+6;i++)
		delete TabBut[i];
	if(StandardPath!=NULL)
		delete StandardPath;
	for(i=0;i<ButNum-MenuButNum+1;i++) delete ImageTab[i];
}

char CWindow::Work()
{
	struct REGPACK reg;
	reg.r_ax=0x1;
	intr(0x33,&reg);//pokazanie kursora myszy
	reg.r_ax=0xf;
	reg.r_cx=0x10;
	reg.r_dx=0x10;
	intr(0x33,&reg);//ustawienie szybko�ci
	do
	{
		reg.r_ax=0x3;
		intr(0x33,&reg);
		if(reg.r_bx&1) React(reg.r_cx,reg.r_dx);
	}while(Active);
	reg.r_ax=0x2;
	intr(0x33,&reg);//schowanie kursora myszy
	if(Result!=0)
	{
		char Path[15];
		strcpy(Path,"win");
		DoText(WinNum,Path);
		strcat(Path,".tmp");
		if(Save(Path)!=1) Error(0);
	}
	return Result;
}

void CWindow::React(int X,int Y)
{
	struct REGPACK reg;
	CheckElements(X,Y);
	CheckButtons(X,Y);
	do
	{
		reg.r_ax=0x3;
		intr(0x33,&reg);
	}while(reg.r_bx&1);//blokada-nic si� nie dzieje, gdy klawisz myszy
										//zosta� wci�ni�ty na pustym polu
	if(Active==0) return;
	reg.r_ax=0x2;
	intr(0x33,&reg);//schowanie kursora
	for(int i=0;i<NumOfElem;i++)
		TabElem[i]->GetOutput(0,NumOfElem);
	for(i=0;i<NumOfElem;i++)
		TabElem[i]->DrawElem();
		//od�wierzenie element�w
	if(NumOfElem>=MaxNumOfElem)
	{
		TabBut[MenuButNum-1]->ChangeText("Move");
		Mode=block;
		for(i=MenuButNum-1;i<ButNum;i++)
			TabBut[i]->SetActivity(0);
	}//zablokowanie klawiszy-za duzo element�w
	else if(Mode==block)
	{
		Mode=move;
		for(i=MenuButNum-1;i<ButNum;i++)
			TabBut[i]->SetActivity(1);
	}//odlokowanie klawiszy - mo�na tworzy� nowe elementy
	reg.r_ax=0x1;
	intr(0x33,&reg);//pokazanie kursora
}

void CWindow::CheckButtons(int X,int Y)
{
	struct REGPACK reg;
	for(int i=0;i<ButNum;i++)//sprawdzenie przycisk�w
		if(i<MenuButNum&&TabBut[i]->IsYourArea(X,Y))//gdy jest to klawisz menu
		{
			if(TabBut[i]->ClickButton())
			{
				reg.r_ax=0x2;
				intr(0x33,&reg);//schowanie myszy
				Action(i);//wykonanie funkcji przycisku
				reg.r_ax=0x1;//pokazanie myszy
				intr(0x33,&reg);
			}
			break;//kolejne przyciski ju� nie b�d� sprawdzane(oszcz�dno�� czasu)
		}//sprawdzenie, czy zosta� naci�ni�ty przycisk
		else if(i>=MenuButNum&&TabBut[i]->IsYourArea(X,Y)&&
						TabBut[i]->ClickButton())	NewElement(i);
			//gdy jest to klawisz elementu i reaguje
}

void CWindow::CheckElements(int X,int Y)
{
	struct REGPACK reg;
	for(int i=0;i<NumOfElem;i++)
		if(TabElem[i]->IsYourArea(X,Y))
			if((Mode==move||Mode==block)||
				(i<NumberOfInBuses+2&&i>1&&(X<=150&&(Y<60||Y>440))))
					//zawsze mo�na zmieni� stan szyny wej�ciowej
			{
				TElementType ButtonType=TabElem[i]->ElementType();
				int ImageNum;
				switch(ButtonType)
				{
					case and:ImageNum=0;break;
					case or:ImageNum=1;break;
					case not:ImageNum=2;break;
					case nand:ImageNum=3;break;
					case nor:ImageNum=4;break;
					case xor:ImageNum=5;break;
					case output:ImageNum=6;break;
					case wire:return;//nic si� nie dzieje
					case inbus:TabElem[i]->ClickElement();return;
						//akcja wykonana zostanie na poziomie wywo�anej funkcji
					case cbus:return;//nic si� nie dzieje
				}
				reg.r_ax=0x2;
				intr(0x33,&reg);//schowanie kursora
				int X1=TabElem[i]->GetXCorner();
				int Y1=TabElem[i]->GetYCorner();//zachowanie poprzedniej pozycji
				int Colour=BackgroundColour;
				if(TabElem[i]->ElementType()==output) Colour=FrameColour;
					//wyj�cie le�y na szarym pasku
				TabElem[i]->DrawElem(Colour);//element "znika"
				DragElement(ImageNum,i);
				reg.r_ax=0x1;
				intr(0x33,&reg);//pokazanie kursora
				return;
			}
			else
			{
				int ImageNum=NumberOfImages-1;
				int XMove;
				int YMove;
				reg.r_ax=0x3;
				intr(0x33,&reg);//odczytanie stanu myszy
				if(reg.r_cx>561) XMove=-68;
				else XMove=10;
				if(reg.r_dx>454) YMove=-15;
				else YMove=10;
				int X1=X+XMove;
				int Y1=Y+YMove;
				reg.r_ax=0x2;
				intr(0x33,&reg);//schowanie kursora
				putimage(X1,Y1,ImageTab[ImageNum],1);
				reg.r_ax=0x1;
				intr(0x33,&reg);//pokazanie kursora
				do
				{
					reg.r_ax=0x3;
					intr(0x33,&reg);//odczytanie stanu myszy
					if(X1!=reg.r_cx+XMove||Y1!=reg.r_dx+YMove)
					{
						if(reg.r_cx>561) XMove=-68;
						else XMove=10;
						if(reg.r_dx>454) YMove=-15;
						else YMove=10;
						reg.r_ax=0x2;
						intr(0x33,&reg);//schowanie kursora
						putimage(X1,Y1,ImageTab[ImageNum],1);
							//skasowanie ikony
						X1=reg.r_cx+XMove;
						Y1=reg.r_dx+YMove;
						putimage(X1,Y1,ImageTab[ImageNum],1);
							//narysowanie ikony w nowym po�o�eniu
						reg.r_ax=0x1;
						intr(0x33,&reg);//pokazanie kursora
					}
				}while(reg.r_bx&1);
				reg.r_ax=0x2;
				intr(0x33,&reg);//schowanie kursora
				putimage(X1,Y1,ImageTab[ImageNum],1);
					//skasowanie ikony
				reg.r_ax=0x1;
				intr(0x33,&reg);//pokazanie kursora
				X1-=XMove;
				Y1-=YMove;//przywr�cenie warto�ci odpowiadaj�cych po�o�eniu kursora
				for(int j=NumberOfInBuses+1;j<NumOfElem;j++)
					if(TabElem[j]->IsYourArea(X1,Y1))
					{
						LinkElem(TabElem[i],X,Y,TabElem[j],X1,Y1);
						return;
					}
			}
}

void CWindow::Action(int ActNum)
{
	switch(ActNum)
	{
		case 0:Error(Load());break;//odczyt z pliku
		case 1:New();break;//nowy element
		case 2:Previous();break;//poprzedni element
		case 3:Next();break;//nast�pny element
		case 4:Error(Save(StandardPath));break;//zachowanie sieci
		case 5:Error(Save());break;//zachowanie sieci w nowym pliku
		case 6:Exit();break;//koniec programu
		case 7:Info();break;//wy�wietlenie informacji
		case 8:MoveOrLink();break;//prze��czanie
	}
}

char CWindow::Load(char*Path)
{
	REGPACK reg;
	CSmallWindow*PathWin;
	char PathFlag=1;
		//flaga m�wi�ca, czy �cie�ka zosta�a podana przy wywo�aniu funkcji
	if(Path==NULL)
	{
		PathFlag=0;
		char*TabText[3];
		TabText[0]=strdup("Give file name:");
		TabText[1]=NULL;
		PathWin=new CSmallWindow(200,150,0,0,"Loading",TabText,1,2);
		if(!PathWin->Work())
		{
			reg.r_ax=0x2;
			intr(0x33,&reg);//schowanie kursora
			setfillstyle(1,BackgroundColour);
			bar(200,150,400,300);
			reg.r_ax=0x1;
			intr(0x33,&reg);//pokazanie kursora
			delete PathWin;
			delete TabText[0];
			return 2;//u�ytkownik zrezygnowa� z opcji
		}
		reg.r_ax=0x2;
		intr(0x33,&reg);//schowanie kursora
		setfillstyle(1,BackgroundColour);
		bar(200,150,400,300);
		reg.r_ax=0x1;
		intr(0x33,&reg);//pokazanie kursora
		Path=new char[PathWin->GetReadTextLength()+4];
		if(!PathWin->GetReadText(Path)) Path=NULL;
		delete TabText[0];
		delete PathWin;
		strcat(Path,".lci");
	}
	if(Path==NULL) return 0;
	FILE*File=NULL;
	if((File=fopen(Path,"rb"))==NULL)
		//otwarcie pliku do odczytu
	{
		delete Path;
		return -1;
	}
	if(PathFlag==0)	delete Path;
	for(int i=0;i<NumOfElem;i++)
		delete TabElem[i];
	fread(&NumOfElem,sizeof(int),1,File);
		//odczytanie ilo�ci element�w
	if(NumOfElem>MaxNumOfElem) return 0;
	if(feof(File)) return 0;
	for(i=0;i<NumOfElem;i++)
	{
		char Type;
		fread(&Type,sizeof(char),1,File);
		if(feof(File)) return 0;
		switch(Type)
		{
			case 0:TabElem[i]=new CAnd(0,0);break;
			case 1:TabElem[i]=new COr(0,0);break;
			case 2:TabElem[i]=new CNot(0,0);break;
			case 3:TabElem[i]=new CNand(0,0);break;
			case 4:TabElem[i]=new CNor(0,0);break;
			case 5:TabElem[i]=new CXor(0,0);break;
			case 6:TabElem[i]=new COutput(0,0);break;
			case 7:return 0;
				//w�z�y s� odczytywane przez druty
			case 8:TabElem[i]=new CWire(0,0);break;
			case 9:TabElem[i]=new CInBus(0,0,0);break;
			case 10:TabElem[i]=new CConstBus(0,0,0);break;
			default:return 0;
		}//przydzielenie pami�ci dla odczytywanego elementu

		if(!TabElem[i]->LoadElement(TabElem,NumOfElem,File,1)) return 0;
				//odczytanie danych elementu w pierwszej fazie
	}
	for(i=0;i<NumOfElem;i++)
		if(!TabElem[i]->LoadElement(TabElem,NumOfElem,File,2)) return 0;
				//odczytanie ka�dego elementu w drugiej fazie
				//odpowiedzialnej za utworzenie po��cze�
	fclose(File);
	setcolor(BackgroundColour);
	setfillstyle(1,BackgroundColour);
	bar(31,61,610,440);
	setcolor(FrameColour);
	setfillstyle(1,FrameColour);
	bar(31,441,610,478);
	bar(611,21,638,478);
	return 1;
}

void CWindow::New()
{
	Active=0;
	Result=2;
}

void CWindow::Previous()
{
	Active=0;
	Result=-1;
}

void CWindow::Next()
{
	Active=0;
	Result=1;
}

char CWindow::Save(char*Path)
{
	REGPACK reg;
	char PathFlag=1;
		//flaga m�wi�ca, czy �cie�ka zosta�a podana przy wywo�aniu funkcji
	if(Path==NULL)
	{
		PathFlag=0;
		CSmallWindow*PathWin;
		char*TabText[3];
		TabText[0]=strdup("Give file name:");
		TabText[1]=NULL;
		PathWin=new CSmallWindow(200,150,0,0,"Saving",TabText,1,2);
		if(!PathWin->Work())
		{
			reg.r_ax=0x2;
			intr(0x33,&reg);//schowanie kursora
			setfillstyle(1,BackgroundColour);
			bar(200,150,400,300);
			reg.r_ax=0x1;
			intr(0x33,&reg);//pokazanie kursora
			delete PathWin;
			delete TabText[0];
			return 1;//u�ytkownik zrezygnowa�
		}
		reg.r_ax=0x2;
		intr(0x33,&reg);//schowanie kursora
		setfillstyle(1,BackgroundColour);
		bar(200,150,400,300);
		reg.r_ax=0x1;
		intr(0x33,&reg);//pokazanie kursora
		Path=new char[PathWin->GetReadTextLength()+4];
		if(!PathWin->GetReadText(Path)) Path=NULL;
		delete TabText[0];
		delete PathWin;
		if(Path==NULL) return 0;
		strcat(Path,".lci");
		if(StandardPath!=NULL) delete StandardPath;
		StandardPath=strdup(Path);
	}//u�ytkownik podaje �cie�k� dost�pu
	FILE*File=NULL;
	if((File=fopen(Path,"wb"))==NULL)
	{
		creat(Path,S_IREAD|S_IWRITE);
		File=fopen(Path,"wb");
	}//otwarcie pliku do zapisu i odczytu
	if(PathFlag==0) delete Path;
	fwrite(&NumOfElem,sizeof(int),1,File);
		//zachowanie ilo�ci element�w
	for(int i=0;i<NumOfElem;i++)
		if(!TabElem[i]->SaveElement(TabElem,NumOfElem,File,1)) return 0;
				//zachowanie ka�dego elementu w pierwszej fazie
	for(i=0;i<NumOfElem;i++)
		if(!TabElem[i]->SaveElement(TabElem,NumOfElem,File,2)) return 0;
				//zachowanie ka�dego elementu w drugiej fazie
	fclose(File);
	return 1;
}

void CWindow::Exit()
{
	Result=0;
	Active=0;
}

void CWindow::Info()
{
	char*TabText[4];
	TabText[0]=new char[40];
	TabText[1]=new char[40];
	TabText[2]=new char[40];
	TabText[3]=new char[40];
	strcpy(TabText[0],"A");
	for(int i=0;i<5;i++) TabText[1][i]=' ';
	TabText[1][i]='\x0';
	strcat(TabText[1],"B");
	for(i=0;i<5;i++) TabText[2][i]=' ';
	TabText[2][i]='\x0';
	strcat(TabText[2],"C");
	for(i=0;i<5;i++) TabText[3][i]=' ';
	TabText[3][i]='\x0';
	strcat(TabText[3],"D");
	CSmallWindow*Window=new CSmallWindow(155,130,470,0,"Information",
																			 TabText,0,1);
	Window->Work();
	delete Window;
	delete TabText[0];
	delete TabText[1];
	delete TabText[2];
	delete TabText[3];
	REGPACK reg;
	reg.r_ax=0x2;
	intr(0x33,&reg);//schowanie kursora
	setfillstyle(1,BackgroundColour);
	bar(155,130,470,300);//zamalowanie okienka
	reg.r_ax=0x1;
	intr(0x33,&reg);//pokazanie kursora
}

void CWindow::MoveOrLink()
{
	if(Mode==block) return;
	if(Mode==move)
	{
		Mode=link;
		TabBut[MenuButNum-1]->ChangeText("Link");
		return;
	}
	Mode=move;
	TabBut[MenuButNum-1]->ChangeText("Move");
}

void CWindow::NewElement(int ElemNum)
{
	struct REGPACK reg;
	reg.r_ax=0x2;
	intr(0x33,&reg);//wy��czenie
	reg.r_ax=0x3;
	intr(0x33,&reg);//sprawdzenie stanu
	int ImageNum;//numer bitmapy w tabeli
	switch(ElemNum)
	{
		case MenuButNum:TabElem[NumOfElem]=new CAnd(reg.r_cx,reg.r_dx);
										ImageNum=0;break;
		case MenuButNum+1:TabElem[NumOfElem]=new COr(reg.r_cx,reg.r_dx);
											ImageNum=1;break;
		case MenuButNum+2:TabElem[NumOfElem]=new CNot(reg.r_cx,reg.r_dx);
											ImageNum=2;break;
		case MenuButNum+3:TabElem[NumOfElem]=new CNand(reg.r_cx,reg.r_dx);
											ImageNum=3;break;
		case MenuButNum+4:TabElem[NumOfElem]=new CNor(reg.r_cx,reg.r_dx);
											ImageNum=4;break;
		case MenuButNum+5:TabElem[NumOfElem]=new CXor(reg.r_cx,reg.r_dx);
											ImageNum=5;break;
		case MenuButNum+6:TabElem[NumOfElem]=new COutput(reg.r_cx,reg.r_dx);
											ImageNum=6;break;

	}
	if(DragElement(ImageNum,NumOfElem))
		NumOfElem++;
	else delete TabElem[NumOfElem];
	reg.r_ax=0x1;
	intr(0x33,&reg);//pokazanie kursora
}

void CWindow::LinkElem(CElement*FirstElem,int X1,int Y1,
											 CElement*NextElem,int X2,int Y2)
{
	if(FirstElem==NextElem) return;
	CWire*Linker=new CWire(0,0);
	TabElem[NumOfElem]=Linker;
	if(FirstElem->LinkNextElem(Linker,X1,Y1)&&
		 NextElem->LinkPrevElem(Linker,X2,Y2)&&
		 Linker->LinkPrevElem(FirstElem,X1,Y1)&&
		 Linker->LinkNextElem(NextElem,X2,Y2)&&
		 Linker->Autoformat(TabElem,NumOfElem)) NumOfElem++;
	else
	{
		FirstElem->DelNextElem(Linker);
		NextElem->DelPrevElem(Linker);
		delete Linker;
		TabElem[NumOfElem]=NULL;
	}
}

void CWindow::DeleteElem(int ElemNum)
{
	CElement*DelElemPoint=TabElem[ElemNum];
	int DelElemNum=TabElem[ElemNum]->DeleteConnections(TabElem,NumOfElem);
	delete DelElemPoint;
	NumOfElem-=DelElemNum;
}

char CWindow::DragElement(int ImageNum,int ElemNum)
{
	struct REGPACK reg;
	int X=-1;
	int Y=-1;
	reg.r_ax=0x3;
	intr(0x33,&reg);//sprawdzenie stanu
	int XDif=TabElem[ElemNum]->GetXCorner()-reg.r_cx;
	int YDif=TabElem[ElemNum]->GetYCorner()-reg.r_dx;
	reg.r_ax=0x4;
	reg.r_cx=TabElem[ElemNum]->GetXCorner();
	reg.r_dx=TabElem[ElemNum]->GetYCorner();
	intr(0x33,&reg);//ustawienie kursora myszy w prawym g�rnym rogu
	do
	{
		reg.r_ax=0x3;
		intr(0x33,&reg);//sprawdzenie stanu
		if(reg.r_cx>613||reg.r_dx>450)
		{
			if(reg.r_cx>613) reg.r_cx=613;
			if(reg.r_dx>450) reg.r_dx=450;
			reg.r_ax=0x4;
			intr(0x33,&reg);//wyr�wnanie do brzegu
		}
		if(reg.r_cx!=X||reg.r_dx!=Y)
		{
			putimage(X,Y,ImageTab[ImageNum],1);
				//zmazanie elementu
			putimage(reg.r_cx,reg.r_dx,ImageTab[ImageNum],1);
				//narysowanie elementu w nowym po�o�eniu
			X=reg.r_cx;
			Y=reg.r_dx;
		}
	}while(reg.r_bx&1);
	putimage(reg.r_cx,reg.r_dx,ImageTab[ImageNum],1);
	if(reg.r_cx<28&&reg.r_dx<430&&reg.r_dx>370) DeleteElem(ElemNum);
	else
	if(!TabElem[ElemNum]->Move(reg.r_cx,reg.r_dx,TabElem,NumOfElem))
	{
		reg.r_ax=0x4;
		reg.r_cx=reg.r_cx-XDif;
		reg.r_dx=reg.r_dx-YDif;
		intr(0x33,&reg);//ustawienie kursora myszy w pierwotnym po�o�eniu
		return 0;
	}
	reg.r_ax=0x4;
	reg.r_cx=reg.r_cx-XDif;
	reg.r_dx=reg.r_dx-YDif;
	intr(0x33,&reg);//ustawienie kursora myszy w pierwotnym po�o�eniu
	return 1;
}

void CWindow::DoText(int Number,char*Text)
{
	int i=0;
	char TmpText[4];
	do
	{
		TmpText[i]=(char)(Number%10+48);
		Number/=10;
		i++;
	}while(Number>0);
	TmpText[i]='\0';
	int TextLen=strlen(Text);
	for(int j=i;j>0;j--)
		Text[i-j+TextLen]=TmpText[j-1];
	Text[i+TextLen]='\0';
}

void CWindow::DrawWin(char Mode)
{
	if(Mode==1)//rysowanie ca�ego okna
	{
		setfillstyle(1,BackgroundColour);
		setcolor(BackgroundColour);
		line(0,0,0,479);
		line(639,0,639,479);
		line(0,479,639,479);
		line(0,0,639,0);//rysowanie ramki
		setfillstyle(1,FrameColour);
		bar(1,21,638,60);//pasek na g�rze
		bar(1,478,30,61);//pasek z lewej
		DrawBasket(3,400);//kosz
	}
	setcolor(BackgroundColour);
	setfillstyle(1,BackgroundColour);
	bar(31,61,610,440);//okno g��wne
	setcolor(FrameColour);
	setfillstyle(1,FrameColour);
	bar(1,478,638,441);//pasek na dole
	bar(611,451,638,61);//pasek z prawej
	setfillstyle(1,HeadingColour);
	bar(1,1,638,20);//pasek g�rny
	setcolor(HeadingTextColour);
	char Text[12]="WINDOW ";
	for(int i=7;i<10;i++)
		Text[i]='\0';
	DoText(WinNum,Text);
	outtextxy(300,10,Text);
	for(i=0;i<ButNum;i++)
		TabBut[i]->DrawButton();
	for(i=0;i<NumOfElem;i++)
		TabElem[i]->DrawElem();
}

void CWindow::DrawBasket(int X,int Y)
{
	setcolor(LineColour);
	line(X,Y,X,Y+30);
	line(X,Y+30,X+26,Y+30);
	line(X+26,Y+30,X+26,Y);
	line(X+26,Y,X,Y);//ramka
	setcolor(BasketColour);
	setfillstyle(1,BasketColour);
	bar(X+6,Y+26,X+20,Y+28);//podstawa
	line(X+6,Y+26,X+2,Y+4);
	line(X+20,Y+26,X+24,Y+4);//d�ugie linie pionowe
	line(X+8,Y+10,X+9,Y+26);
	line(X+13,Y+10,X+13,Y+26);
	line(X+18,Y+10,X+17,Y+26);//kr�tsze linie pionowe
	line(X+4,Y+10,X+22,Y+10);
	line(X+5,Y+14,X+21,Y+14);
	line(X+5,Y+18,X+21,Y+18);
	line(X+6,Y+22,X+20,Y+22);//linie poprzeczne
}

void CWindow::Error(int ErrorNum)
{
	if(ErrorNum>0) return;
	char*TabText[3];
	TabText[0]=new char[30];
	CSmallWindow*Window;
	if(ErrorNum==-1)
	{
		strcpy(TabText[0],"Opening file error!");
		TabText[1]=new char[30];
		strcpy(TabText[1],"File may not exist...");
		TabText[2]=NULL;
		Window=new CSmallWindow(170,150,430,0,"Error!",
														 TabText,0,1);
	}
	else
	{
		strcpy(TabText[0],"All information will be lost!");
		TabText[1]=NULL;
		Window=new CSmallWindow(170,150,430,0,"Critical error!",
														 TabText,0,1);
	}
	Window->Work();
	REGPACK reg;
	reg.r_ax=0x2;
	intr(0x33,&reg);//schowanie kursora
	setfillstyle(1,BackgroundColour);
	bar(170,150,430,300);//zamalowanie okienka
	reg.r_ax=0x1;
	intr(0x33,&reg);//pokazanie kursora
	delete Window;
	delete TabText[0];
	delete TabText[1];
	if(ErrorNum==-1)
	{
		delete TabText[2];
		return;
	}
	closegraph();
	exit(1);
}

#include "inbus.h"
#include "gate.h"

CInBus::CInBus(int X,int Y,char Name)
{
	this->Name=Name;
	JunctionNum=0;
	X1=X;
	X2=X+10;
	Y1=Y;
	Y2=451;
	char Text[2];
	Text[0]=Name;
	Text[1]='\0';
	Button[0]=new CMenuButton(Text,X1,Y1+5,X1+10,Y1+15);
	Text[0]='1';
	Text[1]='\0';
	Button[1]=new CMenuButton(Text,X1,Y2-10,X1+10,Y2);
	InNum=0;
	OutNum=-1;//ilo˜† nieograniczona
	Output=high;
	Visible=true;
	Movable=no;
}

CInBus::~CInBus()
{
	for(int i=0;i<JunctionNum;i++)
		delete TabJunction[i];
	delete Button[0];
	delete Button[1];
}

void CInBus::DrawElem(int Colour)
{
	if(Colour==0)
	{
		switch(Output)
		{
			case low:Colour=LowColour;break;
			case high:Colour=HighColour;break;
			case error:Output=high;Colour=HighColour;break;
		}
	}
	if(Visible==false) Colour=BackgroundColour;
	setcolor(Colour);
	line(X1+5,61,X1+5,Y2-10);//linia gˆ¢wna
	if(Visible==true)
	{
		char Text[2];
		switch(Output)
		{
			case low:Text[0]='0';break;
			case high:Text[0]='1';break;
		}
		Text[1]='\0';
		Button[1]->ChangeText(Text);
		Button[1]->DrawButton();
	}
	else
	{
		setfillstyle(1,FrameColour);
		bar(X1,Y2-10,X2,Y2);
	}
	Button[0]->DrawButton();
	for(int i=0;i<JunctionNum;i++) TabJunction[i]->DrawElem();
}

TOutput CInBus::GetOutput(int AskElemNum,int MaxNum)
{
	if(AskElemNum==0) return Output;
	for(int i=0;i<JunctionNum;i++)
		TabJunction[i]->GetOutput(AskElemNum,MaxNum);
	return Output;
}

void CInBus::Change()
{}

TElementType CInBus::ElementType()
{
	return inbus;
}

void CInBus::ClickElement()
{
	struct REGPACK reg;
	reg.r_ax=0x3;
	intr(0x33,&reg);
	if(Button[0]->IsYourArea(reg.r_cx,reg.r_dx))
	{
		Button[0]->ClickButton();
		if(Visible==true&&JunctionNum==0) Visible=false;
		else Visible=true;
		return;
	}
	if(Visible==true&&Button[1]->IsYourArea(reg.r_cx,reg.r_dx))
		//aby zmieni† stan szyny, szyna musi by† aktywna(widzialna)
	{
		if(Button[1]->ClickButton())
			if(Output==low) Output=high;
			else Output=low;
		return;
	}
}

char CInBus::LinkNextElem(CElement*NextElem,int X,int Y)
{
	if(NextElem->ElementType()!=wire) return 0;//bˆ¥d
	if(JunctionNum>=MaxBusJunctionNum) return 0;//za duzo w©zˆ¢w
	int XTmp1;
	int YTmp1;
	for(int i=0;i<JunctionNum;i++)
	{
		XTmp1=TabJunction[i]->GetXCorner();
		YTmp1=TabJunction[i]->GetYCorner();
		if(X<XTmp1+6&&X>XTmp1-6&&Y<YTmp1+6&&Y>YTmp1-6) return 0;
			 //powi¥zanie za blisko istniej¥cego w©zˆa
	}
	X=X1+5;
	TabJunction[JunctionNum]=new CJunction(X,Y);
	TabJunction[JunctionNum]->LinkPrevElem(this,0,0);
	TabJunction[JunctionNum]->LinkNextElem(NextElem,X,Y);
	JunctionNum++;
  return 1;
}

char CInBus::LinkPrevElem(CElement*PrevElem,int X,int Y)
{
	return 0;
}

char CInBus::DelNextElem(CElement*DelElem)
{
	for(int i=0;i<JunctionNum;i++)
	{
		char Deleting=TabJunction[i]->DelNextElem(DelElem);
		if(Deleting==2)
		{
			TabJunction[i]->DrawElem(BackgroundColour);
			delete TabJunction[i];
			for(int j=i;j<JunctionNum;j++) TabJunction[j]=TabJunction[j+1];
			JunctionNum--;
			return 1;
		}
		if(Deleting==1) return 1;
	}
	return 0;
}

char CInBus::SaveElement(CElement**TabElem,int NumOfElem,FILE*File,char Phase)
{
	if(Phase==1)//pierwsza faza zachowywania
	{
		char Type=9;
		fwrite(&Type,sizeof(char),1,File);
		fwrite(&Name,sizeof(char),1,File);
		fwrite(&X1,sizeof(int),1,File);
		fwrite(&Y1,sizeof(int),1,File);
		fwrite(&X2,sizeof(int),1,File);
		fwrite(&Y2,sizeof(int),1,File);
		fwrite(&Output,sizeof(char),1,File);
		fwrite(&Visible,sizeof(char),1,File);
		fwrite(&JunctionNum,sizeof(int),1,File);
		for(int i=0;i<JunctionNum;i++)
			if(!TabJunction[i]->SaveElement(TabElem,NumOfElem,File,1)) return 0;
				//zachowanie w©zˆ¢w w pierwszej fazie
	}
	else//druga faza zachowywania
	{
		for(int i=0;i<JunctionNum;i++)
			if(!TabJunction[i]->SaveElement(TabElem,NumOfElem,File,2)) return 0;
				//zachowanie w©zˆ¢w w drugiej fazie
	}
	return 1;
}

char CInBus::LoadElement(CElement**TabElem,int NumOfElem,
													 FILE*File,char Phase)
{
	if(Phase==1)//pierwsza faza odczytu
	{
		if(feof(File)) return 0;
		fread(&Name,sizeof(char),1,File);
		if(feof(File)) return 0;
		fread(&X1,sizeof(int),1,File);
    if(X1<0||X1>639) return 0;
		if(feof(File)) return 0;
		fread(&Y1,sizeof(int),1,File);
		if(Y1<0||Y1>479) return 0;
		if(feof(File)) return 0;
		fread(&X2,sizeof(int),1,File);
		if(X2<0||X2>639) return 0;
		if(feof(File)) return 0;
		fread(&Y2,sizeof(int),1,File);
		if(Y2<0||Y2>479) return 0;
		delete Button[0];
		delete Button[1];
		char Text[2];
		Text[0]=Name;
		Text[1]='\0';
		Button[0]=new CMenuButton(Text,X1,Y1+5,X1+10,Y1+15);
		Text[0]='1';
		Text[1]='\0';
		Button[1]=new CMenuButton(Text,X1,Y2-10,X1+10,Y2);
			//po odczytaniu nowych wsp¢ˆrz©dnych przyciski trzeba stworzy† na nowo
		if(feof(File)) return 0;
		fread(&Output,sizeof(char),1,File);
		if(Output!=0&&Output!=1) return 0;
		if(feof(File)) return 0;
		fread(&Visible,sizeof(char),1,File);
		if(Visible!=0&&Visible!=1) return 0;
		if(feof(File)) return 0;
		fread(&JunctionNum,sizeof(int),1,File);
		if(JunctionNum>MaxJunctionNum) return 0;
		for(int i=0;i<JunctionNum;i++)
		{
			char Type;
			if(feof(File)) return 0;
			fread(&Type,sizeof(char),1,File);
			if(Type!=7) return 0;//odczytywany element nie jest w©zˆem
			TabJunction[i]=new CJunction(0,0);
			if(!TabJunction[i]->LoadElement(TabElem,NumOfElem,File,1)) return 0;
				//odczyt w©zˆ¢w w pierwszej fazie
		}
	}
	else//druga faza odczytu
	{
		for(int i=0;i<JunctionNum;i++)
			if(!TabJunction[i]->LoadElement(TabElem,NumOfElem,File,2)) return 0;
				//odczyt w©zˆ¢w w pierwszej fazie
	}
	return 1;
}

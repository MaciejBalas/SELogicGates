#include "constbus.h"
#include "gate.h"

CConstBus::CConstBus(int X,int Y,int Type)
{
	JunctionNum=0;
	for(int i=0;i<MaxJunctionNum;i++) TabJunction[i]=NULL;
	X1=X;
	X2=620;
	Y1=Y;
	Y2=Y1+10;
	InNum=0;
	OutNum=-1;//ilo˜† nieograniczona
	if(Type) Output=high;
	else Output=low;
	Movable=yes;
}

CConstBus::~CConstBus()
{
	for(int i=0;i<JunctionNum;i++)
		delete TabJunction[i];
}

void CConstBus::DrawElem(int Colour)
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
	setcolor(Colour);
	line(X1,Y2-5,X2-10,Y2-5);
	line(X1,Y2-4,X2-10,Y2-4);
	char Text[2];
	switch(Output)
	{
		case low:Text[0]='0';break;
		case high:Text[0]='1';break;
	}
	Text[1]='\0';
	outtextxy(X2-5,Y2-3,Text);
	for(int i=0;i<JunctionNum;i++) TabJunction[i]->DrawElem(Colour);
}

TOutput CConstBus::GetOutput(int AskElemNum,int MaxNum)
{
	if(AskElemNum==0) return Output;
	for(int i=0;i<JunctionNum;i++)
		TabJunction[i]->GetOutput(AskElemNum,MaxNum);
	return Output;
}

TElementType CConstBus::ElementType()
{
	return cbus;
}

void CConstBus::ClickElement()
{}

char CConstBus::LinkNextElem(CElement*NextElem,int X,int Y)
{
	if(NextElem->ElementType()!=wire) return 0;//bˆ¥d
	if(JunctionNum>=MaxBusJunctionNum) return 0;//za du¾o w©zˆ¢w
	int XTmp1;
	int YTmp1;
	for(int i=0;i<JunctionNum;i++)
	{
		XTmp1=TabJunction[i]->GetXCorner();
		YTmp1=TabJunction[i]->GetYCorner();
		if(X<XTmp1+6&&X>XTmp1-6&&Y<YTmp1+6&&Y>YTmp1-6) return 0;
			 //powi¥zanie za blisko istniej¥cego w©zˆa
	}
	Y=Y1+6;
	TabJunction[JunctionNum]=new CJunction(X,Y);
	TabJunction[JunctionNum]->LinkPrevElem(this,0,0);
	TabJunction[JunctionNum]->LinkNextElem(NextElem,X,Y);
	JunctionNum++;
	return 1;
}

char CConstBus::LinkPrevElem(CElement*PrevElem,int X,int Y)
{
	return 0;
}

char CConstBus::DelNextElem(CElement*DelElem)
{
	for(int i=0;i<JunctionNum;i++)
	{
		char Deleting=TabJunction[i]->DelNextElem(DelElem);
		if(Deleting==2)
		{
			TabJunction[i]->DrawElem(FrameColour);
			delete TabJunction[i];
			for(int j=i;j<JunctionNum;j++) TabJunction[j]=TabJunction[j+1];
			JunctionNum--;
			return 1;
		}
		if(Deleting==1) return 1;
	}
	return 0;
}

char CConstBus::SaveElement(CElement**TabElem,int NumOfElem,
														FILE*File,char Phase)
{
	if(Phase==1)//pierwsza faza zachowywania
	{
		char Type=10;
		fwrite(&Type,sizeof(char),1,File);
		fwrite(&X1,sizeof(int),1,File);
		fwrite(&Y1,sizeof(int),1,File);
		fwrite(&X2,sizeof(int),1,File);
		fwrite(&Y2,sizeof(int),1,File);
		fwrite(&Output,sizeof(char),1,File);
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

char CConstBus::LoadElement(CElement**TabElem,int NumOfElem,
													 FILE*File,char Phase)
{
	if(Phase==1)//pierwsza faza odczytu
	{
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
		if(feof(File)) return 0;
		fread(&Output,sizeof(char),1,File);
		if(Output!=0&&Output!=1) return 0;
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

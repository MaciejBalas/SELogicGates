#include "element.h"
#include "gate.h"

CElement::~CElement()
{}

int CElement::IsOnBoard()
{
	if(X1>150&&X2<610&&Y1>60&&Y2<440) return 1;
	return 0;
}

int CElement::IsYourArea(int X,int Y)
{
	if(X>=X1&&X<=X2&&Y>=Y1&&Y<=Y2) return 1;
	return 0;
}

char CElement::IsElemPrev(CElement*Element)
{
	for(int j=0;j<InNum;j++)
		if(TabPrevElem[j]==Element) return 1;
	return 0;
}

char CElement::IsElemNext(CElement*Element)
{
	for(int j=0;j<OutNum;j++)
		if(TabNextElem[j]==Element) return 1;
	return 0;
}

int CElement::GetXCorner(char Right)
{
	if(Right) return X2;
	return X1;
}

int CElement::GetYCorner(char Down)
{
	if(Down) return Y2;
	return Y1;
}

int CElement::IsAreaFree(CElement**TabElem,int NumOfElem)
{
	int i = 0;
	int ElemNum;
	for(int i=0;i<=NumOfElem;i++) if(this==TabElem[i])
	{
		ElemNum=i;
		break;
	}//ustalenie numeru elementu
	if(X2<0) X2=X1;
	if(Y2<0) Y2=Y1;
	int X=X1;
	int Y=Y1;
	if(TabElem[ElemNum]->ElementType()==wire) return 0;//wystĄpi bĄd
	for(i=0;i<NumOfElem;i++)
	{
		if(i==ElemNum) i++;//nie bada si© tego samego elementu
		if(i>=NumOfElem) break;//zabezpieczenie przed przekroczeniem tabeli
		do
		{
			if(TabElem[i]->IsYourArea(X,Y))
				if(!TabElem[ElemNum]->IsElemPrev(TabElem[i])&&
					 !TabElem[ElemNum]->IsElemNext(TabElem[i])) return 0;
					 //znaleziony element nie jest nast©pny ani poprzedni
			X+=5;
		}while(X<X2);
		X=X2;
		do
		{
			if(TabElem[i]->IsYourArea(X,Y))
			if(!TabElem[ElemNum]->IsElemPrev(TabElem[i])&&
				 !TabElem[ElemNum]->IsElemNext(TabElem[i])) return 0;
				 //znaleziony element nie jest nast©pny ani poprzedni
			Y+=5;
		}while(Y<Y2);
		Y=Y2;
		do
		{
			if(TabElem[i]->IsYourArea(X,Y))
			if(!TabElem[ElemNum]->IsElemPrev(TabElem[i])&&
				 !TabElem[ElemNum]->IsElemNext(TabElem[i])) return 0;
				 //znaleziony element nie jest nast©pny ani poprzedni
			X-=5;
		}while(X>X1);
		X=X1;
		do
		{
			if(TabElem[i]->IsYourArea(X,Y))
			if(!TabElem[ElemNum]->IsElemPrev(TabElem[i])&&
				 !TabElem[ElemNum]->IsElemNext(TabElem[i])) return 0;
				 //znaleziony element nie jest nast©pny ani poprzedni
			Y-=5;
		}while(Y>Y1);
	}
	return 1;
}

char CElement::Move(int X,int Y,CElement**TabElem,int NumOfElem)
{
	int i = 0;
	if(Movable==no) return 0;
	int X1Prev=X1;
	int Y1Prev=Y1;
	int X2Prev=X2;
	int Y2Prev=Y2;
	X2=X2-X1+X;
	Y2=Y2-Y1+Y;
	X1=X;
	Y1=Y;
	if(!(IsOnBoard()&&IsAreaFree(TabElem,NumOfElem)))
	{
		X2=X2Prev;
		Y2=Y2Prev;
		X1=X1Prev;
		Y1=Y1Prev;
		return 0;
	}//sprawdzenie poprawnoci nowego pooľenia elementu
	for(int i=0;i<InNum;i++)
		if(TabPrevElem[i]!=NULL)
		{
			int TmpX=TabPrevElem[i]->GetXCorner(1);
			int TmpY=TabPrevElem[i]->GetYCorner(1);
				//potrzebne sĄ wsp˘rz©dne koäca linii
			if(TabPrevElem[i]->IsOnBoard())
				TabPrevElem[i]->DrawElem(BackgroundColour);
					//poĄczenie zniknie, jeľeli byo narysowane
			TabPrevElem[i]->MoveEnd(TmpX+X-X1Prev,TmpY+Y-Y1Prev);
			if(!TabPrevElem[i]->Autoformat(TabElem,NumOfElem))
			{
				X2=X2Prev;
				Y2=Y2Prev;
				X1=X1Prev;
				Y1=Y1Prev;
				TabPrevElem[i]->MoveEnd(TmpX,TmpY);
				for(int j=i-1;j>=0;j--)
					if(TabPrevElem[j]!=NULL)
					{
						int TmpX=TabPrevElem[j]->GetXCorner(1);
						int TmpY=TabPrevElem[j]->GetYCorner(1);
							//potrzebne sĄ wsp˘rz©dne koäca linii
						TabPrevElem[j]->MoveEnd(TmpX-X+X1Prev,TmpY-Y+Y1Prev);
						TabPrevElem[j]->Autoformat(TabElem,NumOfElem);
					}//poniewaľ kt˘rej z linii nie dao si© sformatowa†,
					//trzeba przywr˘ci† pooľenie wczeniej sformatowanych linii
				return 0;
			}
		}
	for(i=0;i<OutNum;i++)
		if(TabNextElem[i]!=NULL)
		{
			int TmpX=TabNextElem[i]->GetXCorner();
			int TmpY=TabNextElem[i]->GetYCorner();
			if(TabNextElem[i]->IsOnBoard())
				TabNextElem[i]->DrawElem(BackgroundColour);
					//poĄczenie zniknie, jeľeli byo narysowane
			TabNextElem[i]->MoveBeg(TmpX+X-X1Prev,TmpY+Y-Y1Prev);
			if(!TabNextElem[i]->Autoformat(TabElem,NumOfElem))
			{
				X2=X2Prev;
				Y2=Y2Prev;
				X1=X1Prev;
				Y1=Y1Prev;
				TabNextElem[i]->MoveBeg(TmpX,TmpY);
				for(int j=i-1;j>=0;j--)
					if(TabPrevElem[j]!=NULL)
					{
						int TmpX=TabPrevElem[j]->GetXCorner(1);
						int TmpY=TabPrevElem[j]->GetYCorner(1);
							//potrzebne sĄ wsp˘rz©dne koäca linii
						TabPrevElem[j]->MoveBeg(TmpX-X+X1Prev,TmpY-Y+Y1Prev);
						TabPrevElem[j]->Autoformat(TabElem,NumOfElem);
					}//poniewaľ kt˘rej z linii nie dao si© sformatowa†,
					//trzeba przywr˘ci† pooľenie wczeniej sformatowanych linii
				for(int j=InNum-1;j>=0;j--)
					if(TabPrevElem[j]!=NULL)
					{
						int TmpX=TabPrevElem[j]->GetXCorner(1);
						int TmpY=TabPrevElem[j]->GetYCorner(1);
							//potrzebne sĄ wsp˘rz©dne koäca linii
						TabPrevElem[j]->MoveEnd(TmpX-X+X1Prev,TmpY-Y+Y1Prev);
						TabPrevElem[j]->Autoformat(TabElem,NumOfElem);
					}//poniewaľ kt˘rej z linii nie dao si© sformatowa†,
					//trzeba przywr˘ci† pooľenie wczeniej sformatowanych linii
				return 0;
			}
		}
	return 1;
}

void CElement::MoveBeg(int X,int Y)
{}

void CElement::MoveEnd(int X,int Y)
{}

char CElement::LinkNextElem(CElement*NextElem,int X,int Y)
{
	if(NextElem->ElementType()!=wire) return 0;
		//bramka moľe by† poĄczona tylko z drutem
	if(TabNextElem[0]!=NULL) return 0;//istnieje juľ element nast©pny
	TabNextElem[0]=NextElem;
	NextElem->MoveBeg(X1+25,Y1+14);
	return 1;
}

char CElement::LinkPrevElem(CElement*PrevElem,int X,int Y)
{
	int i = 0;
	if(PrevElem->ElementType()!=wire) return 0;
		//bramka moľe by† poĄczona tylko z drutem
	X-=X1;
	Y-=Y1;//zmienne X i Y okrelajĄ wzgl©dne pooľenie
	int MinY;
	int MaxY;
	char Key=0;
	int Hight=(Y2-Y1)/InNum;
	if((Y2-Y1)/InNum) Key=1;//wysoko† jest liczbĄ nieparzystĄ
	for(int i=0;i<InNum;i++)
	{
		if(Key!=0)
		{
			if(Key==1)
			{
				Hight+=1;
				Key=2;
			}
			else
			{
				Hight-=1;
				Key=1;
			}
		}
		MinY=i*Hight+2;
		MaxY=(i+1)*Hight+2;
		if(i==InNum-1) MaxY=Y2;
		if(Y>=MinY&&Y<=MaxY) break;
	}
	if(TabPrevElem[i]!=NULL)
		for(i=0;i<InNum;i++)
			if(TabPrevElem[i]==NULL) break;
	if(i==InNum) return 0;
	TabPrevElem[i]=PrevElem;
	switch(i)
	{
		case 0:Y=12;break;
		case 1:Y=17;break;
	}
	PrevElem->MoveEnd(X1+3,Y1+Y);
	return 1;
}

char CElement::DelNextElem(CElement*DelElem)
{
	for(int i=0;i<OutNum;i++)
		if(TabNextElem[i]==DelElem)
		{
			TabNextElem[i]=NULL;
			return 1;
		}
		return 0;
}

char CElement::DelPrevElem(CElement*DelElem)
{
	for(int i=0;i<InNum;i++)
		if(TabPrevElem[i]==DelElem)
		{
			TabPrevElem[i]=NULL;
			return 1;
		}
		return 0;
}

int CElement::DeleteConnections(CElement**TabElem,int NumOfElem,char Main)
{
	int i = 0;
	int DelElemNum=1;//trzeba wliczy† takľe ten element
	//funkcja wirtualna jest zdefiniowana w tym miejscu dla bramek i wyj†,
	//druty i w©zy majĄ inne ciao funkcji
	for(int i=0;i<NumOfElem;i++)
		if(this==TabElem[i]) break;//znalezienie indeksu bieľĄcego elementu
	for(int j=i;j<NumOfElem;j++)
		TabElem[j]=TabElem[j+1];//wyrzucenie elementu z tabeli
	NumOfElem--;//lokalne zmniejszenie wartoci - nie ma skutku na zewnĄtrz
	for(i=0;i<InNum;i++)
		if(TabPrevElem[i]!=NULL)
		{
			CElement*Temp=TabPrevElem[i];
			DelElemNum+=TabPrevElem[i]->DeleteConnections(TabElem,NumOfElem,1);
			delete Temp;
		}
	for(i=0;i<OutNum;i++)
		if(TabNextElem[i]!=NULL)
		{
			CElement*Temp=TabNextElem[i];
			DelElemNum+=TabNextElem[i]->DeleteConnections(TabElem,NumOfElem,1);
			delete Temp;
		}
	return DelElemNum;
}

char CElement::Autoformat(CElement**TabElem,int NumOfElem)
{
	return 0;
}

char CElement::SaveElement(CElement**TabElem,int NumOfElem,
													 FILE*File,char Phase)
{
	int i = 0;
	int j = 0;
	if(Phase==1)//pierwsza faza zachowywania
	{
		char Type;
		switch(this->ElementType())
		{
			case and:Type=0;break;
			case or:Type=1;break;
			case not:Type=2;break;
			case nand:Type=3;break;
			case nor:Type=4;break;
			case xor:Type=5;break;
			case output:Type=6;break;
			case junction:Type=7;break;
			default:return 0;
		}
		fwrite(&Type,sizeof(char),1,File);
		fwrite(&X1,sizeof(int),1,File);
		fwrite(&Y1,sizeof(int),1,File);
		fwrite(&X2,sizeof(int),1,File);
		fwrite(&Y2,sizeof(int),1,File);
		fwrite(&InNum,sizeof(int),1,File);
	}
	else//druga faza zachowywania
	{
		for(int i=0;i<InNum;i++)
		{
			int PrevElemPos;
			if(TabPrevElem[i]!=NULL)
			{
				for(int j=0;j<NumOfElem;j++)
					if(TabElem[j]==TabPrevElem[i]) break;
						//ustalenie indeksu poprzednich element˘w
				if(j>=NumOfElem) return 0;//bĄd - element nie zosta znaleziony
				PrevElemPos=j;
			}
			else PrevElemPos=-1;//nie ma elementu poprzedniego na i-tej pozycji
			fwrite(&PrevElemPos,sizeof(int),1,File);
		}
		for(i=0;i<OutNum;i++)
		{
			int NextElemPos;
			if(TabNextElem[i]!=NULL)
			{
				for(int j=0;j<NumOfElem;j++)
					if(TabElem[j]==TabNextElem[i]) break;
						//ustalenie indeksu poprzednich element˘w
				if(j>=NumOfElem) return 0;//bĄd - element nie zosta znaleziony
				NextElemPos=j;
			}
			else NextElemPos=-1;//nie ma elementu poprzedniego na i-tej pozycji
			fwrite(&NextElemPos,sizeof(int),1,File);
		}
	}
	return 1;
}

char CElement::LoadElement(CElement**TabElem,int NumOfElem,
													 FILE*File,char Phase)
{
	int i = 0;
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
		fread(&InNum,sizeof(int),1,File);
		if(InNum>MaxPrevElemNum) return 0;
		if(feof(File)) return 0;
	}
	else//druga faza odczytu
	{
		for(int i=0;i<InNum;i++)
		{
			int PrevElemPos;
			if(feof(File)) return 0;
			fread(&PrevElemPos,sizeof(int),1,File);
			if(PrevElemPos>NumOfElem) return 0;
			if(PrevElemPos<0)//element nie by poĄczony
				TabPrevElem[i]=NULL;
			else TabPrevElem[i]=TabElem[PrevElemPos];
				//element by poĄczony z elementem o odczytanym indeksie
		}
		for(i=0;i<OutNum;i++)
		{
			int NextElemPos;
			if(feof(File)) return 0;
			fread(&NextElemPos,sizeof(int),1,File);
			if(NextElemPos>NumOfElem) return 0;
			if(NextElemPos<0)//element nie by poĄczony
				TabNextElem[i]=NULL;
			else TabNextElem[i]=TabElem[NextElemPos];
				//element by poĄczony z elementem o odczytanym indeksie
		}
	}
	return 1;
}

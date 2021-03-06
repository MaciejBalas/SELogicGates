#include "wire.h"
#include "gate.h"

CWire::CWire(int X,int Y,int Colour,char FromJunction,CElement*PrevWire)
{
	X1=X;
	Y1=Y;
	X2=X;
	Y2=Y;
	JunctionNum=0;
	BreakpointsNum=2;
	TabBreakpoints[0][0]=X1;
	TabBreakpoints[0][1]=Y1;
	TabBreakpoints[1][0]=X2;
	TabBreakpoints[1][1]=Y2;
	InNum=1;
	OutNum=1;
	for(int i=0;i<InNum;i++)
		TabPrevElem[i]=NULL;
	for(i=0;i<OutNum;i++)
		TabNextElem[i]=NULL;
	Output=error;
	Movable=no;
}

CWire::~CWire()
{
	for(int i=0;i<JunctionNum;i++)
		delete TabJunction[i];
}

void CWire::DrawElem(int Colour)
{
	if(Colour==0)
	{
		switch(Output)
		{
			case low:Colour=LowColour;break;
			case high:Colour=HighColour;break;
			case error:Colour=ErrorColour;break;
		}
		setcolor(Colour);
		setfillstyle(1,Colour);
		for(int i=0;i<BreakpointsNum-1;i++)
		{
			line(TabBreakpoints[i][0],TabBreakpoints[i][1],
					 TabBreakpoints[i+1][0],TabBreakpoints[i+1][1]);
		}
		for(i=0;i<JunctionNum;i++) TabJunction[i]->DrawElem();
		return;
	}
	setcolor(Colour);//kasowanie elementu
	setfillstyle(1,Colour);
	for(int j=0;j<JunctionNum;j++)
	{
		if(TabJunction[j]->GetXCorner()>610||TabJunction[j]->GetYCorner()>440)
			TabJunction[j]->DrawElem(FrameColour);
		else TabJunction[j]->DrawElem(BackgroundColour);
	}//zamalowanie w�z��w
	for(int i=0;i<BreakpointsNum-1;i++)
	{
		if((TabBreakpoints[i][0]>610&&TabBreakpoints[i+1][0]>610)||
			 (TabBreakpoints[i][1]>440&&TabBreakpoints[i+1][1]>440))
		{
			if(TabBreakpoints[i+1][0]==TabBreakpoints[i][0]||
				 TabBreakpoints[i+1][1]==TabBreakpoints[i][1]) setcolor(FrameColour);
						//ca�a linia jest na szarym polu
		}
		else//cz��� linii mo�e by� na szarym polu
		{
			if(TabBreakpoints[i][0]>610&&
				 TabBreakpoints[i][1]==TabBreakpoints[i+1][1])
			{
				setcolor(FrameColour);
				setfillstyle(1,FrameColour);
				line(611,TabBreakpoints[i][1],TabBreakpoints[i][0],TabBreakpoints[i][1]);
				setcolor(Colour);
				setfillstyle(1,Colour);
				line(TabBreakpoints[i+1][0],TabBreakpoints[i][1],610,TabBreakpoints[i][1]);
				continue;
			}//linia w poziomie, pocz�tkiem wychodzi na prawy szary pasek
			if(TabBreakpoints[i+1][0]>610&&
				 TabBreakpoints[i][1]==TabBreakpoints[i+1][1])
			{
				setcolor(FrameColour);
				setfillstyle(1,FrameColour);
				line(611,TabBreakpoints[i][1],TabBreakpoints[i+1][0],TabBreakpoints[i][1]);
				setcolor(Colour);
				setfillstyle(1,Colour);
				line(TabBreakpoints[i][0],TabBreakpoints[i][1],610,TabBreakpoints[i][1]);
				continue;
			}//linia w poziomie, ko�cem wychodzi na prawy szary pasek
			if(TabBreakpoints[i][1]>440&&
				 TabBreakpoints[i][0]==TabBreakpoints[i+1][0])
			{
				setcolor(FrameColour);
				setfillstyle(1,FrameColour);
				line(TabBreakpoints[i][0],441,TabBreakpoints[i][0],TabBreakpoints[i][1]);
				setcolor(Colour);
				setfillstyle(1,Colour);
				line(TabBreakpoints[i][0],TabBreakpoints[i+1][1],TabBreakpoints[i][0],440);
				continue;
			}//linia w pionie, pocz�tkiem wychodzi na dolny szary pasek
			if(TabBreakpoints[i+1][1]>440&&
				 TabBreakpoints[i][0]==TabBreakpoints[i+1][0])
			{
				setcolor(FrameColour);
				setfillstyle(1,FrameColour);
				line(TabBreakpoints[i][0],441,TabBreakpoints[i][0],TabBreakpoints[i+1][1]);
				setcolor(Colour);
				setfillstyle(1,Colour);
				line(TabBreakpoints[i][0],TabBreakpoints[i][1],TabBreakpoints[i][0],440);
				continue;
			}//linia w pionie, ko�cem wychodzi na dolny szary pasek
		}
		line(TabBreakpoints[i][0],TabBreakpoints[i][1],
				 TabBreakpoints[i+1][0],TabBreakpoints[i+1][1]);
		setcolor(Colour);
		setfillstyle(1,Colour);
	}
}

TOutput CWire::GetOutput(int AskElemNum,int MaxNum)
{
	if(AskElemNum==0) return Output;
		//po��czenie ma zawsze pocz�tek i koniec; funkcja zostanie na pewno
		//wywo�ana z inn� warto�ci� (oszcz�dno�� czasu)
	if(AskElemNum==MaxNum) return Output;
	if(TabPrevElem[0]==NULL) Output=error;
	else Output=TabPrevElem[0]->GetOutput(AskElemNum+1,MaxNum);
	for(int i=0;i<JunctionNum;i++)
		TabJunction[i]->GetOutput(AskElemNum,MaxNum);
	return Output;
}

void CWire::MoveBeg(int X,int Y)
{
	X1=X;
	Y1=Y;
	TabBreakpoints[0][0]=X;
	TabBreakpoints[0][1]=Y;
}

void CWire::MoveEnd(int X,int Y)
{
	if(X>613) X=613;
	TabBreakpoints[BreakpointsNum-1][0]=X2=X;
	TabBreakpoints[BreakpointsNum-1][1]=Y2=Y;
}

int CWire::IsOnBoard()
{
	if(X1>30&&X2>30&&Y1>60&&Y2>60) return 1;
	return 0;
}

int CWire::IsYourArea(int X,int Y)
{
	int MinX;
	int MaxX;
	int MinY;
	int MaxY;
	for(int i=0;i<BreakpointsNum-1;i++)
	{
		if(TabBreakpoints[i][0]<TabBreakpoints[i+1][0])
		{
			MinX=TabBreakpoints[i][0];
			MaxX=TabBreakpoints[i+1][0];
		}
		else
		{
			MinX=TabBreakpoints[i+1][0];
			MaxX=TabBreakpoints[i][0];
		}
		if(TabBreakpoints[i][1]<TabBreakpoints[i+1][1])
		{
			MinY=TabBreakpoints[i][1];
			MaxY=TabBreakpoints[i+1][1];
		}
		else
		{
			MinY=TabBreakpoints[i+1][1];
			MaxY=TabBreakpoints[i][1];
		}
		if(X>=MinX&&X<=MaxX)
			if(Y>=MinY-2&&Y<=MinY+2) return 1;
		if(Y>=MinY&&Y<=MaxY)
			if(X>=MinX-2&&X<=MinX+2) return 1;
	}
	return 0;
}

char CWire::IsElemNext(CElement*Element)
{
	if(TabNextElem[0]==Element) return 1;
	for(int i=0;i<JunctionNum;i++)
		if(TabJunction[i]->IsElemNext(Element)) return 2;
	return 0;
	//funkcja zwraca 1, gdy podany element jest bezpo�rednio nast�pny;
	//funkcja zwraca 2, gdy podany element wychodzi z w�z�a;
	//funkcja zwraca 0, gdy podany element nie jest nast�pny.
}

char CWire::Check(CElement**TabElem,int NumOfElem)
{
	CElement*Wire=NULL;//wska�nik na napotkane po��czenie
	for(int i=0;i<BreakpointsNum-1;i++)
	{
		int X=TabBreakpoints[i][0];
		int Y=TabBreakpoints[i][1];
		if(TabBreakpoints[i][0]==TabBreakpoints[i+1][0])//linia pionowa
			if(TabBreakpoints[i][1]<TabBreakpoints[i+1][1])//linia pionowa w d��
			{
				X-=2;//badana lewa strona
				Y-=2;
				char Left=1;
				do
				{
					if(X<130||X>610||Y<60) return 0;
					for(int j=0;j<NumOfElem;j++)
					{
						if(this==TabElem[j]) j++;//nie bada si� tego samego elementu
						if(j>=NumOfElem) break;
						//zabezpieczenie przed przekroczeniem tabeli
						if(TabElem[j]->IsYourArea(X,Y))
						{
							if(TabElem[j]!=this->TabPrevElem[0]&&
								 TabElem[j]!=this->TabNextElem[0])
								 if(TabElem[j]->ElementType()!=wire&&
										TabElem[j]->ElementType()!=cbus) return 0;
								//znaleziony element nie jest nast�pny ani poprzedni
								//ani nie jest drutem ani szyn� sta��
							if(TabElem[j]==this->TabPrevElem[0]&&
								 this->TabPrevElem[0]->ElementType()==inbus) return 0;
							//na terenie szyn wej�ciowych druty mog� biec tylko w poziomie
							if(this->IsElemPrev(TabElem[j]))
								if(X<TabBreakpoints[0][0]-2) return 0;
							if(this->IsElemNext(TabElem[j]))
								if(X>TabBreakpoints[BreakpointsNum-1][0]+2) return 0;
							//na terenie element�w s�siednich po��czenie mo�e biec tylko
							//w �ci�le okre�lonym obszarze
							if(TabElem[j]->ElementType()==wire)
							{
								if((Y>TabBreakpoints[i][1]-1&&Y<TabBreakpoints[i][1]+1)||
									 (Y>TabBreakpoints[i+1][1]-1&&Y<TabBreakpoints[i+1][1]+1))
										return 0;
								if(Wire==TabElem[j])	return 0;
								Wire=TabElem[j];
							}
						}
						else if(TabElem[j]==Wire) Wire=NULL;
					}
					Y+=5;
					if(Left==1&&Y>TabBreakpoints[i+1][1])
					{
						X+=4;//badana jest prawa strona
						Y=TabBreakpoints[i][1]-2;
						Left=0;
					}
				}while(Y<TabBreakpoints[i+1][1]);
			}
			else//linia pionowa w g�r�
			{
				X-=2;//badana lewa strona
				Y+=2;
				char Left=1;
				do
				{
					if(X<130||X>610||Y<60) return 0;
					for(int j=0;j<NumOfElem;j++)
					{
						if(this==TabElem[j]) j++;//nie bada si� tego samego elementu
						if(j>=NumOfElem) break;
						//zabezpieczenie przed przekroczeniem tabeli
						if(TabElem[j]->IsYourArea(X,Y))
						{
							if(TabElem[j]!=this->TabPrevElem[0]&&
								 TabElem[j]!=this->TabNextElem[0])
								 if(TabElem[j]->ElementType()!=wire&&
										TabElem[j]->ElementType()!=cbus)
										return 0;
								//znaleziony element nie jest nast�pny ani poprzedni
							if(TabElem[j]==this->TabPrevElem[0]&&
								 this->TabPrevElem[0]->ElementType()==inbus)
								 return 0;
							if(this->IsElemPrev(TabElem[j]))
								if(X<TabBreakpoints[0][0]-2) return 0;
							if(this->IsElemNext(TabElem[j]))
								if(X>TabBreakpoints[BreakpointsNum-1][0]+2) return 0;
							if(TabElem[j]->ElementType()==wire)
							{
								if((Y>TabBreakpoints[i][1]-1&&Y<TabBreakpoints[i][1]+1)||
									 (Y>TabBreakpoints[i+1][1]-1&&Y<TabBreakpoints[i+1][1]+1))
										return 0;
								if(Wire==TabElem[j])	return 0;
								Wire=TabElem[j];
							}
						}
						else if(TabElem[j]==Wire) Wire=NULL;
					}
					Y-=5;
					if(Left==1&&Y<TabBreakpoints[i+1][1])
					{
						X+=4;//badana jest prawa strona
						Y=TabBreakpoints[i][1]+2;
						Left=0;
					}
				}while(Y>TabBreakpoints[i+1][1]);
			}
		else//linia pozioma
			if(TabBreakpoints[i][0]<TabBreakpoints[i+1][0])//linia pozioma w prawo
			{
				X-=2;
				Y-=2;//badana g�rna strona
				char Up=1;
				do
				{
				if(X<30||Y>440||Y<60)	return 0;
					for(int j=0;j<NumOfElem;j++)
					{
						if(this==TabElem[j]) j++;//nie bada si� tego samego elementu
						if(j>=NumOfElem) break;
						//zabezpieczenie przed przekroczeniem tabeli
						if(TabElem[j]->IsYourArea(X,Y))
						{
							if(TabElem[j]!=this->TabPrevElem[0]&&
								 TabElem[j]!=this->TabNextElem[0])
								 if(TabElem[j]->ElementType()!=wire&&
										TabElem[j]->ElementType()!=inbus)
										return 0;
								//znaleziony element nie jest nast�pny ani poprzedni
							if(TabElem[j]==this->TabPrevElem[0]&&
								 this->TabPrevElem[0]->ElementType()==cbus)
								 return 0;
							if(this->IsElemPrev(TabElem[j]))
								if(X<TabBreakpoints[0][0]-2) return 0;
							if(this->IsElemNext(TabElem[j]))
								if(X>TabBreakpoints[BreakpointsNum-1][0]+2) return 0;
							if(TabElem[j]->ElementType()==wire)
							{
								if((X>TabBreakpoints[i][0]-1&&X<TabBreakpoints[i][0]+1)||
									 (X>TabBreakpoints[i+1][0]-1&&X<TabBreakpoints[i+1][0]+1))
										return 0;
								if(Wire==TabElem[j])	return 0;
								Wire=TabElem[j];
							}
						}
						else if(TabElem[j]==Wire) Wire=NULL;
					}

					X+=5;
					if(Up==1&&X>TabBreakpoints[i+1][0])
					{
						Y+=4;//badana jest dolna strona
						X=TabBreakpoints[i][0]-2;
						Up=0;
					}
				}while(X<TabBreakpoints[i+1][0]);
			}
			else//linia pozioma w lewo
			{
				X+=2;
				Y-=2;//badana g�rna strona
				char Up=1;
				do
				{
				if(X<30||Y>440||Y<60)	return 0;
					for(int j=0;j<NumOfElem;j++)
					{
						if(this==TabElem[j]) j++;//nie bada si� tego samego elementu
						if(j>=NumOfElem) break;
						//zabezpieczenie przed przekroczeniem tabeli
						if(TabElem[j]->IsYourArea(X,Y))
						{
							if(TabElem[j]->ElementType()!=wire&&
								 TabElem[j]->ElementType()!=inbus) return 0;
							if(TabElem[j]->ElementType()==wire)
							{
								if((X>TabBreakpoints[i][0]-1&&X<TabBreakpoints[i][0]+1)||
									 (X>TabBreakpoints[i+1][0]-1&&X<TabBreakpoints[i+1][0]+1))
										return 0;
								if(Wire==TabElem[j])	return 0;
								Wire=TabElem[j];
							}
						}
						else if(TabElem[j]==Wire) Wire=NULL;
					}
					X-=5;
					if(Up==1&&X<TabBreakpoints[i+1][0])
					{
						Y+=4;//badana jest g�rna strona
						X=TabBreakpoints[i][0]+2;
						Up=0;
					}
				}while(X>TabBreakpoints[i+1][0]);
			}
	}
	for(i=1;i<BreakpointsNum-1;i++)
		for(int j=0;j<NumOfElem;j++)
		{
			if(this==TabElem[j]) j++;//nie bada si� tego samego elementu
			if(j>=NumOfElem) break;
			//zabezpieczenie przed przekroczeniem tabeli
			if(TabElem[j]->IsYourArea(TabBreakpoints[i][0],TabBreakpoints[i][1]))
					return 0;
			//punkt za�amania nie mo�e le�e� na �adnym z element�w
		}
	for(i=0;i<BreakpointsNum-1;i++)
	{
		if(TabBreakpoints[i][0]!=TabBreakpoints[i+1][0]&&
			 TabBreakpoints[i][1]!=TabBreakpoints[i+1][1])
				return 0;
		if(TabBreakpoints[i][0]==TabBreakpoints[i+1][0]&&
			 TabBreakpoints[i][1]==TabBreakpoints[i+1][1])
				return 0;
		for(int j=0;j<BreakpointsNum;j++)
		{
			if(TabBreakpoints[j][0]==TabBreakpoints[i][0])
				if((TabBreakpoints[j][1]<TabBreakpoints[i][1]&&
						TabBreakpoints[j][1]>TabBreakpoints[i+1][1])||
					 (TabBreakpoints[j][1]>TabBreakpoints[i][1]&&
						TabBreakpoints[j][1]<TabBreakpoints[i+1][1])) return 0;
			if(TabBreakpoints[j][1]==TabBreakpoints[i][1])
				if((TabBreakpoints[j][0]<TabBreakpoints[i][0]&&
						TabBreakpoints[j][0]>TabBreakpoints[i+1][0])||
					 (TabBreakpoints[j][0]>TabBreakpoints[i][0]&&
						TabBreakpoints[j][0]<TabBreakpoints[i+1][0])) return 0;
		}
	}
	return 1;
}

char CWire::FormatJunctions(CElement**TabElem,int NumOfElem)
{
	int PrevJunctionPos[MaxJunctionNum][2];
	int NewJunctionPos[MaxJunctionNum][2];
	for(int i=0;i<JunctionNum;i++)
	{
		PrevJunctionPos[i][0]=TabJunction[i]->GetXCorner();
		PrevJunctionPos[i][1]=TabJunction[i]->GetYCorner();
	}
	for(i=0;i<JunctionNum;i++)
	{              	
		int TmpX=PrevJunctionPos[i][0];
		int TmpY=PrevJunctionPos[i][1];
		long int TabDist[2*MaxBreakpointsNum-1];
		int MinIndex=0;
		long int MinValue=100000;
		char OK;
		for(int j=0;j<BreakpointsNum-1;j++)
		{
			if(TabBreakpoints[j][0]==TabBreakpoints[j+1][0])//linia pionowa
				TabDist[j]=
						(long int)(TmpX-TabBreakpoints[j][0])*(TmpX-TabBreakpoints[j][0]);
			else if(TabBreakpoints[j][1]==TabBreakpoints[j+1][1])//linia pozioma
				TabDist[j]=
						(long int)(TmpY-TabBreakpoints[j][1])*(TmpY-TabBreakpoints[j][1]);
		}
		for(j=BreakpointsNum-1;j<2*BreakpointsNum-1;j++)
			TabDist[j]=(long int)(TmpX-TabBreakpoints[j-BreakpointsNum+1][0])*
								 (long int)(TmpX-TabBreakpoints[j-BreakpointsNum+1][0])+
								 (long int)(TmpY-TabBreakpoints[j-BreakpointsNum+1][1])*
								 (long int)(TmpY-TabBreakpoints[j-BreakpointsNum+1][1]);
		char End=0;
		do
		{
			MinValue=100000;
			OK=0;
			for(j=0;j<2*BreakpointsNum-1;j++)
				if(TabDist[j]<MinValue)
				{
					MinValue=TabDist[j];
					MinIndex=j;
				}//znalezienie minimum
			if(MinValue==100000) End=1;
			TabDist[MinIndex]=100000;//wpisanie du�ej warto�ci-odleg�o��
															//nie b�dzie wi�cej brana pod uwag�
			if(MinIndex<BreakpointsNum-1)//najkr�tsza jest odleg�o�� do linii
			{
				OK=0;
				if(TabBreakpoints[MinIndex][0]==TabBreakpoints[MinIndex+1][0])
				//linia pionowa
				{
					if(TabBreakpoints[MinIndex][1]<TabBreakpoints[MinIndex+1][1])
						//linia w d��
					{
						if(TmpY>=TabBreakpoints[MinIndex][1]+10&&
							 TmpY<=TabBreakpoints[MinIndex+1][1]-10)
							{
								TmpX=TabBreakpoints[MinIndex][0];
								OK++;
							}
					}
					else//linia w g�r�
						if(TmpY>=TabBreakpoints[MinIndex][1]-10&&
							 TmpY<=TabBreakpoints[MinIndex+1][1]+10)
							{
								TmpX=TabBreakpoints[MinIndex][0];
								OK++;
							}
				}
				else//linia pozioma
				{
					if(TabBreakpoints[MinIndex][0]<TabBreakpoints[MinIndex+1][0])
						//linia w prawo
					{
						if(TmpX>=TabBreakpoints[MinIndex][0]+10&&
							 TmpX<=TabBreakpoints[MinIndex+1][0]-10)
							{
								TmpY=TabBreakpoints[MinIndex][1];
								OK++;
								putpixel(TmpX,TmpY,BLACK);
							}
					}
					else//linia w lewo
						if(TmpX>=TabBreakpoints[MinIndex][0]-10&&
							 TmpX<=TabBreakpoints[MinIndex+1][0]+10)
							{
								TmpY=TabBreakpoints[MinIndex][1];
								OK++;
							}
				}
				if(OK)
				{
					for(int k=0;k<i;k++)
					{
						if((TmpX<=NewJunctionPos[k][0]+4&&TmpX>=NewJunctionPos[k][0]-4)&&
							 (TmpY<=NewJunctionPos[k][1]+4&&TmpY>=NewJunctionPos[k][1]-4))
						{
							OK=0;
							break;
						}
					}
					if(OK)
						if(!TabJunction[i]->Move(TmpX,TmpY,TabElem,NumOfElem)) OK=0;
				}
			}
			else//najkr�tsza jest odleg�o�� do punktu za�amania
			{
				MinIndex=MinIndex-BreakpointsNum+1;
				int Number=0;
				char AllTested=0;//flaga zako�czenia szukania
				if(MinIndex==BreakpointsNum-1) MinIndex--;
				do
				{
					OK=0;
					Number+=10;
					if(TabBreakpoints[MinIndex][0]==TabBreakpoints[MinIndex+1][0])
					//linia pionowa
					{
						if(TabBreakpoints[MinIndex][1]<TabBreakpoints[MinIndex+1][1])
							//linia w d��
						{
							if(TabBreakpoints[MinIndex][1]+Number<=
								 TabBreakpoints[MinIndex+1][1]-10)//jest miejsce
							{
								TmpX=TabBreakpoints[MinIndex][0];
								TmpY=TabBreakpoints[MinIndex][1]+Number;
								OK++;
							}
						}
						else//linia w g�r�
						{
							if(TabBreakpoints[MinIndex][1]-Number>=
								 TabBreakpoints[MinIndex+1][1]+10)//jest miejsce
							{
								TmpX=TabBreakpoints[MinIndex][0];
								TmpY=TabBreakpoints[MinIndex][1]-Number;
								OK++;
							}
						}
					}
					else//linia pozioma
					{
						if(TabBreakpoints[MinIndex][0]<TabBreakpoints[MinIndex+1][0])
							//linia w prawo
						{
							if(TabBreakpoints[MinIndex][0]+Number<=
								 TabBreakpoints[MinIndex+1][0]-10)//jest miejsce
							{
								TmpX=TabBreakpoints[MinIndex][0]+Number;
								TmpY=TabBreakpoints[MinIndex][1];
								OK++;
							}
						}
						else//linia w lewo
						{
							if(TabBreakpoints[MinIndex][0]-Number>=
								 TabBreakpoints[MinIndex+1][0]+10)//jest miejsce
							{
								TmpX=TabBreakpoints[MinIndex][0]-Number;
								TmpY=TabBreakpoints[MinIndex][1];
								OK++;
							}
						}
					}
					if(OK)
					{
						AllTested=0;
						for(int k=0;k<i;k++)
							if((TmpX<=NewJunctionPos[k][0]+4&&TmpX>=NewJunctionPos[k][0]-4)&&
								 (TmpY<=NewJunctionPos[k][1]+4&&TmpY>=NewJunctionPos[k][1]-4))
							{
								OK=0;
								break;
							}//sprawdzenie czy w�ze� nie le�y na innym w��le
						if(OK)
							if(!TabJunction[i]->Move(TmpX,TmpY,TabElem,NumOfElem)) OK=0;
							//gdy przesuni�cie si� nie uda, to OK=0
					}
					else AllTested=1;
				}while(!OK&&!AllTested);
			}
		}while(!OK&&!End);
		if(!OK)//nie uda�o si� sformatowa� w�z�a
		{
			for(j=JunctionNum-1;j>=0;j--)
				TabJunction[j]->Move(PrevJunctionPos[j][0],PrevJunctionPos[j][1],
														 TabElem,NumOfElem);//powr�t w�z��w
																								//na dawne pozycje
			return 0;
		}
		NewJunctionPos[i][0]=TabJunction[i]->GetXCorner();
		NewJunctionPos[i][1]=TabJunction[i]->GetYCorner();
	}
	return 1;
}

char CWire::FormatLine(int i,CElement**TabElem,int NumOfElem)
{
	if(i==3)
	{
		TabBreakpoints[BreakpointsNum-2][0]=TabBreakpoints[BreakpointsNum-3][0];
		TabBreakpoints[BreakpointsNum-2][1]=TabBreakpoints[BreakpointsNum-1][1];
		if(Check(TabElem,NumOfElem))
			if(FormatJunctions(TabElem,NumOfElem)) return 1;
		TabBreakpoints[BreakpointsNum-2][1]=TabBreakpoints[BreakpointsNum-3][1];
		TabBreakpoints[BreakpointsNum-2][0]=TabBreakpoints[BreakpointsNum-1][0];
		if(Check(TabElem,NumOfElem))
			if(FormatJunctions(TabElem,NumOfElem)) return 1;
		return 0;
	}
	int Tmp1X=TabBreakpoints[BreakpointsNum-i][0];
	int Tmp1Y=TabBreakpoints[BreakpointsNum-i][1];
	int Tmp2X;
	int Tmp2Y;
	TabBreakpoints[BreakpointsNum-i+1][0]=TabBreakpoints[BreakpointsNum-i][0];
	TabBreakpoints[BreakpointsNum-i+1][1]=TabBreakpoints[BreakpointsNum-i][1];
	int Number=0;
	do
	{
		Tmp2X=TabBreakpoints[BreakpointsNum-i+1][0];
			//zachowanie zmienionej warto�ci X
		TabBreakpoints[BreakpointsNum-i+1][0]=Tmp1X;
			//pierwotna warto�� X
		TabBreakpoints[BreakpointsNum-i+1][1]+=Number;
		if(FormatLine(i-1,TabElem,NumOfElem)) return 1;
		TabBreakpoints[BreakpointsNum-i+1][0]=Tmp2X;
			//przywr�cenie zmienionej warto�ci X
		Tmp2Y=TabBreakpoints[BreakpointsNum-i+1][1];
			//zachowanie zmienionej warto�ci Y
		TabBreakpoints[BreakpointsNum-i+1][1]=Tmp1Y;
			//pierwotna warto�� Y
		TabBreakpoints[BreakpointsNum-i+1][0]+=Number;
		if(FormatLine(i-1,TabElem,NumOfElem)) return 1;
		TabBreakpoints[BreakpointsNum-i+1][1]=Tmp2Y;
			//przywr�cenie zmienionej warto�ci Y
		if(Number>0) Number+=5;
		else Number-=5;
		Number*=-1;
	}while(Number<600);
	return 0;
}

char CWire::Autoformat(CElement**TabElem,int NumOfElem)
{
	int TmpTabBreakpoints[MaxBreakpointsNum][2];
	int TmpBreakpointsNum=BreakpointsNum;
	for(int i=0;i<BreakpointsNum;i++)
	{
		TmpTabBreakpoints[i][0]=TabBreakpoints[i][0];
		TmpTabBreakpoints[i][1]=TabBreakpoints[i][1];
	}//zachowanie punkt�w za�amania
	TabBreakpoints[0][0]=X1;
	TabBreakpoints[0][1]=Y1;
	TabBreakpoints[1][0]=X2;
	TabBreakpoints[1][1]=Y2;
	BreakpointsNum=2;
	//powy�sze operacje maj� na celu zlikwidowanie dotychczasowych punkt�w
		//za�ama�
	if(X1==X2||Y1==Y2)
		if(Check(TabElem,NumOfElem)&&FormatJunctions(TabElem,NumOfElem)) return 1;
	for(i=3;i<=MaxBreakpointsNum;i++)
	{
		TabBreakpoints[BreakpointsNum][0]=X2;
		TabBreakpoints[BreakpointsNum][1]=Y2;
		BreakpointsNum++;//zwi�kszenie ilo�ci punkt�w za�amania o 1
		if(FormatLine(i,TabElem,NumOfElem)) return 1;
	}
	BreakpointsNum=TmpBreakpointsNum;
	for(i=0;i<BreakpointsNum;i++)
	{
		TabBreakpoints[i][0]=TmpTabBreakpoints[i][0];
		TabBreakpoints[i][1]=TmpTabBreakpoints[i][1];
	}//przywr�cenie poprzednich punkt�w za�amania*/
	if(!FormatJunctions(TabElem,NumOfElem)) return 0;
	return 0;
}

TElementType CWire::ElementType()
{
	return wire;
}

void CWire::ClickElement()
{}

char CWire::LinkNextElem(CElement*NextElem,int X,int Y)
{
	if(NextElem->ElementType()!=wire)
	{
		if(TabNextElem[0]!=NULL) return 0;
		TabNextElem[0]=NextElem;
		return 1;
	}//do��czenie elementu na ko�cu druta
	//dalej - po��czenie za pomoc� w�z�a
	int XTmp1;
	int YTmp1;
	for(int i=0;i<JunctionNum;i++)
	{
		XTmp1=TabJunction[i]->GetXCorner();
		YTmp1=TabJunction[i]->GetYCorner();
		if(X<XTmp1+6&&X>XTmp1-6&&
			 Y<YTmp1+6&&Y>YTmp1-6)
			 //powi�zanie tworzy si� w okolicy istniej�cego w�z�a
		{
			return 0;
		}
	}
	int MinX;
	int MaxX;
	int MinY;
	int MaxY;
	if(JunctionNum>=MaxJunctionNum) return 0;
	for(i=0;i<BreakpointsNum-1;i++)
	{
		if(TabBreakpoints[i][0]<TabBreakpoints[i+1][0])
		{
			MinX=TabBreakpoints[i][0];
			MaxX=TabBreakpoints[i+1][0];
		}
		else
		{
			MinX=TabBreakpoints[i+1][0];
			MaxX=TabBreakpoints[i][0];
		}
		if(TabBreakpoints[i][1]<TabBreakpoints[i+1][1])
		{
			MinY=TabBreakpoints[i][1];
			MaxY=TabBreakpoints[i+1][1];
		}
		else
		{
			MinY=TabBreakpoints[i+1][1];
			MaxY=TabBreakpoints[i][1];
		}
		if(MinY==MaxY&&Y>=MinY-2&&Y<=MinY+2&&X>=MinX&&X<MaxX)
		{
			Y=TabBreakpoints[i][1];
			break;
		}
		if(MinX==MaxX&&X>=MinX-2&&X<=MinX+2&&Y>=MinY&&Y<MaxY)
		{
			X=TabBreakpoints[i][0];
			break;
		}//sprawdzenie, czy w�ze� nie znajduje si� za blisko punktu przegiecia
	}
	TabJunction[JunctionNum]=new CJunction(X,Y);
	TabJunction[JunctionNum]->LinkPrevElem(this,0,0);
	TabJunction[JunctionNum]->LinkNextElem(NextElem,X,Y);
	JunctionNum++;
	return 1;
}

char CWire::LinkPrevElem(CElement*PrevElem,int X,int Y)
{
	if(TabPrevElem[0]!=NULL) return 0;
	TabPrevElem[0]=PrevElem;
	return 1;
}

char CWire::DelNextElem(CElement*DelElem)
{
	for(int i=0;i<OutNum;i++)
		if(TabNextElem[i]==DelElem)
		{
			TabNextElem[i]=NULL;
			return 1;
		}
	for(i=0;i<JunctionNum;i++)
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

int CWire::DeleteConnections(CElement**TabElem,int NumOfElem,char Main)
{
	int DelElemNum=1;//trzeba wliczy� tak�e ten element
	for(int i=0;i<NumOfElem;i++)
		if(this==TabElem[i]) break;//znalezienie indeksu bie��cego elementu
	for(int j=i;j<NumOfElem;j++)
		TabElem[j]=TabElem[j+1];//wyrzucenie elementu z tabeli
	NumOfElem--;//lokalne zmniejszenie warto�ci - nie ma skutku na zewn�trz
	if(Main==1)
		TabPrevElem[0]->DelNextElem(this);
		//gdy funkcja zosta�a wywo�ana przez bramk� (element bezpo�rednio
		//wskazany do usuni�cia przez u�ytkownika), to trzeba usun�� po��czenie
		//elementu poprzedniego z aktualnym, a gdy funkcja zosta�a wywo�ana przez
		//w�ze�, to wy�ej opisane po��czenie zostanie i tak zniszczone
	TabNextElem[0]->DelPrevElem(this);
	int PrevJunctionNum=JunctionNum;
	for(i=0;i<PrevJunctionNum;i++)
	{
		DelElemNum+=TabJunction[i]->DeleteConnections(TabElem,NumOfElem);
		delete TabJunction[i];
		JunctionNum--;
	}
	this->DrawElem(BackgroundColour);
	return DelElemNum;
}

char CWire::SaveElement(CElement**TabElem,int NumOfElem,FILE*File,char Phase)
{
	if(Phase==1)//pierwsza faza zachowywania
	{
		char Type=8;
		fwrite(&Type,sizeof(char),1,File);
		fwrite(&BreakpointsNum,sizeof(int),1,File);
		for(int i=0;i<BreakpointsNum;i++)
		{
			fwrite(&TabBreakpoints[i][0],sizeof(int),1,File);
			fwrite(&TabBreakpoints[i][1],sizeof(int),1,File);
		}
		fwrite(&JunctionNum,sizeof(int),1,File);
		for(i=0;i<JunctionNum;i++)
			if(!TabJunction[i]->SaveElement(TabElem,NumOfElem,File,1)) return 0;
				//zachowanie w�z��w w pierwszej fazie
	}
	else//druga faza zachowywania
	{
		int PrevElemPos;
		if(TabPrevElem[0]!=NULL)
		{
			for(int j=0;j<NumOfElem;j++)
				if(TabElem[j]==TabPrevElem[0]) break;
					//ustalenie indeksu poprzedniego elementu
			if(j>=NumOfElem) return 0;//b��d - element nie zosta� znaleziony
			PrevElemPos=j;
		}
		else PrevElemPos=-1;//nie ma elementu poprzedniego
		fwrite(&PrevElemPos,sizeof(int),1,File);
			//zachowanie indeksu poprzedniego elementu
		int NextElemPos;
		if(TabNextElem[0]!=NULL)
		{
			for(int j=0;j<NumOfElem;j++)
				if(TabElem[j]==TabNextElem[0]) break;
					//ustalenie indeksu poprzedniego elementu
			if(j>=NumOfElem) return 0;//b��d - element nie zosta� znaleziony
			NextElemPos=j;
		}
		else NextElemPos=-1;//nie ma elementu poprzedniego
		fwrite(&NextElemPos,sizeof(int),1,File);
			//zachowanie indeksu nast�pnego elementu
		for(int i=0;i<JunctionNum;i++)
			if(!TabJunction[i]->SaveElement(TabElem,NumOfElem,File,2)) return 0;
				//zachowanie w�z��w w drugiej fazie
	}
	return 1;
}

char CWire::LoadElement(CElement**TabElem,int NumOfElem,
													 FILE*File,char Phase)
{
	if(Phase==1)//pierwsza faza odczytu
	{
		if(feof(File)) return 0;
		fread(&BreakpointsNum,sizeof(int),1,File);
		if(BreakpointsNum>MaxBreakpointsNum) return 0;
		for(int i=0;i<BreakpointsNum;i++)
		{
			if(feof(File)) return 0;
			fread(&TabBreakpoints[i][0],sizeof(int),1,File);
			if(TabBreakpoints[i][0]<0||TabBreakpoints[i][0]>639) return 0;
			if(feof(File)) return 0;
			fread(&TabBreakpoints[i][1],sizeof(int),1,File);
			if(TabBreakpoints[i][1]<0||TabBreakpoints[i][1]>639) return 0;
		}
		X1=TabBreakpoints[0][0];
		Y1=TabBreakpoints[0][1];
		X2=TabBreakpoints[BreakpointsNum-1][0];
		Y2=TabBreakpoints[BreakpointsNum-1][1];
		if(feof(File)) return 0;
		fread(&JunctionNum,sizeof(int),1,File);
		if(JunctionNum>MaxJunctionNum) return 0;
		for(i=0;i<JunctionNum;i++)
		{
			char Type;
			if(feof(File)) return 0;
			fread(&Type,sizeof(char),1,File);
			if(Type!=7) return 0;//odczytywany element nie jest w�z�em
			TabJunction[i]=new CJunction(0,0);
			if(!TabJunction[i]->LoadElement(TabElem,NumOfElem,File,1)) return 0;
				//odczyt w�z��w w pierwszej fazie
		}
	}
	else//druga faza odczytu
	{
		int PrevElemPos;
		if(feof(File)) return 0;
		fread(&PrevElemPos,sizeof(int),1,File);
		if(PrevElemPos>=NumOfElem) return 0;
		if(PrevElemPos<0)//element nie by� po��czony
			TabPrevElem[0]=NULL;
		else TabPrevElem[0]=TabElem[PrevElemPos];
			//element by� po��czony z elementem o odczytanym indeksie
		int NextElemPos;
		if(feof(File)) return 0;
		fread(&NextElemPos,sizeof(int),1,File);
		if(NextElemPos>=NumOfElem) return 0;
		if(NextElemPos<0)//element nie by� po��czony
			TabNextElem[0]=NULL;
		else TabNextElem[0]=TabElem[NextElemPos];
			//element by� po��czony z elementem o odczytanym indeksie
		for(int i=0;i<JunctionNum;i++)
			if(!TabJunction[i]->LoadElement(TabElem,NumOfElem,File,2)) return 0;
				//odczyt w�z��w w pierwszej fazie
	}
	return 1;
}

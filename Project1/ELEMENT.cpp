#include "element.h"

CElement::~CElement()
{}

int CElement::IsOnBoard()
{
	if (X1>150 && X2<610 && Y1>60 && Y2<440) return 1;
	return 0;
}

int CElement::IsYourArea(int X, int Y)
{
	if (X >= X1 && X <= X2 && Y >= Y1 && Y <= Y2) return 1;
	return 0;
}

char CElement::IsElemPrev(CElement*Element)
{
	for (int j = 0; j<InNum; j++)
		if (TabPrevElem[j] == Element) return 1;
	return 0;
}

char CElement::IsElemNext(CElement*Element)
{
	for (int j = 0; j<OutNum; j++)
		if (TabNextElem[j] == Element) return 1;
	return 0;
}

int CElement::GetXCorner(char Right)
{
	if (Right) return X2;
	return X1;
}

int CElement::GetYCorner(char Down)
{
	if (Down) return Y2;
	return Y1;
}

int CElement::IsAreaFree(CElement**TabElem, int NumOfElem)
{
	int ElemNum;
	int i;
	for (i = 0; i <= NumOfElem; i++) if (this == TabElem[i])
	{
		ElemNum = i;
		break;
	}//ustalenie numeru elementu
	if (X2<0) X2 = X1;
	if (Y2<0) Y2 = Y1;
	int X = X1;
	int Y = Y1;
	if (TabElem[ElemNum]->ElementType() == _wire) return 0;//wyst�pi� b��d
	for (i = 0; i<NumOfElem; i++)
	{
		if (i == ElemNum) i++;//nie bada si� tego samego elementu
		if (i >= NumOfElem) break;//zabezpieczenie przed przekroczeniem tabeli
		do
		{
			if (TabElem[i]->IsYourArea(X, Y))
				if (!TabElem[ElemNum]->IsElemPrev(TabElem[i]) &&
					!TabElem[ElemNum]->IsElemNext(TabElem[i])) return 0;
			//znaleziony element nie jest nast�pny ani poprzedni
			X += 5;
		} while (X<X2);
		X = X2;
		do
		{
			if (TabElem[i]->IsYourArea(X, Y))
				if (!TabElem[ElemNum]->IsElemPrev(TabElem[i]) &&
					!TabElem[ElemNum]->IsElemNext(TabElem[i])) return 0;
			//znaleziony element nie jest nast�pny ani poprzedni
			Y += 5;
		} while (Y<Y2);
		Y = Y2;
		do
		{
			if (TabElem[i]->IsYourArea(X, Y))
				if (!TabElem[ElemNum]->IsElemPrev(TabElem[i]) &&
					!TabElem[ElemNum]->IsElemNext(TabElem[i])) return 0;
			//znaleziony element nie jest nast�pny ani poprzedni
			X -= 5;
		} while (X>X1);
		X = X1;
		do
		{
			if (TabElem[i]->IsYourArea(X, Y))
				if (!TabElem[ElemNum]->IsElemPrev(TabElem[i]) &&
					!TabElem[ElemNum]->IsElemNext(TabElem[i])) return 0;
			//znaleziony element nie jest nast�pny ani poprzedni
			Y -= 5;
		} while (Y>Y1);
	}
	return 1;
}

char CElement::Move(int X, int Y, CElement**TabElem, int NumOfElem)
{
	if (Movable == no) return 0;
	int X1Prev = X1;
	int Y1Prev = Y1;
	int X2Prev = X2;
	int Y2Prev = Y2;
	X2 = X2 - X1 + X;
	Y2 = Y2 - Y1 + Y;
	X1 = X;
	Y1 = Y;
	if (!(IsOnBoard() && IsAreaFree(TabElem, NumOfElem)))
	{
		X2 = X2Prev;
		Y2 = Y2Prev;
		X1 = X1Prev;
		Y1 = Y1Prev;
		return 0;
	}//sprawdzenie poprawno�ci nowego po�o�enia elementu
	int i;
	for (i = 0; i<InNum; i++)
		if (TabPrevElem[i] != NULL)
		{
			int TmpX = TabPrevElem[i]->GetXCorner(1);
			int TmpY = TabPrevElem[i]->GetYCorner(1);
			//potrzebne s� wsp��rz�dne ko�ca linii
			if (TabPrevElem[i]->IsOnBoard())
				TabPrevElem[i]->DrawElem(BackgroundColour);
			//po��czenie zniknie, je�eli by�o narysowane
			TabPrevElem[i]->MoveEnd(TmpX + X - X1Prev, TmpY + Y - Y1Prev);
			if (!TabPrevElem[i]->Autoformat(TabElem, NumOfElem))
			{
				X2 = X2Prev;
				Y2 = Y2Prev;
				X1 = X1Prev;
				Y1 = Y1Prev;
				TabPrevElem[i]->MoveEnd(TmpX, TmpY);
				for (int j = i - 1; j >= 0; j--)
					if (TabPrevElem[j] != NULL)
					{
						int TmpX = TabPrevElem[j]->GetXCorner(1);
						int TmpY = TabPrevElem[j]->GetYCorner(1);
						//potrzebne s� wsp��rz�dne ko�ca linii
						TabPrevElem[j]->MoveEnd(TmpX - X + X1Prev, TmpY - Y + Y1Prev);
						TabPrevElem[j]->Autoformat(TabElem, NumOfElem);
					}//poniewa� kt�rej� z linii nie da�o si� sformatowa�,
					 //trzeba przywr�ci� po�o�enie wcze�niej sformatowanych linii
				return 0;
			}
		}
	for (i = 0; i<OutNum; i++)
		if (TabNextElem[i] != NULL)
		{
			int TmpX = TabNextElem[i]->GetXCorner();
			int TmpY = TabNextElem[i]->GetYCorner();
			if (TabNextElem[i]->IsOnBoard())
				TabNextElem[i]->DrawElem(BackgroundColour);
			//po��czenie zniknie, je�eli by�o narysowane
			TabNextElem[i]->MoveBeg(TmpX + X - X1Prev, TmpY + Y - Y1Prev);
			if (!TabNextElem[i]->Autoformat(TabElem, NumOfElem))
			{
				X2 = X2Prev;
				Y2 = Y2Prev;
				X1 = X1Prev;
				Y1 = Y1Prev;
				TabNextElem[i]->MoveBeg(TmpX, TmpY);
				int j;
				for (j = i - 1; j >= 0; j--)
					if (TabPrevElem[j] != NULL)
					{
						int TmpX = TabPrevElem[j]->GetXCorner(1);
						int TmpY = TabPrevElem[j]->GetYCorner(1);
						//potrzebne s� wsp��rz�dne ko�ca linii
						TabPrevElem[j]->MoveBeg(TmpX - X + X1Prev, TmpY - Y + Y1Prev);
						TabPrevElem[j]->Autoformat(TabElem, NumOfElem);
					}//poniewa� kt�rej� z linii nie da�o si� sformatowa�,
					 //trzeba przywr�ci� po�o�enie wcze�niej sformatowanych linii
				for (j = InNum - 1; j >= 0; j--)
					if (TabPrevElem[j] != NULL)
					{
						int TmpX = TabPrevElem[j]->GetXCorner(1);
						int TmpY = TabPrevElem[j]->GetYCorner(1);
						//potrzebne s� wsp��rz�dne ko�ca linii
						TabPrevElem[j]->MoveEnd(TmpX - X + X1Prev, TmpY - Y + Y1Prev);
						TabPrevElem[j]->Autoformat(TabElem, NumOfElem);
					}//poniewa� kt�rej� z linii nie da�o si� sformatowa�,
					 //trzeba przywr�ci� po�o�enie wcze�niej sformatowanych linii
				return 0;
			}
		}
	return 1;
}

void CElement::MoveBeg(int X, int Y)
{}

void CElement::MoveEnd(int X, int Y)
{}

char CElement::LinkNextElem(CElement*NextElem, int X, int Y)
{
	if (NextElem->ElementType() != _wire) return 0;
	//bramka mo�e by� po��czona tylko z drutem
	if (TabNextElem[0] != NULL) return 0;//istnieje ju� element nast�pny
	TabNextElem[0] = NextElem;
	NextElem->MoveBeg(X1 + 25, Y1 + 14);
	return 1;
}

char CElement::LinkPrevElem(CElement*PrevElem, int X, int Y)
{
	if (PrevElem->ElementType() != _wire) return 0;
	//bramka mo�e by� po��czona tylko z drutem
	X -= X1;
	Y -= Y1;//zmienne X i Y okre�laj� wzgl�dne po�o�enie
	int MinY;
	int MaxY;
	char Key = 0;
	int Hight = (Y2 - Y1) / InNum;
	if ((Y2 - Y1) / InNum) Key = 1;//wysoko�� jest liczb� nieparzyst�
	int i;
	for (i = 0; i<InNum; i++)
	{
		if (Key != 0)
		{
			if (Key == 1)
			{
				Hight += 1;
				Key = 2;
			}
			else
			{
				Hight -= 1;
				Key = 1;
			}
		}
		MinY = i * Hight + 2;
		MaxY = (i + 1)*Hight + 2;
		if (i == InNum - 1) MaxY = Y2;
		if (Y >= MinY && Y <= MaxY) break;
	}
	if (TabPrevElem[i] != NULL)
		for (i = 0; i<InNum; i++)
			if (TabPrevElem[i] == NULL) break;
	if (i == InNum) return 0;
	TabPrevElem[i] = PrevElem;
	switch (i)
	{
	case 0:Y = 12; break;
	case 1:Y = 17; break;
	}
	PrevElem->MoveEnd(X1 + 3, Y1 + Y);
	return 1;
}

char CElement::DelNextElem(CElement*DelElem)
{
	for (int i = 0; i<OutNum; i++)
		if (TabNextElem[i] == DelElem)
		{
			TabNextElem[i] = NULL;
			return 1;
		}
	return 0;
}

char CElement::DelPrevElem(CElement*DelElem)
{
	for (int i = 0; i<InNum; i++)
		if (TabPrevElem[i] == DelElem)
		{
			TabPrevElem[i] = NULL;
			return 1;
		}
	return 0;
}

int CElement::DeleteConnections(CElement**TabElem, int NumOfElem, char Main)
{
	int DelElemNum = 1;//trzeba wliczy� tak�e ten element
					   //funkcja wirtualna jest zdefiniowana w tym miejscu dla bramek i wyj��,
					   //druty i w�z�y maj� inne cia�o funkcji
	int i,j;
	for (i = 0; i<NumOfElem; i++)
		if (this == TabElem[i]) break;//znalezienie indeksu bie��cego elementu
	for (j = i; j<NumOfElem; j++)
		TabElem[j] = TabElem[j + 1];//wyrzucenie elementu z tabeli
	NumOfElem--;//lokalne zmniejszenie warto�ci - nie ma skutku na zewn�trz
	for (i = 0; i<InNum; i++)
		if (TabPrevElem[i] != NULL)
		{
			CElement*Temp = TabPrevElem[i];
			DelElemNum += TabPrevElem[i]->DeleteConnections(TabElem, NumOfElem, 1);
			delete Temp;
		}
	for (i = 0; i<OutNum; i++)
		if (TabNextElem[i] != NULL)
		{
			CElement*Temp = TabNextElem[i];
			DelElemNum += TabNextElem[i]->DeleteConnections(TabElem, NumOfElem, 1);
			delete Temp;
		}
	return DelElemNum;
}

char CElement::Autoformat(CElement**TabElem, int NumOfElem)
{
	return 0;
}

char CElement::SaveElement(CElement**TabElem, int NumOfElem,
	FILE*File, char Phase)
{
	if (Phase == 1)//pierwsza faza zachowywania
	{
		char Type;
		switch (this->ElementType())
		{
		case _and:Type = 0; break;
		case _or :Type = 1; break;
		case _not:Type = 2; break;
		case _nand:Type = 3; break;
		case _nor:Type = 4; break;
		case _xor:Type = 5; break;
		case _output:Type = 6; break;
		case _junction:Type = 7; break;
		default:return 0;
		}
		fwrite(&Type, sizeof(char), 1, File);
		fwrite(&X1, sizeof(int), 1, File);
		fwrite(&Y1, sizeof(int), 1, File);
		fwrite(&X2, sizeof(int), 1, File);
		fwrite(&Y2, sizeof(int), 1, File);
		fwrite(&InNum, sizeof(int), 1, File);
	}
	else//druga faza zachowywania
	{
		int i,j;
		for (i = 0; i<InNum; i++)
		{
			int PrevElemPos;
			if (TabPrevElem[i] != NULL)
			{
				for (j = 0; j<NumOfElem; j++)
					if (TabElem[j] == TabPrevElem[i]) break;
				//ustalenie indeksu poprzednich element�w
				if (j >= NumOfElem) return 0;//b��d - element nie zosta� znaleziony
				PrevElemPos = j;
			}
			else PrevElemPos = -1;//nie ma elementu poprzedniego na i-tej pozycji
			fwrite(&PrevElemPos, sizeof(int), 1, File);
		}
		for (i = 0; i<OutNum; i++)
		{
			int NextElemPos;
			if (TabNextElem[i] != NULL)
			{
				for (int j = 0; j<NumOfElem; j++)
					if (TabElem[j] == TabNextElem[i]) break;
				//ustalenie indeksu poprzednich element�w
				if (j >= NumOfElem) return 0;//b��d - element nie zosta� znaleziony
				NextElemPos = j;
			}
			else NextElemPos = -1;//nie ma elementu poprzedniego na i-tej pozycji
			fwrite(&NextElemPos, sizeof(int), 1, File);
		}
	}
	return 1;
}

char CElement::LoadElement(CElement**TabElem, int NumOfElem,
	FILE*File, char Phase)
{
	if (Phase == 1)//pierwsza faza odczytu
	{
		if (feof(File)) return 0;
		fread(&X1, sizeof(int), 1, File);
		if (X1<0 || X1>639) return 0;
		if (feof(File)) return 0;
		fread(&Y1, sizeof(int), 1, File);
		if (Y1<0 || Y1>479) return 0;
		if (feof(File)) return 0;
		fread(&X2, sizeof(int), 1, File);
		if (X2<0 || X2>639) return 0;
		if (feof(File)) return 0;
		fread(&Y2, sizeof(int), 1, File);
		if (Y2<0 || Y2>479) return 0;
		if (feof(File)) return 0;
		fread(&InNum, sizeof(int), 1, File);
		if (InNum>2) return 0;
		if (feof(File)) return 0;
	}
	else//druga faza odczytu
	{
		int i;
		for (i = 0; i<InNum; i++)
		{
			int PrevElemPos;
			if (feof(File)) return 0;
			fread(&PrevElemPos, sizeof(int), 1, File);
			if (PrevElemPos>NumOfElem) return 0;
			if (PrevElemPos<0)//element nie by� po��czony
				TabPrevElem[i] = NULL;
			else TabPrevElem[i] = TabElem[PrevElemPos];
			//element by� po��czony z elementem o odczytanym indeksie
		}
		for (i = 0; i<OutNum; i++)
		{
			int NextElemPos;
			if (feof(File)) return 0;
			fread(&NextElemPos, sizeof(int), 1, File);
			if (NextElemPos>NumOfElem) return 0;
			if (NextElemPos<0)//element nie by� po��czony
				TabNextElem[i] = NULL;
			else TabNextElem[i] = TabElem[NextElemPos];
			//element by� po��czony z elementem o odczytanym indeksie
		}
	}
	return 1;
}

void CElement::draw_arc(SDL_Renderer* r, int x0, int y0, int radiusX, int radiusY, SDL_Color color)
{
	
	float pi = 3.1416;
	float pih = pi / 2.0; //half of pi

	const int prec = 27; // precision value; value of 1 will draw a diamond, 27 makes pretty smooth circles.
	float theta = 0;     // angle that will be increased each loop
	SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);

	//starting point
	int x = (float)radiusX * cos(theta);//start point
	int y = (float)radiusY * sin(theta);//start point
	int x1 = x;
	int y1 = y;

	//repeat until theta >= 90;
	float step = pih / (float)prec; // amount to add to theta each time (degrees)
	for (theta = step; theta <= pih; theta += step)//step through only a 90 arc (1 quadrant)
	{
		//get new point location
		x1 = (float)radiusX * cosf(theta) + 0.5; //new point (+.5 is a quick rounding method)
		y1 = (float)radiusY * sinf(theta) + 0.5; //new point (+.5 is a quick rounding method)

		//draw line from previous point to new point, ONLY if point incremented
		if ((x != x1) || (y != y1))//only draw if coordinate changed
		{
			SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1);//quadrant TR
			//SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1);//quadrant TL
			//SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1);//quadrant BL
			SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1);//quadrant BR
		}
		//save previous points
		x = x1;//save new previous point
		y = y1;//save new previous point
	}
	//arc did not finish because of rounding, so finish the arc
	if (x != 0)
	{
		x = 0;
		SDL_RenderDrawLine(r, x0 + x, y0 - y, x0 + x1, y0 - y1);//quadrant TR
		SDL_RenderDrawLine(r, x0 - x, y0 - y, x0 - x1, y0 - y1);//quadrant TL
		SDL_RenderDrawLine(r, x0 - x, y0 + y, x0 - x1, y0 + y1);//quadrant BL
		SDL_RenderDrawLine(r, x0 + x, y0 + y, x0 + x1, y0 + y1);//quadrant BR
	}
}

void CElement::draw_circle(SDL_Renderer *renderer,SDL_Point center, int radius, SDL_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx*dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
			}
		}
	}
}
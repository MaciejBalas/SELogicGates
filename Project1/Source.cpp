#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "iostream"
#include "WINDOW.h"
void draw_circle(SDL_Renderer *ren, SDL_Point center, int radius, SDL_Color color)
{
	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w; // horizontal offset
			int dy = radius - h; // vertical offset
			if ((dx*dx + dy * dy) <= (radius * radius))
			{
				SDL_RenderDrawPoint(ren, center.x + dx, center.y + dy);
			}
		}
	}
}
//void Control()
//{
//	int CurrentWinNum = 0;//numer aktualnie otwartego okna
//	int TotalWinNum = 1;//ilo˜† wszystkich otwartych okien
//	char NewPossib = 1;//flaga m¢wi¥ca, czy mo¾e powsta† nowe okno
//	char IsNew = 1;//flaga m¢wi¥ca, czy okno jest nowe
//	char IsPrev;//flaga m¢wi¥ca, czy istnieje okno wcze˜niejsze
//	int TabWin[MaxWinNum];//tablica flag m¢wi¥cych, czy okno istnieje
//	int i;
//	for (i = 0; i<MaxWinNum; i++) TabWin[i] = 0;
//	TabWin[0] = 1;
//	do
//	{
//		IsPrev = 0;
//		IsNext = 0;
//		for (i = 0; i<CurrentWinNum; i++)
//			if (TabWin[i] == 1)
//			{
//				IsPrev = 1;
//				break;
//			}
//		for (i = CurrentWinNum + 1; i<MaxWinNum; i++)
//			if (TabWin[i] == 1)
//			{
//				IsNext = 1;
//				break;
//			}
//		CWindow*Window = new CWindow(CurrentWinNum + 1, IsPrev, IsNext, NewPossib, IsNew);
//		IsNew = 0;
//		char WinResult = Window->Work();
//		if (WinResult == 0)//okno zostaje zamkni©te
//		{
//			TabWin[CurrentWinNum] = 0;
//			TotalWinNum--;
//			if (NewPossib == 0) NewPossib = 1;
//			//skasowane zostaˆo jakie˜ okno, wi©c mo¾na utworzy† nowe okno
//			for (i = CurrentWinNum + 1; i<MaxWinNum; i++)
//				if (TabWin[i] == 1)
//				{
//					CurrentWinNum = i;
//					break;
//				}
//			if (i >= MaxWinNum)//nie zostaˆo znalezione nast©pne otwarte okno
//				for (i = CurrentWinNum - 1; i >= 0; i--)
//					if (TabWin[i] == 1)
//					{
//						CurrentWinNum = i;
//						break;
//					}
//			if (i<0) TotalWinNum = 0;//okno zamkni©te byˆo ostatnie
//		}
//		else
//			if (WinResult == -1)//wy˜wietlone ma by† okno poprzednie
//			{
//				for (i = CurrentWinNum - 1; i >= 0; i--)
//					if (TabWin[i] == 1) break;
//				CurrentWinNum = i;
//				if (i<0) TotalWinNum = 0;//wyst¥piˆ bˆ¥d
//			}
//			else
//				if (WinResult == 1)//wy˜wietlone ma by† okno nast©pne
//				{
//					for (i = CurrentWinNum + 1; i<MaxWinNum; i++)
//						if (TabWin[i] == 1) break;
//					CurrentWinNum = i;
//					if (i >= MaxWinNum) TotalWinNum = 0;//wyst¥piˆ bˆ¥d
//				}
//				else
//					if (WinResult == 2)//ma powsta† nowe okno
//					{
//						for (i = 0; i<MaxWinNum; i++)
//							if (TabWin[i] == 0) break;
//						CurrentWinNum = i;
//						TabWin[CurrentWinNum] = 1;
//						TotalWinNum++;
//						if (i >= MaxWinNum) TotalWinNum = 0;//wyst¥piˆ bˆ¥d
//						if (i == MaxWinNum - 1) NewPossib = 0;
//						IsNew = 1;//kolejne okno b©dzie nowym oknem
//					}
//		delete Window;
//	} while (TotalWinNum>0);
//}
//SDL_Window *window;

int main(int argc, char *argv[])
{
	int CurrentWinNum = 0;//numer aktualnie otwartego okna
	int TotalWinNum = 1;//ilo˜† wszystkich otwartych okien
	char NewPossib = 1;//flaga m¢wi¥ca, czy mo¾e powsta† nowe okno
	char IsNew = 1;//flaga m¢wi¥ca, czy okno jest nowe
	char IsPrev=0;//flaga m¢wi¥ca, czy istnieje okno wcze˜niejsze
	char IsNext=0;//flaga m¢wi¥ca, czy istnieje okno nast©pne
	CWindow *TabWin[MaxWinNum];
	TabWin[CurrentWinNum] = new CWindow(CurrentWinNum + 1, IsPrev, IsNext, NewPossib, IsNew);
	while (true) {
		char choice = TabWin[CurrentWinNum]->Control();
		switch (choice) {
		case 2: {
			CurrentWinNum++;
			TotalWinNum++;
			TabWin[CurrentWinNum] = new CWindow(CurrentWinNum + 1, 1, IsNext, NewPossib, IsNew);
			break;
		}
		case 1: {
			CurrentWinNum++;
			break;
		}
		case -1: {
			CurrentWinNum--;
			break;
		}
		case 0 : {
			return 0;
		}
		}
	}
	//SDL_Renderer *renderer = NULL;

	//SDL_Surface *surf;
	//if (SDL_Init(SDL_INIT_VIDEO) < 0) {
	//	std::cout << "SDL i fucc";
	//	return -1;
	//}

	//SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

	//////////////////////////////////////////////////////////////
	//SDL_Point pt = { 50,50 };
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	//SDL_RenderClear(renderer);
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	//SDL_RenderDrawLine(renderer, pt.x + 8, pt.y + 7, pt.x + 8, pt.y + 22);
	//SDL_RenderDrawLine(renderer, pt.x + 3, pt.y + 14, pt.x + 8, pt.y + 14);
	//SDL_RenderDrawLine(renderer, pt.x + 8, pt.y + 7, pt.x + 17, pt.y + 14);
	//SDL_RenderDrawLine(renderer, pt.x + 8, pt.y + 22, pt.x + 17, pt.y + 14);
	//draw_circle(renderer, SDL_Point{ pt.x + 19, pt.y + 14 }, 2, SDL_Color{ 255,255,255 });
	//SDL_RenderDrawLine(renderer, pt.x + 21, pt.y + 14, pt.x + 24, pt.y + 14);
	//SDL_RenderPresent(renderer);
	/////////////////////////////////////////////////////////////////


	/*while (1) {
		SDL_UpdateWindowSurface(window);
	}*/
	return 0;
}
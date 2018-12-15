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

//SDL_Window *window;
int main(int argc, char *argv[])
{
	CWindow window;
	window.Control();
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
#include "PPU.h"
#include <iostream>


int Video::int_window() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {

		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}


	SDL_CreateWindowAndRenderer(GBWIDTH, GBHEIGHT, 0, &win, &ren);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderFillRect(ren, NULL);
	SDL_RenderPresent(ren);


	return 0;
}
void Video::render()
{
	for (int x = 0; x < 144; x++)
	{
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderDrawPoint(ren,x,50);
	}
	SDL_RenderPresent(ren);
	
}


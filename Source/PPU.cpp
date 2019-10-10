#include "PPU.h"
#include <iostream>
//TODO:
//load the LCD/video information
//
int Video::int_window() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_CreateWindowAndRenderer(GBWIDTH * 2, GBHEIGHT* 2, 0, &win, &ren);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderFillRect(ren, NULL);
	SDL_RenderPresent(ren);
	SDL_RenderSetScale(ren, 2, 2);
	return 0;
}

void Video::render(){

	for (int x = 0; x < 160; x++){
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderDrawPoint(ren,x,72);
	}
	SDL_RenderPresent(ren);
	
}

void PPU::update() {

	if (LCDenabled) {
		switch (amode) {
			case VBLANK:
				vblank();
				break;
			case HBLANK:
				hblank();
				break;
			case OAM:
				oamMode();
				break;
			case VRAM:
				transfer();
				break;
		}
	}
}
void PPU::vblank() {

}
void PPU::hblank() {

}
void PPU::transfer() {

}
void PPU::oamMode() {

}
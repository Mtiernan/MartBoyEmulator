#include "PPU.h"
#include <iostream>
//TODO:
//load the LCD/video information
//support y-loc,x-loc registers
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

void  PPU::scanLine() {
	//need to push line of pixels to framebuffer and inc line pointer
}
void PPU::render() {
	//push entire framebuffer to be rendered through sdl
}
void PPU::update() {

	if (LCDenabled) {
		//switches the current mode and waits a max cycle length before preforming an operation
		vcycles += 1; // needs to be synced with cpu step

		switch (amode) {
			case VRAM:
				if (vcycles >= 172) {
					scanLine();
					amode = HBLANK;
					vcycles = 0;
				}
				break;

			case VBLANK:
				if (vcycles >= 4560) {
					amode = OAM;
					cline = 0;
					render();
				}
				break;

			case HBLANK:
				if (vcycles >= 204)
				{
					if(cline == 143)
					{
						amode = VBLANK;
					}
					else {
						amode = OAM;
						cline++;
					
					}
					vcycles = 0;
				}
				break;

			case OAM:
				if(vcycles >= 80){
					amode = VRAM;
					vcycles = 0;
				}
				break;
		}
	}
}
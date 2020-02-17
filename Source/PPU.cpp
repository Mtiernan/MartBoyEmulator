#include "PPU.h"
#include <iostream>
//TODO:
//currently only updates current line, get/set other lcd registers
//set lcy and interrupt handlers
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
PPU::PPU(){
	cline = 0x0;
	scrX = 0x0;
	scrY = 0x0;
	amode = OAM;
	Mem = NULL;
	LCDenabled = false;
	vcycles = 0;

}

void  PPU::scanLine() {
	//need to push line of pixels to framebuffer and inc line pointer
}
void PPU::render() {
	//push entire framebuffer to be rendered through sdl
}
void PPU::update() {

	LCDenabled = true;

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

				if (cline == 153){
					amode = OAM;
					cline = 0;
					vcycles = 0;
					render();
				}
				else if (vcycles >= 456) {
					//cline still needs to be updated, some games check this value to see if it is in vblanking period
					cline++;
					Mem->write8(0xff44, cline);
					vcycles = 0;
				}
				break;

			case HBLANK:
				if (vcycles >= 204)
				{
					if(cline == 144)
					{
						amode = VBLANK;
						cline++;
						Mem->write8(0xff44, cline);

						//triggers v-blank interrupt
						Mem->write8(0xff0f, Mem->read8(0xff0f) | 0x01);
					}
					else {
						amode = OAM;
						cline++;
						Mem->write8(0xff44, cline);

					
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
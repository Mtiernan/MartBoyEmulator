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

	SDL_CreateWindowAndRenderer(GBWIDTH * 4, GBHEIGHT* 4, 0, &win, &ren);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderFillRect(ren, NULL);
	SDL_RenderPresent(ren);
	SDL_RenderSetScale(ren, 4, 4);
	return 0;
}

void Video::render(int* background) {
	SDL_RenderClear(ren);
	for (int x = 0; x < GBWIDTH * GBHEIGHT; x++){
		if(background[x] == 4)
			SDL_SetRenderDrawColor(ren, 64, 64, 64, 255);
		else if(background[x] == 3 )
			SDL_SetRenderDrawColor(ren, 128, 128, 128, 255);
		else if(background[x]== 2)
			SDL_SetRenderDrawColor(ren, 196, 196, 196, 255);
		else if(background[x] == 1)
			SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

		SDL_RenderDrawPoint(ren,x%GBWIDTH,x/GBHEIGHT);
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
	LCDC = Mem->read8(0xff40);
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
					//render();
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
void PPU::getBackground() {
	//loop through entire background map
	int start = 0;
	int end = 0;
	int bgpointer = 0;
	if (LCDC && 0x16) {
		bgpointer = 0x8000;
	}
	else {
		bgpointer = 0x8800;
	}
	if (LCDC && 0x8) {
		start = 0x9800;
		end = 0x9Bff;
	}
	else{
		start = 0x9C00;
		end = 0x9FFF;
	}
	start = 0x9800;
	uint8_t tilenum;
	bgpointer = 0x8800;
	for (int x = 1; x < 1024 ; x++) {
		tilenum = Mem->read8(start);
		drawBackTile(x, bgpointer + tilenum);
	}
}

void PPU::drawBackTile(int num, int tilePoint)
{
	int y = num / 32;
	int x = num % 32;
	for (int line = 0; line < 8;  line++) {
		uint16_t color = Mem->read16(tilePoint);
		for (int pixel = 0; pixel < 8; pixel++) {
			int pcolor = 0;
			switch (color & 0xC000) {
				case 0xc000: pcolor = 4; break;
				case 0x4000: pcolor = 3; break;
				case 0x2000: pcolor = 2; break;
				case 0x0000: pcolor = 1; break;
			}
			background[(y*255) + pixel + x] = pcolor;
			color = color << 2;
		}
		tilePoint += 2;

	}
}
void PPU::drawTileSet() {
		uint16_t backPoint = 0x8000;
		int pcolor = 0;
		uint16_t line = Mem->read16(backPoint);
	for (int j = 0; j < 256; j++) {
	
		for (int zz = 0; zz < 8; zz++){
			for (int z = 0; z < 8; z++) {
				switch (line & 0xc000) {
				case 0xc000: pcolor = 4; break;
				case 0x4000: pcolor = 3; break;
				case 0x2000: pcolor = 2; break;
				case 0x0000: pcolor = 1; break;
				}
				vid.framebuffer[((j % 20 * 8) + z) + (((j / 20) * 8) + zz) * 160] = pcolor;
				line = line << 2;
			}
			backPoint += 2;
			line = Mem->read16(backPoint);
		}
	}
}
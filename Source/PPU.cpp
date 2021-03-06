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

	SDL_CreateWindowAndRenderer(GBWIDTH*3, GBHEIGHT*3, 0, &win, &ren);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderFillRect(ren, NULL);
	SDL_RenderPresent(ren);
	SDL_RenderSetScale(ren, 3, 3);
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

		SDL_RenderDrawPoint(ren,x%GBWIDTH,x/GBWIDTH);
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
	int map_address = 0x9800;
	for (int x = 0; x < 1024; x++) {
		drawBackTile(Mem->read8(map_address) * 16, 0x8000,x);
		map_address++;

	}
}

void PPU::drawBackTile(int num, int tilePoint, int tnum)
{
	uint16_t tpoint = num  + tilePoint;
	uint8_t line = Mem->read8(tpoint);
	uint8_t line2 = Mem->read8(tpoint+ 1);
	int pcolor = 0;
		for (int tline = 0; tline < 8; tline++) {
			for (int dot = 0; dot < 8; dot++) {
				switch ((line & 0x80) | ((line2 & 0x80) >> 1)) {
				case 0xc0: pcolor = 4; break;
				case 0x80: pcolor = 3; break;
				case 0x40: pcolor = 2; break;
				case 0x00: pcolor = 1; break;
				}
				background[((tnum % 32 * 8) + dot) + ((((tnum / 32) * 8) + tline) * 255)] = pcolor;
				line = line << 1;
				line2 = line2 << 1;
			
		}
			tpoint += 2;
			line = Mem->read8(tpoint);
			line2 = Mem->read8(tpoint + 1);

	}
}

void PPU::drawTileSet() {
		uint16_t backPoint = 0x8000;
		int pcolor = 0;
		uint8_t line = Mem->read8(backPoint);
		uint8_t line2 = Mem->read8(backPoint +1);
	for (int j = 0; j < 256; j++) {
	
		for (int tline = 0; tline < 8; tline++){
			for (int dot = 0; dot < 8; dot++) {
				switch ((line & 0x80) | ((line2 & 0x80) >>1)) {
				case 0xc0: pcolor = 4; break;
				case 0x80: pcolor = 3; break;
				case 0x40: pcolor = 2; break;
				case 0x00: pcolor = 1; break;
				}
				vid.framebuffer[((j % 20 * 8) + dot) + (((j / 20) * 8) + tline) * 160] = pcolor;
				line = line << 1;
				line2 = line2 << 1;
			}
			backPoint += 2;
			line = Mem->read8(backPoint);
			line2 = Mem->read8(backPoint + 1);
		}
	}
}
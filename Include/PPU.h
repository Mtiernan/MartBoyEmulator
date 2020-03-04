#pragma once
#ifndef PPU_H
#define PPU_H
#include "Memory.h"
#include <SDL.h>

#define GBWIDTH 255
#define GBHEIGHT 255

enum mode{
	HBLANK,
	VBLANK,
	SCANL,
	OAM,
	VRAM
};


struct tile{
	uint16_t lines[8];
};

//contains all SDL calls
class Video{
public:
	int int_window();
	void render(uint8_t* background);
	int framebuffer[GBWIDTH * GBHEIGHT];

private:
	SDL_Window* win;
	SDL_Renderer* ren;
};

class PPU{

public:
	PPU();
	Video vid;
	Memory* Mem;
	//status managment
	int vcycles;
	uint8_t cline;
	mode amode;
	bool LCDenabled;

	uint8_t LCDC;
	uint8_t status;
	uint8_t scrX, scrY;

	uint8_t background[65536];
	void getBackground();
	void scanLine();
	void render();
	void update();
	void drawBackTile(int num, int tilepoint);
	
};



#endif
#pragma once
#ifndef PPU_H
#define PPU_H
#include "Memory.h"
#include <SDL.h>

#define GBWIDTH 160
#define GBHEIGHT 144

enum mode{
	HBLANK,
	VBLANK,
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
	void render();
	int framebuffer[GBWIDTH * GBHEIGHT];

private:
	SDL_Window* win;
	SDL_Renderer* ren;
};

class PPU{

	public:

	Video vid;

	//status managment
	int vcycles, cline;
	mode amode;
	bool LCDenabled;
	uint8_t status;
	uint8_t scrX, scrY;

	void scanLine();
	void render();

	void update();
	
	void oamMode();
	void hblank();
	void vblank();
	void transfer();

};



#endif
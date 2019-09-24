#pragma once
#ifndef PPU_H
#define PPU_H
#include "Memory.h"
#include <SDL.h>

#define GBWIDTH 160
#define GBHEIGHT 144

enum mode
{
	HBLANK,
	VBLANK,
	OAM,
	VRAM
};

class Video

{
public:
	int int_window();
	void render();
	int framebuffer[GBWIDTH * GBHEIGHT];

private:
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Surface* sur;

};



class PPU
{
	public:
	Video vid;

};



#endif
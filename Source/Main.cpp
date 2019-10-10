#include <CPU.h>
#include <Input.h>
#include <PPU.h>
#include <iostream>
// Streak: 1
int main(int argc, char*args[])
{
	SDL_Event event;
	bool quit = false;
	CPU Emulator;
	PPU ppu;
	Input input =  Input(Emulator.Mem, &Emulator);
	Emulator.Mem->loadRom();

	//intializing of values to skip put rom
	Emulator.pc = 0x150;
	Emulator.BC.lowbit = 13;
	Emulator.DE.lowbit = 48;
	Emulator.Mem->write8(0xff44, 0x94);
	Emulator.Mem->write8(0xff00, 0xCF); Emulator.sp = 0xFFFE;
	Emulator.sp = 0xFFFE;
 
	//intializing window through SDL
	ppu.vid.int_window();

	//main loop
	while (!quit) {

		//TODO move to a single function call that handles all window events
		if (SDL_PollEvent(&event))
			if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
					quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
				input.getKey(event);	//TODO handle input
	
		while (Emulator.cycles < MAXCYCLES) {
			Emulator.update();
		}
		//TODO move to a single function call that handles all window events
		if (SDL_PollEvent(&event))
			if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
					quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
				input.getKey(event);	//TODO handle input
	
		Emulator.cycles = 0;

		ppu.vid.render();
	}
	//TODO: DESTROY
	return 0;

}
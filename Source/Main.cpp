#include <CPU.h>
#include <Input.h>
#include <PPU.h>
#include <iostream>
// Streak: 2
int main(int argc, char*args[])
{
	SDL_Event event;
	bool quit = false;
	CPU Emulator;
	PPU ppu;
	Input input =  Input(Emulator.Mem, &Emulator);
	Emulator.Mem->loadRom();

	//intializing of values to skip boot rom
	Emulator.pc = 0x150;
	Emulator.BC.low = 13;
	Emulator.DE.low = 48;
	Emulator.Mem->write8(0xff44, 0x94);
	Emulator.Mem->write8(0xff00, 0xCF); Emulator.sp = 0xFFFE;
	Emulator.sp = 0xFFFE;
 
	//intializing window through SDL
	ppu.vid.int_window();

	//main loop
	while (!quit) {

		
		if (SDL_PollEvent(&event))
			if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
					quit = true;
			}
			else if (event.type == SDL_KEYDOWN)
				input.getKeyDown(event);
			else if (event.type == SDL_KEYUP)
				input.getKeyUp(event);

		while (Emulator.cycles < MAXCYCLES) {
			input.update(Emulator.Mem);
			Emulator.update();
		}
		
		Emulator.cycles = 0;
		ppu.vid.render();
	}
	//TODO: DESTROY
	return 0;

}
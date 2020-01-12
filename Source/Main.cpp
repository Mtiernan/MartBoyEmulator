#include <CPU.h>
#include <Input.h>
#include <PPU.h>
#include <iostream>

int main(int argc, char*args[])
{
	bool debug = false;
	SDL_Event event;
	bool quit = false;	
	CPU Emulator;
	PPU ppu;
	Input input =  Input(Emulator.Mem, &Emulator);
	Emulator.Mem->loadRom();

	//intializing of values to skip boot rom
	Emulator.pc = 0x150;
	Emulator.AF.high = 0x01;
	Emulator.BC.low = 0x13;
	Emulator.DE.low =0xD8;
	Emulator.HL.low = 0x4d;
	Emulator.HL.high = 0x01;
	Emulator.Mem->write8(0xff44, 0x94);
	Emulator.Mem->write8(0xff00, 0xCF);
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
			if (Emulator.pc == 0x29b)
				debug = true;
			if (debug) {
				char x;
				std::cout << "PC: " << std::hex << int(Emulator.pc) << std::endl;
				std::cout << "SP: " << std::hex << int(Emulator.sp) << std::endl;
				std::cout << "AF: " << std::hex << int(Emulator.AF.to16()) << std::endl;
				std::cout << "BC: " << std::hex << int(Emulator.BC.to16()) << std::endl;
				std::cout << "DE: " << std::hex << int(Emulator.DE.to16()) << std::endl;
				std::cout << "HL: " << std::hex << int(Emulator.HL.to16()) << std::endl;
				std::cout << "Do you wish to countinue debugging?" << std::endl;
				std::cin >> x;
				if (x != 'y')
					debug = false;

			}
		}
		
		
		Emulator.cycles = 0;
		ppu.vid.render();
	}
	return 0;

}
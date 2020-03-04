#include <CPU.h>
#include <Input.h>
#include <PPU.h>
#include <iostream>


//known todos:
//build a  better debugger
//-conditional PC increments/cycle count
//-interrupt requesting not working?
//track cpu timing to pass to cpu
//bugs:
//add function between two registers doesn't carry correctly

int main(int argc, char*args[])
{
	bool debug = false;
	SDL_Event event;
	bool quit = false;	
	CPU Emulator;
	PPU ppu;
	Input input =  Input(Emulator.Mem, &Emulator);
	ppu.Mem = Emulator.Mem;
	Emulator.Mem->loadRom();

	//intializing of values for intial testing can be deleted later
	Emulator.pc = 0x150;
	Emulator.AF.high = 0x01;
	Emulator.BC.low = 0x13;
	Emulator.DE.low =0xD8;
	Emulator.HL.low = 0x4d;
	Emulator.HL.high = 0x01;
	Emulator.Mem->write8(0xff00, 0xCF);
	Emulator.Mem->write8(0xfffe, 0xc3);
	Emulator.Mem->write8(0xffff, 0x09);
	Emulator.sp = 0xFFFE;
	std::cout << "control " << std::hex << int(Emulator.Mem->read8(0xff00)) << std::endl;
 
	//intializing window through SDL
	ppu.vid.int_window();

	//main loop
	while (!Emulator.quit) {
		
		if (SDL_PollEvent(&event))
			if (event.type == SDL_WINDOWEVENT) {
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
					quit = true;
			}
 			else if (event.type == SDL_KEYDOWN)
   				input.getKeyDown(event);
			else if (event.type == SDL_KEYUP)
				input.getKeyUp(event);
		int prevC = 0;
		while (Emulator.cycles < MAXCYCLES && !Emulator.quit) {

			input.update(Emulator.Mem);
			prevC = Emulator.cycles;
			Emulator.update();
			ppu.update();

			if (Emulator.pc == 0x2F2fffff)
				debug = true;
			if (debug) {
				char x;
				ppu.vid.render(ppu.background);
				std::cout << "PC: " << std::hex << int(Emulator.pc) << std::endl;
				std::cout << "SP: " << std::hex << int(Emulator.sp) << std::endl;
				std::cout << "AF: " << std::hex << int(Emulator.AF.to16()) << std::endl;
				std::cout << "BC: " << std::hex << int(Emulator.BC.to16()) << std::endl;
				std::cout << "DE: " << std::hex << int(Emulator.DE.to16()) << std::endl;
				std::cout << "HL: " << std::hex << int(Emulator.HL.to16()) << std::endl;
				std::cout << "Do you wish to countinue debugging?" << std::endl;
				std::cout << "control " << std::hex << int( Emulator.Mem->read8(0xff00)) << std::endl;
				std::cin >> x;
				if (x != 'y')
					debug = false;
			}
		}			
		Emulator.cycles = 0;
	ppu.getBackground();
	ppu.vid.render(ppu.background);
	}
	
  	return 0;

}
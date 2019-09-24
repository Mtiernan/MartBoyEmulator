#include <CPU.h>
#include <PPU.h>
#include <iostream>

int main(int argc, char*args[])
{
	bool quit = false;
	CPU Emulator;
	Emulator.Mem->loadRom();

	Emulator.pc = 0x100;

	PPU ppu;

    //ppu.vid.int_window();
	//ppu.vid.render();
	//below temp code to fetch next unimpemented opcode
	for(int x = 0; x < 8000; x++)
	{
		Emulator.update();
	}

	return 0;
	

}
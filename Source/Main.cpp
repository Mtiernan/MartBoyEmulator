#include <CPU.h>
#include <PPU.h>
#include <iostream>
// Streak: 3
int main(int argc, char*args[])
{
	bool quit = false;
	CPU Emulator;
	Emulator.Mem->loadRom();
	Emulator.pc = 0x150;
	PPU ppu;
	Emulator.BC.lowbit = 13;
	Emulator.DE.lowbit = 48;
	Emulator.Mem->write8(0xff44, 0x94);
	Emulator.Mem->write8(0xff00, 0xCF);

    //ppu.vid.int_window();
	//ppu.vid.render();

	//below temp code to fetch next unimpemented opcode
	Emulator.sp = 0xFFFE;
	for(int x = 0; x < 8000000; x++)
	{

		Emulator.update();
	}

	return 0;
	

}
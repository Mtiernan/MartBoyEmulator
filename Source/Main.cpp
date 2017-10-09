#include <CPU.h>


int main()
{
	bool quit = false;
	Z80 Emulator;
	Emulator.Mem.loadRom();

	Emulator.pc = 0x100;

	int x = 80000; // to prevent stuck loops while i loop through the program looking for opcodes to implment

	while (quit == false || x == 0) {

		//while the cpu is active we contiue doing operations
		Emulator.readOp(Emulator.Mem.read8(Emulator.pc));

		//this variable is temporay as I run this program to find the next unimplemted opcode
		x--;

	}

	return 0;
	

}
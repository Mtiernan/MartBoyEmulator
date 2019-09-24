
#include "CPU.h"
#include "Opnames.h"
#include <iostream>
using namespace std;

CPU::CPU()
{
	const int MAXCYCLES = 69905;
	Mem = new Memory();
	cycles = 0; 
	sp = 0;
	pc = 0;

}
void StartCpu(){
		
};

void CPU::readOp(uint8_t opcode) {

	switch (opcode) {
	case 0x00:
		pc += opcodeByteSize[opcode];
		break;
	case 0xc3:
		pc = Mem->read16(pc + 1);
		break;

	default:
		cout <<  "Umemplemeted opcode: "  << opNames[opcode] << " Number: " << hex <<(int)opcode <<"\n";
		exit(0);
	}
	cycles += opcodeCycleCount[opcode];
}


void CPU::update()
{
		readOp(Mem->read8(pc));
}


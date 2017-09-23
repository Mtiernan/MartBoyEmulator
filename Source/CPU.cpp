
#include "CPU.h"
#include "Opnames.h"



void StartCpu(){

	sixteenbitregisters test;

	
	
};
void Z80::setflag(uint8_t flag)
{
	//set flag based on value



}
void Z80::clearFlags()
{
	//need to clear flags on cpu. 



}
void Z80::readOp(uint8_t opcode) {

	switch (opcode) {
	case 0x00:
		break;
	
	default:
		exit(0);
	
	}
	pc += opcodeByteSize[opcode];
	cycles += opcodeCycleCount[opcode];
}


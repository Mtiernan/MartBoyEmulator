
#ifndef CPU_H
#define CPU_H
#include "Registers.h"

#include "Memory.h"

class Z80 {

public:
	


private:
	//the regestiers of the z80
	sixteenbitregisters AF,BC,DE,HL;

	//the emulated memory space
	Memory Mem;

	//stack pointer and the program counter
	uint16_t sp, pc;


	//variable to keep track of cycles. 
	int cycles;

	void setflag(uint8_t flag);
	void clearFlags();
	void readOp(uint8_t opcode);



};


#endif

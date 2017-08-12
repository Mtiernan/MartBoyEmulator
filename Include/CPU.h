
#ifndef CPU_H
#define CPU_H
#include "Registers.h"


class Z80 {

public:
	


private:
	//the regestiers of the z80
	sixteenbitregisters AF,BC,DE,HL;

	//stack pointer and the program counter
	uint16_t SP, PC;

	int cycles;
	void setflag(uint8_t flag);
	void clearFlags();
	void add(uint8_t, int);
	void handleOpCode(uint8_t opcode);



};


#endif

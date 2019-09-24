
#ifndef CPU_H
#define CPU_H
#include "Registers.h"

#include "Memory.h"
const int MAXCYCLES = 69905;
class CPU {

public:
	


//private:
	sixteenbitregisters AF,BC,DE,HL;
	Memory* Mem;
	uint16_t sp, pc;


	//variable to keep track of cycles. 
	int cycles;

	CPU();
	void readOp(uint8_t opcode);
	void update();
	void add(uint8_t reg);

};


#endif

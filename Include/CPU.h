
#ifndef CPU_H
#define CPU_H
#include "Registers.h"


class Z80 {

public:
	


private:
	sixteenbitregisters AF,BC,DE,HL;
	sixteenbitregisters SP, PC;

	int cycles;
	void setflag(uint8_t flag);
	void clearFlags();
	void add(uint8_t, int);




};


#endif

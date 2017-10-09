
#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>



class Memory {

private:
	/*there are two places in memory unaccounted for. E000 - FDFF and FEA0 - FEFF. 
	  The first being "echo ram" a duplicated of the WRAM and the second being an undocumented
	  and primarlly unused area in the memory*/

	uint8_t romCart[0x8000]; //this is assuming there is no rom banking
	uint8_t vram[0x2000];
	uint8_t eram[0x2000]; //this can be extended by using banking
	uint8_t wram[0x2000];
	uint8_t oam[0x100];
	uint8_t ioReg[0x80];
	uint8_t hram[0x80];

public:

	void write8(uint16_t address, uint8_t value);
	void write16(uint16_t address, uint16_t value );
	uint16_t read16(uint16_t address);
	uint8_t read8(uint16_t address);
	void loadRom();
	Memory();
};




#endif
#pragma once
#ifndef MEMORY_H
#define MEMORY_H
#include <stdint.h>



class Memory {

private:
	//seperate ram later so program can't write over the rom
	char Ram[0xFFFF];

public:
	//need to implement read/write fucition of the rom.
	void write8(uint16_t address, uint8_t value);
	void write16(uint16_t address, uint16_t value );
	void readValue(uint16_t address);
};





#endif
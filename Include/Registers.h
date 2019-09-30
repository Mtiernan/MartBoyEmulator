#ifndef REGISTERS_H
#define REGISTERS_H


#include <stdint.h> 
//the z80 uses eightbit regiisters A, F, B, C, D, E, H ,L however they are used in pairs
	struct sixReg {
		uint8_t highbit, lowbit;
		uint8_t toint() {
			uint16_t x = highbit << 8 | lowbit;
			return x;
		};
	};


#endif


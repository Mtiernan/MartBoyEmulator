#ifndef REGISTERS_H
#define REGISTERS_H


#include <stdint.h> 
//the z80 uses eightbit regiisters A, F, B, C, D, E, H ,L however they are used in pairs
	struct eightbitregisters {
	public:
		uint8_t value;
	
	};

// the sixteen bit pairs that will be acutally used in the implemtation of the cpu. 
	struct sixteenbitregisters {
		eightbitregisters highbit, lowbit;

	};


#endif


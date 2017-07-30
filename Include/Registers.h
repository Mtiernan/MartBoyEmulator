#ifndef REGISTERS_H
#define REGISTERS_H


#include <stdint.h>

	struct eightbitregisters {
	public:
		uint8_t value;
	
	};


	struct sixteenbitregisters {
		eightbitregisters highbit, lowbit;

	};


#endif


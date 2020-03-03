#ifndef REGISTERS_H
#define REGISTERS_H


#include <stdint.h> 
//the gameboy cpu uses eightbit regiisters A, F, B, C, D, E, H ,L however they are used in pairs
	struct sixReg {
		uint8_t high, low;
		uint16_t to16() {
			uint16_t x = high << 8 | low;
			return x;
		};
		void set(uint16_t value){
			high = value >> 8;
			low = value;
		}
		void inc() {
			set(to16() + 1);
		}
		void dec() {
			set(to16() - 1);
		}
	};


#endif


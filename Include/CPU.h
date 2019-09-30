
#ifndef CPU_H
#define CPU_H
#include "Registers.h"

#include "Memory.h"
const int MAXCYCLES = 69905;

struct Flags{
	bool zero;
	bool carry;
	bool subtract;
	bool halfcarry;
};

class CPU {
	
public:
	
	sixReg AF,BC,DE,HL;
	Flags flags;
	Memory* Mem;
	uint16_t sp, pc;
	bool intrpt; 
	bool advpc;
	bool IME;
	int cycles;
	CPU();

	//cpu state handling functions
	void clearFlags();
	void readOp(uint8_t opcode);
	void interrupt(uint16_t value);
	void update();


	//opcode functions 
	void xOR(uint8_t value);
	void And(uint8_t value);
	void add(sixReg reg, sixReg reg2);
	void adc(uint8_t value);
	void sbc();
	void sub();
	void LDnn(sixReg &reg, uint16_t address);
	void LDn(uint8_t &reg, uint16_t address);
	void LDDrn(uint8_t& reg, sixReg& reg2, bool neg);
	void LDra(uint8_t &reg, uint16_t address);
	void LDar(uint16_t address, uint8_t value);
	void incr(sixReg reg);
	void JRc(bool flag);
	void CPn(uint8_t value);
	void pop(sixReg reg);
	void push(sixReg reg);
	void push(uint16_t value);
	void inc(uint16_t address);
	void ret();
	void call(uint16_t address);

};


#endif


#include "CPU.h"
#include "Opnames.h"
#include <iostream>
using namespace std;
//known implementation flaws:
//-conditional PC increments/cycle count
//-flag handling
//-interrupt handling 
//opcodes: 3C,d9

CPU::CPU(){
	const int MAXCYCLES = 69905;
	
	Mem = new Memory();
	cycles = 0; 
	intrpt = false;
	sp = 0;
	pc = 0;
	AF.highbit = 243;
}

void StartCpu(){
		
};
void CPU::readOp(uint8_t opcode) {
	advpc = true;
	switch (opcode) {
		case 0x00:  break; 
		case 0x05: BC.highbit--;  break;
		case 0x06: LDn(BC.highbit, pc + 1); break;
		case 0x0D: BC.lowbit--; break;
		case 0x0E: LDn(BC.lowbit, pc+1);break;
		case 0x11: LDnn(DE, pc + 1); break;
		case 0x13: incr(DE); break;
		case 0x16: LDn(DE.highbit, pc + 1); break;
		case 0x18: JRc(true); break;
		case 0x19: add(HL, BC); break; 
		case 0x1A: LDn(AF.highbit, DE.highbit << 8 | DE.lowbit); break;
		case 0x20: JRc(!flags.zero); break;
		case 0x21: LDnn(HL,pc+1); break;
		case 0x22: LDDrn(AF.highbit, HL, false); break;
		case 0x28: JRc(flags.zero); break;
		case 0x32: LDDrn(AF.highbit, HL,true);  break;
		case 0x34: incr(HL); break;
		case 0x3C: AF.highbit++; break;		//todo: check for carry
		case 0x3E: LDn(AF.highbit, pc + 1); break;
		case 0x66: LDn(HL.highbit, HL.highbit << 8 | HL.lowbit); break;
		case 0xA7: And(AF.highbit); break;
		case 0xAf: xOR(AF.highbit); break;
		case 0xC0: if (!flags.zero) ret(); break;
		case 0xC1: pop(BC); break;
		case 0xC3: pc = Mem->read16(pc + 1); advpc = false; break;
		case 0xC9: ret(); break;
		case 0xCD: if(flags.zero) call(Mem->read16(pc)); break;
		case 0xCE: adc(AF.highbit); break;
		case 0xCF: push(pc); pc = 0x08; advpc = false;
		case 0xD1: pop(DE); break;
		case 0xD5: push(DE); break;
		case 0xD9: ret(); break; //called after interrupts todo: handle interrupts
		case 0xE0: LDar(0xff + Mem->read8(pc +1),AF.highbit); break;
		case 0xE1: pop(HL); break;
		case 0xE5: push(HL); break;
		case 0xF0: LDra(AF.highbit, 0xff + Mem->read8(pc+1)); break;
		case 0xF1: pop(AF); break;
		case 0xFA: LDn(AF.highbit, Mem->read8(pc) | Mem->read8(pc + 1) << 8); break;
		case 0xFE: CPn(Mem->read8(pc + 1)); break;
		case 0xF3: IME = false; break;

		default:
			cout <<  "unimplemented opcode: "  << opNames[opcode] << " Number: " << hex <<(int)opcode <<"\n";
			exit(0);}
	if(advpc) 
		pc += opcodeByteSize[opcode];
	cycles += opcodeCycleCount[opcode];
}
void CPU::interrupt(uint16_t value) {
	push(pc);
	pc = value;

}
void CPU::update(){
	if (intrpt && IME)
		interrupt(0x00); //pass in the interrupt
	else
		readOp(Mem->read8(pc));

}
void CPU::xOR(uint8_t reg){
	AF.highbit = reg ^ reg;
	if (AF.highbit == 0)
		flags.zero = true;
	else 
		flags.zero = false;	
}
void CPU::LDnn(sixReg &reg, uint16_t address){
	reg.lowbit = Mem->read8(address);
	reg.highbit = Mem->read8(address);
}
void CPU::LDn(uint8_t &reg, uint16_t address){
	reg = Mem->read8(address);
}
void CPU::LDDrn(uint8_t& reg, sixReg& reg2, bool neg){
	uint16_t address = reg2.highbit | reg2.lowbit << 8;
	AF.highbit = Mem->read8(address);
	if (neg)
		address--;
	else
		address++;
	reg2.highbit =  address;
	reg2.lowbit = address >> 8;
}
void CPU::JRc(bool flag){
	if (flag){
		advpc = false;
		uint8_t x = Mem->read8(pc + 1);
		if (0x80 & x){
			x = x ^ 0x80;
			pc = pc - x;
		}
		else{
			pc = pc  + x;
		}
		cycles += 4;
	}
	else
		advpc = true;
}
void CPU::LDar(uint16_t address, uint8_t value){
	Mem->write8(address, value);
}
void CPU::LDra(uint8_t& reg,uint16_t address) {
	uint16_t x = 0xff00 | Mem->read8(pc + 1);
	reg = Mem->read8(address);
}
void CPU::CPn(uint8_t value)
{
	clearFlags();
	//todo set halfcarry
	flags.subtract = true;
	if (value > AF.highbit)
		flags.carry = true;
	else if (value == AF.highbit)
		flags.zero = true;
}
void CPU::clearFlags()
{
	flags.carry = false;
	flags.zero = false;
	flags.halfcarry = false;
	flags.subtract = false;
}
void CPU::call(uint16_t address){
	sp = sp - 2;
	Mem->write16(sp, pc + 2);
	pc = address;
	advpc = false; 	
}
void CPU::And(uint8_t reg)
{
	clearFlags();
	AF.highbit = reg & AF.highbit;
	if (AF.highbit == 0)
		flags.zero = true;
	flags.halfcarry = true;
}
void CPU::adc(uint8_t value)
{
	if (flags.carry)
		value++;
	AF.highbit = AF.highbit + value;
}
void CPU::inc(uint16_t address)
{
	Mem->write8(address, Mem->read8(address) + 1);
}
void CPU::pop(sixReg reg){
	HL.lowbit = Mem->read8(sp);
	HL.highbit = Mem->read8(sp + 1);
	sp += 2;
}
void CPU::ret() {
	pc = Mem->read8(sp) | Mem->read8(sp + 1) << 8;
	sp += 2;
	advpc = false;
}
void CPU::add(sixReg reg, sixReg reg2) {
	flags.subtract = false;
	bool carry = false;
	if (reg.lowbit + reg2.lowbit < reg.lowbit)
		carry = true;

	reg.lowbit = reg.lowbit + reg2.lowbit;

	if ((((reg.highbit & 0xf) + (reg2.highbit & 0xf)) & 0x10) == 0x10)
		flags.halfcarry = true;
	else
		flags.halfcarry = false;

	if (reg.highbit + reg2.highbit < reg.highbit)
		flags.carry = true;

	if (carry)
			reg.highbit = reg.highbit + reg.highbit + 1;
	else
		reg.highbit = reg.highbit + reg.highbit;
}
void CPU::push(sixReg reg) {
	Mem->write8(sp - 1, reg.highbit);
	Mem->write8(sp - 2, reg.lowbit);
	sp -= 2;
}
void CPU::push(uint16_t value) {
	Mem->write16(sp - 2, value);
	sp -= 2;
}
void CPU::incr(sixReg reg) {
	if (reg.lowbit == 0xff) {
		reg.lowbit = 0x00;
		reg.highbit++;
	}
	else
		reg.lowbit++;
}
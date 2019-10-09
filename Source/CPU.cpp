
#include "CPU.h"
#include "Opnames.h"
#include <iostream>
using namespace std;
//known implementation flaws:
//-conditional PC increments/cycle count
//-interrupt handling 
//advace pc after read/refactor pc handling
//IO handling
//cb prefix handeling

CPU::CPU(){
	const int MAXCYCLES = 69905;
	
	Mem = new Memory();
	cycles = 0; 
	intrpt = false;
	sp = 0xFFFE;
	pc = 0;
	AF.highbit = 0;
}

void StartCpu(){
		
};
void CPU::readOp(uint8_t opcode) {
 
	cout << "Calling opcode: " << std::hex << int(opcode) << " \tPC: " << pc << endl;
	pc++;
	switch (opcode) {
		case 0x00:  break; 
		case 0x01: LDnn(BC, pc++); pc++;  break;
		case 0x05: decn(BC.highbit); break;
		case 0x06: LDn(BC.highbit, pc++); break;
		case 0x07: RLCr(AF.highbit); break;
		case 0x08: Mem->write16(Mem->read16(pc++), sp); pc++; break;
		case 0x0B: decnn(BC); break;
		case 0x0D: decn(BC.lowbit); break;
		case 0x0C: incn(BC.lowbit); break;
		case 0x0E: LDn(BC.lowbit, pc++); break;
		case 0x11: LDnn(DE, pc++); pc++; break;
		case 0x13: incr(DE); break;
		case 0x16: LDn(DE.highbit, pc++); pc++; break;
		case 0x18: JRc(true); break;
		case 0x19: add(HL, BC); break; 
		case 0x1A: LDn(AF.highbit, DE.highbit << 8 | DE.lowbit); break;
		case 0x1D: decn(DE.lowbit); cout << "e is : " << DE.lowbit; break;
		case 0x20: JRc(!flags.zero); break;
		case 0x21: LDnn(HL,pc++); pc++; break;
		case 0x22: LDDrn(AF.highbit, HL, false); break;
		case 0x25: decn(HL.highbit);   break;
		case 0x28: JRc(flags.zero); break;
		case 0x2A: LDDrn(AF.highbit, HL, false); break;
		case 0x2f: AF.highbit = ~AF.highbit; break; //io handling must work for the correct values to be given
		case 0x31: sp = Mem->read16(pc++); pc++; break;
		case 0x32: LDDrn(AF.highbit, HL,true);  break;
		case 0x34: incr(HL); break;
		case 0x36: Mem->write8(HL.toint(), Mem->read8(pc++)); break;
		case 0x3C: incn(AF.highbit); break;
		case 0x3E: LDn(AF.highbit, pc++);  break;
		case 0x66: LDn(HL.highbit, HL.highbit << 8 | HL.lowbit); break;
		case 0x78: AF.highbit = BC.highbit; break;
		case 0xA7: And(AF.highbit); break;
		case 0xAf: xOR(AF.highbit); break;
		case 0xB1: Or(BC.lowbit); break;
		case 0xC0: if (!flags.zero) ret(); break;
		case 0xC1: pop(BC); break;
		case 0xC3: pc = Mem->read16(pc++); break;
		case 0xC9: ret(); break;
		case 0xCD: if (flags.zero) call(Mem->read16(pc++)); break;
		case 0xCE: adc(AF.highbit); break;
		case 0xCF: push(pc); pc = 0x08; 
		case 0xD1: pop(DE); break;
		case 0xD5: push(DE); break;
		case 0xD9: ret(); break; //called after interrupts todo: handle interrupts
		case 0xE0: LDar(0xff00 + Mem->read8(pc++),AF.highbit); break;
		case 0xE1: pop(HL); break;
		case 0xE2: LDar(0xff00 + BC.lowbit, AF.highbit); break;
		case 0xE5: push(HL); break;
		case 0xE6: And(Mem->read8(pc++)); break;
		case 0xEA: LDra(AF.highbit, Mem->read8(Mem->read16(pc++))); pc++; break;
		case 0xF0: LDra(AF.highbit, 0xff00 + Mem->read8(pc++)); break;
		case 0xF1: pop(AF); break;
		case 0xFA: LDn(AF.highbit, Mem->read8(pc++) | Mem->read8(pc++) << 8); break;
		case 0xFB: IME = true; break;
		case 0xFE: CPn(Mem->read8(pc++)); break;
		case 0xF3: IME = false; break;

		default:
			cout <<  "unimplemented opcode: "  << opNames[opcode] << " Number: " << hex <<(int)opcode <<"\n" <<"PC: " <<pc;
			exit(0);}
	if (pc > 0x8000)
		cout << "PC outside of scope";
	cycles += opcodeCycleCount[opcode];
}
void CPU::interrupt(uint16_t value) {
	push(pc);
	pc = value;

}
void CPU::update(){
	if (intrpt && IME)
		interrupt(0x00); //Todo: pass in the interrupt
	else
		readOp(Mem->read8(pc));

}
void CPU::xOR(uint8_t reg){
	AF.highbit = AF.highbit ^ reg;
	if (AF.highbit == 0)
		flags.zero = true;
	else 
		flags.zero = false;	
}
void CPU::LDnn(sixReg &reg, uint16_t address){
	reg.lowbit = Mem->read8(address);
	reg.highbit = Mem->read8(address + 1);
}
void CPU::LDn(uint8_t &reg, uint16_t address){
	reg = Mem->read8(address);
}
void CPU::LDDrn(uint8_t& reg, sixReg& reg2, bool neg){
	uint16_t address = reg2.highbit << 8 | reg2.lowbit;
	Mem->write8(address, AF.highbit);
	if (neg)
		address--;
	else
		address++;
	reg2.highbit =  address >> 8;
	reg2.lowbit = address;
}
void CPU::JRc(bool flag){
	int8_t x = Mem->read8(pc++);
	if (flag) {
		pc = pc + x;
		cycles += 4;
	}
}
void CPU::LDar(uint16_t address, uint8_t value){
	Mem->write8(address, value);
}
void CPU::LDra(uint8_t& reg,uint16_t address) {
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
	Mem->write16(sp, pc + 1);
	pc = address;
	
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
	pc = Mem->read8(sp) | Mem->read8(sp + 1)<< 8;
	sp += 2;
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
void CPU::incn(uint8_t &reg){
	reg++;
	if (reg == 0)
		flags.zero = true;
	else
		flags.zero = false;
	flags.subtract = false;
}
void CPU::decn(uint8_t &reg){
	reg--;
	if (reg == 0)
		flags.zero = true;
	else
		flags.zero = false;
	flags.subtract = true;
}
void CPU::RLCr(uint8_t& reg) {
	flags.subtract = false;
	flags.zero = false;
	flags.halfcarry = false;

	if (0x80 & reg) {
		flags.carry = true;
		reg = reg << 1;
		reg += 1;
	}
	else
		reg = reg << 1;
}
void CPU::decnn(sixReg& reg) {
	if (reg.lowbit > 0)
		reg.lowbit--;
	else if(reg.highbit > 0) {
		reg.highbit--;
		reg.lowbit = 0xff;
	}
	
}
void CPU::Or(uint8_t value) {
	clearFlags();
	AF.highbit = AF.highbit | value;
	if (AF.highbit == 0) {
		flags.zero = true;
	}
}
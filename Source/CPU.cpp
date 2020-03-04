
#include "CPU.h"
#include "Opnames.h"
#include <iostream>
using namespace std;

//todo implement SUBn function
CPU::CPU(){
	const int MAXCYCLES = 69905;
	
	Mem = new Memory();
	cycles = 0; 
	intrpt = false;
	sp = 0xFFFE;
	pc = 0;
	AF.high = 0;
}

void StartCpu(){
		
};
void CPU::readOp(uint8_t opcode) {
	//cout << "Calling opcode: " << std::hex << int(opcode) << " \tPC: " << pc << endl;
	pc++;
	switch (opcode) {
	case 0x00: break;
	case 0x01: LDnn(BC, pc++); pc++;  break;
	case 0x02: LDar(BC.to16(), AF.high); break;
	case 0x03: BC.inc(); break;
	case 0x04: incn(BC.high); break;
	case 0x05: decn(BC.high); break;
	case 0x06: LDn(BC.high, pc++); break;
	case 0x07: RLCr(AF.high); break;
	case 0x08: Mem->write16(Mem->read16(pc++), sp); pc++; break;
	case 0x09: add(HL, BC); break;
	case 0x0A: LDn(AF.high, BC.to16()); break;
	case 0x0B: decnn(BC); break;
	case 0x0C: incn(BC.low); break;
	case 0x0D: decn(BC.low); break;
	case 0x0E: LDn(BC.low, pc++); break;
	//case 0x0F: RCCA(); break;
	//case 0x10: stop(); break;
	case 0x11: LDnn(DE, pc++); pc++; break;
	case 0x12: LDra(AF.high, DE.to16()); break;
	case 0x13: incr(DE); break;
	case 0x14: incn(DE.high); break;
	case 0x15: decn(DE.high); break;
	case 0x16: LDn(DE.high, pc++); break;
	//case 0x17: RLA(); break;
	case 0x18: JRc(true); break;
	case 0x19: add(HL, DE); break;
	case 0x1A: LDn(AF.high, DE.high << 8 | DE.low); break;
	case 0x1B: DE.dec(); break;
	case 0x1C: incn(DE.low); break;
	case 0x1D: decn(DE.low); break;
	case 0x1E: DE.low = Mem->read8(pc++); break;
	//case 0x1F: RRA(); break;
	case 0x20: JRc(!flags.zero); break;
	case 0x21: LDnn(HL, pc++); pc++; break;
	case 0x22: LDDrn(AF.high, HL, false); break;
	case 0x23: incr(HL); break;
	case 0x24: incn(HL.high); break;
	case 0x25: decn(HL.high);   break;
	case 0x26: HL.high = Mem->read8(pc++); break;
	//case 0x27: DAA(); break;
	case 0x28: JRc(flags.zero); break;
	case 0x29: add(HL, HL); break;
	case 0x2A: LDDnr(AF.high, HL, false); break;
	case 0x2B: HL.dec(); break;
	case 0x2C: incn(HL.low); break;
	case 0x2D: decn(HL.low); break;
	case 0x2E: HL.low = Mem->read8(pc++); break;
	case 0x2F: AF.high = ~AF.high; break;
	case 0x30: JRc(!flags.carry); break;
	case 0x31: sp = Mem->read16(pc++); pc++; break;
	case 0x32: LDDrn(AF.high, HL, true);  break;
	case 0x33: sp++; break;
	case 0x34: incr(HL); break;
	case 0x35: Mem->write8(HL.to16(), Mem->read8(HL.to16()) - 1); break;
	case 0x36: Mem->write8(HL.to16(), Mem->read8(pc++)); break;
	//case 0x37: SCF(); break;
	case 0x38: JRc(flags.carry); break;
	case 0x39: HL.set(HL.to16() + sp); break;
	case 0x3A: LDDnr(AF.high, HL, true); break;
	case 0x3B: sp--; break;
	case 0x3C: incn(AF.high); break;
	case 0x3D: decn(AF.high); break;
	case 0x3E: LDn( AF.high, pc++);  break;
	//case 0x3f: CCF(); break;
	case 0x40: BC.high = BC.high; break;
	case 0x41: BC.high = BC.low; break;
	case 0x42: BC.high = DE.high; break;
	case 0x43: BC.high = DE.low; break;
	case 0x44: BC.high = HL.high; break;
	case 0x45: BC.high = HL.low; break;
	case 0x46: LDra(BC.high, HL.to16()); break;
	case 0x47: BC.high = AF.high; break;
	case 0x48: BC.low = BC.high; break;
	case 0x49: BC.low = BC.low; break;
	case 0x4A: BC.low = DE.high; break;
	case 0x4B: BC.low = DE.low; break;
	case 0x4C: BC.low = HL.high; break;
	case 0x4D: BC.low = HL.low; break;
	case 0x4E: LDra(BC.low, HL.to16()); break;
	case 0x4f: BC.low = AF.high; break;
	case 0x50: DE.high = BC.high; break;
	case 0x51: DE.high = BC.low; break;
	case 0x52: DE.high = DE.high; break;
	case 0x53: DE.high = DE.low; break;
	case 0x54: DE.high = HL.high;  break;
	case 0x55: DE.high = HL.low; break;
	case 0x56: LDra(DE.high, HL.to16()); break;
	case 0x57: DE.high = AF.high; break;
	case 0x58: DE.low = BC.high; break;
	case 0x59: DE.low = BC.low; break;
	case 0x5A: DE.low = DE.high; break;
	case 0x5B: DE.low = DE.low; break;
	case 0x5C: DE.low = HL.high; break;
	case 0x5D: DE.low = HL.low; break;
	case 0x5E: DE.low = Mem->read8(HL.to16()); break;
	case 0x5f: DE.low = AF.high; break;
	case 0x60: HL.high = BC.high; break;
	case 0x61: HL.high = BC.low; break;
	case 0x62: HL.high = DE.high; break;
	case 0x63: HL.high = DE.low; break;
	case 0x64: HL.high = HL.high; break;
	case 0x65: HL.high = HL.low; break;
	case 0x66: LDn(HL.high, HL.to16()); break;
	case 0x67: HL.high = AF.high; break;
	case 0x68: HL.low = BC.high; break;
	case 0x69: HL.low = BC.low; break;
	case 0x6A: HL.low = DE.high; break;
	case 0x6B: HL.low = DE.low; break;
	case 0x6C: HL.low = HL.high; break;
	case 0x6D: HL.low = HL.low; break;
	case 0x6E: LDn(HL.low, HL.to16()); break;
	case 0x6F: HL.low = AF.high; break; 
	case 0x70: LDar(HL.to16(), BC.high); break;
	case 0x71: LDar(HL.to16(), BC.low); break;
	case 0x72: LDar(HL.to16(), DE.high); break;
	case 0x73: LDar(HL.to16(), DE.low); break;
	case 0x74: LDar(HL.to16(), HL.high); break;
	case 0x75: LDar(HL.to16(), HL.low); break;
	//case 0x76: halt(); break;
	case 0x77: LDar(HL.to16(), AF.high); break;
	case 0x78: AF.high = BC.high; break;
	case 0x79: AF.high = BC.low; break;
	case 0x7A: AF.high = DE.high; break;
	case 0x7B: AF.high = DE.low; break;
	case 0x7C: AF.high = HL.high; break;
	case 0x7D: AF.high = HL.low; break;
	case 0x7E: LDra(AF.high, HL.to16()); break;
	case 0x7F: AF.high = AF.high; break;
	case 0x80: addn(BC.high); break;
	case 0x81: addn(BC.low); break;
	case 0x82: addn(DE.high); break;
	case 0x83: addn(DE.low); break;
	case 0x84: addn(HL.high); break;
	case 0x85: addn(HL.low); break;
	case 0x86: addn(Mem->read8(HL.to16())); break;
	case 0x87: addn(AF.high); break;
	case 0x88: adc(BC.high); break;
	case 0x89: adc(BC.low); break;
	case 0x8A: adc(DE.high); break;
	case 0x8B: adc(DE.low); break;
	case 0x8C: adc(HL.high); break;
	case 0x8D: adc(HL.low); break;
	case 0x8E: adc(Mem->read8(HL.to16())); break;
	case 0x8F: adc(AF.high); break;
	case 0x90: sub(BC.high); break;
	case 0x91: sub(BC.low); break;
	case 0x92: sub(DE.high); break;
	case 0x93: sub(DE.low); break;
	case 0x94: sub(HL.high); break;
	case 0x95: sub(HL.low); break;
	case 0x96: sub(Mem->read8(HL.to16())); break;
	case 0x97: sub(AF.high); break;
	case 0x98: sbc(BC.high); break;
	case 0x99: sbc(BC.low); break;
	case 0x9A: sbc(DE.high); break;
	case 0x9B: sbc(DE.low); break;
	case 0x9C: sbc(HL.high); break;
	case 0x9D: sbc(HL.low); break;
	case 0x9E: sbc(Mem->read8(HL.to16())); break;
	case 0x9F: sbc(AF.high); break;
	case 0xA0: And(BC.high); break;
	case 0xA1: And(BC.low); break;
	case 0xA2: And(DE.high); break;
	case 0xA3: And(DE.low); break;
	case 0xA4: And(HL.high); break;
	case 0xA5: And(HL.low); break;
	case 0xA6: And(Mem->read8(HL.to16())); break;
	case 0xA7: And(AF.high); break;
	case 0xA8: xOR(BC.high); break;
	case 0xA9: xOR(BC.low); break;
	case 0xAA: xOR(DE.high); break;
	case 0xAB: xOR(DE.low); break;
	case 0xAC: xOR(HL.high); break;
	case 0xAD: xOR(HL.low); break;
	case 0xAE: xOR(Mem->read8(HL.to16())); break;
	case 0xAF: xOR(AF.high); break;
	case 0xB0: Or(BC.high); break;
	case 0xB1: Or(BC.low); break;
	case 0xB2: Or(DE.high); break;
	case 0xB3: Or(DE.low); break;
	case 0xB4: Or(HL.high); break;
	case 0xB5: Or(HL.low); break;
	case 0xB6: Or(Mem->read8(HL.to16())); break;
	case 0xB7: Or(AF.high); break;
	case 0xB8: CPn(BC.high); break;
	case 0xB9: CPn(BC.low); break;
	case 0xBA: CPn(DE.high); break;
	case 0xBB: CPn(DE.low); break;
	case 0xBC: CPn(HL.high); break;
	case 0xBD: CPn(HL.low); break;
	case 0xBE: CPn(Mem->read8(HL.to16())); break;
	case 0xBF: CPn(AF.high); break;
	case 0xC0: if (!flags.zero) ret(); break;
	case 0xC1: pop(BC); break;
	case 0xC2: JPc(!flags.zero); break;
	case 0xC3: pc = Mem->read16(pc++); break;
	case 0xC4: if (!flags.zero) call(Mem->read16(pc)); pc += 2; break;
	case 0xC5: push(BC); break;
	case 0xC6: addn(Mem->read8(pc++)); break;
	case 0xC7: call(0x00); break;
	case 0xC8: if (flags.zero) ret(); break;
	case 0xC9: ret(); break;
	case 0xCA: JPc(flags.zero); break;
	case 0xCB: CBcode(Mem->read8(pc)); break;
	case 0xCC: if (flags.zero) call(Mem->read16(pc++)); break;
	case 0xCD: call(Mem->read16(pc++)); break;
	case 0xCE: adc(AF.high); break;
	case 0xCF: push(pc); pc = 0x08; break;
	case 0xD0: if (!flags.zero); ret(); break;
	case 0xD1: pop(DE); break;
	case 0xD2: JPc(!flags.carry); break;
	//case 0xd3: break;
	case 0xD4: if(!flags.carry) call(Mem->read16(pc++)); pc++; break; 
	case 0xD5: push(DE); break;
	case 0xD6: sub(Mem->read8(pc++)); break;
	case 0xD7: call(0x0010); break;
	case 0xD8: if (flags.carry) ret(); break;
	case 0xD9: ret(); break; //doesn't reset interrupt flag
	case 0xDA: JPc(flags.carry); break;
	//case 0xDB: break;
	case 0xDC: if (flags.carry) call(Mem->read16(pc++)); break;
	case 0xDE: sbc(Mem->read8(pc++)); break;
	case 0xDF: call(0x0018); break;
	case 0xE0: LDar(0xff00 + Mem->read8(pc++), AF.high); break;
	case 0xE1: pop(HL); break;
	case 0xE2: LDar(0xff00 + BC.low, AF.high); break;
	case 0xE5: push(HL); break;
	case 0xE6: And(Mem->read8(pc++)); break;
	case 0xEA: LDar(Mem->read16(pc++),AF.high); pc++; break;
	case 0xE9: pc = HL.to16(); break;
	case 0xEF: push(pc); pc = 0x0028; break;
	case 0xF0: LDra(AF.high, 0xff00 + Mem->read8(pc++)); break;
	case 0xF1: pop(AF); break;
	case 0xF3: IME = false; break;
	case 0xF5: push(AF); break;
	case 0xF8: HL.set(sp + int8_t(Mem->read8(pc++))); break;
	case 0xFA: LDn(AF.high, Mem->read8(pc++) | Mem->read8(pc++) << 8); break;
	case 0xFB: IME = true; break;
	case 0xFE: CPn(Mem->read8(pc++)); break;
	case 0xFF: call(0x0038); break;
	
	default:
		cout << "unimplemented opcode: " << opNames[opcode] << " Number: " << hex << (int)opcode << " " << "PC: " << pc << "\n";

		quit = true;
	}

	if (pc > 0xffff)
		cout << "PC outside of scope";
	cycles += opcodeCycleCount[opcode];
}
void CPU::checkINT() {
	//masks requested intterupts too the enabled intterrupts
	uint8_t flag = Mem->read8(0xffff) & Mem->read8(0xff0f);
	//handle intterupt 
	if (flag) {
		//v-blank
		if (flag & 0x01) {
			Mem->write8(0xff0f, Mem->read8(0xff0f) & ~(0x01));
			pc -= 1;
			call(0x40);
		}
		//LCDC STAT
		else if (flag & 0x02) {
			Mem->write8(0xff0f, Mem->read8(0xff0f) & ~(0x02));
			pc -= 1;
			call(0x48);
		}
		//Timer overflow
		else if (flag & 0x04) {
			Mem->write8(0xff0f, Mem->read8(0xff0f) & ~(0x04));
			pc -= 1;
			call(0x50);
		}
		//serial
		else if (flag & 0x08) {
			Mem->write8(0xff0f, Mem->read8(0xff0f) & ~(0x08));
			pc -= 1;
			call(0x58);
		}
		//joypad
		else if (flag & 0x10) {
			Mem->write8(0xff0f, Mem->read8(0xff0f) & ~(0x10));
			pc -= 1;
			call(0x60);
		}
	}
}
void CPU::update(){
	if (IME)
		checkINT();
	readOp(Mem->read8(pc));

}
void CPU::xOR(uint8_t reg){
	AF.high = AF.high ^ reg;
	if (AF.high == 0)
		flags.zero = true;
	else 
		flags.zero = false;	
}
void CPU::LDnn(sixReg &reg, uint16_t address){
	reg.low = Mem->read8(address);
	reg.high = Mem->read8(address + 1);
}
void CPU::LDn(uint8_t &reg, uint16_t address){
	reg = Mem->read8(address);
}
void CPU::LDDrn(uint8_t& reg, sixReg& reg2, bool neg){
	uint16_t address = reg2.high << 8 | reg2.low;
	Mem->write8(address, reg);
	if (neg)
		address--;
	else
		address++;
	reg2.high =  address >> 8;
	reg2.low = address;
}
void CPU::LDDnr(uint8_t& reg, sixReg& reg2, bool neg) {
	uint16_t address = reg2.high << 8 | reg2.low;
	reg = Mem->read8(address);
	if (neg)
		address--;
	else
		address++;
	reg2.high = address >> 8;
	reg2.low = address;
}
void CPU::JRc(bool flag){
	int8_t x = Mem->read8(pc++);
	if (flag) {
		pc = pc + x;
		cycles += 4;
	}
}
void CPU::JPc(bool flag){
	if (flag) {
		pc = Mem->read16(pc);
	}
	pc += 2;
}
void CPU::LDar(uint16_t address, uint8_t value){
	Mem->write8(address, value);
}
void CPU::LDra(uint8_t& reg, uint16_t address) {
	reg = Mem->read8(address);
}
void CPU::CPn(uint8_t value)
{
	clearFlags();
	//todo set halfcarry
	flags.subtract = true;
	if (value > AF.high)
		flags.carry = true;
	else if (value == AF.high)
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
void CPU::And(uint8_t reg){
	clearFlags();
	AF.high = reg & AF.high;
	if (AF.high == 0)
		flags.zero = true;
	flags.halfcarry = true;
}
void CPU::adc(uint8_t value){
	if (flags.carry)
		value++;
	clearFlags();
	AF.high = AF.high + value;
	if (AF.high < value)
		flags.carry = true;
	if (AF.high == 0)
		flags.zero = true;
}
void CPU::inc(uint16_t address)
{
	Mem->write8(address, Mem->read8(address) + 1);
}
void CPU::pop(sixReg& reg){
	reg.low = Mem->read8(sp);
	reg.high = Mem->read8(sp + 1);
	sp += 2;
}
void CPU::ret() {
	pc = Mem->read8(sp) | Mem->read8(sp + 1 )<< 8;
	sp += 2;
}
void CPU::add(sixReg& reg, sixReg& reg2) {
	flags.subtract = false;
	bool carry = false;
	uint8_t temp = reg.low + reg2.low;
	if (temp < reg.low)
		carry = true;

	reg.low = temp;

	if ((((reg.high & 0xf) + (reg2.high & 0xf)) & 0x10) == 0x10)
		flags.halfcarry = true;
	else
		flags.halfcarry = false;

	if (reg.high + reg2.high < reg.high)
		flags.carry = true;

	if (carry)
			reg.high = reg.high + reg2.high + 1;
	else
		reg.high = reg2.high + reg.high;
}
void CPU::push(sixReg reg) {
	Mem->write8(sp - 1, reg.high);
	Mem->write8(sp - 2, reg.low);
	sp -= 2;
}
void CPU::push(uint16_t value) {
	Mem->write16(sp - 2, value);
	sp -= 2;
}
void CPU::incr(sixReg& reg) {
	if (reg.low == 0xff) {
		reg.low = 0x00;
		reg.high++;
	}
	else
		reg.low++;
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
	if (reg.low > 0)
		reg.low--;
	else if(reg.high > 0) {
		reg.high--;
		reg.low = 0xff;
	}
	
}
void CPU::Or(uint8_t value) {
	clearFlags();
	AF.high = AF.high | value;
	if (AF.high == 0) {
		flags.zero = true;
	}
}
void CPU::RLC(uint8_t& reg) {
	flags.halfcarry = false;
	flags.subtract = false;
	flags.carry = 0x80 & reg;
	reg = reg << 1;
	if (reg == 0)
		flags.zero;
}
void CPU::swap(uint8_t& reg) {
	clearFlags();
	uint8_t x = 0;
	x = reg << 4;
	x = x | reg >> 4;

}
void CPU::SRA(uint8_t& reg)
{
	uint8_t x;
	x = 0x80 & reg;
	flags.carry = 0x01 & reg;
	reg = reg >> 1;
	reg |= x;
	if (reg == 0)
		flags.zero = 0;

}
void CPU::SLA(uint8_t& reg)
{
	flags.carry = 0x80 & reg;
	reg = reg << 1;
	reg &= 0xFE;
	if (reg == 0)
		flags.zero = 0;

}
void CPU::CBcode(uint8_t code){
	pc++;
	switch (code) {
	case 0x07: RLC(AF.high); break;
	case 0x27: SLA(AF.high); break;
	case 0x28: SRA(BC.high); break;
	case 0x37: swap(AF.high); break;
	case 0x77: SLA(AF.high); break;
	case 0x87: AF.high = AF.high && 0xFE; break;
	default:
		cout << "unimp CB code: " << hex << int(code) << "\n";
		cout << "pc " << hex << int(pc) << " " << int(Mem->read8(pc));
		quit = true;
	}
}

void CPU::addn(uint8_t reg) {
	clearFlags();
	uint8_t temp = reg + AF.high; 
	if (reg + AF.high < AF.high)
		flags.carry = true;
	if (temp == 0x0)
		flags.zero = true;
	AF.high = temp;
}

void CPU::sub(uint8_t reg) {
	clearFlags();
	flags.subtract = true;
	if (AF.high < 0)
		flags.carry = true;
	if ((reg & 0xF) - (AF.high & 0xF) < 0)
		flags.halfcarry = true;
	AF.high = AF.high - reg;
	if (AF.high == 0)
		flags.zero = true;
}

void CPU::sbc(uint8_t reg) {
	if (flags.carry)
		reg++;
	clearFlags();
	flags.subtract = true;
	if (AF.high < 0)
		flags.carry = true;
	if ((reg & 0xF) - (AF.high & 0xF) < 0)
		flags.halfcarry = true;
	AF.high = AF.high - reg;
	if (AF.high == 0)
		flags.zero = true;
}
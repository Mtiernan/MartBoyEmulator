#include <Memory.h>
#include <iostream>
#include <fstream>
using namespace std;

Memory::Memory() 
{

	



}
void Memory::loadRom() {
	/*	//Warning the romcart is only allocated for 0x8000 bytes of memory because that is what is needed for the tetris cart of the original gameboy. 
	Which means if the rom you are loading uses rom banking this function does not work 
	*/

	ifstream file("tetris.gb", ifstream::binary);
	
	//load file into stream named file tetris is used as an example/test

	int length;

	file.seekg(0, file.end);
	length = file.tellg();
	file.seekg(0, file.beg);
	//gets length of file

	file.read((char*)romcart, length);

	//read the characters into romcart


}

uint8_t Memory::read8(uint16_t address) {

	//read a memory from the correct section oo

	if (address <= 0x7FFF)
		return romcart[address];

	else if (0x7FFF < address && address <= 0x9FFF)
		return vram[address - 0x8000];

	else if (0x9FFF < address && address <= 0xbFFF)
		return eram[address - 0xA000];

	else if (0xBFFF < address && address <= 0xDFFF)
		return wram[address - 0xC000];

	else if (0xfdff < address && address <= 0xFE9F)
		return oam[address - 0xfe00];

	else if (address == 0xff04) return 0;
	else if (0xff79 < address && address <= 0xfffe)
		return hram[address - 0xff80];


	return NULL;
}


uint16_t Memory::read16(uint16_t address)
{//combines two values from memory into a 16 bit value

	return (read8(address) | (read8(address + 1) << 8));
}
void Memory::write8(uint16_t address, uint8_t value)
{
	//read a byte from mermory
	if (address <= 0x7FFF)
	{

	}
	else if (0x7FFF < address && address <= 0x9FFF)
		vram[address - 0x8000] = value;

	else if (0x9FFF < address && address <= 0xbFFF)
		eram[address - 0xA000] = value;

	else if (0xBFFF < address && address <= 0xDFFF)
		wram[address - 0xC000] = value;

	else if (0xfdff < address && address <= 0xFEFF)
		oam[address - 0xfe00] = value;

	else if (0xff79 < address && address <= 0xfffe)
		hram[address - 0xff80] = value;



}

void Memory::write16(uint16_t address, uint16_t value) {
	//writes the first byte
	write8(address, value & 0x00ff);
	//writes the second byte
	write8(address + 1, ((value & 0xff00) >> 8));
}
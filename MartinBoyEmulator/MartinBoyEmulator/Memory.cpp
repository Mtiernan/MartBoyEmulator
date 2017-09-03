#include <Memory.h>


void Memory::loadRom() {




}

uint8_t Memory::read8(uint16_t address) {


	if (address <= 0x7FFF)
		return romCart[address];

	else if (0x7FFF < address <= 0x9FFF)
		return vram[address - 0x8000];

	else if (0x9FFF < address <= 0xbFFF)
		return eram[address - 0xA000];

	else if (0xBFFF < address <= 0xDFFF)
		return wram[address - 0xC000];

	else if (0xfdff < address <= 0xFEFF)
		return oam[address - 0xfe00];

	else if (0xff79 < address <= 0xfffe)
		return hram[address - 0xff80];







}
void Memory::write8(uint16_t address, uint8_t value)
{
	if (address <= 0x7FFF)
		romCart[address] = value;

	else if (0x7FFF < address <= 0x9FFF)
		vram[address - 0x8000] = value;

	else if (0x9FFF < address <= 0xbFFF)
		eram[address - 0xA000] = value;

	else if (0xBFFF < address <= 0xDFFF)
		wram[address - 0xC000] = value;

	else if (0xfdff < address <= 0xFEFF)
		oam[address - 0xfe00] = value;

	else if (0xff79 < address <= 0xfffe)
		hram[address - 0xff80] = value;



}
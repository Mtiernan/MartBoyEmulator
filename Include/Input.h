
#ifndef INPUT_H
#define INPUT_H
#include "Memory.h"
#include "CPU.h"
#include <SDL.h>
/*
input is handled at memory FF00
flip bit to 0 to set
bit 7: unused
bit 6: unused
bit 5: p15 port buttons
bit 4: p14 port directions
bit 3: p13 down or start
bit 2: p12 up or select
bit 1: p11 left or b
bit 0: p10 right or a
										ff00 = 1111 1111
*/

enum button {
	up,
	down,
	left,
	right,
	a,
	b,
	select,
	start
};

class Input {
private:
	Memory* mem;
	CPU* cpu;
	uint8_t buttons, directions;
public:
	Input(Memory* mem, CPU* cpu);
	void getKeyDown(SDL_Event keyEvent);
	void getKeyUp(SDL_Event keyEvent);
	void buttonPress(button butt, bool held);
	void reset();
	void update(Memory* mem);
};


#endif
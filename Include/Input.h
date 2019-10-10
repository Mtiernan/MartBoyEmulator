
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

*/

enum Button{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	SELECT,
	START,
	A,	
	B
};

class Input {
private:
	Memory* mem;
	CPU* cpu;
public:
	Input(Memory* mem, CPU* cpu);
	void getKey(SDL_Event keyEvent);
	void buttonPress(Button button);
	void reset();
};


#endif
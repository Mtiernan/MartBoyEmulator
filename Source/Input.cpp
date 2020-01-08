#include "Input.h"
#include <iostream>

void Input::getKeyDown(SDL_Event keyEvent) {
		
		
			switch (keyEvent.key.keysym.sym) {
			case SDLK_w:
				buttonPress(up, true);
				std::cout << "up makes directions: " << std::hex << (int)directions << "\n";
				break;
			case SDLK_s:
				buttonPress(down, true);
				break;
			case SDLK_a:
				buttonPress(left, true);
				break;
			case SDLK_d:
				buttonPress(right, true);
				break;
			case SDLK_j:
				buttonPress(a, true);
				break;
			case SDLK_k:
				buttonPress(b, true);
				break;
			case SDLK_RETURN:
				buttonPress(select, true);
				break;
			case SDLK_SPACE:
				buttonPress(start, true);
				break;
			}
	
}

void Input::getKeyUp(SDL_Event keyEvent) {

	switch (keyEvent.key.keysym.sym) {
	case SDLK_w:
		buttonPress(up, false);
		std::cout << "up makes directions: " << std::hex << (int)directions <<"\n";
		break;
	case SDLK_s:
		buttonPress(down, false);
		break;
	case SDLK_a:
		buttonPress(left, false);
		break;
	case SDLK_d:
		buttonPress(right, false);
		break;
	case SDLK_j:
		buttonPress(a, false);
		break;
	case SDLK_k:
		buttonPress(b, false);
		break;
	case SDLK_RETURN:
		buttonPress(select, false);
		break;
	case SDLK_SPACE:
		buttonPress(start, false);
		break;
	}

}
Input::Input(Memory* memory, CPU* emu)
{
	mem = memory;
	cpu = emu;
	directions = 0xf;
	buttons = 0xf;
}

void Input::reset(){ 
	mem->write8(0xff00, 0xff);
}

void Input::buttonPress(button butt, bool held){

	//sets correct position to 0 on keydown or back to 1 on keyup
	switch (butt){
	case up:
		if (held)
			directions &= ~(1 << 2);
		else
			directions |= 1 << 2;
		break;
	case down:
		if (held)
			directions &= ~(1 << 3);
		else
			directions |= 1 << 3;
		break;
	case left:
		if (held)
			directions &= ~(1 << 1);
		else
			directions |= 1 << 1;
		break;
	case right:
		if (held)
			directions &= ~(1 << 0);
		else
			directions |= 1 << 0;
		break;
	case a:
		if (held)
			buttons &= ~(1 << 0);
		else
			buttons |= 1 << 0;
		break;
	case b:
		if (held)
			buttons &= ~(1 << 1);
		else
			buttons |= 1 << 1;
		break;
	case select:
		if (held)
			buttons &= ~(1 << 2);
		else
			buttons |= 1 << 2;
		break;
	case start:
		if (held)
			buttons &= ~(1 << 3);
		else
			buttons |= 1 << 3;
		break;
	}
	
}

void Input::update(Memory* mem) {

	uint8_t inputVal = mem->read8(0xFF00);
	
	//dpad
	if (inputVal ^ 0x10)
	{
		inputVal &= directions;
	}

	//buttons
	else if (inputVal ^ 0x20)
	{
		inputVal &= buttons;
	}
	else 
		return;
	
	mem->write8(0xFF00, inputVal);

}
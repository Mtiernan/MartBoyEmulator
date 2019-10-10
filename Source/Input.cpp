#include "Input.h"
#include <iostream>

void Input::getKey(SDL_Event keyEvent) {
		
		switch (keyEvent.key.keysym.sym) {
		case SDLK_w:
			std::cout << "up\n";
			buttonPress(UP);
			break;
		case SDLK_s: 
			std::cout << "down\n";
			buttonPress(DOWN);
			break;
		case SDLK_a: 
			std::cout << "left\n";
			buttonPress(LEFT);
			break;
		case SDLK_d: 
			std::cout << "right\n";
			buttonPress(RIGHT);
			break;
		case SDLK_j: 
			std::cout << "a\n";
			buttonPress(A);
			break;
		case SDLK_k:
			std::cout << "b\n";
			buttonPress(B);
			break;
		case SDLK_RETURN:
			std::cout << "select\n";
			buttonPress(SELECT);
			break;
		case SDLK_SPACE:
			std::cout << "start\n";
			buttonPress(START);
			break;
		}
	
}

Input::Input(Memory* memory, CPU* emu)
{
	mem = memory;
	cpu = emu;
}

void Input::reset(){ 
	mem->write8(0xff00, 0xff);
}

void Input::buttonPress(Button button){

}
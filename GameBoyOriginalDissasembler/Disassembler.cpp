#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#include  <Opcodes.h>



int main() {
	
	ifstream file("tetris.gb", ifstream::binary);
	//load file into stream named file tetris is used as an example/test

	int length, PC;
	PC = 0;
	
	file.seekg(0, file.end);
	length = file.tellg();
	file.seekg(0, file.beg);
	//gets length of file

	
	char *buffer = new char[length];
	//create a buffer the size of the file
	
	file.read(buffer, length);

	//read the characters into buffer
	ofstream output;
	output.open("Disassembled.txt");
	uint8_t opcode;
	
	while (PC < length ) 
	{
		opcode = uint8_t(buffer[PC]);
		output << hex << PC << '\t'  << hex <<  int(opcode) << '\t' << opnames[opcode] << endl;
		PC += opcodebytesize[opcode];


	}
	//go through buffer printing out commands


	return 0;
}
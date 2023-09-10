#include <stdint.h>
#include <stdio.h>
#include "Cpu.hpp"
#include "RegFile32I.h"

int main(int argc, char* argv[])
{
	const uint64_t memSize = 1024 * 1024;
	uint8_t* memory = new uint8_t[memSize];
	Cpu<RegFile32I> cpu;
	cpu.setMemory(memory, memSize);
	cpu.fetch();
	return 0;
}
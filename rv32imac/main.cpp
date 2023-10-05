#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include "general.h"
#include "rv32imac.h"

char GlobalPrintBuffer[256];

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Usage: riscv program.bin\n");
		return 1;
	}
	rv32imac cpu;
	cpu.pMemory = new uint8_t[1024 * 1024];
	const char* filename = argv[1];
	if (loadElf(filename, cpu.pMemory, cpu.pc) == err_t::error) {
		fprintf(stderr, "Loading elf failed.\n");
		return 1;
	}
	uint64_t iCounter = 0;
	while (true) {
		const uint32_t mcode = *((uint32_t*)&cpu.pMemory[cpu.pc]);
		if (iCounter == 17) {
			printf("error\n");
		}
		const err_t err = cpu.execute(mcode);
		iCounter++;
		if (err != err_t::ok) {
			printf("ERROR at pc = %lu\n", cpu.pc);
			return 1;
		}
		char* buffer = reinterpret_cast<char*>(cpu.pMemory + 0xFFC00);
		if (buffer[0] != '\0') {
			const char* text = buffer + 1;
			strncpy(GlobalPrintBuffer, text + 1, sizeof(GlobalPrintBuffer));
			printf("%s\n", text);
			buffer[0] = '\0';
		}
	}
	return 0;
}
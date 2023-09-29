#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include "memory.h"
#include "RiscvCpu.h"

char GlobalPrintBuffer[256];

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Usage: riscv program.bin\n");
		return 1;
	}
	Memory memory;
	if (memory.init(1024 * 1024) == res_t::ERROR) {
		fprintf(stderr, "Memory init failed.\n");
		return 1;
	}
	uint64_t startAddr = 0;
	const char* filename = argv[1];
	if (loadElf(filename, memory.data(), startAddr) == res_t::ERROR) {
		fprintf(stderr, "Loading elf failed.\n");
		return 1;
	}

	RiscvCpu cpu(memory);
	cpu.iRegFile.pc = startAddr;

	while (true) {
		const res_t resInstr = cpu.nextInstr();
		if (resInstr == res_t::ERROR) {
			fprintf(stderr, "Instruction error.\n");
			break;
		}
		char* buffer = reinterpret_cast<char*>(memory.data() + 0xFFC00);
		if (buffer[0] != '\0') {
			const char* text = buffer + 1;
			strncpy(GlobalPrintBuffer, text + 1, sizeof(GlobalPrintBuffer));
			printf("%s\n", text);
			buffer[0] = '\0';
		}
	}
	return 0;
}
#include <stdint.h>
#include <stdio.h>
#include <cstring>
#include "Memory.h"
#include "RiscvCpu.h"

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Usage: riscv program.bin\n");
		return 1;
	}
	char printBuffer[256];
	Memory memory;
	if (memory.init(1024 * 1024) == res_t::ERROR) {
		fprintf(stderr, "Memory init failed.\n");
		return 1;
	}
	memory.load(argv[1], 0x10000);
	RiscvCpu cpu(memory);
	while (true) {
		const res_t resInstr = cpu.nextInstr();
		if (resInstr == res_t::ERROR) {
			fprintf(stderr, "Instruction error.\n");
			break;
		}
		char* buffer = reinterpret_cast<char*>(memory.data() + 0xFFC00);
		if (buffer[0] != '\0') {
			const char *text = buffer + 1;
			strncpy(printBuffer, text + 1, sizeof(printBuffer));
			printf("%s\n", text);
			buffer[0]= '\0';
		}
	}
	return 0;
}
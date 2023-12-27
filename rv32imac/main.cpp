#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include "general.h"
#include "xwindow.h"
#include "hart.h"

char GlobalPrintBuffer[256];

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Usage: riscv program.bin\n");
		return 1;
	}
	uint8_t* memory = new uint8_t[16 * 1024 * 1024];
	hart hart(memory);
	xwindow window(1024, 786, &memory[1024 * 1024]);
	window.open();
	loadFile(argv[1], memory, 0);
	hart.start(0);
	window.loop();
	window.close();
	return 0;
}
#include <cstring>
#include <stdint.h>
#include <stdio.h>
#include "general.h"
#include "xwindow.h"
#include "hart.h"
#include "memory.h"

using namespace riscv;

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Usage: riscv program.bin\n");
		return 1;
	}
	memory memory;
	memory.init(16 * 1024 * 1024);
	loadFile(argv[1], memory.data(), 0);
	hart hart(memory);
	xwindow window(1024, 786, memory, 1024 * 1024);
	window.open();
	hart.start(0);
	window.loop();
	window.close();
	return 0;
}
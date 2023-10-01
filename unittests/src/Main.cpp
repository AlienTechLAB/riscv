#include <stdio.h>
#include "MemoryTests.h"
#include "DecoderTests.h"

int main()
{
	printf("\n\n\n");
	readWriteTests();
	endianTests();

	DecoderTests::runTests();

	// TODO - end memory tests
	return 0;
}
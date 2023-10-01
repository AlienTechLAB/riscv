#include <assert.h>
#include <stdio.h>
#include "DecoderTests.h"

namespace DecoderTests
{

void getCIWimmTest()
{
	assert(getCIWimm(static_cast<uint16_t>(1 << 5)) == 8);
	assert(getCIWimm(static_cast<uint16_t>(1 << 6)) == 4);
	assert(getCIWimm(static_cast<uint16_t>(1 << 7)) == 64);
	assert(getCIWimm(static_cast<uint16_t>(1 << 8)) == 128);
	assert(getCIWimm(static_cast<uint16_t>(1 << 9)) == 256);
	assert(getCIWimm(static_cast<uint16_t>(1 << 10)) == 512);
	assert(getCIWimm(static_cast<uint16_t>(1 << 11)) == 16);
	assert(getCIWimm(static_cast<uint16_t>(1 << 12)) == 32);
	printf("getCIWimmTest OK\n");
}

void runTests()
{
	getCIWimmTest();
}

}
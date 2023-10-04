#include <assert.h>
#include <stdio.h>
#include "DecoderTests.h"

namespace DecoderTests
{

void nzuimm549623Test()
{
	assert(nzuimm549623(static_cast<uint16_t>(1 << 5)) == 8);
	assert(nzuimm549623(static_cast<uint16_t>(1 << 6)) == 4);
	assert(nzuimm549623(static_cast<uint16_t>(1 << 7)) == 64);
	assert(nzuimm549623(static_cast<uint16_t>(1 << 8)) == 128);
	assert(nzuimm549623(static_cast<uint16_t>(1 << 9)) == 256);
	assert(nzuimm549623(static_cast<uint16_t>(1 << 10)) == 512);
	assert(nzuimm549623(static_cast<uint16_t>(1 << 11)) == 16);
	assert(nzuimm549623(static_cast<uint16_t>(1 << 12)) == 32);
	printf("nzuimm549623Test OK\n");
}

void funct3Test()
{
	assert(funct3(static_cast<uint16_t>(1 << 13)) == 1);
	assert(funct3(static_cast<uint16_t>(1 << 14)) == 2);
	assert(funct3(static_cast<uint16_t>(1 << 15)) == 4);
	assert(funct3(static_cast<uint16_t>(0xE000)) == 7);
	printf("funct3Test OK\n");
}

void rdpTest()
{
	assert(rd(static_cast<uint16_t>(0)) == 8);
	assert(rd(static_cast<uint16_t>(1 << 2)) == 9);
	assert(rd(static_cast<uint16_t>(2 << 2)) == 10);
	assert(rd(static_cast<uint16_t>(3 << 2)) == 11);
	assert(rd(static_cast<uint16_t>(4 << 2)) == 12);
	assert(rd(static_cast<uint16_t>(5 << 2)) == 13);
	assert(rd(static_cast<uint16_t>(6 << 2)) == 14);
	assert(rd(static_cast<uint16_t>(7 << 2)) == 15);
	printf("rdpTest OK\n");
}

void runTests()
{
	nzuimm549623Test();
	funct3Test();
	rdpTest();
}

}
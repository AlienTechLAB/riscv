#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "Memory.h"

void rdwr8Test();
void rdwr16Test(const Endian endian);
void rdwr32Test(const Endian endian);
void rdwr64Test(const Endian endian);
void readWriteTests();

void rdwr8Test()
{
	Memory memory;
	memory.init(1024);
	uint8_t u8 = 0x12;
	assert(memory.readUint8(u8, 0) == res_t::OK);
	assert(u8 == 0x00);
	assert(memory.writeUint8((uint8_t)0x12, 0) == res_t::OK);
	assert(memory.readUint8(u8, 0) == res_t::OK);
	assert(u8 == 0x12);
	int8_t s8 = 0x12;
	assert(memory.readInt8(s8, 1) == res_t::OK);
	assert(s8 == 0x00);
	assert(memory.writeInt8((uint8_t)0x12, 1) == res_t::OK);
	assert(memory.readInt8(s8, 1) == res_t::OK);
	assert(s8 == 0x12);
}

void rdwr16Test(const Endian endian)
{
	Memory memory;
	memory.init(1024);
	uint16_t u16 = 0x1234;
	assert(memory.readUint16(u16, 0, endian) == res_t::OK);
	assert(u16 == 0x0000);
	assert(memory.writeUint16((uint16_t)0x1234, 0, endian) == res_t::OK);
	assert(memory.readUint16(u16, 0, endian) == res_t::OK);
	assert(u16 == 0x1234);
	int16_t s16 = 0x1234;
	assert(memory.readInt16(s16, 2, endian) == res_t::OK);
	assert(s16 == 0x0000);
	assert(memory.writeInt16((int16_t)0x1234, 2, endian) == res_t::OK);
	assert(memory.readInt16(s16, 2, endian) == res_t::OK);
	assert(s16 == 0x1234);
}

void rdwr32Test(const Endian endian)
{
	Memory memory;
	memory.init(1024);
	uint32_t u32 = 0x12345678;
	assert(memory.readUint32(u32, 0, endian) == res_t::OK);
	assert(u32 == 0x00000000);
	assert(memory.writeUint32(0x12345678, 0, endian) == res_t::OK);
	assert(memory.readUint32(u32, 0, endian) == res_t::OK);
	assert(u32 == 0x12345678);
	int32_t s32 = 0x12345678;
	assert(memory.readInt32(s32, 4, endian) == res_t::OK);
	assert(s32 == 0x00000000);
	assert(memory.writeInt32(0x12345678, 4, endian) == res_t::OK);
	assert(memory.readInt32(s32, 4, endian) == res_t::OK);
	assert(s32 == 0x12345678);
}

void rdwr64Test(const Endian endian)
{
	Memory memory;
	memory.init(1024);
	uint64_t u64 = 0x0123456789ABCDEF;
	assert(memory.readUint64(u64, 0, endian) == res_t::OK);
	assert(u64 == 0x0000000000000000);
	assert(memory.writeUint64(0x0123456789ABCDEF, 0, endian) == res_t::OK);
	assert(memory.readUint64(u64, 0, endian) == res_t::OK);
	assert(u64 == 0x0123456789ABCDEF);
	int64_t s64 = 0x0123456789ABCDEF;
	assert(memory.readInt64(s64, 8, endian) == res_t::OK);
	assert(s64 == 0x0000000000000000);
	assert(memory.writeInt64(0x0123456789ABCDEF, 8, endian) == res_t::OK);
	assert(memory.readInt64(s64, 8, endian) == res_t::OK);
	assert(s64 == 0x0123456789ABCDEF);
}

void readWriteTests()
{
	rdwr8Test();
	rdwr16Test(Endian::LITTLE);
	rdwr32Test(Endian::LITTLE);
	rdwr64Test(Endian::LITTLE);
	rdwr16Test(Endian::BIG);
	rdwr32Test(Endian::BIG);
	rdwr64Test(Endian::BIG);
	printf("readWriteTests OK\n");
}

int main()
{
	printf("\n\n\n");
	readWriteTests();

	return 0;
}
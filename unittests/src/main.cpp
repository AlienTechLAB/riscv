#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include "Memory.h"

void rdwr8Test();
void rdwr16Test(const Endian endian);
void rdwr32Test(const Endian endian);
void rdwr64Test(const Endian endian);
void readWriteTests();
void littleEndianInt16Test();
void littleEndianUint16Test();
void bigEndianInt16Test();
void bigEndianUint16Test();
void littleEndianInt32Test();
void littleEndianUint32Test();
void bigEndianInt32Test();
void bigEndianUint32Test();
void littleEndianInt64Test();
void littleEndianUint64Test();
void bigEndianInt64Test();
void bigEndianUint64Test();
void endianTests();

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
	printf("rdwr8Test OK\n");
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
	printf("rdwr16Test OK\n");
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
	printf("rdwr32Test OK\n");
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
	printf("rdwr64Test OK\n");
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
}

void littleEndianInt16Test()
{
	Memory memory;
	memory.init(1024);
	const int16_t s16 = 0x0102;
	assert(memory.writeInt16(s16, 0, Endian::LITTLE) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x02);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x01);
	printf("littleEndianInt16Test OK\n");
}

void littleEndianUint16Test()
{
	Memory memory;
	memory.init(1024);
	const uint16_t u16 = 0x1122;
	assert(memory.writeUint16(u16, 0, Endian::LITTLE) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x22);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x11);
	printf("littleEndianUint16Test OK\n");
}

void bigEndianInt16Test()
{
	Memory memory;
	memory.init(1024);
	const int16_t s16 = 0x0102;
	assert(memory.writeInt16(s16, 0, Endian::BIG) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x01);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x02);
	printf("bigEndianInt16Test OK\n");
}

void bigEndianUint16Test()
{
	Memory memory;
	memory.init(1024);
	const uint16_t u16 = 0x1122;
	assert(memory.writeUint16(u16, 0, Endian::BIG) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x11);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x22);
	printf("bigEndianUint16Test OK\n");
}

void littleEndianInt32Test()
{
	Memory memory;
	memory.init(1024);
	const int32_t s32 = 0x01020304;
	assert(memory.writeInt32(s32, 0, Endian::LITTLE) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x04);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x03);
	assert(memory.readUint8(byte, 2) == res_t::OK);
	assert(byte == 0x02);
	assert(memory.readUint8(byte, 3) == res_t::OK);
	assert(byte == 0x01);
	printf("littleEndianInt32Test OK\n");
}

void littleEndianUint32Test()
{
	Memory memory;
	memory.init(1024);
	const uint32_t u32 = 0x11223344;
	assert(memory.writeUint32(u32, 0, Endian::LITTLE) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x44);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x33);
	assert(memory.readUint8(byte, 2) == res_t::OK);
	assert(byte == 0x22);
	assert(memory.readUint8(byte, 3) == res_t::OK);
	assert(byte == 0x11);
	printf("littleEndianUint32Test OK\n");
}

void bigEndianInt32Test()
{
	Memory memory;
	memory.init(1024);
	const int32_t s32 = 0x01020304;
	assert(memory.writeInt32(s32, 0, Endian::BIG) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x01);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x02);
	assert(memory.readUint8(byte, 2) == res_t::OK);
	assert(byte == 0x03);
	assert(memory.readUint8(byte, 3) == res_t::OK);
	assert(byte == 0x04);
	printf("bigEndianInt32Test OK\n");
}

void bigEndianUint32Test()
{
	Memory memory;
	memory.init(1024);
	const uint32_t u32 = 0x11223344;
	assert(memory.writeUint32(u32, 0, Endian::BIG) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x11);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x22);
	assert(memory.readUint8(byte, 2) == res_t::OK);
	assert(byte == 0x33);
	assert(memory.readUint8(byte, 3) == res_t::OK);
	assert(byte == 0x44);
	printf("bigEndianUint32Test OK\n");
}

void littleEndianInt64Test()
{
	Memory memory;
	memory.init(1024);
	const int64_t s64 = 0x0102030405060708;
	assert(memory.writeInt64(s64, 0, Endian::LITTLE) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x08);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x07);
	assert(memory.readUint8(byte, 2) == res_t::OK);
	assert(byte == 0x06);
	assert(memory.readUint8(byte, 3) == res_t::OK);
	assert(byte == 0x05);
	assert(memory.readUint8(byte, 4) == res_t::OK);
	assert(byte == 0x04);
	assert(memory.readUint8(byte, 5) == res_t::OK);
	assert(byte == 0x03);
	assert(memory.readUint8(byte, 6) == res_t::OK);
	assert(byte == 0x02);
	assert(memory.readUint8(byte, 7) == res_t::OK);
	assert(byte == 0x01);
	printf("littleEndianInt64Test OK\n");
}

void littleEndianUint64Test()
{
	Memory memory;
	memory.init(1024);
	const uint64_t u64 = 0x1122334455667788;
	assert(memory.writeUint64(u64, 0, Endian::LITTLE) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x88);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x77);
	assert(memory.readUint8(byte, 2) == res_t::OK);
	assert(byte == 0x66);
	assert(memory.readUint8(byte, 3) == res_t::OK);
	assert(byte == 0x55);
	assert(memory.readUint8(byte, 4) == res_t::OK);
	assert(byte == 0x44);
	assert(memory.readUint8(byte, 5) == res_t::OK);
	assert(byte == 0x33);
	assert(memory.readUint8(byte, 6) == res_t::OK);
	assert(byte == 0x22);
	assert(memory.readUint8(byte, 7) == res_t::OK);
	assert(byte == 0x11);
	printf("littleEndianUint64Test OK\n");
}

void bigEndianInt64Test()
{
	Memory memory;
	memory.init(1024);
	const int64_t s64 = 0x0102030405060708;
	assert(memory.writeInt64(s64, 0, Endian::BIG) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x01);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x02);
	assert(memory.readUint8(byte, 2) == res_t::OK);
	assert(byte == 0x03);
	assert(memory.readUint8(byte, 3) == res_t::OK);
	assert(byte == 0x04);
	assert(memory.readUint8(byte, 4) == res_t::OK);
	assert(byte == 0x05);
	assert(memory.readUint8(byte, 5) == res_t::OK);
	assert(byte == 0x06);
	assert(memory.readUint8(byte, 6) == res_t::OK);
	assert(byte == 0x07);
	assert(memory.readUint8(byte, 7) == res_t::OK);
	assert(byte == 0x08);
	printf("bigEndianInt64Test OK\n");
}

void bigEndianUint64Test()
{
	Memory memory;
	memory.init(1024);
	const int64_t s64 = 0x1122334455667788;
	assert(memory.writeInt64(s64, 0, Endian::BIG) == res_t::OK);
	uint8_t byte = 0;
	assert(memory.readUint8(byte, 0) == res_t::OK);
	assert(byte == 0x11);
	assert(memory.readUint8(byte, 1) == res_t::OK);
	assert(byte == 0x22);
	assert(memory.readUint8(byte, 2) == res_t::OK);
	assert(byte == 0x33);
	assert(memory.readUint8(byte, 3) == res_t::OK);
	assert(byte == 0x44);
	assert(memory.readUint8(byte, 4) == res_t::OK);
	assert(byte == 0x55);
	assert(memory.readUint8(byte, 5) == res_t::OK);
	assert(byte == 0x66);
	assert(memory.readUint8(byte, 6) == res_t::OK);
	assert(byte == 0x77);
	assert(memory.readUint8(byte, 7) == res_t::OK);
	assert(byte == 0x88);
	printf("bigEndianUint64Test OK\n");
}

void endianTests()
{
	littleEndianInt16Test();
	littleEndianUint16Test();
	bigEndianInt16Test();
	bigEndianUint16Test();

	littleEndianInt32Test();
	littleEndianUint32Test();
	bigEndianInt32Test();
	bigEndianUint32Test();

	littleEndianInt64Test();
	littleEndianUint64Test();
	bigEndianInt64Test();
	bigEndianUint64Test();
}

int main()
{
	printf("\n\n\n");
	readWriteTests();
	endianTests();
	return 0;
}
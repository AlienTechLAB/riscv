#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "riscv.h"

class Memory
{
public:
	~Memory();
	res_t init(uint64_t memSize);
	uint8_t* data();
	void clear();
	res_t load(const char* filename, uint64_t address = 0);
	res_t save(const char* filename, uint64_t address, uint64_t size);
	res_t readInt8(int8_t& value, uint64_t address);
	res_t writeInt8(int8_t value, uint64_t address);
	res_t readUint8(uint8_t& value, uint64_t address);
	res_t writeUint8(uint8_t value, uint64_t address);
	res_t readInt16(int16_t& value, uint64_t address, Endian endian = Endian::LITTLE);
	res_t writeInt16(int16_t value, uint64_t address, Endian endian = Endian::LITTLE);
	res_t readUint16(uint16_t& value, uint64_t address, Endian endian = Endian::LITTLE);
	res_t writeUint16(uint16_t value, uint64_t address, Endian endian = Endian::LITTLE);
	res_t readInt32(int32_t& value, uint64_t address, Endian endian = Endian::LITTLE);
	res_t writeInt32(int32_t value, uint64_t address, Endian endian = Endian::LITTLE);
	res_t readUint32(uint32_t& value, uint64_t address, Endian endian = Endian::LITTLE);
	res_t writeUint32(uint32_t value, uint64_t address, Endian endian = Endian::LITTLE);
	res_t readInt64(int64_t& value, uint64_t address, Endian endian = Endian::LITTLE);
	res_t writeInt64(int64_t value, uint64_t address, Endian endian = Endian::LITTLE);
	res_t readUint64(uint64_t& value, uint64_t address, Endian endian = Endian::LITTLE);
	res_t writeUint64(uint64_t value, uint64_t address, Endian endian = Endian::LITTLE);

private:
	uint8_t* pData{ nullptr };
	uint64_t iSize{ 0 };
};

#endif	// MEMORY_H
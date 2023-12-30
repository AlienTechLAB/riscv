#ifndef MEMORY_H
#define MEMORY_H

#include <mutex>
#include <stdint.h>
#include "types.h"

using namespace riscv;

class memory
{
public:
	~memory();
	err_t init(uint64_t memSize);
	uint64_t size();
	uint8_t* data();
	void lock();
	void unlock();
	void clear();
	err_t readInt8(int8_t& value, uint64_t address);
	err_t writeInt8(int8_t value, uint64_t address);
	err_t readUint8(uint8_t& value, uint64_t address);
	err_t writeUint8(uint8_t value, uint64_t address);
	err_t readInt16(int16_t& value, uint64_t address, endian_t endian);
	err_t writeInt16(int16_t value, uint64_t address, endian_t endian);
	err_t readUint16(uint16_t& value, uint64_t address, endian_t endian);
	err_t writeUint16(uint16_t value, uint64_t address, endian_t endian);
	err_t readInt32(int32_t& value, uint64_t address, endian_t endian);
	err_t writeInt32(int32_t value, uint64_t address, endian_t endian);
	err_t readUint32(uint32_t& value, uint64_t address, endian_t endian);
	err_t writeUint32(uint32_t value, uint64_t address, endian_t endian);
	err_t readInt64(int64_t& value, uint64_t address, endian_t endian);
	err_t writeInt64(int64_t value, uint64_t address, endian_t endian);
	err_t readUint64(uint64_t& value, uint64_t address, endian_t endian);
	err_t writeUint64(uint64_t value, uint64_t address, endian_t endian);

private:
	uint8_t* pData{ nullptr };
	uint64_t iSize{ 0 };
	std::mutex iMutex;
};

#endif	// MEMORY_H
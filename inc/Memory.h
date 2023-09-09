#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include "Errors.h"

enum class endian_t {
	LITTLE,
	BIG
};

class Memory
{
public:
	Memory(uint64_t size);
	~Memory();
	uint64_t size() const;
	uint8_t* data() const;
	endian_t getEndian() const;
	void setEndian(endian_t endian);
	err_t getByte(uint64_t address, uint8_t& byte);
	err_t getWord(uint64_t address, uint16_t& word);
	err_t getDWord(uint64_t address, uint32_t& dword);
	err_t getQWord(uint64_t address, uint64_t& qword);

private:
	endian_t iEndian{ endian_t::LITTLE };
	uint8_t* iData{ nullptr };
	uint64_t iSize{ 0 };
};

#endif	// MEMORY_H
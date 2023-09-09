#include "Memory.h"

Memory::Memory(uint64_t size)
	: iSize(size)
{
	iData = new uint8_t[iSize];
}

Memory::~Memory()
{
	delete iData;
}

uint64_t Memory::size() const
{
	return iSize;
}

uint8_t* Memory::data() const
{
	return iData;
}

endian_t Memory::getEndian() const
{
	return iEndian;
}

void Memory::setEndian(endian_t endian)
{
	iEndian = endian;
}

err_t Memory::getByte(uint64_t address, uint8_t& byte)
{
	if (address >= iSize)
		return err_t::OUT_OF_MEM;
	byte = iData[address];
	return err_t::OK;
}

err_t Memory::getWord(uint64_t address, uint16_t& word)
{
	if (address >= iSize - 1)
		return err_t::OUT_OF_MEM;
	if (iEndian == endian_t::LITTLE) {
		word =  static_cast<uint16_t>(iData[address]);
		word |= static_cast<uint16_t>(iData[address + 1]) << 8;
	} else {
		word =  static_cast<uint16_t>(iData[address]) << 8;
		word |= static_cast<uint16_t>(iData[address + 1]);
	}
	return err_t::OK;
}

err_t Memory::getDWord(uint64_t address, uint32_t& dword)
{
	if (address >= iSize - 3)
		return err_t::OUT_OF_MEM;
	if (iEndian == endian_t::LITTLE) {
		dword =  static_cast<uint32_t>(iData[address]);
		dword |= static_cast<uint32_t>(iData[address + 1]) << 8;
		dword |= static_cast<uint32_t>(iData[address + 2]) << 16;
		dword |= static_cast<uint32_t>(iData[address + 3]) << 24;
	} else {
		dword =  static_cast<uint32_t>(iData[address]) << 24;
		dword |= static_cast<uint32_t>(iData[address + 1]) << 16;
		dword |= static_cast<uint32_t>(iData[address + 2]) << 8;
		dword |= static_cast<uint32_t>(iData[address + 3]);
	}
	return err_t::OK;
}

err_t Memory::getQWord(uint64_t address, uint64_t& qword)
{
	if (address >= iSize - 7)
		return err_t::OUT_OF_MEM;
	if (iEndian == endian_t::LITTLE) {
		qword =  static_cast<uint64_t>(iData[address]);
		qword |= static_cast<uint64_t>(iData[address + 1]) << 8;
		qword |= static_cast<uint64_t>(iData[address + 2]) << 16;
		qword |= static_cast<uint64_t>(iData[address + 3]) << 24;
		qword |= static_cast<uint64_t>(iData[address + 4]) << 32;
		qword |= static_cast<uint64_t>(iData[address + 5]) << 40;
		qword |= static_cast<uint64_t>(iData[address + 6]) << 48;
		qword |= static_cast<uint64_t>(iData[address + 7]) << 56;
	} else {
		qword =  static_cast<uint64_t>(iData[address]) << 56;
		qword |= static_cast<uint64_t>(iData[address + 1]) << 48;
		qword |= static_cast<uint64_t>(iData[address + 2]) << 40;
		qword |= static_cast<uint64_t>(iData[address + 3]) << 32;
		qword |= static_cast<uint64_t>(iData[address + 4]) << 24;
		qword |= static_cast<uint64_t>(iData[address + 5]) << 16;
		qword |= static_cast<uint64_t>(iData[address + 6]) << 8;
		qword |= static_cast<uint64_t>(iData[address + 7]);
	}
	return err_t::OK;
}
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include "Memory.h"

Memory::~Memory()
{
	delete[] pData;
}

res_t Memory::init(const uint64_t memSize)
{
	if (memSize == 0)
		return res_t::ERROR;
	pData = new uint8_t[memSize];
	if (pData == nullptr)
		return res_t::ERROR;
	iSize = memSize;
	clear();
	return res_t::OK;
}

uint64_t Memory::size()
{
	return iSize;
}

uint8_t* Memory::data()
{
	return pData;
}

void Memory::clear()
{
	memset(pData, 0, iSize);
}

res_t Memory::load(const char* filename, const uint64_t address)
{
	if (filename == nullptr || address >= iSize)
		return res_t::ERROR;
	struct stat stats;
	if (stat(filename, &stats) != 0)
		return res_t::ERROR;
	if (!S_ISREG(stats.st_mode))
		return res_t::ERROR;
	const uint64_t fileSize = stats.st_size;
	if (iSize - address < fileSize)
		return res_t::ERROR;
	FILE* file = fopen(filename, "rb");
	if (file == nullptr)
		return res_t::ERROR;
	if (fread(pData + address, 1, fileSize, file) != fileSize) {
		fclose(file);
		return res_t::ERROR;
	}
	if (fclose(file))
		return res_t::ERROR;
	return res_t::OK;
}

res_t Memory::save(const char* filename, const uint64_t address, const uint64_t size)
{
	if (filename == nullptr || address >= iSize || iSize - address < size)
		return res_t::ERROR;
	FILE* file = fopen(filename, "wb");
	if (file == nullptr)
		return res_t::ERROR;
	if (fwrite(pData + address, 1, size, file) != size) {
		fclose(file);
		return res_t::ERROR;
	}
	if (fflush(file) != 0)
		return res_t::ERROR;
	if (fclose(file))
		return res_t::ERROR;
	return res_t::OK;
}

res_t Memory::readInt8(int8_t& value, const uint64_t address)
{
	if (address >= iSize)
		return res_t::ERROR;
	value = static_cast<int8_t>(pData[address]);
	return res_t::OK;
}

res_t Memory::writeInt8(const int8_t value, const uint64_t address)
{
	if (address >= iSize)
		return res_t::ERROR;
	pData[address] = static_cast<uint8_t>(value);
	return res_t::OK;
}

res_t Memory::readUint8(uint8_t& value, const uint64_t address)
{
	if (address >= iSize)
		return res_t::ERROR;
	value = pData[address];
	return res_t::OK;
}

res_t Memory::writeUint8(const uint8_t value, const uint64_t address)
{
	if (address >= iSize)
		return res_t::ERROR;
	pData[address] = value;
	return res_t::OK;
}

res_t Memory::readInt16(int16_t& value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		value = static_cast<int16_t>(pData[address]);
		value |= static_cast<int16_t>(pData[address + 1]) << 8;
	} else {
		value = static_cast<int16_t>(pData[address]) << 8;
		value |= static_cast<int16_t>(pData[address + 1]);
	}
	return res_t::OK;
}

res_t Memory::writeInt16(const int16_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		pData[address] = static_cast<uint8_t>(value & 0xFF);
		pData[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
	} else {
		pData[address] = static_cast<uint8_t>((value >> 8) & 0xFF);
		pData[address + 1] = static_cast<uint8_t>(value & 0xFF);
	}
	return res_t::OK;
}

res_t Memory::readUint16(uint16_t& value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		value = static_cast<uint16_t>(pData[address]);
		value |= static_cast<uint16_t>(pData[address + 1]) << 8;
	} else {
		value = static_cast<uint16_t>(pData[address]) << 8;
		value |= static_cast<uint16_t>(pData[address + 1]);
	}
	return res_t::OK;
}

res_t Memory::writeUint16(const uint16_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		pData[address] = static_cast<uint8_t>(value & 0xFF);
		pData[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
	} else {
		pData[address] = static_cast<uint8_t>((value >> 8) & 0xFF);
		pData[address + 1] = static_cast<uint8_t>(value & 0xFF);
	}
	return res_t::OK;
}

res_t Memory::readInt32(int32_t& value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 3)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		value = static_cast<int32_t>(pData[address]);
		value |= static_cast<int32_t>(pData[address + 1]) << 8;
		value |= static_cast<int32_t>(pData[address + 2]) << 16;
		value |= static_cast<int32_t>(pData[address + 3]) << 24;
	} else {
		value = static_cast<int32_t>(pData[address]) << 24;
		value |= static_cast<int32_t>(pData[address + 1]) << 16;
		value |= static_cast<int32_t>(pData[address + 2]) << 8;
		value |= static_cast<int32_t>(pData[address + 3]);
	}
	return res_t::OK;
}

res_t Memory::writeInt32(const int32_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		pData[address] = static_cast<uint8_t>(value & 0xFF);
		pData[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
		pData[address + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
		pData[address + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);
	} else {
		pData[address] = static_cast<uint8_t>((value >> 24) & 0xFF);
		pData[address + 1] = static_cast<uint8_t>((value >> 16) & 0xFF);
		pData[address + 2] = static_cast<uint8_t>((value >> 8) & 0xFF);
		pData[address + 3] = static_cast<uint8_t>(value & 0xFF);
	}
	return res_t::OK;
}

res_t Memory::readUint32(uint32_t& value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 3)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		value = static_cast<uint32_t>(pData[address]);
		value |= static_cast<uint32_t>(pData[address + 1]) << 8;
		value |= static_cast<uint32_t>(pData[address + 2]) << 16;
		value |= static_cast<uint32_t>(pData[address + 3]) << 24;
	} else {
		value = static_cast<uint32_t>(pData[address]) << 24;
		value |= static_cast<uint32_t>(pData[address + 1]) << 16;
		value |= static_cast<uint32_t>(pData[address + 2]) << 8;
		value |= static_cast<uint32_t>(pData[address + 3]);
	}
	return res_t::OK;
}

res_t Memory::writeUint32(const uint32_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		pData[address] = static_cast<uint8_t>(value & 0xFF);
		pData[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
		pData[address + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
		pData[address + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);
	} else {
		pData[address] = static_cast<uint8_t>((value >> 24) & 0xFF);
		pData[address + 1] = static_cast<uint8_t>((value >> 16) & 0xFF);
		pData[address + 2] = static_cast<uint8_t>((value >> 8) & 0xFF);
		pData[address + 3] = static_cast<uint8_t>(value & 0xFF);
	}
	return res_t::OK;
}

res_t Memory::readInt64(int64_t& value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 7)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		value = static_cast<int64_t>(pData[address]);
		value |= static_cast<int64_t>(pData[address + 1]) << 8;
		value |= static_cast<int64_t>(pData[address + 2]) << 16;
		value |= static_cast<int64_t>(pData[address + 3]) << 24;
		value |= static_cast<int64_t>(pData[address + 4]) << 32;
		value |= static_cast<int64_t>(pData[address + 5]) << 40;
		value |= static_cast<int64_t>(pData[address + 6]) << 48;
		value |= static_cast<int64_t>(pData[address + 7]) << 56;
	} else {
		value = static_cast<int64_t>(pData[address]) << 56;
		value |= static_cast<int64_t>(pData[address + 1]) << 48;
		value |= static_cast<int64_t>(pData[address + 2]) << 40;
		value |= static_cast<int64_t>(pData[address + 3]) << 32;
		value |= static_cast<int64_t>(pData[address + 4]) << 24;
		value |= static_cast<int64_t>(pData[address + 5]) << 16;
		value |= static_cast<int64_t>(pData[address + 6]) << 8;
		value |= static_cast<int64_t>(pData[address + 7]);
	}
	return res_t::OK;
}

res_t Memory::writeInt64(const int64_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		pData[address] = static_cast<uint8_t>(value & 0xFF);
		pData[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
		pData[address + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
		pData[address + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);
		pData[address + 4] = static_cast<uint8_t>((value >> 32) & 0xFF);
		pData[address + 5] = static_cast<uint8_t>((value >> 40) & 0xFF);
		pData[address + 6] = static_cast<uint8_t>((value >> 48) & 0xFF);
		pData[address + 7] = static_cast<uint8_t>((value >> 56) & 0xFF);
	} else {
		pData[address] = static_cast<uint8_t>((value >> 56) & 0xFF);
		pData[address + 1] = static_cast<uint8_t>((value >> 48) & 0xFF);
		pData[address + 2] = static_cast<uint8_t>((value >> 40) & 0xFF);
		pData[address + 3] = static_cast<uint8_t>((value >> 32) & 0xFF);
		pData[address + 4] = static_cast<uint8_t>((value >> 24) & 0xFF);
		pData[address + 5] = static_cast<uint8_t>((value >> 16) & 0xFF);
		pData[address + 6] = static_cast<uint8_t>((value >> 8) & 0xFF);
		pData[address + 7] = static_cast<uint8_t>(value & 0xFF);
	}
	return res_t::OK;
}

res_t Memory::readUint64(uint64_t& value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 7)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		value = static_cast<uint64_t>(pData[address]);
		value |= static_cast<uint64_t>(pData[address + 1]) << 8;
		value |= static_cast<uint64_t>(pData[address + 2]) << 16;
		value |= static_cast<uint64_t>(pData[address + 3]) << 24;
		value |= static_cast<uint64_t>(pData[address + 4]) << 32;
		value |= static_cast<uint64_t>(pData[address + 5]) << 40;
		value |= static_cast<uint64_t>(pData[address + 6]) << 48;
		value |= static_cast<uint64_t>(pData[address + 7]) << 56;
	} else {
		value = static_cast<uint64_t>(pData[address]) << 56;
		value |= static_cast<uint64_t>(pData[address + 1]) << 48;
		value |= static_cast<uint64_t>(pData[address + 2]) << 40;
		value |= static_cast<uint64_t>(pData[address + 3]) << 32;
		value |= static_cast<uint64_t>(pData[address + 4]) << 24;
		value |= static_cast<uint64_t>(pData[address + 5]) << 16;
		value |= static_cast<uint64_t>(pData[address + 6]) << 8;
		value |= static_cast<uint64_t>(pData[address + 7]);
	}
	return res_t::OK;
}

res_t Memory::writeUint64(const uint64_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE) {
		pData[address] = static_cast<uint8_t>(value & 0xFF);
		pData[address + 1] = static_cast<uint8_t>((value >> 8) & 0xFF);
		pData[address + 2] = static_cast<uint8_t>((value >> 16) & 0xFF);
		pData[address + 3] = static_cast<uint8_t>((value >> 24) & 0xFF);
		pData[address + 4] = static_cast<uint8_t>((value >> 32) & 0xFF);
		pData[address + 5] = static_cast<uint8_t>((value >> 40) & 0xFF);
		pData[address + 6] = static_cast<uint8_t>((value >> 48) & 0xFF);
		pData[address + 7] = static_cast<uint8_t>((value >> 56) & 0xFF);
	} else {
		pData[address] = static_cast<uint8_t>((value >> 56) & 0xFF);
		pData[address + 1] = static_cast<uint8_t>((value >> 48) & 0xFF);
		pData[address + 2] = static_cast<uint8_t>((value >> 40) & 0xFF);
		pData[address + 3] = static_cast<uint8_t>((value >> 32) & 0xFF);
		pData[address + 4] = static_cast<uint8_t>((value >> 24) & 0xFF);
		pData[address + 5] = static_cast<uint8_t>((value >> 16) & 0xFF);
		pData[address + 6] = static_cast<uint8_t>((value >> 8) & 0xFF);
		pData[address + 7] = static_cast<uint8_t>(value & 0xFF);
	}
	return res_t::OK;
}
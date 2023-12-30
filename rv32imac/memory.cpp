#include <string.h>
#include <stdio.h>
#include "general.h"
#include "memory.h"

memory::~memory()
{
	delete[] pData;
}

err_t memory::init(const uint64_t memSize)
{
	if (memSize == 0)
		return err_t::error;
	pData = new uint8_t[memSize];
	if (pData == nullptr)
		return err_t::error;
	iSize = memSize;
	clear();
	return err_t::ok;
}

uint64_t memory::size()
{
	return iSize;
}

uint8_t* memory::data()
{
	return pData;
}

void memory::lock()
{
	iMutex.lock();
}

void memory::unlock()
{
	iMutex.unlock();
}

void memory::clear()
{
	std::lock_guard<std::mutex> lock(iMutex);
	memset(pData, 0, iSize);
}

err_t memory::readInt8(int8_t& value, const uint64_t address)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize)
		return err_t::error;
	value = static_cast<int8_t>(pData[address]);
	return err_t::ok;
}

err_t memory::writeInt8(const int8_t value, const uint64_t address)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize)
		return err_t::error;
	pData[address] = static_cast<uint8_t>(value);
	return err_t::ok;
}

err_t memory::readUint8(uint8_t& value, const uint64_t address)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize)
		return err_t::error;
	value = pData[address];
	return err_t::ok;
}

err_t memory::writeUint8(const uint8_t value, const uint64_t address)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize)
		return err_t::error;
	pData[address] = value;
	return err_t::ok;
}

err_t memory::readInt16(int16_t& value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 1)
		return err_t::error;
	if (endian == endian_t::little)
		value = rdInt16LE(pData + address);
	else
		value = rdInt16BE(pData + address);
	return err_t::ok;
}

err_t memory::writeInt16(const int16_t value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 1)
		return err_t::error;
	if (endian == endian_t::little)
		wrInt16LE(pData + address, value);
	else
		wrInt16BE(pData + address, value);
	return err_t::ok;
}

err_t memory::readUint16(uint16_t& value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 1)
		return err_t::error;
	if (endian == endian_t::little)
		value = rdUint16LE(pData + address);
	else
		value = rdUint16BE(pData + address);
	return err_t::ok;
}

err_t memory::writeUint16(const uint16_t value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 1)
		return err_t::error;
	if (endian == endian_t::little)
		wrUint16LE(pData + address, value);
	else
		wrUint16BE(pData + address, value);
	return err_t::ok;
}

err_t memory::readInt32(int32_t& value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 3)
		return err_t::error;
	if (endian == endian_t::little)
		value = rdInt32LE(pData + address);
	else
		value = rdInt32BE(pData + address);
	return err_t::ok;
}

err_t memory::writeInt32(const int32_t value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 1)
		return err_t::error;
	if (endian == endian_t::little)
		wrInt32LE(pData + address, value);
	else
		wrInt32BE(pData + address, value);
	return err_t::ok;
}

err_t memory::readUint32(uint32_t& value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 3)
		return err_t::error;
	if (endian == endian_t::little)
		value = rdUint32LE(pData + address);
	else
		value = rdUint32BE(pData + address);
	return err_t::ok;
}

err_t memory::writeUint32(const uint32_t value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 1)
		return err_t::error;
	if (endian == endian_t::little)
		wrUint32LE(pData + address, value);
	else
		wrUint32BE(pData + address, value);
	return err_t::ok;
}

err_t memory::readInt64(int64_t& value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 7)
		return err_t::error;
	if (endian == endian_t::little)
		value = rdInt64LE(pData + address);
	else
		value = rdInt64BE(pData + address);
	return err_t::ok;
}

err_t memory::writeInt64(const int64_t value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 1)
		return err_t::error;
	if (endian == endian_t::little)
		wrInt64LE(pData + address, value);
	else
		wrInt64BE(pData + address, value);
	return err_t::ok;
}

err_t memory::readUint64(uint64_t& value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 7)
		return err_t::error;
	if (endian == endian_t::little)
		value = rdUint64LE(pData + address);
	else
		value = rdUint64BE(pData + address);
	return err_t::ok;
}

err_t memory::writeUint64(const uint64_t value, const uint64_t address, const endian_t endian)
{
	std::lock_guard<std::mutex> lock(iMutex);
	if (address >= iSize - 1)
		return err_t::error;
	if (endian == endian_t::little)
		wrUint64LE(pData + address, value);
	else
		wrUint64BE(pData + address, value);
	return err_t::ok;
}
#include <string.h>
#include <stdio.h>
#include "general.h"
#include "memory.h"

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
	if (endian == Endian::LITTLE)
		value = rdInt16LE(pData + address);
	else
		value = rdInt16BE(pData + address);
	return res_t::OK;
}

res_t Memory::writeInt16(const int16_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE)
		wrInt16LE(pData + address, value);
	else
		wrInt16BE(pData + address, value);
	return res_t::OK;
}

res_t Memory::readUint16(uint16_t& value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE)
		value = rdUint16LE(pData + address);
	else
		value = rdUint16BE(pData + address);
	return res_t::OK;
}

res_t Memory::writeUint16(const uint16_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE)
		wrUint16LE(pData + address, value);
	else
		wrUint16BE(pData + address, value);
	return res_t::OK;
}

res_t Memory::readInt32(int32_t& value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 3)
		return res_t::ERROR;
	if (endian == Endian::LITTLE)
		value = rdInt32LE(pData + address);
	else
		value = rdInt32BE(pData + address);
	return res_t::OK;
}

res_t Memory::writeInt32(const int32_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE)
		wrInt32LE(pData + address, value);
	else
		wrInt32BE(pData + address, value);
	return res_t::OK;
}

res_t Memory::readUint32(uint32_t& value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 3)
		return res_t::ERROR;
	if (endian == Endian::LITTLE)
		value = rdUint32LE(pData + address);
	else
		value = rdUint32BE(pData + address);
	return res_t::OK;
}

res_t Memory::writeUint32(const uint32_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE)
		wrUint32LE(pData + address, value);
	else
		wrUint32BE(pData + address, value);
	return res_t::OK;
}

res_t Memory::readInt64(int64_t& value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 7)
		return res_t::ERROR;
	if (endian == Endian::LITTLE)
		value = rdInt64LE(pData + address);
	else
		value = rdInt64BE(pData + address);
	return res_t::OK;
}

res_t Memory::writeInt64(const int64_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE)
		wrInt64LE(pData + address, value);
	else
		wrInt64BE(pData + address, value);
	return res_t::OK;
}

res_t Memory::readUint64(uint64_t& value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 7)
		return res_t::ERROR;
	if (endian == Endian::LITTLE)
		value = rdUint64LE(pData + address);
	else
		value = rdUint64BE(pData + address);
	return res_t::OK;
}

res_t Memory::writeUint64(const uint64_t value, const uint64_t address, const Endian endian)
{
	if (address >= iSize - 1)
		return res_t::ERROR;
	if (endian == Endian::LITTLE)
		wrUint64LE(pData + address, value);
	else
		wrUint64BE(pData + address, value);
	return res_t::OK;
}
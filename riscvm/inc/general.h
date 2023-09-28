#ifndef GENERAL_H
#define GENERAL_H

#include <stdint.h>

enum class res_t {
	OK,
	ERROR,
	MISALIGNED
};

inline int16_t rdInt16LE(const uint8_t* buffer)
{
	int16_t value = (static_cast<int16_t>(buffer[1]) << 8);
	value |= static_cast<int16_t>(buffer[0]);
	return value;
}

inline int16_t rdInt16BE(const uint8_t* buffer)
{
	int16_t value = (static_cast<int16_t>(buffer[0]) << 8);
	value |= static_cast<int16_t>(buffer[1]);
	return value;
}

inline uint16_t rdUint16LE(const uint8_t* buffer)
{
	uint16_t value = (static_cast<uint16_t>(buffer[1]) << 8);
	value |= static_cast<uint16_t>(buffer[0]);
	return value;
}

inline uint16_t rdUint16BE(const uint8_t* buffer)
{
	uint16_t value = (static_cast<uint16_t>(buffer[0]) << 8);
	value |= static_cast<uint16_t>(buffer[1]);
	return value;
}

inline int32_t rdInt32LE(const uint8_t* buffer)
{
	int32_t value = (static_cast<int32_t>(buffer[3]) << 24);
	value |= (static_cast<int32_t>(buffer[2]) << 16);
	value |= (static_cast<int32_t>(buffer[1]) << 8);
	value |= static_cast<int32_t>(buffer[0]);
	return value;
}

inline int32_t rdInt32BE(const uint8_t* buffer)
{
	int32_t value = (static_cast<int32_t>(buffer[0]) << 24);
	value |= (static_cast<int32_t>(buffer[1]) << 16);
	value |= (static_cast<int32_t>(buffer[2]) << 8);
	value |= static_cast<int32_t>(buffer[3]);
	return value;
}

inline uint32_t rdUint32LE(const uint8_t* buffer)
{
	uint32_t value = (static_cast<uint32_t>(buffer[3]) << 24);
	value |= (static_cast<uint32_t>(buffer[2]) << 16);
	value |= (static_cast<uint32_t>(buffer[1]) << 8);
	value |= static_cast<uint32_t>(buffer[0]);
	return value;
}

inline uint32_t rdUint32BE(const uint8_t* buffer)
{
	uint32_t value = (static_cast<uint32_t>(buffer[0]) << 24);
	value |= (static_cast<uint32_t>(buffer[1]) << 16);
	value |= (static_cast<uint32_t>(buffer[2]) << 8);
	value |= static_cast<uint32_t>(buffer[3]);
	return value;
}

inline int64_t rdInt64LE(const uint8_t* buffer)
{
	int64_t value = (static_cast<int64_t>(buffer[7]) << 56);
	value |= (static_cast<int64_t>(buffer[6]) << 48);
	value |= (static_cast<int64_t>(buffer[5]) << 40);
	value |= (static_cast<int64_t>(buffer[4]) << 32);
	value |= (static_cast<int64_t>(buffer[3]) << 24);
	value |= (static_cast<int64_t>(buffer[2]) << 16);
	value |= (static_cast<int64_t>(buffer[1]) << 8);
	value |= static_cast<int64_t>(buffer[0]);
	return value;
}

inline int64_t rdInt64BE(const uint8_t* buffer)
{
	int64_t value = (static_cast<int64_t>(buffer[0]) << 56);
	value |= (static_cast<int64_t>(buffer[1]) << 48);
	value |= (static_cast<int64_t>(buffer[2]) << 40);
	value |= (static_cast<int64_t>(buffer[3]) << 32);
	value |= (static_cast<int64_t>(buffer[4]) << 24);
	value |= (static_cast<int64_t>(buffer[5]) << 16);
	value |= (static_cast<int64_t>(buffer[6]) << 8);
	value |= static_cast<int64_t>(buffer[7]);
	return value;
}

inline uint64_t rdUint64LE(const uint8_t* buffer)
{
	uint64_t value = (static_cast<uint64_t>(buffer[7]) << 56);
	value |= (static_cast<uint64_t>(buffer[6]) << 48);
	value |= (static_cast<uint64_t>(buffer[5]) << 40);
	value |= (static_cast<uint64_t>(buffer[4]) << 32);
	value |= (static_cast<uint64_t>(buffer[3]) << 24);
	value |= (static_cast<uint64_t>(buffer[2]) << 16);
	value |= (static_cast<uint64_t>(buffer[1]) << 8);
	value |= static_cast<uint64_t>(buffer[0]);
	return value;
}

inline uint64_t rdUint64BE(const uint8_t* buffer)
{
	uint64_t value = (static_cast<uint64_t>(buffer[0]) << 56);
	value |= (static_cast<uint64_t>(buffer[1]) << 48);
	value |= (static_cast<uint64_t>(buffer[2]) << 40);
	value |= (static_cast<uint64_t>(buffer[3]) << 32);
	value |= (static_cast<uint64_t>(buffer[4]) << 24);
	value |= (static_cast<uint64_t>(buffer[5]) << 16);
	value |= (static_cast<uint64_t>(buffer[6]) << 8);
	value |= static_cast<uint64_t>(buffer[7]);
	return value;
}

inline void wrInt16LE(uint8_t* buffer, const int16_t value)
{
	buffer[0] = static_cast<uint8_t>(value & 0xFF);
	buffer[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
}

inline void wrInt16BE(uint8_t* buffer, const int16_t value)
{
	buffer[1] = static_cast<uint8_t>(value & 0xFF);
	buffer[0] = static_cast<uint8_t>((value >> 8) & 0xFF);
}

inline void wrUint16LE(uint8_t* buffer, const uint16_t value)
{
	buffer[0] = static_cast<uint8_t>(value & 0xFF);
	buffer[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
}

inline void wrUint16BE(uint8_t* buffer, const uint16_t value)
{
	buffer[1] = static_cast<uint8_t>(value & 0xFF);
	buffer[0] = static_cast<uint8_t>((value >> 8) & 0xFF);
}

inline void wrInt32LE(uint8_t* buffer, const int32_t value)
{
	buffer[0] = static_cast<uint8_t>(value & 0xFF);
	buffer[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
	buffer[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
	buffer[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
}

inline void wrInt32BE(uint8_t* buffer, const int32_t value)
{
	buffer[3] = static_cast<uint8_t>(value & 0xFF);
	buffer[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
	buffer[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
	buffer[0] = static_cast<uint8_t>((value >> 24) & 0xFF);
}

inline void wrUint32LE(uint8_t* buffer, const uint32_t value)
{
	buffer[0] = static_cast<uint8_t>(value & 0xFF);
	buffer[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
	buffer[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
	buffer[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
}

inline void wrUint32BE(uint8_t* buffer, const uint32_t value)
{
	buffer[3] = static_cast<uint8_t>(value & 0xFF);
	buffer[2] = static_cast<uint8_t>((value >> 8) & 0xFF);
	buffer[1] = static_cast<uint8_t>((value >> 16) & 0xFF);
	buffer[0] = static_cast<uint8_t>((value >> 24) & 0xFF);
}

inline void wrInt64LE(uint8_t* buffer, const int64_t value)
{
	buffer[0] = static_cast<uint8_t>(value & 0xFF);
	buffer[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
	buffer[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
	buffer[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
	buffer[4] = static_cast<uint8_t>((value >> 32) & 0xFF);
	buffer[5] = static_cast<uint8_t>((value >> 40) & 0xFF);
	buffer[6] = static_cast<uint8_t>((value >> 48) & 0xFF);
	buffer[7] = static_cast<uint8_t>((value >> 56) & 0xFF);
}

inline void wrInt64BE(uint8_t* buffer, const int64_t value)
{
	buffer[7] = static_cast<uint8_t>(value & 0xFF);
	buffer[6] = static_cast<uint8_t>((value >> 8) & 0xFF);
	buffer[5] = static_cast<uint8_t>((value >> 16) & 0xFF);
	buffer[4] = static_cast<uint8_t>((value >> 24) & 0xFF);
	buffer[3] = static_cast<uint8_t>((value >> 32) & 0xFF);
	buffer[2] = static_cast<uint8_t>((value >> 40) & 0xFF);
	buffer[1] = static_cast<uint8_t>((value >> 48) & 0xFF);
	buffer[0] = static_cast<uint8_t>((value >> 56) & 0xFF);
}

inline void wrUint64LE(uint8_t* buffer, const uint64_t value)
{
	buffer[0] = static_cast<uint8_t>(value & 0xFF);
	buffer[1] = static_cast<uint8_t>((value >> 8) & 0xFF);
	buffer[2] = static_cast<uint8_t>((value >> 16) & 0xFF);
	buffer[3] = static_cast<uint8_t>((value >> 24) & 0xFF);
	buffer[4] = static_cast<uint8_t>((value >> 32) & 0xFF);
	buffer[5] = static_cast<uint8_t>((value >> 40) & 0xFF);
	buffer[6] = static_cast<uint8_t>((value >> 48) & 0xFF);
	buffer[7] = static_cast<uint8_t>((value >> 56) & 0xFF);
}

inline void wrUint64BE(uint8_t* buffer, const uint64_t value)
{
	buffer[7] = static_cast<uint8_t>(value & 0xFF);
	buffer[6] = static_cast<uint8_t>((value >> 8) & 0xFF);
	buffer[5] = static_cast<uint8_t>((value >> 16) & 0xFF);
	buffer[4] = static_cast<uint8_t>((value >> 24) & 0xFF);
	buffer[3] = static_cast<uint8_t>((value >> 32) & 0xFF);
	buffer[2] = static_cast<uint8_t>((value >> 40) & 0xFF);
	buffer[1] = static_cast<uint8_t>((value >> 48) & 0xFF);
	buffer[0] = static_cast<uint8_t>((value >> 56) & 0xFF);
}

res_t getFileSize(const char* filename, uint64_t& fileSize);
res_t loadFile(const char* filename, uint8_t* buffer, uint64_t offset, uint64_t size);
res_t saveFile(const char* filename, uint8_t* buffer, uint64_t size);
res_t loadElf(const char* filename, uint8_t* memory, uint64_t& startAddr);

#endif	// GENERAL_H
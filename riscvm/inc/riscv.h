#ifndef RISCV_H
#define RISCV_H

#include <stdint.h>

enum class res_t {
	OK,
	ERROR,
	MISALIGNED
};

enum class Endian {
	LITTLE,
	BIG
};

enum class ISet : uint32_t {
	RV32I = 1,
	RV32M = 2,
	RV32A = 4,
	RV32F = 8,
	RV32D = 16,
	RV64I = 32,
	RV64M = 64,
	RV64A = 128,
	RV64F = 256,
	RV64D = 512,
	RV32G = RV32I | RV32M | RV32A | RV32F | RV32D,
	RV64G = RV64I | RV64M | RV64A | RV64F | RV64D
};

//-----------------------------------------------------------------------------------------------------
// Documentation: "The RISC-V Instruction Set Manual, Volume I: User-Level ISA, Document Version 2.2"
// Section 2.2: "Base Instruction Formats", page 11, Figure 2.2.
//-----------------------------------------------------------------------------------------------------

inline uint8_t getRd(const uint32_t instr)
{
	return (instr >> 7) & 0b00011111;
}

inline uint8_t getFunct3(const uint32_t instr)
{
	return (instr >> 12) & 0b00000111;
}

inline uint8_t getRs1(const uint32_t instr)
{
	return (instr >> 15) & 0b00011111;
}

inline uint8_t getRs2(const uint32_t instr)
{
	return (instr >> 20) & 0b00011111;
}

inline uint8_t getFunct7(const uint32_t instr)
{
	return (instr >> 25) & 0b01111111;
}

//-----------------------------------------------------------------------------------------------------
// Documentation: "The RISC-V Instruction Set Manual, Volume I: User-Level ISA, Document Version 2.2"
// Section 2.4: "Integer Computational Instructions", page 14
//-----------------------------------------------------------------------------------------------------

inline uint8_t getShamt(const uint32_t instr)
{
	return (instr >> 20) & 0b00011111;
}

//-----------------------------------------------------------------------------------------------------
// Documentation: "The RISC-V Instruction Set Manual, Volume I: User-Level ISA, Document Version 2.2"
// Section 2.3: "Immediate Encoding Variants", page 12.
// Figure 2.3: "RISC-V base instruction formats showing immediate variants."
//-----------------------------------------------------------------------------------------------------

inline int32_t getIimm(const uint32_t instr)
{
	return static_cast<int32_t>(instr) >> 20;
}

inline int32_t getSimm(const uint32_t instr)
{
	constexpr uint32_t maskImm11_5 = 0b11111110000000000000000000000000;
	constexpr uint32_t maskImm4_0  = 0b00000000000000000000111110000000;
	const uint32_t shuffledBits = (instr & maskImm11_5) | ((instr & maskImm4_0) << 13);
	return static_cast<int32_t>(shuffledBits) >> 20;
}

inline int32_t getBimm(const uint32_t instr)
{
	constexpr uint32_t maskImm12   = 0b10000000000000000000000000000000;
	constexpr uint32_t maskImm10_5 = 0b01111110000000000000000000000000;
	constexpr uint32_t maskImm4_1  = 0b00000000000000000000111100000000;
	constexpr uint32_t maskImm11   = 0b00000000000000000000000010000000;
	const uint32_t shuffledBits = (instr & maskImm12) | ((instr & maskImm11) << 23) | ((instr & maskImm10_5) >> 1) | ((instr & maskImm4_1) << 12);
	return static_cast<int32_t>(shuffledBits) >> 19;
}

inline int32_t getUimm(const uint32_t instr)
{
	constexpr uint32_t maskImm = 0b11111111111111111111000000000000;
	return static_cast<int32_t>(instr & maskImm);
}

inline int32_t getJimm(const uint32_t instr)
{
	constexpr uint32_t maskImm20    = 0b10000000000000000000000000000000;
	constexpr uint32_t maskImm10_1  = 0b01111111111000000000000000000000;
	constexpr uint32_t maskImm11    = 0b00000000000100000000000000000000;
	constexpr uint32_t maskImm19_12 = 0b00000000000011111111000000000000;
	const uint32_t shuffledBits = (instr & maskImm20) | ((instr & maskImm19_12) << 11) | ((instr & maskImm11) << 2) | ((instr & maskImm10_1) >> 9);
	return static_cast<int32_t>(shuffledBits) >> 11;
}

#endif	// RISCV_H
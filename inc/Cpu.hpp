#ifndef CPU_HPP
#define CPU_HPP

#include <stdint.h>
#include "Errors.h"

template <typename TRegFile>
class Cpu
{
public:
	void setMemory(uint8_t* memory, uint64_t memSize)
	{
		iMemory = memory;
		iMemSize = memSize;
	}

	res_t fetch()
	{
		// TODO - check if pc is in memory span and alignemt.
		const uint8_t* pc = &iMemory[iRegFile.pc];
		const int32_t instrLen = getInstrLen(pc);
		if (instrLen == -1)
			return res_t::ERROR;
		if (instrLen == 2) {
			// 16-bit instruction, only in C extension. TODO
			return res_t::ERROR;
		}
		const uint8_t opcode = pc[0] & 0b01111111;
		
		return res_t::ERROR;
	}

private:
	uint8_t* iMemory{ nullptr };
	uint64_t iMemSize{ 0 };
	TRegFile iRegFile;

	//-------------------------------------------------------------------------------------------------------
	// Documentation: "The RISC-V Instruction Set Manual, Volume I: User-Level ISA, Document Version 2.2"
	// Section 1.2: "Instruction Length Encoding", Figure 1.1: "RISC-V instruction length encoding.", page 6.
	//-------------------------------------------------------------------------------------------------------
	int32_t getInstrLen(const uint8_t* pc)
	{
		if (pc[0] & 0b00000011 != 0b00000011)
			return 2;
		if (pc[0] & 0b00011111 != 0b00011111)
			return 4;
		if (pc[0] & 0b00111111 == 0b00011111)
			return 6;
		if (pc[0] & 0b01111111 == 0b00111111)
			return 8;
		if (pc[0] & 0b01111111 == 0b01111111 && pc[1] & 01110000 != 01110000)
			return 10 + ((pc[1] & 01110000) >> 3);	// (80 + 16*nnn)-bit, instr[1]'s format: 0nnn0000
		// Either: the instruction has 192 (or more) bytes or is incorrect.
		return -1;
	}
};

#endif	// CPU_HPP
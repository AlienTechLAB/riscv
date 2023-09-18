#ifndef RISCVCPU_H
#define RISCVCPU_H

#include <stdint.h>
#include "Memory.h"

struct RegFile
{
	uint32_t x[32];
	uint32_t pc;
};

class RiscvCpu
{
public:
	RiscvCpu(Memory& memory);
	void setEndian(Endian endian);
	res_t nextInstr();

private:
	Memory& iMemory;
	uint64_t iMemSize{ 0 };
	RegFile iRegFile;
	Endian iEndian{ Endian::LITTLE };

	res_t on16bitInstr(uint8_t opcode, uint16_t instr16);
	res_t on32bitInstr(uint8_t opcode, uint32_t instr32);
	res_t on48bitInstr(uint8_t opcode, uint32_t instr32, uint16_t instr16);
	res_t on64bitInstr(uint8_t opcode, uint64_t instr64);
	res_t onUpTo192bitInstr(uint8_t opcode, uint8_t nnn);
	res_t opcode_01100011(uint32_t instr32);
	res_t opcode_00000011(uint32_t instr32);
	res_t opcode_00010011(uint32_t instr32);
	res_t opcode_00010011_001(const uint32_t instr32);
	res_t opcode_00010011_101(const uint32_t instr32);

	res_t lui(uint32_t instr32);
	res_t auipc(uint32_t instr32);
	res_t jal(uint32_t instr32);
	res_t jalr(uint32_t instr32);
	res_t beq(uint32_t instr32);
	res_t bne(uint32_t instr32);
	res_t blt(uint32_t instr32);
	res_t bge(uint32_t instr32);
	res_t bltu(uint32_t instr32);
	res_t bgeu(uint32_t instr32);
	res_t lb(uint32_t instr32);
	res_t lh(uint32_t instr32);
	res_t lw(uint32_t instr32);
	res_t lbu(uint32_t instr32);
	res_t lhu(uint32_t instr32);
	res_t addi(uint32_t instr32);
	res_t slti(uint32_t instr32);
	res_t sltiu(uint32_t instr32);
	res_t xori(uint32_t instr32);
	res_t ori(uint32_t instr32);
	res_t andi(uint32_t instr32);
	res_t slli(uint32_t instr32);
	res_t srli(uint32_t instr32);
	res_t srai(const uint32_t instr32);

	res_t iTypeInstr(const uint32_t instrData);
};

#endif	// RISCVCPU_H
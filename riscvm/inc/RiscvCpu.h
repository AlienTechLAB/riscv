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

	RegFile iRegFile;

private:
	Memory& iMemory;
	uint64_t iMemSize{ 0 };
	Endian iEndian{ Endian::LITTLE };

	res_t on16bitInstr(uint16_t instr16);
	res_t op_00(const uint16_t instr16);
	res_t op_01(const uint16_t instr16);
	res_t op_10(const uint16_t instr16);

	res_t on32bitInstr(uint8_t opcode, uint32_t instr32);
	res_t opcode_01100011(uint32_t instr32);
	res_t opcode_00000011(uint32_t instr32);
	res_t opcode_00010011(uint32_t instr32);
	res_t opcode_00010011_001(uint32_t instr32);
	res_t opcode_00010011_101(uint32_t instr32);
	res_t opcode_00110011(uint32_t instr32);
	res_t opcode_00110011_000(uint32_t instr32);
	res_t opcode_00110011_101(uint32_t instr32);
	res_t opcode_00100011(uint32_t instr32);
	
	res_t on48bitInstr(uint8_t opcode, uint32_t instr32, uint16_t instr16);
	res_t on64bitInstr(uint8_t opcode, uint64_t instr64);
	res_t onUpTo192bitInstr(uint8_t opcode, uint8_t nnn);

	// RVC instructions.
	res_t C_ADDI4SPN(uint16_t instr16);

	// RV32I instructions.
	res_t LUI(uint32_t instr32);
	res_t AUIPC(uint32_t instr32);
	res_t JAL(uint32_t instr32);
	res_t JALR(uint32_t instr32);
	res_t BEQ(uint32_t instr32);
	res_t BNE(uint32_t instr32);
	res_t BLT(uint32_t instr32);
	res_t BGE(uint32_t instr32);
	res_t BLTU(uint32_t instr32);
	res_t BGEU(uint32_t instr32);
	res_t LB(uint32_t instr32);
	res_t LH(uint32_t instr32);
	res_t LW(uint32_t instr32);
	res_t LBU(uint32_t instr32);
	res_t LHU(uint32_t instr32);
	res_t SB(uint32_t instr32);
	res_t SH(uint32_t instr32);
	res_t SW(uint32_t instr32);
	res_t ADDI(uint32_t instr32);
	res_t SLTI(uint32_t instr32);
	res_t SLTIU(uint32_t instr32);
	res_t XORI(uint32_t instr32);
	res_t ORI(uint32_t instr32);
	res_t ANDI(uint32_t instr32);
	res_t SLLI(uint32_t instr32);
	res_t SRLI(uint32_t instr32);
	res_t SRAI(uint32_t instr32);
	res_t ADD(uint32_t instr32);
	res_t SUB(uint32_t instr32);
	res_t SLL(uint32_t instr32);
	res_t SLT(uint32_t instr32);
	res_t SLTU(uint32_t instr32);
	res_t XOR(uint32_t instr32);
	res_t SRL(uint32_t instr32);
	res_t SRA(uint32_t instr32);
	res_t OR(uint32_t instr32);
	res_t AND(uint32_t instr32);
};

#endif	// RISCVCPU_H
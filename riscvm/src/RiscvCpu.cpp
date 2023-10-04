#include <stdio.h>
#include <string.h>
#include "RiscvCpu.h"
#include "Riscv.h"

RiscvCpu::RiscvCpu(Memory& memory)
	: iMemory(memory)
{
	memset(&iRegFile, 0, sizeof(RegFile));
}

void RiscvCpu::setEndian(Endian endian)
{
	iEndian = endian;
}

//-----------------------------------------------------------------------------------------------------
// Documentation: "The RISC-V Instruction Set Manual, Volume I: User-Level ISA, Document Version 2.2"
// Section 1.2 "Instruction Length Encoding", page 6.
//-----------------------------------------------------------------------------------------------------
res_t RiscvCpu::nextInstr()
{
	uint8_t opcode;
	if (iMemory.readUint8(opcode, iRegFile.pc) == res_t::ERROR)
		return res_t::ERROR;
	opcode &= 0b01111111;
	if ((opcode & 0b00000011) != 0b00000011) {
		uint16_t instr16;
		if (iMemory.readUint16(instr16, iRegFile.pc, iEndian) == res_t::ERROR)
			return res_t::ERROR;
		if (on16bitInstr(instr16) == res_t::ERROR)
			return res_t::ERROR;
		return res_t::OK;
	}
	if ((opcode & 0b00011111) != 0b00011111) {
		uint32_t instr32;
		if (iMemory.readUint32(instr32, iRegFile.pc, iEndian) == res_t::ERROR)
			return res_t::ERROR;
		if (on32bitInstr(opcode, instr32) == res_t::ERROR)
			return res_t::ERROR;
		return res_t::OK;
	}
	if ((opcode & 0b00111111) == 0b00011111) {
		uint32_t instr32;
		if (iMemory.readUint32(instr32, iRegFile.pc, iEndian) == res_t::ERROR)
			return res_t::ERROR;
		uint16_t instr16;
		if (iMemory.readUint16(instr16, iRegFile.pc + 4, iEndian) == res_t::ERROR)
			return res_t::ERROR;
		if (on48bitInstr(opcode, instr32, instr16) == res_t::ERROR)
			return res_t::ERROR;
		return res_t::OK;
	}
	if ((opcode & 0b01111111) == 0b00111111) {
		uint64_t instr64;
		if (iMemory.readUint64(instr64, iRegFile.pc, iEndian) == res_t::ERROR)
			return res_t::ERROR;
		if (on64bitInstr(opcode, instr64) == res_t::ERROR)
			return res_t::ERROR;
		return res_t::OK;
	}
	if ((opcode & 0b01111111) == 0b01111111) {
		uint8_t opcode2;
		if (iMemory.readUint8(opcode2, iRegFile.pc + 1) == res_t::ERROR)
			return res_t::ERROR;
		const uint8_t nnn = (opcode2 >> 4) & 0b00000111;
		if (nnn != 0b111) {
			if (onUpTo192bitInstr(opcode, nnn) == res_t::ERROR)
				return res_t::ERROR;
			return res_t::OK;
		} else {
			// Reserved for >= 192-bits
			return res_t::ERROR;
		}
	}
	return res_t::ERROR;
}

res_t RiscvCpu::on16bitInstr(const uint16_t instr16)
{
	// TODO - check extencion "C"
	if (instr16 == 0)
		return res_t::ILLEGAL_INSTR;
	const uint8_t op = instr16 & 0b11;
	switch (op) {
		case 0b00:
			return op_00(instr16);
		case 0b01:
			return op_01(instr16);
		case 0b10:
			return op_10(instr16);
	};
	return res_t::ILLEGAL_INSTR;
}

// Table 12.4: "Instruction listing for RVC, Quadrant 0."
res_t RiscvCpu::op_00(const uint16_t instr16)
{
	switch (funct3(instr16)) {
		case 0b000:
			return C_ADDI4SPN(instr16);
			break;
	}
	return res_t::ERROR;
}

res_t RiscvCpu::op_01(const uint16_t instr16)
{
	return res_t::ERROR;
}

res_t RiscvCpu::op_10(const uint16_t instr16)
{
	return res_t::ERROR;
}

res_t RiscvCpu::on32bitInstr(const uint8_t opcode, const uint32_t instr32)
{
	switch (opcode) {
		case 0b00110111:
			return LUI(instr32);
		case 0b00010111:
			return AUIPC(instr32);
		case 0b01101111:
			return JAL(instr32);
		case 0b01100111:
			return JALR(instr32);
		case 0b01100011:
			return opcode_01100011(instr32);
		case 0b00000011:
			return opcode_00000011(instr32);
		case 0b00010011:
			return opcode_00010011(instr32);
		case 0b00110011:
			return opcode_00110011(instr32);
		case 0b00100011:
			return opcode_00100011(instr32);
	};
	return res_t::ILLEGAL_INSTR;
}

res_t RiscvCpu::opcode_01100011(const uint32_t instr32)
{
	switch (funct3(instr32)) {
		case 0b000:
			return BEQ(instr32);
		case 0b001:
			return BNE(instr32);
		case 0b100:
			return BLT(instr32);
		case 0b101:
			return BGE(instr32);
		case 0b110:
			return BLTU(instr32);
		case 0b111:
			return BGEU(instr32);
	}
	return res_t::ILLEGAL_INSTR;
}

res_t RiscvCpu::opcode_00000011(const uint32_t instr32)
{
	switch (funct3(instr32)) {
		case 0b000:
			return LB(instr32);
		case 0b001:
			return LH(instr32);
		case 0b010:
			return LW(instr32);
		case 0b100:
			return LBU(instr32);
		case 0b101:
			return LHU(instr32);
	}
	return res_t::ILLEGAL_INSTR;
}

res_t RiscvCpu::opcode_00010011(const uint32_t instr32)
{
	switch (funct3(instr32)) {
		case 0b000:
			return ADDI(instr32);
		case 0b001:
			return opcode_00010011_001(instr32);
		case 0b010:
			return SLTI(instr32);
		case 0b011:
			return SLTIU(instr32);
		case 0b100:
			return XORI(instr32);
		case 0b101:
			return opcode_00010011_101(instr32);
		case 0b110:
			return ORI(instr32);
		case 0b111:
			return ANDI(instr32);
	}
	return res_t::ILLEGAL_INSTR;
}

res_t RiscvCpu::opcode_00010011_001(const uint32_t instr32)
{
	if (getFunct7(instr32) == 0b0000000)
		return SLLI(instr32);
	return res_t::ILLEGAL_INSTR;
}

res_t RiscvCpu::opcode_00010011_101(const uint32_t instr32)
{
	switch (getFunct7(instr32)) {
		case 0b0000000:
			return SRLI(instr32);
		case 0b0100000:
			return SRAI(instr32);
	}
	return res_t::ILLEGAL_INSTR;
}

res_t RiscvCpu::opcode_00110011(const uint32_t instr32)
{
	switch (funct3(instr32)) {
		case 0b000:
			return opcode_00110011_000(instr32);
		case 0b001:
			return SLL(instr32);
		case 0b010:
			return SLT(instr32);
		case 0b011:
			return SLTU(instr32);
		case 0b100:
			return XOR(instr32);
		case 0b101:
			return opcode_00110011_101(instr32);
		case 0b110:
			return OR(instr32);
		case 0b111:
			return AND(instr32);
	}
	return res_t::ILLEGAL_INSTR;
}

res_t RiscvCpu::opcode_00110011_000(const uint32_t instr32)
{
	switch (getFunct7(instr32)) {
		case 0b0000000:
			return ADD(instr32);
		case 0b0100000:
			return SUB(instr32);
	}
	return res_t::ILLEGAL_INSTR;
}

res_t RiscvCpu::opcode_00110011_101(const uint32_t instr32)
{
	switch (getFunct7(instr32)) {
		case 0b0000000:
			return SRL(instr32);
		case 0b0100000:
			return SRA(instr32);
	}
	return res_t::ILLEGAL_INSTR;
}

res_t RiscvCpu::opcode_00100011(uint32_t instr32)
{
	switch (funct3(instr32)) {
		case 0b000:
			return SB(instr32);
		case 0b001:
			return SH(instr32);
		case 0b010:
			return SW(instr32);
	}
	return res_t::ILLEGAL_INSTR;
}

res_t RiscvCpu::on48bitInstr(const uint8_t opcode, const uint32_t instr32, const uint16_t instr16)
{
	return res_t::ERROR;
}

res_t RiscvCpu::on64bitInstr(const uint8_t opcode, const uint64_t instr64)
{
	return res_t::ERROR;
}

res_t RiscvCpu::onUpTo192bitInstr(const uint8_t opcode, const uint8_t nnn)
{
	// iRegFile.pc += (10 + 2 * nnn);
	return res_t::ERROR;
}

res_t RiscvCpu::C_ADDI4SPN(const uint16_t instr16)
{
	// c.addi4spn rd',uimm
	const uint32_t nzuimm = nzuimm549623(instr16);
	if (nzuimm == 0)
		return res_t::ILLEGAL_INSTR;  // "RES" - reserved, see: Section 12.7 "RVC Instruction Set Listings", page 81.
	iRegFile.x[rd(instr16)] = iRegFile.x[2] + nzuimm;
	return res_t::OK;
}

res_t RiscvCpu::LUI(const uint32_t instr32)
{
	// lui rd,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0)
		iRegFile.x[rd] = getUimm(instr32);
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::AUIPC(const uint32_t instr32)
{
	// auipc rd,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0)
		iRegFile.x[rd] = iRegFile.pc + getUimm(instr32);
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::JAL(const uint32_t instr32)
{
	// jal rd,offset
	const int32_t off = getJimm(instr32);
	const uint8_t rd = getRd(instr32);
	if (rd != 0)
		iRegFile.x[rd] = iRegFile.pc + 4;
	iRegFile.pc += off;
	return res_t::OK;
}

res_t RiscvCpu::JALR(const uint32_t instr32)
{
	// jalr rd,rs1,offset
	if (funct3(instr32) != 0b000)
		return res_t::ERROR;
	const int32_t off = getIimm(instr32);
	const uint8_t rd = getRd(instr32);
	const uint8_t rs1 = getRs1(instr32);
	if (rd != 0)
		iRegFile.x[rd] = iRegFile.pc + 4;
	const uint32_t newPc = ((iRegFile.x[rs1] + off) & ~1);
	if ((newPc & 0b11) != 0) {
		// TODO - support of 16-bit instr.
		return res_t::MISALIGNED;
	}
	iRegFile.pc = newPc;
	return res_t::OK;
}

res_t RiscvCpu::BEQ(const uint32_t instr32)
{
	// beq rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = iRegFile.x[rs1] == iRegFile.x[rs2] ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::BNE(const uint32_t instr32)
{
	// bne rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = iRegFile.x[rs1] != iRegFile.x[rs2] ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::BLT(const uint32_t instr32)
{
	// blt rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = static_cast<int32_t>(iRegFile.x[rs1]) < static_cast<int32_t>(iRegFile.x[rs2]) ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::BGE(const uint32_t instr32)
{
	// bge rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = static_cast<int32_t>(iRegFile.x[rs1]) >= static_cast<int32_t>(iRegFile.x[rs2]) ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::BLTU(const uint32_t instr32)
{
	// bltu rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = iRegFile.x[rs1] < iRegFile.x[rs2] ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::BGEU(const uint32_t instr32)
{
	// bgeu rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = iRegFile.x[rs1] >= iRegFile.x[rs2] ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::LB(const uint32_t instr32)
{
	// lb rd,offset(rs1)
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const int32_t off = getIimm(instr32);
		const uint8_t rs1 = getRs1(instr32);
		int8_t sbyte;
		if (iMemory.readInt8(sbyte, iRegFile.x[rs1] + off) == res_t::ERROR)
			return res_t::ERROR;
		const int32_t signExtended = static_cast<int32_t>(sbyte);
		iRegFile.x[rd] = static_cast<uint32_t>(signExtended);
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::LH(const uint32_t instr32)
{
	// lh rd,offset(rs1)
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const int32_t off = getIimm(instr32);
		const uint8_t rs1 = getRs1(instr32);
		int16_t shword;
		if (iMemory.readInt16(shword, iRegFile.x[rs1] + off, iEndian) == res_t::ERROR)
			return res_t::ERROR;
		const int32_t signExtended = static_cast<int32_t>(shword);
		iRegFile.x[rd] = static_cast<uint32_t>(signExtended);
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::LW(const uint32_t instr32)
{
	// LW rd,offset(rs1)
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const int32_t off = getIimm(instr32);
		const uint8_t rs1 = getRs1(instr32);
		int32_t sword;
		if (iMemory.readInt32(sword, iRegFile.x[rs1] + off, iEndian) == res_t::ERROR)
			return res_t::ERROR;
		iRegFile.x[rd] = static_cast<uint32_t>(sword);
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::LBU(const uint32_t instr32)
{
	// lbu rd,offset(rs1)
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const int32_t off = getIimm(instr32);
		const uint8_t rs1 = getRs1(instr32);
		uint8_t byte;
		if (iMemory.readUint8(byte, iRegFile.x[rs1] + off) == res_t::ERROR)
			return res_t::ERROR;
		iRegFile.x[rd] = static_cast<uint32_t>(byte);
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::LHU(const uint32_t instr32)
{
	// lhu rd,offset(rs1)
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const int32_t off = getIimm(instr32);
		const uint8_t rs1 = getRs1(instr32);
		uint16_t hword;
		if (iMemory.readUint16(hword, iRegFile.x[rs1] + off, iEndian) == res_t::ERROR)
			return res_t::ERROR;
		iRegFile.x[rd] = static_cast<uint32_t>(hword);
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SB(const uint32_t instr32)
{
	// sb rs2,offset(rs1)
	const int32_t off = getSimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	uint8_t byte = static_cast<uint8_t>(iRegFile.x[rs2] & 0xFF);
	if (iMemory.writeUint8(byte, iRegFile.x[rs1] + off) == res_t::ERROR)
		return res_t::ERROR;
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SH(const uint32_t instr32)
{
	// sh rs2,offset(rs1)
	const int32_t off = getSimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	uint16_t hword = static_cast<uint16_t>(iRegFile.x[rs2] & 0xFFFF);
	if (iMemory.writeUint16(hword, iRegFile.x[rs1] + off, iEndian) == res_t::ERROR)
		return res_t::ERROR;
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SW(const uint32_t instr32)
{
	// sw rs2,offset(rs1)
	const int32_t off = getSimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	if (iMemory.writeUint32(iRegFile.x[rs2], iRegFile.x[rs1] + off, iEndian) == res_t::ERROR)
		return res_t::ERROR;
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::ADDI(uint32_t instr32)
{
	// addi rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const int32_t imm = getIimm(instr32);
		const uint8_t rs1 = getRs1(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] + static_cast<uint32_t>(imm);
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SLTI(uint32_t instr32)
{
	// slti rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const int32_t imm = getIimm(instr32);
		const uint8_t rs1 = getRs1(instr32);
		iRegFile.x[rd] = static_cast<int32_t>(iRegFile.x[rs1]) < imm ? 1 : 0;
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SLTIU(uint32_t instr32)
{
	// sltiu rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const int32_t imm = getIimm(instr32);
		const uint8_t rs1 = getRs1(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] < static_cast<uint32_t>(imm) ? 1 : 0;
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::XORI(uint32_t instr32)
{
	// xori rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const int32_t imm = getIimm(instr32);
		const uint8_t rs1 = getRs1(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] ^ imm;
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::ORI(uint32_t instr32)
{
	// ori rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const int32_t imm = getIimm(instr32);
		const uint8_t rs1 = getRs1(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] | imm;
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::ANDI(uint32_t instr32)
{
	// andi rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const int32_t imm = getIimm(instr32);
		const uint8_t rs1 = getRs1(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] & imm;
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SLLI(const uint32_t instr32)
{
	// slli rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(instr32);
		const uint8_t shamt = getShamt(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] << shamt;
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SRLI(const uint32_t instr32)
{
	// srli rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint32_t shamt = getShamt(instr32);
		const uint8_t rs1 = getRs1(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] >> shamt;
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SRAI(const uint32_t instr32)
{
	// srai rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint32_t shamt = getShamt(instr32);
		const uint8_t rs1 = getRs1(instr32);
		iRegFile.x[rd] = static_cast<uint32_t>(static_cast<int32_t>(iRegFile.x[rs1]) >> shamt);
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::ADD(const uint32_t instr32)
{
	// add rd,rs1,rs2
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(instr32);
		const uint8_t rs2 = getRs2(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] + iRegFile.x[rs2];
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SUB(const uint32_t instr32)
{
	// sub rd,rs1,rs2
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(instr32);
		const uint8_t rs2 = getRs2(instr32);
		iRegFile.x[rd] = iRegFile.x[rs2] - iRegFile.x[rs1];
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SLL(const uint32_t instr32)
{
	// sll rd,rs1,rs2
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(instr32);
		const uint8_t rs2 = getRs2(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] << (iRegFile.x[rs2] & 0b11111);
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SLT(const uint32_t instr32)
{
	// slt rd,rs1,rs2
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(instr32);
		const uint8_t rs2 = getRs2(instr32);
		iRegFile.x[rd] = static_cast<int32_t>(iRegFile.x[rs1]) < static_cast<int32_t>(iRegFile.x[rs2]) ? 1 : 0;
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SLTU(const uint32_t instr32)
{
	// sltu rd,rs1,rs2
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(instr32);
		const uint8_t rs2 = getRs2(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] < iRegFile.x[rs2] ? 1 : 0;
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::XOR(const uint32_t instr32)
{
	// xor rd,rs1,rs2
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(instr32);
		const uint8_t rs2 = getRs2(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] ^ iRegFile.x[rs2];
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SRL(const uint32_t instr32)
{
	// srl rd,rs1,rs2
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(instr32);
		const uint8_t rs2 = getRs2(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] >> (iRegFile.x[rs2] & 0b11111);
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::SRA(const uint32_t instr32)
{
	// sra rd,rs1,rs2
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(instr32);
		const uint8_t rs2 = getRs2(instr32);
		iRegFile.x[rd] = static_cast<uint32_t>(static_cast<int32_t>(iRegFile.x[rs1]) >> (iRegFile.x[rs2] & 0b11111));
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::OR(const uint32_t instr32)
{
	// or rd,rs1,rs2
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(instr32);
		const uint8_t rs2 = getRs2(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] | iRegFile.x[rs2];
	}
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::AND(const uint32_t instr32)
{
	// and rd,rs1,rs2
	const uint8_t rd = getRd(instr32);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(instr32);
		const uint8_t rs2 = getRs2(instr32);
		iRegFile.x[rd] = iRegFile.x[rs1] & iRegFile.x[rs2];
	}
	iRegFile.pc += 4;
	return res_t::OK;
}
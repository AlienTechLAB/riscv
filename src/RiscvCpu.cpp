#include <stdio.h>
#include <string.h>
#include "RiscvCpu.h"
#include "InstrFormats.h"
#include "riscv.h"

RiscvCpu::RiscvCpu(Memory& memory) : iMemory(memory)
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
	if ((opcode & 0x00000011) != 0x00000011) {
		uint16_t instr16;
		if (iMemory.readUint16(instr16, iRegFile.pc) == res_t::ERROR)
			return res_t::ERROR;
		if (on16bitInstr(opcode, instr16) == res_t::ERROR)
			return res_t::ERROR;
		return res_t::OK;
	}
	if ((opcode & 0x00011111) != 0x00011111) {
		uint32_t instr32;
		if (iMemory.readUint32(instr32, iRegFile.pc) == res_t::ERROR)
			return res_t::ERROR;
		if (on32bitInstr(opcode, instr32) == res_t::ERROR)
			return res_t::ERROR;
		return res_t::OK;
	}
	if ((opcode & 0x00111111) == 0x00011111) {
		uint32_t instr32;
		if (iMemory.readUint32(instr32, iRegFile.pc) == res_t::ERROR)
			return res_t::ERROR;
		uint16_t instr16;
		if (iMemory.readUint16(instr16, iRegFile.pc + 4) == res_t::ERROR)
			return res_t::ERROR;
		if (on48bitInstr(opcode, instr32, instr16) == res_t::ERROR)
			return res_t::ERROR;
		return res_t::OK;
	}
	if ((opcode & 0x01111111) == 0x00111111) {
		uint64_t instr64;
		if (iMemory.readUint64(instr64, iRegFile.pc) == res_t::ERROR)
			return res_t::ERROR;
		if (on64bitInstr(opcode, instr64) == res_t::ERROR)
			return res_t::ERROR;
		return res_t::OK;
	}
	if ((opcode & 0x01111111) == 0x01111111) {
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

res_t RiscvCpu::on16bitInstr(const uint8_t opcode, const uint16_t instr16)
{
	// TODO - extencion "C"
	return res_t::ERROR;
}

res_t RiscvCpu::on32bitInstr(const uint8_t opcode, const uint32_t instr32)
{
	res_t res = res_t::OK;
	switch (opcode) {
		case 0b00110111:
			return lui(instr32);
		case 0b00010111:
			return auipc(instr32);
		case 0b01101111:
			return jal(instr32);
		case 0b01100111:
			return jalr(instr32);
		case 0b01100011:
			return opcode_01100011(instr32);
		case 0b00000011:
			return opcode_00000011(instr32);
		case 0b00010011:
			return opcode_00010011(instr32);

	};
	return res_t::ERROR;
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

res_t RiscvCpu::opcode_01100011(const uint32_t instr32)
{
	switch (getFunct3(instr32)) {
		case 0b000:
			return beq(instr32);
		case 0b001:
			return bne(instr32);
		case 0b100:
			return blt(instr32);
		case 0b101:
			return bge(instr32);
		case 0b110:
			return bltu(instr32);
		case 0b111:
			return bgeu(instr32);
	}
	return res_t::ERROR;
}

res_t RiscvCpu::opcode_00000011(const uint32_t instr32)
{
	switch (getFunct3(instr32)) {
		case 0b000:
			return lb(instr32);
		case 0b001:
			return lh(instr32);
		case 0b010:
			return lw(instr32);
		case 0b100:
			return lbu(instr32);
		case 0b101:
			return lhu(instr32);
	}
	return res_t::ERROR;
}

res_t RiscvCpu::opcode_00010011(const uint32_t instr32)
{
	switch (getFunct3(instr32)) {
		case 0b000:
			return addi(instr32);
		case 0b001:
			return opcode_00010011_001(instr32);
		case 0b010:
			return slti(instr32);
		case 0b011:
			return sltiu(instr32);
		case 0b100:
			return xori(instr32);
		case 0b101:
			return opcode_00010011_101(instr32);
		case 0b110:
			return ori(instr32);
		case 0b111:
			return andi(instr32);
	}
	return res_t::ERROR;
}

res_t RiscvCpu::opcode_00010011_001(const uint32_t instr32)
{
	if (getFunct7(instr32) == 0b0000000)
		return slli(instr32);
	return res_t::ERROR;
}

res_t RiscvCpu::opcode_00010011_101(const uint32_t instr32)
{
	switch (getFunct7(instr32)) {
		case 0b0000000:
			return srli(instr32);
		case 0b0100000:
			return srai(instr32);
	}
	return res_t::ERROR;
}

res_t RiscvCpu::lui(const uint32_t instr32)
{
	// lui rd,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0)
		iRegFile.x[rd] = getUimm(instr32);
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::auipc(const uint32_t instr32)
{
	// auipc rd,imm
	const uint8_t rd = getRd(instr32);
	if (rd != 0)
		iRegFile.x[rd] = iRegFile.pc + getUimm(instr32);
	iRegFile.pc += 4;
	return res_t::OK;
}

res_t RiscvCpu::jal(const uint32_t instr32)
{
	// jal rd,offset
	const int32_t off = getJimm(instr32);
	const uint8_t rd = getRd(instr32);
	if (rd != 0)
		iRegFile.x[rd] = iRegFile.pc + 4;
	iRegFile.pc += off;
	return res_t::OK;
}

res_t RiscvCpu::jalr(const uint32_t instr32)
{
	// jalr rd,rs1,offset
	if (getFunct3(instr32) != 0b000)
		return res_t::ERROR;
	const int32_t off = getIimm(instr32);
	const uint8_t rd = getRd(instr32);
	const uint8_t rs1 = getRs1(instr32);
	if (rd != 0)
		iRegFile.x[rd] = iRegFile.pc + 4;
	const uint32_t newPc = ((iRegFile.x[rs1] + off) & ~1);
	if (newPc & 0b11 != 0) {
		// TODO - support of 16-bit instr.
		return res_t::MISALIGNED;
	}
	iRegFile.pc = newPc;
	return res_t::OK;
}

res_t RiscvCpu::beq(const uint32_t instr32)
{
	// beq rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = iRegFile.x[rs1] == iRegFile.x[rs2] ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::bne(const uint32_t instr32)
{
	// bne rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = iRegFile.x[rs1] != iRegFile.x[rs2] ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::blt(const uint32_t instr32)
{
	// blt rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = static_cast<int32_t>(iRegFile.x[rs1]) < static_cast<int32_t>(iRegFile.x[rs2]) ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::bge(const uint32_t instr32)
{
	// bge rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = static_cast<int32_t>(iRegFile.x[rs1]) >= static_cast<int32_t>(iRegFile.x[rs2]) ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::bltu(const uint32_t instr32)
{
	// bltu rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = iRegFile.x[rs1] < iRegFile.x[rs2] ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::bgeu(const uint32_t instr32)
{
	// bgeu rs1,rs2,offset
	const int32_t off = getBimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t rs2 = getRs2(instr32);
	iRegFile.pc = iRegFile.x[rs1] >= iRegFile.x[rs2] ? iRegFile.pc + off : iRegFile.pc + 4;
	return res_t::OK;
}

res_t RiscvCpu::lb(const uint32_t instr32)
{
	// lb rd,offset(rs1)
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const int32_t off = getIimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	int8_t sbyte;
	if (iMemory.readInt8(sbyte, iRegFile.x[rs1] + off) == res_t::ERROR)
		return res_t::ERROR;
	const int32_t signExtended = static_cast<int32_t>(sbyte);
	iRegFile.x[rd] = static_cast<uint32_t>(signExtended);
	return res_t::OK;
}

res_t RiscvCpu::lh(const uint32_t instr32)
{
	// lh rd,offset(rs1)
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const int32_t off = getIimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	int16_t shword;
	if (iMemory.readInt16(shword, iRegFile.x[rs1] + off) == res_t::ERROR)
		return res_t::ERROR;
	const int32_t signExtended = static_cast<int32_t>(shword);
	iRegFile.x[rd] = static_cast<uint32_t>(signExtended);
	return res_t::OK;
}

res_t RiscvCpu::lw(const uint32_t instr32)
{
	// lw rd,offset(rs1)
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const int32_t off = getIimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	int32_t sword;
	if (iMemory.readInt32(sword, iRegFile.x[rs1] + off) == res_t::ERROR)
		return res_t::ERROR;
	iRegFile.x[rd] = static_cast<uint32_t>(sword);
	return res_t::OK;
}

res_t RiscvCpu::lbu(const uint32_t instr32)
{
	// lbu rd,offset(rs1)
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const int32_t off = getIimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	uint8_t byte;
	if (iMemory.readUint8(byte, iRegFile.x[rs1] + off) == res_t::ERROR)
		return res_t::ERROR;
	iRegFile.x[rd] = static_cast<uint32_t>(byte);
	return res_t::OK;
}

res_t RiscvCpu::lhu(const uint32_t instr32)
{
	// lhu rd,offset(rs1)
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const int32_t off = getIimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	uint16_t hword;
	if (iMemory.readUint16(hword, iRegFile.x[rs1] + off) == res_t::ERROR)
		return res_t::ERROR;
	iRegFile.x[rd] = static_cast<uint32_t>(hword);
	return res_t::OK;
}

res_t RiscvCpu::addi(uint32_t instr32)
{
	// addi rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const int32_t imm = getIimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	iRegFile.x[rd] = iRegFile.x[rs1] + static_cast<uint32_t>(imm);
	return res_t::OK;
}

res_t RiscvCpu::slti(uint32_t instr32)
{
	// slti rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const int32_t imm = getIimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	iRegFile.x[rd] = static_cast<int32_t>(iRegFile.x[rs1]) < imm ? 1 : 0;
	return res_t::OK;
}

res_t RiscvCpu::sltiu(uint32_t instr32)
{
	// sltiu rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const int32_t imm = getIimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	iRegFile.x[rd] = iRegFile.x[rs1] < static_cast<uint32_t>(imm) ? 1 : 0;
	return res_t::OK;
}

res_t RiscvCpu::xori(uint32_t instr32)
{
	// xori rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const int32_t imm = getIimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	iRegFile.x[rd] = iRegFile.x[rs1] ^ imm;
	return res_t::OK;
}

res_t RiscvCpu::ori(uint32_t instr32)
{
	// ori rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const int32_t imm = getIimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	iRegFile.x[rd] = iRegFile.x[rs1] | imm;
	return res_t::OK;
}

res_t RiscvCpu::andi(uint32_t instr32)
{
	// andi rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const int32_t imm = getIimm(instr32);
	const uint8_t rs1 = getRs1(instr32);
	iRegFile.x[rd] = iRegFile.x[rs1] & imm;
	return res_t::OK;
}

res_t RiscvCpu::slli(const uint32_t instr32)
{
	// slli rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const uint8_t rs1 = getRs1(instr32);
	const uint8_t shamt = getShamt(instr32);
	iRegFile.x[rd] = iRegFile.x[rs1] << shamt;
	return res_t::OK;
}

res_t RiscvCpu::srli(const uint32_t instr32)
{
	// srli rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const uint32_t shamt = getShamt(instr32);
	const uint8_t rs1 = getRs1(instr32);
	iRegFile.x[rd] = iRegFile.x[rs1] >> shamt;
	return res_t::OK;
}

res_t RiscvCpu::srai(const uint32_t instr32)
{
	// srai rd,rs1,imm
	const uint8_t rd = getRd(instr32);
	if (rd == 0)
		return res_t::OK;
	const uint32_t shamt = getShamt(instr32);
	const uint8_t rs1 = getRs1(instr32);
	iRegFile.x[rd] = static_cast<uint32_t>(static_cast<int32_t>(iRegFile.x[rs1]) >> shamt);
	return res_t::OK;
}
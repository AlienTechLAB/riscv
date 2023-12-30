#include <cstring>
#include "rv32imac.h"
#include "decoder.h"

namespace riscv {

rv32imac::rv32imac(memory& memory)
	: iMemory(memory)
{
	reset();
}

void rv32imac::reset()
{
	std::memset(x, 0, sizeof(x));
	pc = 0;
}

err_t rv32imac::next()
{
	uint32_t mcode;
	if (iMemory.readUint32(mcode, pc, iEndian) == err_t::error)
		return err_t::memory;
	return execute(mcode);
}

err_t rv32imac::execute(const uint32_t mcode)
{

	switch (mcode & 0b11) {
		case 0b00:
			return quadrant0(mcode);
		case 0b01:
			return quadrant1(mcode);
		case 0b10:
			return quadrant2(mcode);
		case 0b11:
			return instr32(mcode);
	}
	return err_t::error;
}

err_t rv32imac::quadrant0(const uint16_t mcode)
{
	if (mcode == 0)
		return err_t::illegal;
	const uint32_t funct3 = cfunct3(mcode);
	switch (funct3) {
		case 0b000:
			return execute_caddi4spn(mcode);
		case 0b001:
			return err_t::illegal;
		case 0b010:
			return execute_clw(mcode);
		case 0b011:
			return err_t::illegal;
		case 0b100:
			return err_t::reserved;
		case 0b101:
			return err_t::illegal;
		case 0b110:
			return execute_csw(mcode);
		case 0b111:
			return err_t::illegal;
	}
	return err_t::error;
}

err_t rv32imac::quadrant1(const uint16_t mcode)
{
	const uint32_t funct3 = cfunct3(mcode);
	switch (funct3) {
		case 0b000:
			return quadrant1_000(mcode);
		case 0b001:
			return execute_cjal(mcode);
		case 0b010:
			return execute_cli(mcode);
		case 0b011:
			return quadrant1_011(mcode);
		case 0b100:
			return quadrant1_100(mcode);
		case 0b101:
			return execute_cj(mcode);
		case 0b110:
			return execute_cbeqz(mcode);
		case 0b111:
			return execute_cbnez(mcode);
	}
	return err_t::error;
}

err_t rv32imac::quadrant2(const uint16_t mcode)
{
	const uint32_t funct3 = cfunct3(mcode);
	switch (funct3) {
		case 0b000:
			return quadrant2_000(mcode);
		case 0b001:
			return err_t::illegal;
		case 0b010:
			return execute_clwsp(mcode);
		case 0b011:
			return err_t::error;
		case 0b100:
			return quadrant2_100(mcode);
		case 0b101:
			return err_t::error;
		case 0b110:
			return execute_cswsp(mcode);
		case 0b111:
			return err_t::error;
	}
	return err_t::error;
}

err_t rv32imac::instr32(const uint32_t mcode)
{
	const uint8_t opcode = mcode & 0b1111111;
	switch (opcode) {
		case 0b0110111:
			return execute_lui(mcode);
		case 0b0010111:
			return execute_auipc(mcode);
		case 0b1101111:
			return execute_jal(mcode);
		case 0b1100111:
			return execute_jalr(mcode);
		case 0b1100011:
			return execute_11_opcode_1100011(mcode);
		case 0b0000011:
			return execute_11_opcode_0000011(mcode);
		case 0b0010011:
			return execute_11_opcode_0010011(mcode);
		case 0b0110011:
			return execute_11_opcode_0110011(mcode);
		case 0b0100011:
			return execute_11_opcode_0100011(mcode);
	};
	return err_t::error;
}

err_t rv32imac::quadrant1_000(const uint16_t mcode)
{
	if (mcode == 1)
		return execute_cnop();
	return execute_caddi(mcode);
}

err_t rv32imac::quadrant1_011(const uint16_t mcode)
{
	const uint32_t rd = getC01Rd(mcode);
	if (rd == 2)
		return execute_caddi16sp(mcode);
	return executr_clui(mcode);
}

err_t rv32imac::quadrant1_100(const uint16_t mcode)
{
	const uint8_t b1110 = (mcode >> 10) & 0b11;
	if (b1110 == 0b00) {
		const uint8_t b12 = (mcode >> 12) & 1;
		if (b12 == 1)
			return err_t::nse;
		return execute_csrli(mcode);
	} else if (b1110 == 0b01) {
		const uint8_t b12 = (mcode >> 12) & 1;
		if (b12 == 1)
			return err_t::nse;
		return execute_csrai(mcode);
	} else if (b1110 == 0b10) {
		return execute_candi(mcode);
	} else {
		const uint8_t b12 = (mcode >> 12) & 1;
		const uint8_t b65 = (mcode >> 5) & 0b11;
		if (b12 == 0) {
			switch (b65) {
				case 0b00:
					return execute_csub(mcode);
				case 0b01:
					return execute_cxor(mcode);
				case 0b10:
					return execute_cor(mcode);
				case 0b11:
					return execute_cand(mcode);
			}
		} else {
			switch (b65) {
				case 0b00:
					return err_t::reserved;
				case 0b01:
					return err_t::reserved;
				case 0b10:
					return err_t::reserved;
				case 0b11:
					return err_t::reserved;
			}
		}
	}
	return err_t::error;
}

err_t rv32imac::quadrant2_000(const uint16_t mcode)
{
	const uint32_t b12 = (mcode >> 11) & 1;
	if (b12)
		return err_t::nse;
	return execute_slli(mcode);
}

err_t rv32imac::quadrant2_100(const uint16_t mcode)
{
	const uint32_t b12 = (mcode >> 11) & 1;
	const uint32_t rs2 = getC10Rs2(mcode);
	if (b12 == 0) {
		if (rs2 == 0) {
			const uint32_t rs1 = getC10Rs1(mcode);
			if (rs1 == 0)
				return err_t::reserved;
			return execute_cjr(mcode);
		} else {
			const uint32_t rd = getC10Rd(mcode);
			if (rd == 0) {
				// HINT
				pc += 2;
				return err_t::ok;
			}
			return execute_cmv(mcode);
		}
	} else {
		if (mcode == 0b1001000000000010)
			return execute_cebreak(mcode);
		const uint32_t rs2 = getC10Rs2(mcode);
		if (rs2 == 0)
			return execute_cjalr(mcode);
		return execute_cadd(mcode);
	}
	return err_t::error;
}

err_t rv32imac::execute_11_opcode_1100011(const uint32_t mcode)
{
	const uint32_t funct3 = getFunct3(mcode);
	switch (funct3) {
		case 0b000:
			return execute_beq(mcode);
		case 0b001:
			return execute_bne(mcode);
		case 0b100:
			return execute_blt(mcode);
		case 0b101:
			return execute_bge(mcode);
		case 0b110:
			return execute_bltu(mcode);
		case 0b111:
			return execute_bgeu(mcode);
	}
	return err_t::illegal;
}

err_t rv32imac::execute_11_opcode_0000011(const uint32_t mcode)
{
	const uint32_t funct3 = getFunct3(mcode);
	switch (funct3) {
		case 0b000:
			return execute_lb(mcode);
		case 0b001:
			return execute_lh(mcode);
		case 0b010:
			return execute_lw(mcode);
		case 0b100:
			return execute_lbu(mcode);
		case 0b101:
			return execute_lhu(mcode);
	}
	return err_t::illegal;
}

err_t rv32imac::execute_11_opcode_0010011(const uint32_t mcode)
{
	const uint32_t funct3 = getFunct3(mcode);
	switch (funct3) {
		case 0b000:
			return execute_addi(mcode);
		case 0b001:
			return execute_11_opcode_0010011_funct3_001(mcode);
		case 0b010:
			return execute_slti(mcode);
		case 0b011:
			return execute_sltiu(mcode);
		case 0b100:
			return execute_xori(mcode);
		case 0b101:
			return execute_11_opcode_0010011_funct3_101(mcode);
		case 0b110:
			return execute_ori(mcode);
		case 0b111:
			return execute_andi(mcode);
	}
	return err_t::illegal;
}

err_t rv32imac::execute_11_opcode_0110011(const uint32_t mcode)
{
	const uint32_t funct3 = getFunct3(mcode);
	switch (funct3) {
		case 0b000:
			return execute_11_opcode_0110011_funct3_000(mcode);
		case 0b001:
			return execute_sll(mcode);
		case 0b010:
			return execute_slt(mcode);
		case 0b011:
			return execute_sltu(mcode);
		case 0b100:
			return execute_xor(mcode);
		case 0b101:
			return execute_11_opcode_0110011_funct3_101(mcode);
		case 0b110:
			return execute_or(mcode);
		case 0b111:
			return execute_and(mcode);
	}
	return err_t::illegal;
}

err_t rv32imac::execute_11_opcode_0100011(uint32_t mcode)
{
	const uint32_t funct3 = getFunct3(mcode);
	switch (funct3) {
		case 0b000:
			return execute_sb(mcode);
		case 0b001:
			return execute_sh(mcode);
		case 0b010:
			return execute_sw(mcode);
	}
	return err_t::illegal;
}

err_t rv32imac::execute_11_opcode_0010011_funct3_001(const uint32_t mcode)
{
	const uint8_t funct7 = getFunct7(mcode);
	if (funct7 == 0b0000000)
		return execute_slli(mcode);
	return err_t::illegal;
}

err_t rv32imac::execute_11_opcode_0010011_funct3_101(const uint32_t mcode)
{
	const uint8_t funct7 = getFunct7(mcode);
	switch (funct7) {
		case 0b0000000:
			return execute_srli(mcode);
		case 0b0100000:
			return execute_srai(mcode);
	}
	return err_t::illegal;
}

err_t rv32imac::execute_11_opcode_0110011_funct3_000(const uint32_t mcode)
{
	switch (getFunct7(mcode)) {
		case 0b0000000:
			return execute_add(mcode);
		case 0b0100000:
			return execute_sub(mcode);
	}
	return err_t::illegal;
}

err_t rv32imac::execute_11_opcode_0110011_funct3_101(const uint32_t mcode)
{
	switch (getFunct7(mcode)) {
		case 0b0000000:
			return execute_srl(mcode);
		case 0b0100000:
			return execute_sra(mcode);
	}
	return err_t::illegal;
}

// Extension "C" ------------------------------------------------
err_t rv32imac::execute_cadd(uint16_t mcode)
{
	const uint32_t rd = getC10Rd(mcode);
	if (rd == 0) {
		// HINT
		pc += 2;
		return err_t::ok;
	}
	const uint32_t rs2 = getC10Rs2(mcode);
	x[rd] += x[rs2];
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_caddi(const uint16_t mcode)
{
	const uint32_t rd = getC01Rd(mcode);
	if (rd == 0) {
		// HINT
		pc += 2;
		return err_t::ok;
	}
	const int32_t nzimm = getCI1imm(mcode);
	x[rd] = x[rd] + nzimm;
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_caddi16sp(const uint16_t mcode)
{
	const int32_t nzimm = getCI2imm(mcode);
	x[2] += nzimm;
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_caddi4spn(const uint16_t mcode)
{
	const uint32_t offset = getCIWimm(mcode);
	if (offset == 0)
		return err_t::reserved;
	const uint32_t rd = getC00Rdp(mcode);
	x[rd] = x[2] + offset;
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_cand(const uint16_t mcode)
{
	const uint32_t rs2p = getC00Rs2p(mcode);
	const uint32_t rdp = getC01Rd(mcode);
	x[rdp] = x[rdp] & x[rs2p];
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_candi(const uint16_t mcode)
{
	const uint32_t rs1p = getC01Rs1p(mcode);
	const uint32_t rdp = getC01Rd(mcode);
	const int32_t imm = getCI1imm(mcode);
	x[rdp] = x[rdp] & imm;
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_cbeqz(uint16_t mcode)
{
	const uint32_t rs1p = getC01Rs1p(mcode);
	const int32_t imm = getCBimm(mcode);
	if (x[rs1p] == 0)
		pc += imm;
	else
		pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_cbnez(const uint16_t mcode)
{
	const uint32_t rs1p = getC01Rs1p(mcode);
	const int32_t imm = getCBimm(mcode);
	if (x[rs1p] != 0)
		pc += imm;
	else
		pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_cebreak(const uint16_t mcode)
{
	return err_t::error;
}

err_t rv32imac::execute_cjal(const uint16_t mcode)
{
	const int32_t imm = getCJimm(mcode);
	x[1] = pc + 2;
	pc += imm;
	return err_t::ok;
}

err_t rv32imac::execute_cjalr(const uint16_t mcode)
{
	const uint32_t rs1 = getC10Rs1(mcode);
	const uint64_t tempPc = pc;
	pc = x[rs1];
	x[1] = tempPc + 2;
	return err_t::ok;
}

err_t rv32imac::execute_cj(const uint16_t mcode)
{
	const int32_t imm = getCJimm(mcode);
	pc += imm;
	return err_t::ok;
}

err_t rv32imac::execute_cjr(uint16_t mcode)
{
	const uint32_t rs1 = getC10Rs1(mcode);
	pc = x[rs1];
	return err_t::ok;
}

err_t rv32imac::execute_cli(const uint16_t mcode)
{
	const uint32_t rd = getC01Rd(mcode);
	if (rd == 0) {
		// HINT
		pc += 2;
		return err_t::ok;
	}
	const int32_t imm = getCI1imm(mcode);
	x[rd] = imm;
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::executr_clui(const uint16_t mcode)
{
	const int32_t nzimm = getCI3imm(mcode);
	if (nzimm == 0)
		return err_t::reserved;
	const uint32_t rd = getC01Rd(mcode);
	if (rd == 0) {
		// HINT
		pc += 2;
		return err_t::ok;
	}
	x[rd] = nzimm;
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_csrai(const uint16_t mcode)
{
	const uint32_t shamt = getCI1uimm(mcode);  // TODO getCI1uimm ?
	if (shamt == 0) {
		// HINT
		pc += 2;
		return err_t::ok;
	}
	const uint32_t rdp = getC01Rdp(mcode);
	int32_t tmp = static_cast<int32_t>(x[rdp]);
	tmp >>= shamt;
	x[rdp] = static_cast<uint32_t>(tmp);
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_csrli(const uint16_t mcode)
{
	const uint32_t shamt = getCI1uimm(mcode);
	if (shamt == 0) {
		// HINT
		pc += 2;
		return err_t::ok;
	}
	const uint32_t rdp = getC01Rdp(mcode);
	x[rdp] >>= shamt;
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_clw(const uint16_t mcode)
{
	const uint32_t offset = getCL3uimm(mcode);
	const uint32_t rd = getC00Rdp(mcode);
	const uint32_t rs1 = getC00Rs1p(mcode);
	uint32_t value;
	if (iMemory.readUint32(value, x[rs1] + offset, iEndian) == err_t::error)
		return err_t::memory;
	x[rd] = value;
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_clwsp(uint16_t mcode)
{
	const uint32_t rd = getC10Rd(mcode);
	const uint32_t offset = getUImmQ2_010(mcode);
	uint32_t value;
	if (iMemory.readUint32(value, x[2] + offset, iEndian) == err_t::error)
		return err_t::memory;
	x[rd] = value;
	return err_t::ok;
}

err_t rv32imac::execute_cmv(const uint16_t mcode)
{
	const uint32_t rd = getC10Rd(mcode);
	const uint32_t rs2 = getC10Rs2(mcode);
	x[rd] = x[rs2];
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_cnop()
{
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_cor(const uint16_t mcode)
{
	const uint32_t rs2p = getC00Rs2p(mcode);
	const uint32_t rdp = getC01Rd(mcode);
	x[rdp] = x[rdp] | x[rs2p];
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_slli(uint16_t mcode)
{
	const uint32_t rd = getC10Rd(mcode);
	const uint32_t shamt = getCI1uimm(mcode);
	if (rd == 0 || shamt == 0) {
		// HINT
		pc += 2;
		return err_t::ok;
	}
	x[rd] = x[rd] << shamt;
	return err_t::ok;
}

err_t rv32imac::execute_csub(const uint16_t mcode)
{
	const uint32_t rs2p = getC00Rs2p(mcode);
	const uint32_t rdp = getC01Rd(mcode);
	x[rdp] -= x[rs2p];
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_csw(const uint16_t mcode)
{
	const uint32_t offset = getCL3uimm(mcode);
	const uint32_t rs1 = getC00Rs1p(mcode);
	const uint32_t rs2 = getC00Rs2p(mcode);
	if (iMemory.writeUint32(x[rs2], x[rs1] + offset, iEndian) == err_t::error)
		return err_t::memory;
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_cswsp(uint16_t mcode)
{
	const uint32_t offset = getUImmQ2_110(mcode);
	const uint32_t rs2 = getC10Rs2(mcode);
	if (iMemory.writeUint32(x[rs2], x[2] + offset, iEndian) == err_t::error)
		return err_t::memory;
	pc += 2;
	return err_t::ok;
}

err_t rv32imac::execute_cxor(const uint16_t mcode)
{
	const uint32_t rs2p = getC00Rs2p(mcode);
	const uint32_t rdp = getC01Rdp(mcode);
	x[rdp] = x[rdp] ^ x[rs2p];
	pc += 2;
	return err_t::ok;
}

// RV32I --------------------------------------------------------
err_t rv32imac::execute_auipc(const uint32_t mcode)
{
	// auipc rd,imm
	const uint32_t rd = getRd(mcode);
	if (rd != 0)
		x[rd] = pc + getUimm(mcode);
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_add(const uint32_t mcode)
{
	// add rd,rs1,rs2
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(mcode);
		const uint8_t rs2 = getRs2(mcode);
		x[rd] = x[rs1] + x[rs2];
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_addi(const uint32_t mcode)
{
	// addi rd,rs1,imm
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const int32_t imm = getIimm(mcode);
		const uint8_t rs1 = getRs1(mcode);
		x[rd] = x[rs1] + static_cast<uint32_t>(imm);
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_and(const uint32_t mcode)
{
	// and rd,rs1,rs2
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(mcode);
		const uint8_t rs2 = getRs2(mcode);
		x[rd] = x[rs1] & x[rs2];
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_andi(const uint32_t mcode)
{
	// andi rd,rs1,imm
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const int32_t imm = getIimm(mcode);
		const uint8_t rs1 = getRs1(mcode);
		x[rd] = x[rs1] & imm;
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_beq(const uint32_t mcode)
{
	// beq rs1,rs2,offset
	const int32_t off = getBimm(mcode);
	const uint32_t rs1 = getRs1(mcode);
	const uint32_t rs2 = getRs2(mcode);
	pc = x[rs1] == x[rs2] ? pc + off : pc + 4;
	return err_t::ok;
}

err_t rv32imac::execute_bge(const uint32_t mcode)
{
	// bge rs1,rs2,offset
	const int32_t off = getBimm(mcode);
	const uint32_t rs1 = getRs1(mcode);
	const uint32_t rs2 = getRs2(mcode);
	pc = static_cast<int32_t>(x[rs1]) >= static_cast<int32_t>(x[rs2]) ? pc + off : pc + 4;
	return err_t::ok;
}

err_t rv32imac::execute_bgeu(const uint32_t mcode)
{
	// bgeu rs1,rs2,offset
	const int32_t off = getBimm(mcode);
	const uint32_t rs1 = getRs1(mcode);
	const uint32_t rs2 = getRs2(mcode);
	pc = x[rs1] >= x[rs2] ? pc + off : pc + 4;
	return err_t::ok;
}

err_t rv32imac::execute_blt(const uint32_t mcode)
{
	// blt rs1,rs2,offset
	const int32_t off = getBimm(mcode);
	const uint32_t rs1 = getRs1(mcode);
	const uint32_t rs2 = getRs2(mcode);
	pc = static_cast<int32_t>(x[rs1]) < static_cast<int32_t>(x[rs2]) ? pc + off : pc + 4;
	return err_t::ok;
}

err_t rv32imac::execute_bltu(const uint32_t mcode)
{
	// bltu rs1,rs2,offset
	const int32_t off = getBimm(mcode);
	const uint32_t rs1 = getRs1(mcode);
	const uint32_t rs2 = getRs2(mcode);
	pc = x[rs1] < x[rs2] ? pc + off : pc + 4;
	return err_t::ok;
}

err_t rv32imac::execute_bne(const uint32_t mcode)
{
	// bne rs1,rs2,offset
	const int32_t off = getBimm(mcode);
	const uint32_t rs1 = getRs1(mcode);
	const uint32_t rs2 = getRs2(mcode);
	pc = x[rs1] != x[rs2] ? pc + off : pc + 4;
	return err_t::ok;
}

err_t rv32imac::execute_jal(const uint32_t mcode)
{
	// jal rd,offset
	const int32_t offset = getJimm(mcode);
	const uint32_t rd = getRd(mcode);
	if (rd != 0)
		x[rd] = pc + 4;
	pc += offset;
	return err_t::ok;
}

err_t rv32imac::execute_jalr(const uint32_t mcode)
{
	// jalr rd,rs1,offset
	if (getFunct3(mcode) != 0b000)
		return err_t::error;
	const int32_t off = getIimm(mcode);
	const uint32_t rd = getRd(mcode);
	const uint32_t rs1 = getRs1(mcode);
	if (rd != 0)
		x[rd] = pc + 4;
	const uint32_t newPc = ((x[rs1] + off) & ~1);
	if ((newPc & 0b11) != 0) {
		// TODO - support of 16-bit instr.
		return err_t::misaligned;
	}
	pc = newPc;
	return err_t::ok;
}

err_t rv32imac::execute_lb(const uint32_t mcode)
{
	// lb rd,offset(rs1)
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const int32_t offset = getIimm(mcode);
		const uint8_t rs1 = getRs1(mcode);
		int8_t sbyte;
		if (iMemory.readInt8(sbyte, x[rs1] + offset) == err_t::error)
			return err_t::memory;
		const int32_t signExtended = static_cast<int32_t>(sbyte);
		x[rd] = static_cast<uint32_t>(signExtended);
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_lbu(const uint32_t mcode)
{
	// lbu rd,offset(rs1)
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const int32_t offset = getIimm(mcode);
		const uint8_t rs1 = getRs1(mcode);
		uint8_t byte;
		if (iMemory.readUint8(byte, x[rs1] + offset) == err_t::error)
			return err_t::memory;
		x[rd] = static_cast<uint32_t>(byte);
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_lh(const uint32_t mcode)
{
	// lh rd,offset(rs1)
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const int32_t offset = getIimm(mcode);
		const uint8_t rs1 = getRs1(mcode);
		int16_t shword;
		if (iMemory.readInt16(shword, x[rs1] + offset, iEndian) == err_t::error)
			return err_t::memory;
		const int32_t signExtended = static_cast<int32_t>(shword);
		x[rd] = static_cast<uint32_t>(signExtended);
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_lhu(const uint32_t mcode)
{
	// lhu rd,offset(rs1)
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const int32_t offset = getIimm(mcode);
		const uint8_t rs1 = getRs1(mcode);
		uint16_t hword;
		if (iMemory.readUint16(hword, x[rs1] + offset, iEndian) == err_t::error)
			return err_t::memory;
		x[rd] = static_cast<uint32_t>(hword);
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_lui(const uint32_t mcode)
{
	// lui rd,imm
	const uint32_t rd = getRd(mcode);
	if (rd != 0)
		x[rd] = getUimm(mcode);
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_lw(const uint32_t mcode)
{
	// LW rd,offset(rs1)
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const int32_t offset = getIimm(mcode);
		const uint8_t rs1 = getRs1(mcode);
		int32_t sword;
		if (iMemory.readInt32(sword, x[rs1] + offset, iEndian) == err_t::error)
			return err_t::memory;
		x[rd] = static_cast<uint32_t>(sword);
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_or(const uint32_t mcode)
{
	// or rd,rs1,rs2
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(mcode);
		const uint8_t rs2 = getRs2(mcode);
		x[rd] = x[rs1] | x[rs2];
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_ori(const uint32_t mcode)
{
	// ori rd,rs1,imm
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const int32_t imm = getIimm(mcode);
		const uint8_t rs1 = getRs1(mcode);
		x[rd] = x[rs1] | imm;
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_sb(const uint32_t mcode)
{
	// sb rs2,offset(rs1)
	const int32_t offset = getSimm(mcode);
	const uint8_t rs1 = getRs1(mcode);
	const uint8_t rs2 = getRs2(mcode);
	const uint8_t byte = static_cast<uint8_t>(x[rs2] & 0xFF);
	if (iMemory.writeUint8(byte, x[rs1] + offset) == err_t::error)
		return err_t::memory;
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_sh(const uint32_t mcode)
{
	// sh rs2,offset(rs1)
	const int32_t offset = getSimm(mcode);
	const uint8_t rs1 = getRs1(mcode);
	const uint8_t rs2 = getRs2(mcode);
	const uint16_t hword = static_cast<uint16_t>(x[rs2] & 0xFFFF);
	if (iMemory.writeUint16(hword, x[rs1] + offset, iEndian) == err_t::error)
		return err_t::memory;
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_sll(const uint32_t mcode)
{
	// sll rd,rs1,rs2
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(mcode);
		const uint8_t rs2 = getRs2(mcode);
		x[rd] = x[rs1] << (x[rs2] & 0b11111);
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_slli(const uint32_t mcode)
{
	// slli rd,rs1,imm
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(mcode);
		const uint8_t shamt = getShamt(mcode);
		x[rd] = x[rs1] << shamt;
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_slt(const uint32_t mcode)
{
	// slt rd,rs1,rs2
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(mcode);
		const uint8_t rs2 = getRs2(mcode);
		x[rd] = static_cast<int32_t>(x[rs1]) < static_cast<int32_t>(x[rs2]) ? 1 : 0;
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_sltu(const uint32_t mcode)
{
	// sltu rd,rs1,rs2
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(mcode);
		const uint8_t rs2 = getRs2(mcode);
		x[rd] = x[rs1] < x[rs2] ? 1 : 0;
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_slti(const uint32_t mcode)
{
	// slti rd,rs1,imm
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const int32_t imm = getIimm(mcode);
		const uint8_t rs1 = getRs1(mcode);
		x[rd] = static_cast<int32_t>(x[rs1]) < imm ? 1 : 0;
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_sltiu(const uint32_t mcode)
{
	// sltiu rd,rs1,imm
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const int32_t imm = getIimm(mcode);
		const uint8_t rs1 = getRs1(mcode);
		x[rd] = x[rs1] < static_cast<uint32_t>(imm) ? 1 : 0;
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_sra(const uint32_t mcode)
{
	// sra rd,rs1,rs2
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(mcode);
		const uint8_t rs2 = getRs2(mcode);
		x[rd] = static_cast<uint32_t>(static_cast<int32_t>(x[rs1]) >> (x[rs2] & 0b11111));
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_srai(const uint32_t mcode)
{
	// srai rd,rs1,imm
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint32_t shamt = getShamt(mcode);
		const uint8_t rs1 = getRs1(mcode);
		x[rd] = static_cast<uint32_t>(static_cast<int32_t>(x[rs1]) >> shamt);
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_srl(const uint32_t mcode)
{
	// srl rd,rs1,rs2
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(mcode);
		const uint8_t rs2 = getRs2(mcode);
		x[rd] = x[rs1] >> (x[rs2] & 0b11111);
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_srli(const uint32_t mcode)
{
	// srli rd,rs1,imm
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint32_t shamt = getShamt(mcode);
		const uint8_t rs1 = getRs1(mcode);
		x[rd] = x[rs1] >> shamt;
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_sub(const uint32_t mcode)
{
	// sub rd,rs1,rs2
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(mcode);
		const uint8_t rs2 = getRs2(mcode);
		x[rd] = x[rs2] - x[rs1];
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_sw(const uint32_t mcode)
{
	// sw rs2,offset(rs1)
	const int32_t offset = getSimm(mcode);
	const uint8_t rs1 = getRs1(mcode);
	const uint8_t rs2 = getRs2(mcode);
	const uint32_t word = static_cast<uint32_t>(x[rs2] & 0xFFFFFFFF);
	if (iMemory.writeUint32(word, x[rs1] + offset, iEndian) == err_t::error)
		return err_t::memory;
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_xor(const uint32_t mcode)
{
	// xor rd,rs1,rs2
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const uint8_t rs1 = getRs1(mcode);
		const uint8_t rs2 = getRs2(mcode);
		x[rd] = x[rs1] ^ x[rs2];
	}
	pc += 4;
	return err_t::ok;
}

err_t rv32imac::execute_xori(const uint32_t mcode)
{
	// xori rd,rs1,imm
	const uint8_t rd = getRd(mcode);
	if (rd != 0) {
		const int32_t imm = getIimm(mcode);
		const uint8_t rs1 = getRs1(mcode);
		x[rd] = x[rs1] ^ imm;
	}
	pc += 4;
	return err_t::ok;
}

}  // namespace riscv
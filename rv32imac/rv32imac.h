#ifndef RV64GC_H
#define RV64GC_H

#include <stdint.h>
#include "types.h"

namespace riscv {

class rv32imac
{
public:
	rv32imac();
	void reset();

	err_t execute(uint32_t mcode);

	uint32_t x[32];
	uint64_t pc{ 0 };
	uint8_t* pMemory{ nullptr };

private:
	err_t quadrant0(uint16_t mcode);
	err_t quadrant1(uint16_t mcode);
	err_t quadrant2(uint16_t mcode);
	err_t instr32(uint32_t mcode);

	err_t quadrant1_000(uint16_t mcode);
	err_t quadrant1_011(uint16_t mcode);
	err_t quadrant1_100(uint16_t mcode);
	err_t quadrant2_000(uint16_t mcode);
	err_t quadrant2_100(uint16_t mcode);

	err_t execute_11_opcode_1100011(uint32_t mcode);
	err_t execute_11_opcode_0000011(uint32_t mcode);
	err_t execute_11_opcode_0010011(uint32_t mcode);
	err_t execute_11_opcode_0110011(uint32_t mcode);
	err_t execute_11_opcode_0100011(uint32_t mcode);
	err_t execute_11_opcode_0010011_funct3_001(uint32_t mcode);
	err_t execute_11_opcode_0010011_funct3_101(uint32_t mcode);
	err_t execute_11_opcode_0110011_funct3_000(uint32_t instr32);
	err_t execute_11_opcode_0110011_funct3_101(uint32_t instr32);

	// Extension "C" ------------------------------------------------
	err_t execute_cadd(uint16_t mcode);
	err_t execute_caddi(uint16_t mcode);
	err_t execute_caddi16sp(uint16_t mcode);
	err_t execute_caddi4spn(uint16_t mcode);
	err_t execute_cand(uint16_t mcode);
	err_t execute_candi(uint16_t mcode);
	err_t execute_cbeqz(uint16_t mcode);
	err_t execute_cbnez(uint16_t mcode);
	err_t execute_cebreak(uint16_t mcode);
	err_t execute_cjal(uint16_t mcode);
	err_t execute_cjalr(uint16_t mcode);
	err_t execute_cj(uint16_t mcode);
	err_t execute_cjr(uint16_t mcode);
	err_t execute_cli(uint16_t mcode);
	err_t executr_clui(uint16_t mcode);
	err_t execute_clw(uint16_t mcode);
	err_t execute_clwsp(uint16_t mcode);
	err_t execute_cmv(uint16_t mcode);
	err_t execute_cnop();
	err_t execute_cor(uint16_t mcode);
	err_t execute_slli(uint16_t mcode);
	err_t execute_csrai(uint16_t mcode);
	err_t execute_csrli(uint16_t mcode);
	err_t execute_csub(uint16_t mcode);
	err_t execute_csw(uint16_t mcode);
	err_t execute_cswsp(uint16_t mcode);
	err_t execute_cxor(uint16_t mcode);

	// RV32I --------------------------------------------------------
	err_t execute_auipc(uint32_t mcode);
	err_t execute_add(uint32_t mcode);
	err_t execute_addi(uint32_t mcode);
	err_t execute_and(uint32_t mcode);
	err_t execute_andi(uint32_t mcode);
	err_t execute_beq(uint32_t mcode);
	err_t execute_bge(uint32_t mcode);
	err_t execute_bgeu(uint32_t mcode);
	err_t execute_blt(uint32_t mcode);
	err_t execute_bltu(uint32_t mcode);
	err_t execute_bne(uint32_t mcode);
	err_t execute_jal(uint32_t mcode);
	err_t execute_jalr(uint32_t mcode);
	err_t execute_lb(uint32_t mcode);
	err_t execute_lbu(uint32_t mcode);
	err_t execute_lh(uint32_t mcode);
	err_t execute_lhu(uint32_t mcode);
	err_t execute_lui(uint32_t mcode);
	err_t execute_lw(uint32_t mcode);
	err_t execute_or(uint32_t mcode);
	err_t execute_ori(uint32_t mcode);
	err_t execute_sb(uint32_t mcode);
	err_t execute_sh(uint32_t mcode);
	err_t execute_sll(uint32_t mcode);
	err_t execute_slli(uint32_t mcode);
	err_t execute_slt(uint32_t mcode);
	err_t execute_sltu(uint32_t mcode);
	err_t execute_slti(uint32_t mcode);
	err_t execute_sltiu(uint32_t mcode);
	err_t execute_sra(uint32_t mcode);
	err_t execute_srai(uint32_t instr32);
	err_t execute_srl(uint32_t mcode);
	err_t execute_srli(uint32_t instr32);
	err_t execute_sub(uint32_t mcode);
	err_t execute_sw(uint32_t mcode);
	err_t execute_xor(uint32_t mcode);
	err_t execute_xori(uint32_t mcode);
};

}  // namespace riscv

#endif	// RV64GC_H
#include <assert.h>
#include "decoder.h"
#include "riscv.h"
#include "decode_tests.h"

using namespace riscv;

namespace tests {

void decode_illegal_reserved_test()
{
	instr_t instr;
	//-----------------------------FEDCBA9876543210
	assert(decode(base_t::rv32i, 0b0000000000000000, instr) == err_t::illegal);
	assert(decode(base_t::rv32i, 0b1000000000000000, instr) == err_t::reserved);
	assert(decode(base_t::rv32i, 0b1001110001000001, instr) == err_t::reserved);
	assert(decode(base_t::rv32i, 0b1001110001100001, instr) == err_t::reserved);
	assert(decode(base_t::rv32i, 0b0000000000000100, instr) == err_t::reserved); // c.addi4spn, nzuimm = 0
	assert(decode(base_t::rv32i, 0b0000000000001000, instr) == err_t::reserved); // c.addi4spn, nzuimm = 0
	assert(decode(base_t::rv32i, 0b0000000000001100, instr) == err_t::reserved); // c.addi4spn, nzuimm = 0
	assert(decode(base_t::rv32i, 0b0000000000010000, instr) == err_t::reserved); // c.addi4spn, nzuimm = 0
	assert(decode(base_t::rv32i, 0b0000000000010100, instr) == err_t::reserved); // c.addi4spn, nzuimm = 0
	assert(decode(base_t::rv32i, 0b0000000000011000, instr) == err_t::reserved); // c.addi4spn, nzuimm = 0
	assert(decode(base_t::rv32i, 0b0000000000011100, instr) == err_t::reserved); // c.addi4spn, nzuimm = 0
	assert(decode(base_t::rv64i, 0b0010000000000101, instr) == err_t::reserved); // c.addiw, rd = 0
	assert(decode(base_t::rv64i, 0b0110000100000001, instr) == err_t::reserved); // c.addi16sp
	assert(decode(base_t::rv64i, 0b0110000000000001, instr) == err_t::reserved); // c.lui

	printf("decode_illegal_reserved_test\n");
}

void get_reg_42_test()
{
	//------------------FEDCBA9876543210
	assert(get_reg_42(0b0000000000000000) == reg_t::x8);
	assert(get_reg_42(0b0000000000000100) == reg_t::x9);
	assert(get_reg_42(0b0000000000001000) == reg_t::x10);
	assert(get_reg_42(0b0000000000001100) == reg_t::x11);
	assert(get_reg_42(0b0000000000010000) == reg_t::x12);
	assert(get_reg_42(0b0000000000010100) == reg_t::x13);
	assert(get_reg_42(0b0000000000011000) == reg_t::x14);
	assert(get_reg_42(0b0000000000011100) == reg_t::x15);
	printf("get_reg_42_test\n");
}

void get_fp_reg_42_test()
{
	//------------------FEDCBA9876543210
	assert(get_fp_reg_42(0b0000000000000000) == reg_t::f8);
	assert(get_fp_reg_42(0b0000000000000100) == reg_t::f9);
	assert(get_fp_reg_42(0b0000000000001000) == reg_t::f10);
	assert(get_fp_reg_42(0b0000000000001100) == reg_t::f11);
	assert(get_fp_reg_42(0b0000000000010000) == reg_t::f12);
	assert(get_fp_reg_42(0b0000000000010100) == reg_t::f13);
	assert(get_fp_reg_42(0b0000000000011000) == reg_t::f14);
	assert(get_fp_reg_42(0b0000000000011100) == reg_t::f15);
	printf("get_fp_reg_42_test\n");
}

void get_reg_97_test()
{
	//------------------FEDCBA9876543210
	assert(get_reg_97(0b0000000000000000) == reg_t::x8);
	assert(get_reg_97(0b0000000010000000) == reg_t::x9);
	assert(get_reg_97(0b0000000100000000) == reg_t::x10);
	assert(get_reg_97(0b0000000110000000) == reg_t::x11);
	assert(get_reg_97(0b0000001000000000) == reg_t::x12);
	assert(get_reg_97(0b0000001010000000) == reg_t::x13);
	assert(get_reg_97(0b0000001100000000) == reg_t::x14);
	assert(get_reg_97(0b0000001110000000) == reg_t::x15);
	printf("get_reg_97_test\n");
}

void get_fp_reg_97_test()
{
	//---------------------FEDCBA9876543210
	assert(get_fp_reg_97(0b0000000000000000) == reg_t::f8);
	assert(get_fp_reg_97(0b0000000010000000) == reg_t::f9);
	assert(get_fp_reg_97(0b0000000100000000) == reg_t::f10);
	assert(get_fp_reg_97(0b0000000110000000) == reg_t::f11);
	assert(get_fp_reg_97(0b0000001000000000) == reg_t::f12);
	assert(get_fp_reg_97(0b0000001010000000) == reg_t::f13);
	assert(get_fp_reg_97(0b0000001100000000) == reg_t::f14);
	assert(get_fp_reg_97(0b0000001110000000) == reg_t::f15);
	printf("get_fp_reg_97_test\n");
}

void get_reg_11_7_test()
{
	//--------------------FEDCBA9876543210
	assert(get_reg_11_7(0b0000000000000000) == reg_t::x0);
	assert(get_reg_11_7(0b0000000010000000) == reg_t::x1);
	assert(get_reg_11_7(0b0000000100000000) == reg_t::x2);
	assert(get_reg_11_7(0b0000000110000000) == reg_t::x3);
	assert(get_reg_11_7(0b0000001000000000) == reg_t::x4);
	assert(get_reg_11_7(0b0000001010000000) == reg_t::x5);
	assert(get_reg_11_7(0b0000001100000000) == reg_t::x6);
	assert(get_reg_11_7(0b0000001110000000) == reg_t::x7);
	assert(get_reg_11_7(0b0000010000000000) == reg_t::x8);
	assert(get_reg_11_7(0b0000010010000000) == reg_t::x9);
	assert(get_reg_11_7(0b0000010100000000) == reg_t::x10);
	assert(get_reg_11_7(0b0000010110000000) == reg_t::x11);
	assert(get_reg_11_7(0b0000011000000000) == reg_t::x12);
	assert(get_reg_11_7(0b0000011010000000) == reg_t::x13);
	assert(get_reg_11_7(0b0000011100000000) == reg_t::x14);
	assert(get_reg_11_7(0b0000011110000000) == reg_t::x15);
	assert(get_reg_11_7(0b0000100000000000) == reg_t::x16);
	assert(get_reg_11_7(0b0000100010000000) == reg_t::x17);
	assert(get_reg_11_7(0b0000100100000000) == reg_t::x18);
	assert(get_reg_11_7(0b0000100110000000) == reg_t::x19);
	assert(get_reg_11_7(0b0000101000000000) == reg_t::x20);
	assert(get_reg_11_7(0b0000101010000000) == reg_t::x21);
	assert(get_reg_11_7(0b0000101100000000) == reg_t::x22);
	assert(get_reg_11_7(0b0000101110000000) == reg_t::x23);
	assert(get_reg_11_7(0b0000110000000000) == reg_t::x24);
	assert(get_reg_11_7(0b0000110010000000) == reg_t::x25);
	assert(get_reg_11_7(0b0000110100000000) == reg_t::x26);
	assert(get_reg_11_7(0b0000110110000000) == reg_t::x27);
	assert(get_reg_11_7(0b0000111000000000) == reg_t::x28);
	assert(get_reg_11_7(0b0000111010000000) == reg_t::x29);
	assert(get_reg_11_7(0b0000111100000000) == reg_t::x30);
	assert(get_reg_11_7(0b0000111110000000) == reg_t::x31);
	printf("get_reg_11_7_test\n");
}

void decode_csddi4spn()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e, base_t::rv64i, base_t::rv128i }) {
		instr_t instr;
		//-----------------------------FEDCBA9876543210
		assert(decode(base_t::rv32i, 0b0001000000111100, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_addi4spn);
		assert(instr.uimm32 == 40);
		assert(instr.rd == reg_t::x15);
	}
	printf("decode_csddi4spn\n");
}

void decode_cfld()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e, base_t::rv64i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0011011111111100, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_fld);
		assert(instr.uimm32 == 232);
		assert(instr.rd == reg_t::f15);
		assert(instr.rs1 == reg_t::x15);
	}
	printf("decode_cfld\n");
}

void decode_clq()
{
	instr_t instr;
	//------------------------------FEDCBA9876543210
	assert(decode(base_t::rv128i, 0b0011011111111100, instr) == err_t::ok);
	assert(instr.mnemonic == mnemonic_t::c_lq);
	assert(instr.uimm32 == 480);
	assert(instr.rd == reg_t::x15);
	assert(instr.rs1 == reg_t::x15);
	printf("decode_clq\n");
}

void decode_clw()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e, base_t::rv64i, base_t::rv128i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0101011111111100, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_lw);
		assert(instr.uimm32 == 108);
		assert(instr.rd == reg_t::x15);
		assert(instr.rs1 == reg_t::x15);
	}
	printf("decode_clw\n");
}

void decode_cflw()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0111011111111100, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_flw);
		assert(instr.uimm32 == 108);
		assert(instr.rd == reg_t::f15);
		assert(instr.rs1 == reg_t::x15);
	}
	printf("decode_cflw\n");
}

void decode_cld()
{
	const base_t base = base_t::rv64i;
	instr_t instr;
	//--------------------FEDCBA9876543210
	assert(decode(base, 0b0111011111111100, instr) == err_t::ok);
	assert(instr.mnemonic == mnemonic_t::c_ld);
	assert(instr.uimm32 == 232);
	assert(instr.rd == reg_t::x15);
	assert(instr.rs1 == reg_t::x15);
	printf("decode_cld\n");
}

void decode_fsd()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e, base_t::rv64i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b1011011111111100, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_fsd);
		assert(instr.uimm32 == 232);
		assert(instr.rs1 == reg_t::x15);
		assert(instr.rs2 == reg_t::f15);
	}
	printf("decode_fsd\n");
}

void decode_c_sq()
{
	const base_t base = base_t::rv128i;
	instr_t instr;
	//--------------------FEDCBA9876543210
	assert(decode(base, 0b1011011111111100, instr) == err_t::ok);
	assert(instr.mnemonic == mnemonic_t::c_sq);
	assert(instr.uimm32 == 480);
	assert(instr.rs1 == reg_t::x15);
	assert(instr.rs2 == reg_t::x15);
	printf("decode_c_sq\n");
}

void decode_c_sw()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e, base_t::rv64i, base_t::rv128i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b1101011111111100, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_sw);
		assert(instr.uimm32 == 108);
		assert(instr.rs1 == reg_t::x15);
		assert(instr.rs2 == reg_t::x15);
	}
	printf("decode_c_sw\n");
}

void decode_c_fsw()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b1111011111111100, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_fsw);
		assert(instr.uimm32 == 108);
		assert(instr.rs1 == reg_t::x15);
		assert(instr.rs2 == reg_t::x15);
	}
	printf("decode_c_fsw\n");
}

void decode_c_sd()
{
	for (const base_t base : std::vector<base_t> { base_t::rv64i, base_t::rv128i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b1111011111111100, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_sd);
		assert(instr.uimm32 == 232);
		assert(instr.rs1 == reg_t::x15);
		assert(instr.rs2 == reg_t::x15);
	}
	printf("decode_c_sd\n");
}

void decode_nop()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e, base_t::rv64i, base_t::rv128i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0000000000000001, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_nop);
	}
	printf("decode_nop\n");
}

void decode_c_addi()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e, base_t::rv64i, base_t::rv128i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0001111111000101, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_addi);
		assert(static_cast<int32_t>(instr.uimm32) == -15);
		assert(instr.rd == reg_t::x31);
		assert(instr.rs1 == reg_t::x31);
		assert(instr.hint == false);
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0000000010000001, instr) == err_t::ok);
		assert(instr.hint == true);
	}
	printf("decode_c_addi\n");
}

void decode_c_jal()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0011000000000001, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_jal);
		assert(static_cast<int32_t>(instr.uimm32) == -2048);
	}
	printf("decode_c_jal\n");
}

void decode_c_addiw()
{
	for (const base_t base : std::vector<base_t> { base_t::rv64i, base_t::rv128i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0011000011000101, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_addiw);
		assert(instr.rd == reg_t::x1);
		assert(instr.rs1 == reg_t::x1);
		assert(static_cast<int32_t>(instr.uimm32) == -15);
	}
	printf("decode_c_addiw\n");
}

void decode_c_li()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e, base_t::rv64i, base_t::rv128i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0101000011000101, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_li);
		assert(instr.rd == reg_t::x1);
		assert(instr.rs1 == reg_t::x1);
		assert(static_cast<int32_t>(instr.uimm32) == -15);
		assert(instr.hint == false);
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0101000001000101, instr) == err_t::ok);
		assert(instr.hint == true);
	}
	printf("decode_c_li\n");
}

void decode_caddi16sp()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e, base_t::rv64i, base_t::rv128i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0111000101000101, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_addi16sp);
		assert(static_cast<int32_t>(instr.uimm32) == -464);
	}
	printf("decode_caddi16sp\n");
}

void decode_clui()
{
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e, base_t::rv64i, base_t::rv128i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0110000010000101, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_lui);
		assert(instr.rd == reg_t::x1);
		assert(static_cast<int32_t>(instr.uimm32) == 4096);
		assert(instr.hint == false);
	}
	for (const base_t base : std::vector<base_t> { base_t::rv32i, base_t::rv32e, base_t::rv64i, base_t::rv128i }) {
		instr_t instr;
		//--------------------FEDCBA9876543210
		assert(decode(base, 0b0110000000000101, instr) == err_t::ok);
		assert(instr.mnemonic == mnemonic_t::c_lui);
		assert(instr.rd == reg_t::x0);
		assert(static_cast<int32_t>(instr.uimm32) == 4096);
		assert(instr.hint);
	}
	printf("decode_clui\n");
}

void run_decode_tests()
{
	decode_illegal_reserved_test();
	get_put_tests();

	get_reg_42_test();
	get_fp_reg_42_test();
	get_reg_97_test();
	get_fp_reg_97_test();
	get_reg_11_7_test();

	// Quadrant 0
	decode_csddi4spn();
	decode_cfld();
	decode_clq();
	decode_clw();
	decode_cflw();
	decode_cld();
	decode_fsd();
	decode_c_sq();
	decode_c_sw();
	decode_c_fsw();
	decode_c_sd();

	// Quadrant 1
	decode_nop();
	decode_c_addi();
	decode_c_jal();
	decode_c_addiw();
	decode_c_li();
	decode_caddi16sp();
	decode_clui();

	csrli_tests();
}

}
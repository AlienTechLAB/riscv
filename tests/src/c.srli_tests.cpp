#include <vector>
#include <assert.h>
#include "decoder.h"
#include "riscv.h"
#include "decode_tests.h"

namespace tests {

//----------------------------FEDCBA9876543210
const uint16_t base_csrli = 0b1000000000000001;

void csrli_128_shamt_0_test()
{
	instr_t instr;
	assert(decode(base_t::rv128i, base_csrli, instr) == err_t::ok); // shamt = 0 -> imm = 64
	assert(instr.mnemonic == mnemonic_t::c_srli);
	assert(instr.rd == reg_t::x8);
	assert(instr.rs1 == reg_t::x8);
	assert(static_cast<int32_t>(instr.uimm32) == 64);
	assert(instr.hint == false);
}

void csrli_zero_shamt_tests()
{
	for (const base_t base : std::vector<base_t>{ base_t::rv32i, base_t::rv32e, base_t::rv64i }) {
		instr_t instr;
		assert(decode(base, base_csrli, instr) == err_t::ok); // shamt = 0 -> hint = true
		assert(instr.mnemonic == mnemonic_t::c_srli);
		assert(instr.rd == reg_t::x8);
		assert(instr.rs1 == reg_t::x8);
		assert(static_cast<int32_t>(instr.uimm32) == 0);
		assert(instr.hint);
	}
}

void csrli_tests()
{
	csrli_128_shamt_0_test();
	csrli_zero_shamt_tests();
	printf("csrli_tests\n");
}

}  // namespace tests
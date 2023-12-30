#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <algorithm>
#include <stdint.h>

namespace riscv {

enum class err_t : uint8_t {
	ok,
	reserved,
	nse,
	error,
	unknown,
	memory,
	misaligned,
	illegal,
	isa_error,
	no_extension
};

enum class endian_t : uint8_t {
	little,
	big
};

// TODO - move into isa_t?
enum base_t : uint8_t {
	rv32i = 1,
	rv32e = 2,
	rv64i = 4,
	rv128i = 8,
	all = rv32i | rv32e | rv64i | rv128i
};

// Volume I, Chapter 20, Table 20.1, page 109
enum reg_t : uint8_t {
	none = 0xFF,
	//------------------------------------------------------------------------------------
	// Register			ABI Name			Description								Saver
	//------------------------------------------------------------------------------------
	x0 = 0,				zero = 0,		//	Hard-wired zero							  -
	x1 = 1,				ra = 1,			//	Return address							Caller
	x2 = 2,				sp = 2,			//	Stack pointer							Callee
	x3 = 3,				gp = 3,			//	Global pointer		  					  -
	x4 = 4,				tp = 4,			//	Thread pointer		  					  -
	x5 = 5,				t0 = 5,			//	Temporary/alternate link register		Caller
	x6 = 6,				t1 = 6,			//	Temporaries								Caller
	x7 = 7,				t2 = 7,			//	Temporaries								Caller
	x8 = 8,				s0 = 8, fp = 8,	//	Saved register/frame pointer			Callee
	x9 = 9,				s1 = 9,			//	Saved register							Callee
	x10 = 10,			a0 = 10,		//	Function arguments/return values		Caller
	x11 = 11,			a1 = 11,		//	Function arguments/return values		Caller
	x12 = 12,			a2 = 12,		//	Function arguments						Caller
	x13 = 13,			a3 = 13,		//	Function arguments						Caller
	x14 = 14,			a4 = 14,		//	Function arguments						Caller
	x15 = 15,			a5 = 15,		//	Function arguments						Caller
	x16 = 16,			a6 = 16,		//	Function arguments						Caller
	x17 = 17,			a7 = 17,		//	Function arguments						Caller
	x18 = 18,			s2 = 18,		//	Saved registers							Callee
	x19 = 19,			s3 = 19,		//	Saved registers							Callee
	x20 = 20,			s4 = 20,		//	Saved registers							Callee
	x21 = 21,			s5 = 21,		//	Saved registers							Callee
	x22 = 22,			s6 = 22,		//	Saved registers							Callee
	x23 = 23,			s7 = 23,		//	Saved registers							Callee
	x24 = 24,			s8 = 24,		//	Saved registers							Callee
	x25 = 25,			s9 = 25,		//	Saved registers							Callee
	x26 = 26,			s10 = 26,		//	Saved registers							Callee
	x27 = 27,			s11 = 27,		//	Saved registers							Callee
	x28 = 28,			t3 = 28,		//	Temporaries								Caller
	x29 = 29,			t4 = 29,		//	Temporaries								Caller
	x30 = 30,			t5 = 30,		//	Temporaries								Caller
	x31 = 31,			t6 = 31,		//	Temporaries								Caller

	//------------------------------------------------------------------------------------
	// Register			ABI Name			Description								Saver
	//------------------------------------------------------------------------------------
	f0 = 32,			ft0 = 32,		//	FP temporaries							Caller
	f1 = 33,			ft1 = 33,		//	FP temporaries							Caller
	f2 = 34,			ft2 = 34,		//	FP temporaries							Caller
	f3 = 35,			ft3 = 35,		//	FP temporaries							Caller
	f4 = 36,			ft4 = 36,		//	FP temporaries							Caller
	f5 = 37,			ft5 = 37,		//	FP temporaries							Caller
	f6 = 38,			ft6 = 38,		//	FP temporaries							Caller
	f7 = 39,			ft7 = 39,		//	FP temporaries							Caller
	f8 = 40,			fs0 = 40,		//	FP saved registers						Callee
	f9 = 41,			fs1 = 41,		//	FP saved registers						Callee
	f10 = 42,			fa0 = 42,		//	FP arguments/return values				Caller
	f11 = 43,			fa1 = 43,		//	FP arguments/return values				Caller
	f12 = 44,			fa2 = 44,		//	FP arguments							Caller
	f13 = 45,			fa3 = 45,		//	FP arguments							Caller
	f14 = 46,			fa4 = 46,		//	FP arguments							Caller
	f15 = 47,			fa5 = 47,		//	FP arguments							Caller
	f16 = 48,			fa6 = 48,		//	FP arguments							Caller
	f17 = 49,			fa7 = 49,		//	FP arguments							Caller
	f18 = 50,			fs2 = 50,		//	FP saved registers						Callee
	f19 = 51,			fs3 = 51,		//	FP saved registers						Callee
	f20 = 52,			fs4 = 52,		//	FP saved registers						Callee
	f21 = 53,			fs5 = 53,		//	FP saved registers						Callee
	f22 = 54,			fs6 = 54,		//	FP saved registers						Callee
	f23 = 55,			fs7 = 55,		//	FP saved registers						Callee
	f24 = 56,			fs8 = 56,		//	FP saved registers						Callee
	f25 = 57,			fs9 = 57,		//	FP saved registers						Callee
	f26 = 58,			fs10 = 58,		//	FP saved registers						Callee
	f27 = 59,			fs11 = 59,		//	FP saved registers						Callee
	f28 = 60,			ft8 = 60,		//	FP temporaries							Caller
	f29 = 61,			ft9 = 61,		//	FP temporaries							Caller
	f30 = 62,			ft10 = 62,		//	FP temporaries							Caller
	f31 = 63,			ft11 = 63,		//	FP temporaries							Caller
};


enum class mnemonic_t : uint8_t {
	// Volume I, Chapter 12.7, Tables: 12.4, 12.5, 12.6, pages: 82-83
	c_addi4spn,
	c_fld,
	c_lq,
	c_lw,
	c_flw,
	c_ld,
	c_fsd,
	c_sq,
	c_sw,
	c_nop,
	c_fsw,
	c_sd,
	c_addi,
	c_jal,
	c_addiw,
	c_li,
	c_addi16sp,
	c_lui,
	c_srli,
	none
	
	// Volume I, Chapter 19, Tables: 19.2, pages: 104-107
};

struct instr_t
{
	mnemonic_t mnemonic{ mnemonic_t::none };
	uint8_t bases{ 0 };
	bool hint{ false };
	reg_t rd{ reg_t::none };
	reg_t rs1{ reg_t::none };
	reg_t rs2{ reg_t::none };
	uint8_t size{ 0 };
	uint32_t uimm32{ 0 };
};

}  // namespace riscv

#endif	// TYPES_H
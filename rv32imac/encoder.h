#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>
#include "types.h"

namespace riscv {

inline void setJimm(uint32_t& mcode, int32_t number)
{
	//----------------------33222222222211111111110000000000
	//----------------------10987654321098765432109876543210
	const uint32_t mask = 0b00000000000000000000111111111111;
	//---------------------------------33222222222211111111110000000000
	//---------------------------------10987654321098765432109876543210
	const uint32_t b20   = (number & 0b00000000000100000000000000000000) << 11;
	const uint32_t b1912 = (number & 0b00000000000011111111000000000000);
	const uint32_t b11   = (number & 0b00000000000000000000100000000000) << 9;
	const uint32_t b101  = (number & 0b00000000000000000000011111111110) << 20;
	mcode = (mcode & mask) | b20 | b1912 | b11 | b101;
}

inline void setBimm(uint32_t& mcode, const int32_t number)
{
	//----------------------33222222222211111111110000000000
	//----------------------10987654321098765432109876543210
	const uint32_t mask = 0b00000001111111111111000001111111;
	//--------------------------------33222222222211111111110000000000
	//--------------------------------10987654321098765432109876543210
	const uint32_t b12  = (number & 0b00000000000000000001000000000000) << 19;
	const uint32_t b11  = (number & 0b00000000000000000000100000000000) >> 4;
	const uint32_t b41  = (number & 0b00000000000000000000000000011110) << 7;
	const uint32_t b105 = (number & 0b00000000000000000000011111100000) << 20;
	mcode = (mcode & mask) | b12 | b11 | b41 | b105;
}

inline void setSimm(uint32_t& mcode, const int32_t number)
{
	//----------------------33222222222211111111110000000000
	//----------------------10987654321098765432109876543210
	const uint32_t mask = 0b00000001111111111111000001111111;
	//--------------------------------33222222222211111111110000000000
	//--------------------------------10987654321098765432109876543210
	const uint32_t b115 = (number & 0b00000000000000000000111111100000) << 20;
	const uint32_t b40  = (number & 0b00000000000000000000000000011111) << 7;
	mcode = (mcode & mask) | b115 | b40;
}

inline void setCIWimm(uint16_t& mcode, const uint16_t number)
{
	//----------------------FEDCBA9876543210
	const uint16_t mask = 0b1110000000011111;
	//-------------------------------FEDCBA9876543210
	const uint16_t b54 = (number & 0b0000000000110000) << 7;
	const uint16_t b96 = (number & 0b0000001111000000) << 1;
	const uint16_t b2  = (number & 0b0000000000000100) << 4;
	const uint16_t b3  = (number & 0b0000000000001000) << 2;
	mcode = (mcode & mask) | b54 | b96 | b2 | b3;
}

inline void setCL1uimm(uint16_t& mcode, const uint16_t number)
{
	//----------------------FEDCBA9876543210
	const uint16_t mask = 0b1110001110011111;
	//-------------------------------FEDCBA9876543210
	const uint16_t b53 = (number & 0b0000000000111000) << 7;
	const uint16_t b76 = (number & 0b0000000011000000) >> 1;
	mcode = (mcode & mask) | b53 | b76;
}

inline void setCL2uimm(uint16_t& mcode, const uint16_t number)
{
	//----------------------FEDCBA9876543210
	const uint16_t mask = 0b1110001110011111;
	//-------------------------------FEDCBA9876543210
	const uint16_t b54 = (number & 0b0000000000110000) << 7;
	const uint16_t b8  = (number & 0b0000000100000000) << 2;
	const uint16_t b76 = (number & 0b0000000011000000) >> 1;
	mcode = (mcode & mask) | b54 | b8 | b76;
}

inline void setCL3uimm(uint16_t& mcode, const uint16_t number)
{
	//----------------------FEDCBA9876543210
	const uint16_t mask = 0b1110001110011111;
	//-------------------------------FEDCBA9876543210
	const uint16_t b53 = (number & 0b0000000000111000) << 7;
	const uint16_t b2  = (number & 0b0000000000000100) << 4;
	const uint16_t b6  = (number & 0b0000000001000000) >> 1;
	mcode = (mcode & mask) | b53 | b2 | b6;
}

inline void setCI1imm(uint16_t& mcode, const int16_t number)
{
	//----------------------FEDCBA9876543210
	const uint16_t mask = 0b1110111110000011;
	//-------------------------------FEDCBA9876543210
	const uint16_t b5  = (number & 0b0000000000100000) << 7;
	const uint16_t b40 = (number & 0b0000000000011111) << 2;
	mcode = (mcode & mask) | b5 | b40;
}

inline void setCI1uimm(uint16_t& mcode, const uint16_t number)
{
	//----------------------FEDCBA9876543210
	const uint16_t mask = 0b1110111110000011;
	//-------------------------------FEDCBA9876543210
	const uint16_t b5  = (number & 0b0000000000100000) << 7;
	const uint16_t b40 = (number & 0b0000000000011111) << 2;
	mcode = (mcode & mask) | b5 | b40;
}

inline void setCI2imm(uint16_t& mcode, const int16_t number)
{
	//----------------------FEDCBA9876543210
	const uint16_t mask = 0b1110111110000011;
	//-------------------------------FEDCBA9876543210
	const uint16_t b9  = (number & 0b0000001000000000) << 3;
	const uint16_t b4  = (number & 0b0000000000010000) << 2;
	const uint16_t b6  = (number & 0b0000000001000000) >> 1;
	const uint16_t b87 = (number & 0b0000000110000000) >> 4;
	const uint16_t b5  = (number & 0b0000000000100000) >> 3;
	mcode = (mcode & mask) | b9 | b4 | b6 | b87 | b5;
}

inline void setCI3imm(uint16_t& mcode, const int32_t number)
{
	//----------------------FEDCBA9876543210
	const uint16_t mask = 0b1110111110000011;
	//---------------------------------33222222222211111111110000000000
	//---------------------------------10987654321098765432109876543210
	const uint32_t b17   = (number & 0b00000000000000100000000000000000) >> 5;
	const uint32_t b1612 = (number & 0b00000000000000011111000000000000) >> 10;
	mcode = (mcode & mask) | static_cast<uint16_t>(b17 | b1612);
}

inline void setCJimm(uint16_t& mcode, const int16_t number)
{
	//----------------------FEDCBA9876543210
	const uint16_t mask = 0b1110000000000011;
	//-------------------------------FEDCBA9876543210
	const uint16_t b11 = (number & 0b0000100000000000) << 1;
	const uint16_t b4  = (number & 0b0000000000010000) << 7;
	const uint16_t b98 = (number & 0b0000001100000000) << 1;
	const uint16_t b10 = (number & 0b0000010000000000) >> 2;
	const uint16_t b6  = (number & 0b0000000001000000) << 1;
	const uint16_t b7  = (number & 0b0000000010000000) >> 1;
	const uint16_t b31 = (number & 0b0000000000001110) << 2;
	const uint16_t b5  = (number & 0b0000000000100000) >> 3;
	mcode = (mcode & mask) | b11 | b4 | b98 | b10 | b6 | b7 | b31 | b5;
}

}  // namespace riscv

#endif	// ENCODER_H
#ifndef DECODER_H
#define DECODER_H

#include <stdint.h>
#include "types.h"

namespace riscv {

inline uint32_t getRd(const uint32_t mcode)
{
	return (mcode >> 7) & 0b11111;
}

inline uint32_t getRs1(const uint32_t mcode)
{
	return (mcode >> 15) & 0b11111;
}

inline uint32_t getRs2(const uint32_t mcode)
{
	return (mcode >> 20) & 0b00011111;
}

inline uint8_t getFunct3(const uint32_t mcode)
{
	return (mcode >> 12) & 0b00000111;
}

inline uint8_t getFunct7(const uint32_t mcode)
{
	return (mcode >> 25) & 0b01111111;
}

inline uint8_t getShamt(const uint32_t mcode)
{
	return (mcode >> 20) & 0b00111111;
}

inline int32_t getIimm(const uint32_t mcode)
{
	return static_cast<int32_t>(mcode) >> 20;
}

inline int32_t getUimm(const uint32_t mcode)
{
	//--------------------------33222222222211111111110000000000
	//--------------------------10987654321098765432109876543210
	constexpr uint32_t mask = 0b11111111111111111111000000000000;
	return static_cast<int32_t>(mcode & mask);
}

inline int32_t getJimm(const uint32_t mcode)
{
	//--------------------------------33222222222211111111110000000000
	//--------------------------------10987654321098765432109876543210
	const uint32_t b20   = (mcode & 0b10000000000000000000000000000000);
	const uint32_t b101  = (mcode & 0b01111111111000000000000000000000) >> 9;
	const uint32_t b11   = (mcode & 0b00000000000100000000000000000000) << 2;
	const uint32_t b1912 = (mcode & 0b00000000000011111111000000000000) << 11;
	const int32_t  sign  = static_cast<int32_t>(b20 | b101 | b11 | b1912);
	return sign >> 11;
}

inline int32_t getBimm(const uint32_t mcode)
{
	//-------------------------------33222222222211111111110000000000
	//-------------------------------10987654321098765432109876543210
	const uint32_t b12  = (mcode & 0b10000000000000000000000000000000);
	const uint32_t b11  = (mcode & 0b00000000000000000000000010000000) << 23;
	const uint32_t b105 = (mcode & 0b01111110000000000000000000000000) >> 1;
	const uint32_t b41  = (mcode & 0b00000000000000000000111100000000) << 12;
	const int32_t  sign = static_cast<int32_t>(b12 | b11 | b105 | b41);
	return sign >> 19;
}

inline int32_t getSimm(const uint32_t mcode)
{
	//------------------------------33222222222211111111110000000000
	//------------------------------10987654321098765432109876543210
	const uint32_t b15 = (mcode & 0b11111110000000000000000000000000);
	const uint32_t b40 = (mcode & 0b00000000000000000000111110000000) << 13;
	const int32_t  sign = static_cast<int32_t>(b15 | b40);
	return sign >> 20;
}

inline uint32_t getC00Rdp(const uint16_t mcode)
{
	return ((mcode >> 2) & 0b111) + 8;
}

inline uint32_t getC00Rs1p(const uint32_t mcode)
{
	return ((mcode >> 7) & 0b111) + 8;
}

inline uint32_t getC00Rs2p(const uint32_t mcode)
{
	return ((mcode >> 2) & 0b111) + 8;
}

inline uint32_t getC01Rd(const uint32_t mcode)
{
	return ((mcode >> 7) & 0b11111);
}

inline uint32_t getC01Rdp(const uint32_t mcode)
{
	return ((mcode >> 7) & 0b111) + 8;
}

inline uint32_t getC01Rs1p(const uint32_t mcode)
{
	return ((mcode >> 7) & 0b111) + 8;
}

inline uint32_t getC01Rs1(const uint32_t mcode)
{
	return ((mcode >> 7) & 0b11111);
}

inline uint32_t getC10Rd(const uint32_t mcode)
{
	return ((mcode >> 7) & 0b11111);
}

inline uint32_t getC10Rs1(const uint32_t mcode)
{
	return ((mcode >> 7) & 0b11111);
}

inline uint32_t getC10Rs2(const uint32_t mcode)
{
	return ((mcode >> 2) & 0b11111);
}

inline uint32_t cfunct2(const uint32_t mcode)
{
	return ((mcode >> 5) & 0b11);
}

inline uint32_t cfunct3(const uint32_t mcode)
{
	return ((mcode >> 13) & 0b111);
}

inline uint32_t cfunct6(const uint32_t mcode)
{
	return ((mcode >> 10) & 0b111111);
}

inline uint32_t getCIWimm(const uint16_t mcode)
{
	//------------------------------FEDCBA9876543210
	const uint32_t b54 = (mcode & 0b0001100000000000) >> 7;
	const uint32_t b96 = (mcode & 0b0000011110000000) >> 1;
	const uint32_t b2  = (mcode & 0b0000000001000000) >> 4;
	const uint32_t b3  = (mcode & 0b0000000000100000) >> 2;
	return b54 | b96 | b2 | b3;
}

inline uint32_t getCL1uimm(const uint16_t mcode)
{
	//------------------------------FEDCBA9876543210
	const uint32_t b53 = (mcode & 0b0001110000000000) >> 7;
	const uint32_t b76 = (mcode & 0b0000000001100000) << 1;
	return b53 | b76;
}

inline uint32_t getCL2uimm(const uint16_t mcode)
{
	//------------------------------FEDCBA9876543210
	const uint32_t b54 = (mcode & 0b0001100000000000) >> 7;
	const uint32_t b8  = (mcode & 0b0000010000000000) >> 2;
	const uint32_t b76 = (mcode & 0b0000000001100000) << 1;
	return b54 | b8 | b76;
}

inline uint32_t getCL3uimm(const uint16_t mcode)
{
	//------------------------------FEDCBA9876543210
	const uint32_t b53 = (mcode & 0b0001110000000000) >> 7;
	const uint32_t b2  = (mcode & 0b0000000001000000) >> 4;
	const uint32_t b6  = (mcode & 0b0000000000100000) << 1;
	return b53 | b2 | b6;
}

inline int32_t getCI1imm(const uint16_t mcode)
{
	//------------------------------FEDCBA9876543210
	const uint32_t b5  = (mcode & 0b0001000000000000) << 19;
	const uint32_t b40 = (mcode & 0b0000000001111100) << 24;
	return static_cast<int32_t>(b5 | b40) >> 26;
}

inline int32_t getCI2imm(const uint16_t mcode)
{
	//------------------------------FEDCBA9876543210
	const uint32_t b9  = (mcode & 0b0001000000000000) << 19;
	const uint32_t b4  = (mcode & 0b0000000001000000) << 20;
	const uint32_t b6  = (mcode & 0b0000000000100000) << 23;
	const uint32_t b87 = (mcode & 0b0000000000011000) << 26;
	const uint32_t b5  = (mcode & 0b0000000000000100) << 25;
	return static_cast<int32_t>(b9| b4 | b6 | b87 | b5) >> 22;
}

inline int32_t getCI3imm(const uint16_t mcode)
{
	//--------------------------------FEDCBA9876543210
	const uint32_t b17   = (mcode & 0b0001000000000000) << 19;
	const uint32_t b1612 = (mcode & 0b0000000001111100) << 24;
	return static_cast<int32_t>(b17 | b1612) >> 14;
}

inline uint32_t getCI1uimm(const uint16_t mcode)
{
	//------------------------------FEDCBA9876543210
	const uint32_t b5  = (mcode & 0b0001000000000000) >> 7;
	const uint32_t b40 = (mcode & 0b0000000001111100) >> 2;
	return b5 | b40;
}

inline int32_t getCJimm(const uint16_t mcode)
{
	//------------------------------FEDCBA9876543210
	const uint32_t b11 = (mcode & 0b0001000000000000) << 19;
	const uint32_t b4  = (mcode & 0b0000100000000000) << 13;
	const uint32_t b98 = (mcode & 0b0000011000000000) << 19;
	const uint32_t b10 = (mcode & 0b0000000100000000) << 22;
	const uint32_t b6  = (mcode & 0b0000000010000000) << 19;
	const uint32_t b7  = (mcode & 0b0000000001000000) << 21;
	const uint32_t b31 = (mcode & 0b0000000000111000) << 18;
	const uint32_t b5  = (mcode & 0b0000000000000100) << 23;
	return static_cast<int32_t>(b11 | b4 | b98 | b10 | b6 | b7 | b31 | b5) >> 20;
}

inline int32_t getCBimm(const uint16_t mcode)
{
	//------------------------------FEDCBA9876543210
	const uint32_t b8  = (mcode & 0b0001000000000000) >> 4;
	const uint32_t b43 = (mcode & 0b0000110000000000) >> 7;
	const uint32_t b76 = (mcode & 0b0000000001100000) << 1;
	const uint32_t b21 = (mcode & 0b0000000000011000) >> 2;
	const uint32_t b5  = (mcode & 0b0000000000000100) << 3;
	uint32_t imm = (b8 | b43 | b76 | b21 | b5);
	if (b8 == 1)
		imm |= 0xFFFFFE00;
	return static_cast<int32_t>(imm);
}

inline uint32_t getUImmQ2_010(const uint16_t mcode)
{
	//------------------------------FEDCBA9876543210
	const uint32_t b5  = (mcode & 0b0001000000000000) >> 7;
	const uint32_t b42 = (mcode & 0b0000000001110000) >> 2;
	const uint32_t b76 = (mcode & 0b0000000000001100) << 4;
	const uint32_t uimm = b5 | b42 | b76;
	return uimm;
}

inline uint32_t getUImmQ2_110(const uint16_t mcode)
{
	//------------------------------FEDCBA9876543210
	const uint32_t b52 = (mcode & 0b0001111000000000) >> 7;
	const uint32_t b76 = (mcode & 0b0000000110000000) >> 1;
	const uint32_t uimm = b52 | b76;
	return uimm;
}

}  // namespace riscv

#endif	// DECODER_H
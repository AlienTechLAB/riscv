//-----------------------------------------------------------------------------------------------------
// Documentation: "The RISC-V Instruction Set Manual, Volume I: User-Level ISA, Document Version 2.2"
// Chapter 20, "RISC-V Assembly Programmer’s Handbook"
// Table 20.1: "Assembler mnemonics for RISC-V integer and floating-point registers.", page 109.
//-----------------------------------------------------------------------------------------------------

#ifndef REGFILE32I_H
#define REGFILE32I_H

#include <stdint.h>

struct RegFile32I
{
    //-----------------------------------------------------------------------------------------------------
    //             Register               ABI Name                      Description
    //-----------------------------------------------------------------------------------------------------
    const uint32_t x0{0}; const uint32_t& zero{x0};                  // Hard-wired zero
          uint32_t x1{0};       uint32_t& ra{x1};                    // Return address
          uint32_t x2{0};       uint32_t& sp{x2};                    // Stack pointer
          uint32_t x3{0};       uint32_t& gp{x3};                    // Global pointer
          uint32_t x4{0};       uint32_t& tp{x4};                    // Thread pointer
          uint32_t x5{0};       uint32_t& t0{x5};                    // Temporary / alternate link register
          uint32_t x6{0};       uint32_t& t1{x6};                    // Temporaries
          uint32_t x7{0};       uint32_t& t2{x7};                    // Temporaries
          uint32_t x8{0};       uint32_t& s0{x8}; uint32_t& fp{x8};  // Saved register / frame pointer
          uint32_t x9{0};       uint32_t& s1{x9};                    // Saved register
          uint32_t x10{0};      uint32_t& a0{x10};                   // Function arguments / return values
          uint32_t x11{0};      uint32_t& a1{x11};                   // Function arguments / return values
          uint32_t x12{0};      uint32_t& a2{x12};                   // Function arguments
          uint32_t x13{0};      uint32_t& a3{x13};                   // Function arguments
          uint32_t x14{0};      uint32_t& a4{x14};                   // Function arguments
          uint32_t x15{0};      uint32_t& a5{x15};                   // Function arguments
          uint32_t x16{0};      uint32_t& a6{x16};                   // Function arguments
          uint32_t x17{0};      uint32_t& a7{x17};                   // Function arguments
          uint32_t x18{0};      uint32_t& s2{x18};                   // Saved registers
          uint32_t x19{0};      uint32_t& s3{x19};                   // Saved registers
          uint32_t x20{0};      uint32_t& s4{x20};                   // Saved registers
          uint32_t x21{0};      uint32_t& s5{x21};                   // Saved registers
          uint32_t x22{0};      uint32_t& s6{x22};                   // Saved registers
          uint32_t x23{0};      uint32_t& s7{x23};                   // Saved registers
          uint32_t x24{0};      uint32_t& s8{x24};                   // Saved registers
          uint32_t x25{0};      uint32_t& s9{x25};                   // Saved registers
          uint32_t x26{0};      uint32_t& s10{x26};                  // Saved registers
          uint32_t x27{0};      uint32_t& s11{x27};                  // Saved registers
          uint32_t x28{0};      uint32_t& t3{x28};                   // Temporaries
          uint32_t x29{0};      uint32_t& t4{x29};                   // Temporaries
          uint32_t x30{0};      uint32_t& t5{x30};                   // Temporaries
          uint32_t x31{0};      uint32_t& t6{x31};                   // Temporaries

          uint32_t pc{0};                                            // Program Counter
};

#endif // REGFILE32I_H
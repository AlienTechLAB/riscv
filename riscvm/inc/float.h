#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

struct FloatRegisters
{
          float    f0{0.0f};    float&    ft0{f0};                   // FP temporaries
          float    f1{0.0f};    float&    ft1{f1};                   // FP temporaries
          float    f2{0.0f};    float&    ft2{f2};                   // FP temporaries
          float    f3{0.0f};    float&    ft3{f3};                   // FP temporaries
          float    f4{0.0f};    float&    ft4{f4};                   // FP temporaries
          float    f5{0.0f};    float&    ft5{f5};                   // FP temporaries
          float    f6{0.0f};    float&    ft6{f6};                   // FP temporaries
          float    f7{0.0f};    float&    ft7{f7};                   // FP temporaries
          float    f8{0.0f};    float&    fs0{f8};                   // FP saved registers
          float    f9{0.0f};    float&    fs1{f9};                   // FP saved registers
          float    f10{0.0f};   float&    fa0{f10};                  // FP arguments / return values
          float    f11{0.0f};   float&    fa1{f11};                  // FP arguments / return values
          float    f12{0.0f};   float&    fa2{f12};                  // FP arguments
          float    f13{0.0f};   float&    fa3{f13};                  // FP arguments
          float    f14{0.0f};   float&    fa4{f14};                  // FP arguments
          float    f15{0.0f};   float&    fa5{f15};                  // FP arguments
          float    f16{0.0f};   float&    fa6{f16};                  // FP arguments
          float    f17{0.0f};   float&    fa7{f17};                  // FP arguments
          float    f18{0.0f};   float&    fs2{f18};                  // FP saved registers
          float    f19{0.0f};   float&    fs3{f19};                  // FP saved registers
          float    f20{0.0f};   float&    fs4{f20};                  // FP saved registers
          float    f21{0.0f};   float&    fs5{f21};                  // FP saved registers
          float    f22{0.0f};   float&    fs6{f22};                  // FP saved registers
          float    f23{0.0f};   float&    fs7{f23};                  // FP saved registers
          float    f24{0.0f};   float&    fs8{f24};                  // FP saved registers
          float    f25{0.0f};   float&    fs9{f25};                  // FP saved registers
          float    f26{0.0f};   float&    fs10{f26};                 // FP saved registers
          float    f27{0.0f};   float&    fs11{f27};                 // FP saved registers
          float    f28{0.0f};   float&    ft8{f28};                  // FP temporaries
          float    f29{0.0f};   float&    ft9{f29};                  // FP temporaries
          float    f30{0.0f};   float&    ft10{f30};                 // FP temporaries
          float    f31{0.0f};   float&    ft11{f31};                 // FP temporaries

          uint32_t pc{0};                                            // Program Counter
};
#endif // REGISTERS_H
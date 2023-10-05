#ifndef DECODERTESTS_H
#define DECODERTESTS_H

#include <stdint.h>
#include "riscv.h"
//#include "decoder.h" TODO

using namespace riscv;

namespace tests {

void decode_illegal_reserved_test();

void getUimm549623Test();
void setUimm549623Test();
void brutTestUimm549623();

void getUimm5376Test();
void setUimm5376Test();
void brutTestUimm5376();

void getUimm54876Test();
void setUimm54876Test();
void brutUimm54876Test();

void getUimm5326Test();
void setUimm5326Test();
void brutUimm5326Test();

void getImm540Test();
void setImm540Test();
void brutImm540Test();

void getUimm540Test();
void setUimm540Test();
void brutTestUimm540();

void getImm114981067315Test();
void setImm114981067315Test();
void brutImm114981067315Test();

void getImm946875Test();
void setImm946875Test();
void brutImm946875();

void getImm171612Test();
void setImm171612Test();
void brutImm171612();

void get_put_tests();
void run_decode_tests();
void csrli_tests();

}  // namespace tests

#endif	// DECODERTESTS_H
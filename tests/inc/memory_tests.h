#ifndef MEMORYTESTS_H
#define MEMORYTESTS_H

#include <stdint.h>
#include "riscv.h"
#include "types.h"

using namespace riscv;

namespace tests {

void rdwr8Test();
void rdwr16Test(endian_t endian);
void rdwr32Test(endian_t endian);
void rdwr64Test(endian_t endian);
void readWriteTests();
void littleEndianInt16Test();
void littleEndianUint16Test();
void bigEndianInt16Test();
void bigEndianUint16Test();
void littleEndianInt32Test();
void littleEndianUint32Test();
void bigEndianInt32Test();
void bigEndianUint32Test();
void littleEndianInt64Test();
void littleEndianUint64Test();
void bigEndianInt64Test();
void bigEndianUint64Test();
void endianTests();

}  // namespace tests

#endif	// MEMORYTESTS_H
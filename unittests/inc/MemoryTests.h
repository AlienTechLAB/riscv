#ifndef MEMORYTESTS_H
#define MEMORYTESTS_H

#include <stdint.h>
#include "Riscv.h"

void rdwr8Test();
void rdwr16Test(const Endian endian);
void rdwr32Test(const Endian endian);
void rdwr64Test(const Endian endian);
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

#endif // MEMORYTESTS_H
/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-as -march=rv64gc -o HelloAsm.o HelloAsm.s
/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-ld -o bin/HelloAsm HelloAsm.o
/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-objdump -S --disassemble bin/HelloAsm > HelloAsm.dump.s
rm HelloAsm.o
# https://gcc.gnu.org/onlinedocs/gcc/RISC-V-Options.html
/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-g++ -o bin/HelloCpp HelloCpp.cpp
/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-g++ -S -o HelloCpp.s HelloCpp.cpp
/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-objdump -S --disassemble bin/HelloCpp > HelloCpp.dump.s



# TROUBLE SHOOTING:
# "HelloAsm.s:5: Error: unrecognized opcode `c.addi4spn a0,sp,8', extension `c' required" -> -march=rv64gc

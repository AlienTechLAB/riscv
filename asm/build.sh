/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-as -march=rv32i -o HelloAsm.o HelloAsm.s
/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-objcopy -O binary HelloAsm.o HelloAsm.bin
/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-objdump -D -b binary -m riscv:rv32 HelloAsm.bin > HelloAsm.dis

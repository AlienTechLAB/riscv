/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-as -o HelloWorld.o HelloWorld.s
/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-ld -o HelloWorld HelloWorld.o
/home/alien/Desktop/RISC-V/asm/toolchain/bin/riscv64-unknown-elf-objcopy -O binary HelloWorld HelloWorld.bin
rm HelloWorld HelloWorld.o

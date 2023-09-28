.text
.global _start

_start:
    lui  a0,%hi(0xFFC00)
    addi a0,a0,%lo(0xFFC00)
    add  a1,x0,a0
    addi a1,a1,1
    lui  a2,%hi(message)
    addi a2,a2,%lo(message)

copy_loop:
    lb a3,0(a2)
    sb a3,0(a1)
    addi a1,a1,1
    addi a2,a2,1
    beq  a3,x0,copy_done
    j copy_loop 

copy_done:
    addi x1,x0,1
    sb x1,0(a0)
    j _start

.data
message:
    .string "Hello, World!"

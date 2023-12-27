.text
.global _start

_start:
    li t0, 0x0000FF00
_screen:
    li t1, 0x100000
    li t2, 1024 * 786
fill_loop:
    sw t0, 0(t1)
    addi t1, t1, 4
    addi t2, t2, -1
    bnez t2, fill_loop
    addi t0, t0, 1
    j _screen

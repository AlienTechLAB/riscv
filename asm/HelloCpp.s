	.file	"HelloCpp.cpp"
	.option nopic
	.attribute arch, "rv64i2p1_m2p0_a2p1_f2p2_d2p2_c2p0_zicsr2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.rodata
	.align	3
.LC0:
	.string	"Hello C++"
	.string	""
	.text
	.align	1
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	addi	sp,sp,-48
	.cfi_def_cfa_offset 48
	sd	s0,40(sp)
	.cfi_offset 8, -8
	addi	s0,sp,48
	.cfi_def_cfa 8, 0
	li	a5,1048576
	addi	a5,a5,-1024
	sd	a5,-32(s0)
	lui	a5,%hi(.LC0)
	addi	a5,a5,%lo(.LC0)
	sd	a5,-40(s0)
.L4:
	sw	zero,-20(s0)
	j	.L2
.L3:
	ld	a4,-40(s0)
	lw	a5,-20(s0)
	addiw	a3,a5,1
	sw	a3,-20(s0)
	add	a4,a4,a5
	lw	a5,-20(s0)
	addi	a5,a5,1
	ld	a3,-32(s0)
	add	a5,a3,a5
	lbu	a4,0(a4)
	sb	a4,0(a5)
.L2:
	lw	a5,-20(s0)
	ld	a4,-40(s0)
	add	a5,a4,a5
	lbu	a5,0(a5)
	bne	a5,zero,.L3
	ld	a5,-32(s0)
	sb	zero,0(a5)
	j	.L4
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (g2ee5e430018) 12.2.0"

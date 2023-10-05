
bin/HelloAsm:     file format elf64-littleriscv


Disassembly of section .text:

00000000000100e8 <_start>:
   100e8:	00100537          	lui	a0,0x100
   100ec:	c0050513          	add	a0,a0,-1024 # ffc00 <__global_pointer$+0xee2ee>
   100f0:	85aa                	mv	a1,a0
   100f2:	0585                	add	a1,a1,1
   100f4:	6645                	lui	a2,0x11
   100f6:	11260613          	add	a2,a2,274 # 11112 <__DATA_BEGIN__>

00000000000100fa <copy_loop>:
   100fa:	00060683          	lb	a3,0(a2)
   100fe:	00d58023          	sb	a3,0(a1)
   10102:	0585                	add	a1,a1,1
   10104:	0605                	add	a2,a2,1
   10106:	c291                	beqz	a3,1010a <copy_done>
   10108:	bfcd                	j	100fa <copy_loop>

000000000001010a <copy_done>:
   1010a:	4085                	li	ra,1
   1010c:	00150023          	sb	ra,0(a0)
   10110:	bfe1                	j	100e8 <_start>

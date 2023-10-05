
bin/HelloCpp:     file format elf64-littleriscv


Disassembly of section .text:

00000000000100e8 <exit>:
   100e8:	1141                	add	sp,sp,-16
   100ea:	4581                	li	a1,0
   100ec:	e022                	sd	s0,0(sp)
   100ee:	e406                	sd	ra,8(sp)
   100f0:	842a                	mv	s0,a0
   100f2:	220000ef          	jal	10312 <__call_exitprocs>
   100f6:	f481b503          	ld	a0,-184(gp) # 11c58 <_global_impure_ptr>
   100fa:	6d3c                	ld	a5,88(a0)
   100fc:	c391                	beqz	a5,10100 <exit+0x18>
   100fe:	9782                	jalr	a5
   10100:	8522                	mv	a0,s0
   10102:	386000ef          	jal	10488 <_exit>

0000000000010106 <register_fini>:
   10106:	00000793          	li	a5,0
   1010a:	c789                	beqz	a5,10114 <register_fini+0xe>
   1010c:	6541                	lui	a0,0x10
   1010e:	3d450513          	add	a0,a0,980 # 103d4 <__libc_fini_array>
   10112:	acdd                	j	10408 <atexit>
   10114:	8082                	ret

0000000000010116 <_start>:
   10116:	00002197          	auipc	gp,0x2
   1011a:	bfa18193          	add	gp,gp,-1030 # 11d10 <__global_pointer$>
   1011e:	f6018513          	add	a0,gp,-160 # 11c70 <completed.1>
   10122:	f9818613          	add	a2,gp,-104 # 11ca8 <__BSS_END__>
   10126:	8e09                	sub	a2,a2,a0
   10128:	4581                	li	a1,0
   1012a:	13e000ef          	jal	10268 <memset>
   1012e:	00000517          	auipc	a0,0x0
   10132:	2da50513          	add	a0,a0,730 # 10408 <atexit>
   10136:	c519                	beqz	a0,10144 <_start+0x2e>
   10138:	00000517          	auipc	a0,0x0
   1013c:	29c50513          	add	a0,a0,668 # 103d4 <__libc_fini_array>
   10140:	2c8000ef          	jal	10408 <atexit>
   10144:	0ba000ef          	jal	101fe <__libc_init_array>
   10148:	4502                	lw	a0,0(sp)
   1014a:	002c                	add	a1,sp,8
   1014c:	4601                	li	a2,0
   1014e:	04e000ef          	jal	1019c <main>
   10152:	bf59                	j	100e8 <exit>

0000000000010154 <__do_global_dtors_aux>:
   10154:	1141                	add	sp,sp,-16
   10156:	e022                	sd	s0,0(sp)
   10158:	f601c783          	lbu	a5,-160(gp) # 11c70 <completed.1>
   1015c:	e406                	sd	ra,8(sp)
   1015e:	ef91                	bnez	a5,1017a <__do_global_dtors_aux+0x26>
   10160:	00000793          	li	a5,0
   10164:	cb81                	beqz	a5,10174 <__do_global_dtors_aux+0x20>
   10166:	6545                	lui	a0,0x11
   10168:	4c050513          	add	a0,a0,1216 # 114c0 <__EH_FRAME_BEGIN__>
   1016c:	00000097          	auipc	ra,0x0
   10170:	000000e7          	jalr	zero # 0 <exit-0x100e8>
   10174:	4785                	li	a5,1
   10176:	f6f18023          	sb	a5,-160(gp) # 11c70 <completed.1>
   1017a:	60a2                	ld	ra,8(sp)
   1017c:	6402                	ld	s0,0(sp)
   1017e:	0141                	add	sp,sp,16
   10180:	8082                	ret

0000000000010182 <frame_dummy>:
   10182:	00000793          	li	a5,0
   10186:	cb91                	beqz	a5,1019a <frame_dummy+0x18>
   10188:	6545                	lui	a0,0x11
   1018a:	f6818593          	add	a1,gp,-152 # 11c78 <object.0>
   1018e:	4c050513          	add	a0,a0,1216 # 114c0 <__EH_FRAME_BEGIN__>
   10192:	00000317          	auipc	t1,0x0
   10196:	00000067          	jr	zero # 0 <exit-0x100e8>
   1019a:	8082                	ret

000000000001019c <main>:
   1019c:	7179                	add	sp,sp,-48
   1019e:	f422                	sd	s0,40(sp)
   101a0:	1800                	add	s0,sp,48
   101a2:	001007b7          	lui	a5,0x100
   101a6:	c0078793          	add	a5,a5,-1024 # ffc00 <__global_pointer$+0xedef0>
   101aa:	fef43023          	sd	a5,-32(s0)
   101ae:	67c1                	lui	a5,0x10
   101b0:	4b078793          	add	a5,a5,1200 # 104b0 <__errno+0x6>
   101b4:	fcf43c23          	sd	a5,-40(s0)
   101b8:	fe042623          	sw	zero,-20(s0)
   101bc:	a025                	j	101e4 <main+0x48>
   101be:	fd843703          	ld	a4,-40(s0)
   101c2:	fec42783          	lw	a5,-20(s0)
   101c6:	0017869b          	addw	a3,a5,1
   101ca:	fed42623          	sw	a3,-20(s0)
   101ce:	973e                	add	a4,a4,a5
   101d0:	fec42783          	lw	a5,-20(s0)
   101d4:	0785                	add	a5,a5,1
   101d6:	fe043683          	ld	a3,-32(s0)
   101da:	97b6                	add	a5,a5,a3
   101dc:	00074703          	lbu	a4,0(a4)
   101e0:	00e78023          	sb	a4,0(a5)
   101e4:	fec42783          	lw	a5,-20(s0)
   101e8:	fd843703          	ld	a4,-40(s0)
   101ec:	97ba                	add	a5,a5,a4
   101ee:	0007c783          	lbu	a5,0(a5)
   101f2:	f7f1                	bnez	a5,101be <main+0x22>
   101f4:	fe043783          	ld	a5,-32(s0)
   101f8:	00078023          	sb	zero,0(a5)
   101fc:	bf75                	j	101b8 <main+0x1c>

00000000000101fe <__libc_init_array>:
   101fe:	1101                	add	sp,sp,-32
   10200:	e822                	sd	s0,16(sp)
   10202:	67c5                	lui	a5,0x11
   10204:	6445                	lui	s0,0x11
   10206:	e04a                	sd	s2,0(sp)
   10208:	4f478793          	add	a5,a5,1268 # 114f4 <__preinit_array_end>
   1020c:	4f440713          	add	a4,s0,1268 # 114f4 <__preinit_array_end>
   10210:	ec06                	sd	ra,24(sp)
   10212:	e426                	sd	s1,8(sp)
   10214:	40e78933          	sub	s2,a5,a4
   10218:	00e78d63          	beq	a5,a4,10232 <__libc_init_array+0x34>
   1021c:	40395913          	sra	s2,s2,0x3
   10220:	4f440413          	add	s0,s0,1268
   10224:	4481                	li	s1,0
   10226:	601c                	ld	a5,0(s0)
   10228:	0485                	add	s1,s1,1
   1022a:	0421                	add	s0,s0,8
   1022c:	9782                	jalr	a5
   1022e:	ff24ece3          	bltu	s1,s2,10226 <__libc_init_array+0x28>
   10232:	6445                	lui	s0,0x11
   10234:	67c5                	lui	a5,0x11
   10236:	50878793          	add	a5,a5,1288 # 11508 <__do_global_dtors_aux_fini_array_entry>
   1023a:	4f840713          	add	a4,s0,1272 # 114f8 <__init_array_start>
   1023e:	40e78933          	sub	s2,a5,a4
   10242:	40395913          	sra	s2,s2,0x3
   10246:	00e78b63          	beq	a5,a4,1025c <__libc_init_array+0x5e>
   1024a:	4f840413          	add	s0,s0,1272
   1024e:	4481                	li	s1,0
   10250:	601c                	ld	a5,0(s0)
   10252:	0485                	add	s1,s1,1
   10254:	0421                	add	s0,s0,8
   10256:	9782                	jalr	a5
   10258:	ff24ece3          	bltu	s1,s2,10250 <__libc_init_array+0x52>
   1025c:	60e2                	ld	ra,24(sp)
   1025e:	6442                	ld	s0,16(sp)
   10260:	64a2                	ld	s1,8(sp)
   10262:	6902                	ld	s2,0(sp)
   10264:	6105                	add	sp,sp,32
   10266:	8082                	ret

0000000000010268 <memset>:
   10268:	433d                	li	t1,15
   1026a:	872a                	mv	a4,a0
   1026c:	02c37163          	bgeu	t1,a2,1028e <memset+0x26>
   10270:	00f77793          	and	a5,a4,15
   10274:	e3c1                	bnez	a5,102f4 <memset+0x8c>
   10276:	e1bd                	bnez	a1,102dc <memset+0x74>
   10278:	ff067693          	and	a3,a2,-16
   1027c:	8a3d                	and	a2,a2,15
   1027e:	96ba                	add	a3,a3,a4
   10280:	e30c                	sd	a1,0(a4)
   10282:	e70c                	sd	a1,8(a4)
   10284:	0741                	add	a4,a4,16
   10286:	fed76de3          	bltu	a4,a3,10280 <memset+0x18>
   1028a:	e211                	bnez	a2,1028e <memset+0x26>
   1028c:	8082                	ret
   1028e:	40c306b3          	sub	a3,t1,a2
   10292:	068a                	sll	a3,a3,0x2
   10294:	00000297          	auipc	t0,0x0
   10298:	9696                	add	a3,a3,t0
   1029a:	00a68067          	jr	10(a3)
   1029e:	00b70723          	sb	a1,14(a4)
   102a2:	00b706a3          	sb	a1,13(a4)
   102a6:	00b70623          	sb	a1,12(a4)
   102aa:	00b705a3          	sb	a1,11(a4)
   102ae:	00b70523          	sb	a1,10(a4)
   102b2:	00b704a3          	sb	a1,9(a4)
   102b6:	00b70423          	sb	a1,8(a4)
   102ba:	00b703a3          	sb	a1,7(a4)
   102be:	00b70323          	sb	a1,6(a4)
   102c2:	00b702a3          	sb	a1,5(a4)
   102c6:	00b70223          	sb	a1,4(a4)
   102ca:	00b701a3          	sb	a1,3(a4)
   102ce:	00b70123          	sb	a1,2(a4)
   102d2:	00b700a3          	sb	a1,1(a4)
   102d6:	00b70023          	sb	a1,0(a4)
   102da:	8082                	ret
   102dc:	0ff5f593          	zext.b	a1,a1
   102e0:	00859693          	sll	a3,a1,0x8
   102e4:	8dd5                	or	a1,a1,a3
   102e6:	01059693          	sll	a3,a1,0x10
   102ea:	8dd5                	or	a1,a1,a3
   102ec:	02059693          	sll	a3,a1,0x20
   102f0:	8dd5                	or	a1,a1,a3
   102f2:	b759                	j	10278 <memset+0x10>
   102f4:	00279693          	sll	a3,a5,0x2
   102f8:	00000297          	auipc	t0,0x0
   102fc:	9696                	add	a3,a3,t0
   102fe:	8286                	mv	t0,ra
   10300:	fa2680e7          	jalr	-94(a3)
   10304:	8096                	mv	ra,t0
   10306:	17c1                	add	a5,a5,-16
   10308:	8f1d                	sub	a4,a4,a5
   1030a:	963e                	add	a2,a2,a5
   1030c:	f8c371e3          	bgeu	t1,a2,1028e <memset+0x26>
   10310:	b79d                	j	10276 <memset+0xe>

0000000000010312 <__call_exitprocs>:
   10312:	715d                	add	sp,sp,-80
   10314:	f052                	sd	s4,32(sp)
   10316:	f481ba03          	ld	s4,-184(gp) # 11c58 <_global_impure_ptr>
   1031a:	f84a                	sd	s2,48(sp)
   1031c:	e486                	sd	ra,72(sp)
   1031e:	1f8a3903          	ld	s2,504(s4)
   10322:	e0a2                	sd	s0,64(sp)
   10324:	fc26                	sd	s1,56(sp)
   10326:	f44e                	sd	s3,40(sp)
   10328:	ec56                	sd	s5,24(sp)
   1032a:	e85a                	sd	s6,16(sp)
   1032c:	e45e                	sd	s7,8(sp)
   1032e:	e062                	sd	s8,0(sp)
   10330:	02090863          	beqz	s2,10360 <__call_exitprocs+0x4e>
   10334:	8b2a                	mv	s6,a0
   10336:	8bae                	mv	s7,a1
   10338:	4a85                	li	s5,1
   1033a:	59fd                	li	s3,-1
   1033c:	00892483          	lw	s1,8(s2)
   10340:	fff4841b          	addw	s0,s1,-1
   10344:	00044e63          	bltz	s0,10360 <__call_exitprocs+0x4e>
   10348:	048e                	sll	s1,s1,0x3
   1034a:	94ca                	add	s1,s1,s2
   1034c:	020b8663          	beqz	s7,10378 <__call_exitprocs+0x66>
   10350:	2084b783          	ld	a5,520(s1)
   10354:	03778263          	beq	a5,s7,10378 <__call_exitprocs+0x66>
   10358:	347d                	addw	s0,s0,-1
   1035a:	14e1                	add	s1,s1,-8
   1035c:	ff3418e3          	bne	s0,s3,1034c <__call_exitprocs+0x3a>
   10360:	60a6                	ld	ra,72(sp)
   10362:	6406                	ld	s0,64(sp)
   10364:	74e2                	ld	s1,56(sp)
   10366:	7942                	ld	s2,48(sp)
   10368:	79a2                	ld	s3,40(sp)
   1036a:	7a02                	ld	s4,32(sp)
   1036c:	6ae2                	ld	s5,24(sp)
   1036e:	6b42                	ld	s6,16(sp)
   10370:	6ba2                	ld	s7,8(sp)
   10372:	6c02                	ld	s8,0(sp)
   10374:	6161                	add	sp,sp,80
   10376:	8082                	ret
   10378:	00892783          	lw	a5,8(s2)
   1037c:	6498                	ld	a4,8(s1)
   1037e:	37fd                	addw	a5,a5,-1
   10380:	04878463          	beq	a5,s0,103c8 <__call_exitprocs+0xb6>
   10384:	0004b423          	sd	zero,8(s1)
   10388:	db61                	beqz	a4,10358 <__call_exitprocs+0x46>
   1038a:	31092783          	lw	a5,784(s2)
   1038e:	008a96bb          	sllw	a3,s5,s0
   10392:	00892c03          	lw	s8,8(s2)
   10396:	8ff5                	and	a5,a5,a3
   10398:	2781                	sext.w	a5,a5
   1039a:	ef89                	bnez	a5,103b4 <__call_exitprocs+0xa2>
   1039c:	9702                	jalr	a4
   1039e:	00892703          	lw	a4,8(s2)
   103a2:	1f8a3783          	ld	a5,504(s4)
   103a6:	01871463          	bne	a4,s8,103ae <__call_exitprocs+0x9c>
   103aa:	fb2787e3          	beq	a5,s2,10358 <__call_exitprocs+0x46>
   103ae:	dbcd                	beqz	a5,10360 <__call_exitprocs+0x4e>
   103b0:	893e                	mv	s2,a5
   103b2:	b769                	j	1033c <__call_exitprocs+0x2a>
   103b4:	31492783          	lw	a5,788(s2)
   103b8:	1084b583          	ld	a1,264(s1)
   103bc:	8ff5                	and	a5,a5,a3
   103be:	2781                	sext.w	a5,a5
   103c0:	e799                	bnez	a5,103ce <__call_exitprocs+0xbc>
   103c2:	855a                	mv	a0,s6
   103c4:	9702                	jalr	a4
   103c6:	bfe1                	j	1039e <__call_exitprocs+0x8c>
   103c8:	00892423          	sw	s0,8(s2)
   103cc:	bf75                	j	10388 <__call_exitprocs+0x76>
   103ce:	852e                	mv	a0,a1
   103d0:	9702                	jalr	a4
   103d2:	b7f1                	j	1039e <__call_exitprocs+0x8c>

00000000000103d4 <__libc_fini_array>:
   103d4:	1101                	add	sp,sp,-32
   103d6:	e822                	sd	s0,16(sp)
   103d8:	67c5                	lui	a5,0x11
   103da:	6445                	lui	s0,0x11
   103dc:	50878793          	add	a5,a5,1288 # 11508 <__do_global_dtors_aux_fini_array_entry>
   103e0:	51040413          	add	s0,s0,1296 # 11510 <impure_data>
   103e4:	8c1d                	sub	s0,s0,a5
   103e6:	e426                	sd	s1,8(sp)
   103e8:	ec06                	sd	ra,24(sp)
   103ea:	40345493          	sra	s1,s0,0x3
   103ee:	c881                	beqz	s1,103fe <__libc_fini_array+0x2a>
   103f0:	1461                	add	s0,s0,-8
   103f2:	943e                	add	s0,s0,a5
   103f4:	601c                	ld	a5,0(s0)
   103f6:	14fd                	add	s1,s1,-1
   103f8:	1461                	add	s0,s0,-8
   103fa:	9782                	jalr	a5
   103fc:	fce5                	bnez	s1,103f4 <__libc_fini_array+0x20>
   103fe:	60e2                	ld	ra,24(sp)
   10400:	6442                	ld	s0,16(sp)
   10402:	64a2                	ld	s1,8(sp)
   10404:	6105                	add	sp,sp,32
   10406:	8082                	ret

0000000000010408 <atexit>:
   10408:	85aa                	mv	a1,a0
   1040a:	4681                	li	a3,0
   1040c:	4601                	li	a2,0
   1040e:	4501                	li	a0,0
   10410:	a009                	j	10412 <__register_exitproc>

0000000000010412 <__register_exitproc>:
   10412:	f481b703          	ld	a4,-184(gp) # 11c58 <_global_impure_ptr>
   10416:	1f873783          	ld	a5,504(a4)
   1041a:	c3b1                	beqz	a5,1045e <__register_exitproc+0x4c>
   1041c:	4798                	lw	a4,8(a5)
   1041e:	487d                	li	a6,31
   10420:	06e84263          	blt	a6,a4,10484 <__register_exitproc+0x72>
   10424:	c505                	beqz	a0,1044c <__register_exitproc+0x3a>
   10426:	00371813          	sll	a6,a4,0x3
   1042a:	983e                	add	a6,a6,a5
   1042c:	10c83823          	sd	a2,272(a6)
   10430:	3107a883          	lw	a7,784(a5)
   10434:	4605                	li	a2,1
   10436:	00e6163b          	sllw	a2,a2,a4
   1043a:	00c8e8b3          	or	a7,a7,a2
   1043e:	3117a823          	sw	a7,784(a5)
   10442:	20d83823          	sd	a3,528(a6)
   10446:	4689                	li	a3,2
   10448:	02d50063          	beq	a0,a3,10468 <__register_exitproc+0x56>
   1044c:	00270693          	add	a3,a4,2
   10450:	068e                	sll	a3,a3,0x3
   10452:	2705                	addw	a4,a4,1
   10454:	c798                	sw	a4,8(a5)
   10456:	97b6                	add	a5,a5,a3
   10458:	e38c                	sd	a1,0(a5)
   1045a:	4501                	li	a0,0
   1045c:	8082                	ret
   1045e:	20070793          	add	a5,a4,512
   10462:	1ef73c23          	sd	a5,504(a4)
   10466:	bf5d                	j	1041c <__register_exitproc+0xa>
   10468:	3147a683          	lw	a3,788(a5)
   1046c:	4501                	li	a0,0
   1046e:	8ed1                	or	a3,a3,a2
   10470:	30d7aa23          	sw	a3,788(a5)
   10474:	00270693          	add	a3,a4,2
   10478:	068e                	sll	a3,a3,0x3
   1047a:	2705                	addw	a4,a4,1
   1047c:	c798                	sw	a4,8(a5)
   1047e:	97b6                	add	a5,a5,a3
   10480:	e38c                	sd	a1,0(a5)
   10482:	8082                	ret
   10484:	557d                	li	a0,-1
   10486:	8082                	ret

0000000000010488 <_exit>:
   10488:	05d00893          	li	a7,93
   1048c:	00000073          	ecall
   10490:	00054363          	bltz	a0,10496 <_exit+0xe>
   10494:	a001                	j	10494 <_exit+0xc>
   10496:	1141                	add	sp,sp,-16
   10498:	e022                	sd	s0,0(sp)
   1049a:	842a                	mv	s0,a0
   1049c:	e406                	sd	ra,8(sp)
   1049e:	4080043b          	negw	s0,s0
   104a2:	008000ef          	jal	104aa <__errno>
   104a6:	c100                	sw	s0,0(a0)
   104a8:	a001                	j	104a8 <_exit+0x20>

00000000000104aa <__errno>:
   104aa:	f581b503          	ld	a0,-168(gp) # 11c68 <_impure_ptr>
   104ae:	8082                	ret

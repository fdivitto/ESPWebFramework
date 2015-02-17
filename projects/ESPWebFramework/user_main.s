	.file	"user_main.cpp"
	.text
.Ltext0:
	.section	.irom0.text,"axG",@progbits,_ZN3fdv4Task5entryEPv,comdat
	.literal_position
	.align	4
	.weak	_ZN3fdv4Task5entryEPv
	.type	_ZN3fdv4Task5entryEPv, @function
_ZN3fdv4Task5entryEPv:
.LFB74:
	.file 1 "src/fdvtask.h"
	.loc 1 80 0
.LVL0:
	.loc 1 82 0
	l32i.n	a3, a2, 0
	.loc 1 80 0
	addi	sp, sp, -16
.LCFI0:
	.loc 1 82 0
	l32i.n	a3, a3, 0
	.loc 1 80 0
	s32i.n	a0, sp, 12
	.loc 1 82 0
	callx0	a3
.LVL1:
	.loc 1 83 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
.LCFI1:
	ret.n
.LFE74:
	.size	_ZN3fdv4Task5entryEPv, .-_ZN3fdv4Task5entryEPv
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align	4
.LC5:
	.string	""
	.section	.irom0.text,"axG",@progbits,_ZN3fdv4Task5entryEPv,comdat
	.literal_position
	.literal .LC0, _ZTVN3fdv14HardwareSerialE+8
	.literal .LC1, _ZN3fdv14HardwareSerial9s_serialsE
	.literal .LC2, 115200
	.literal .LC3, _ZTVN3fdv4TaskE+8
	.literal .LC4, _ZN3fdv4Task5entryEPv
	.literal .LC6, .LC5
	.literal .LC7, _ZTV5Task1+8
	.align	4
	.weak	_ZN8MainTask3runEv
	.type	_ZN8MainTask3runEv, @function
_ZN8MainTask3runEv:
.LFB79:
	.file 2 "src/user_main.cpp"
	.loc 2 104 0
.LVL2:
	addi	sp, sp, -80
.LCFI2:
	s32i	a0, sp, 76
	s32i	a12, sp, 72
	s32i	a13, sp, 68
	s32i	a14, sp, 64
	s32i.n	a15, sp, 60
	.loc 2 104 0
	mov.n	a15, a2
.LBB116:
	.loc 2 106 0
	call0	_ZN3fdv13DisableStdOutEv
.LVL3:
	.loc 2 107 0
	call0	_ZN3fdv15DisableWatchDogEv
.LVL4:
.LBB117:
.LBB118:
	.file 3 "src/fdvserial.h"
	.loc 3 148 0
	l32r	a13, .LC0
.LBB119:
.LBB120:
	.file 4 "src/fdvsync.h"
	.loc 4 206 0
	movi.n	a4, 0
	movi.n	a3, 1
	movi	a2, 0x80
.LBE120:
.LBE119:
	.loc 3 148 0
	s32i.n	a13, sp, 28
.LVL5:
.LBB123:
.LBB121:
	.loc 4 206 0
	call0	xQueueGenericCreate
.LVL6:
.LBE121:
.LBE123:
	.loc 3 150 0
	addi	a12, sp, 28
.LVL7:
	l32r	a4, .LC1
	.loc 3 151 0
	l32r	a3, .LC2
.LBB124:
.LBB122:
	.loc 4 206 0
	s32i.n	a2, sp, 32
.LBE122:
.LBE124:
	.loc 3 151 0
	mov.n	a2, a12
	.loc 3 150 0
	s32i.n	a12, a4, 0
	.loc 3 151 0
	call0	_ZN3fdv14HardwareSerial8reconfigEm
.LVL8:
.LBE118:
.LBE117:
.LBB125:
.LBB126:
.LBB127:
.LBB128:
	.loc 1 50 0
	movi.n	a8, 0
	.loc 1 49 0
	l32r	a14, .LC3
	.loc 1 50 0
	l32r	a3, .LC6
	l32r	a2, .LC4
	addi	a5, sp, 16
.LVL9:
	addi	a7, sp, 20
	s32i.n	a8, sp, 0
	s32i.n	a8, sp, 4
	movi	a4, 0x100
	movi.n	a6, 2
	.loc 1 49 0
	s32i.n	a14, sp, 16
	.loc 1 50 0
	call0	xTaskGenericCreate
.LVL10:
.LBE128:
.LBE127:
	.loc 2 43 0
	l32r	a3, .LC7
.LBE126:
.LBE125:
.LBB130:
.LBB131:
	.loc 1 60 0
	l32i.n	a2, a15, 4
.LBE131:
.LBE130:
.LBB133:
.LBB129:
	.loc 2 43 0
	s32i.n	a3, sp, 16
	s32i.n	a12, sp, 24
.LVL11:
.LBE129:
.LBE133:
.LBB134:
.LBB132:
	.loc 1 60 0
	call0	vTaskSuspend
.LVL12:
.LBE132:
.LBE134:
.LBB135:
.LBB136:
.LBB137:
	.loc 1 55 0
	l32i.n	a2, sp, 20
	.loc 1 54 0
	s32i.n	a14, sp, 16
	.loc 1 55 0
	call0	vTaskDelete
.LVL13:
.LBE137:
.LBE136:
.LBE135:
.LBB138:
.LBB139:
.LBB140:
.LBB141:
	.loc 4 211 0
	l32i.n	a2, sp, 32
.LBE141:
.LBE140:
	.loc 3 143 0
	s32i.n	a13, sp, 28
.LVL14:
.LBB143:
.LBB142:
	.loc 4 211 0
	call0	vQueueDelete
.LVL15:
.LBE142:
.LBE143:
.LBE139:
.LBE138:
.LBE116:
	.loc 2 114 0
	l32i	a0, sp, 76
	l32i	a12, sp, 72
.LVL16:
	l32i	a13, sp, 68
	l32i	a14, sp, 64
	l32i.n	a15, sp, 60
.LVL17:
	addi	sp, sp, 80
.LCFI3:
.LVL18:
	ret.n
.LFE79:
	.size	_ZN8MainTask3runEv, .-_ZN8MainTask3runEv
	.section	.rodata.str1.4
	.align	4
.LC11:
	.string	"Comandi disponibili:"
	.align	4
.LC13:
	.string	"Fabrizio"
	.align	4
.LC15:
	.string	"Di Vittorio"
	.align	4
.LC17:
	.string	"h    = help"
	.align	4
.LC19:
	.string	"r    = reset"
	.align	4
.LC21:
	.string	"1..9 = test 1 a 9"
	.global	__udivsi3
	.section	.irom0.text,"axG",@progbits,_ZN3fdv4Task5entryEPv,comdat
	.literal_position
	.literal .LC10, _ZN3fdv14FlashAllocator5s_posE
	.literal .LC12, .LC11+1
	.literal .LC14, .LC13
	.literal .LC16, .LC15
	.literal .LC18, .LC17+1
	.literal .LC20, .LC19+1
	.literal .LC22, .LC21+1
	.align	4
	.weak	_ZN5Task13runEv
	.type	_ZN5Task13runEv, @function
_ZN5Task13runEv:
.LFB78:
	.loc 2 56 0
.LVL19:
.LBB213:
.LBB214:
.LBB215:
.LBB216:
	.file 5 "src/fdvflash.h"
	.loc 5 85 0
	l32r	a3, .LC10
.LBE216:
.LBE215:
.LBE214:
.LBE213:
	.loc 2 56 0
	addi	sp, sp, -112
.LCFI4:
.LBB329:
.LBB225:
.LBB221:
.LBB217:
	.loc 5 85 0
	l32i.n	a5, a3, 0
.LBE217:
.LBE221:
.LBE225:
.LBE329:
	.loc 2 56 0
	s32i	a12, sp, 104
.LBB330:
.LBB226:
.LBB222:
.LBB218:
	.loc 5 86 0
	addmi	a4, a5, 0x1000
.LBE218:
.LBE222:
.LBE226:
.LBE330:
	.loc 2 56 0
	s32i	a0, sp, 108
	s32i	a13, sp, 100
	s32i	a14, sp, 96
	s32i	a15, sp, 92
.LBB331:
.LBB227:
.LBB223:
.LBB219:
	.loc 5 85 0
	s32i.n	a5, sp, 52
.LVL20:
	extui	a5, a5, 12, 16
.LVL21:
.LBE219:
.LBE223:
.LBE227:
.LBE331:
	.loc 2 56 0
	mov.n	a12, a2
.LBB332:
.LBB228:
.LBB224:
.LBB220:
	.loc 5 86 0
	s32i.n	a4, a3, 0
.LVL22:
	s32i.n	a5, sp, 60
.LVL23:
.L6:
.LBE220:
.LBE224:
.LBE228:
.LBB229:
	.loc 2 61 0
	l32i.n	a2, a12, 8
	movi.n	a3, -1
	l32i.n	a4, a2, 0
	l32i.n	a4, a4, 24
	callx0	a4
.LVL24:
	beqz.n	a2, .L6
.LBB230:
	.loc 2 63 0
	l32i.n	a2, a12, 8
	l32i.n	a3, a2, 0
	l32i.n	a3, a3, 12
	callx0	a3
.LVL25:
.LBB231:
	.loc 2 64 0
	extui	a2, a2, 0, 8
	movi.n	a3, 0x32
	beq	a2, a3, .L8
	bltu	a3, a2, .L9
	movi.n	a3, 0x31
	beq	a2, a3, .L10
	j	.L6
.L9:
	movi	a3, 0x68
	beq	a2, a3, .L11
	movi	a3, 0x72
	beq	a2, a3, .L12
	j	.L6
.L11:
.LBB232:
	.loc 2 67 0
	l32i.n	a14, a12, 8
.LVL26:
	l32r	a13, .LC12
.LBB233:
.LBB234:
.LBB235:
	.loc 3 99 0
	movi.n	a3, 0x43
.LVL27:
.L15:
	.loc 3 100 0
	l32i.n	a2, a14, 0
	addi.n	a13, a13, 1
.LVL28:
	l32i.n	a4, a2, 4
	mov.n	a2, a14
	callx0	a4
.LVL29:
	addi.n	a2, a13, -1
	.loc 3 99 0
	l8ui	a3, a2, 0
	bnez.n	a3, .L15
	j	.L53
.LVL30:
.L34:
.LBE235:
.LBE234:
.LBE233:
.LBB238:
.LBB239:
.LBB240:
	.loc 3 100 0
	l32i.n	a2, a14, 0
	addi.n	a13, a13, 1
.LVL31:
	l32i.n	a4, a2, 4
	mov.n	a2, a14
	callx0	a4
.LVL32:
	addi.n	a2, a13, -1
	.loc 3 99 0
	l8ui	a3, a2, 0
	bnez.n	a3, .L34
	j	.L54
.LVL33:
.L35:
.LBE240:
.LBE239:
.LBE238:
.LBB245:
.LBB246:
.LBB247:
	.loc 3 100 0
	l32i.n	a2, a14, 0
	addi.n	a13, a13, 1
.LVL34:
	l32i.n	a4, a2, 4
	mov.n	a2, a14
	callx0	a4
.LVL35:
	addi.n	a2, a13, -1
	.loc 3 99 0
	l8ui	a3, a2, 0
	bnez.n	a3, .L35
	j	.L55
.LVL36:
.L36:
.LBE247:
.LBE246:
.LBE245:
.LBB252:
.LBB253:
.LBB254:
	.loc 3 100 0
	l32i.n	a2, a14, 0
	addi.n	a13, a13, 1
.LVL37:
	l32i.n	a4, a2, 4
	mov.n	a2, a14
	callx0	a4
.LVL38:
	addi.n	a2, a13, -1
	.loc 3 99 0
	l8ui	a3, a2, 0
	bnez.n	a3, .L36
.LVL39:
.LBE254:
.LBE253:
.LBB256:
.LBB257:
	.loc 3 85 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
	l32i.n	a4, a3, 4
	movi.n	a3, 0xd
	callx0	a4
.LVL40:
	.loc 3 86 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
	l32i.n	a4, a3, 4
	movi.n	a3, 0xa
	callx0	a4
.LVL41:
	j	.L6
.LVL42:
.L12:
.LBE257:
.LBE256:
.LBE252:
	.loc 2 73 0
	call0	system_restart
.LVL43:
	.loc 2 74 0
	j	.L6
.LVL44:
.L10:
.LBB259:
.LBB260:
.LBB261:
.LBB262:
	.loc 5 167 0
	call0	_ZN3fdv17DisableInterruptsEv
.LVL45:
	.loc 5 168 0
	l32i.n	a2, sp, 52
	mov.n	a3, sp
	movi.n	a4, 0x24
	call0	spi_flash_read
.LVL46:
	.loc 5 169 0
	call0	_ZN3fdv16EnableInterruptsEv
.LVL47:
.LBE262:
.LBE261:
.LBE260:
	.loc 2 78 0
	l32r	a4, .LC14
	.loc 2 79 0
	l32r	a2, .LC16
	.loc 2 78 0
	l32i.n	a8, a4, 0
	l32i.n	a7, a4, 4
	l8ui	a6, a4, 8
	.loc 2 79 0
	l32i.n	a5, a2, 0
	l32i.n	a4, a2, 4
	l32i.n	a3, a2, 8
	.loc 2 80 0
	l32i.n	a2, sp, 32
	.loc 2 78 0
	s32i.n	a8, sp, 0
	.loc 2 80 0
	addi.n	a2, a2, 1
	.loc 2 78 0
	s32i.n	a7, sp, 4
	s8i	a6, sp, 8
	.loc 2 79 0
	s32i.n	a5, sp, 16
	s32i.n	a4, sp, 20
	s32i.n	a3, sp, 24
	.loc 2 80 0
	s32i.n	a2, sp, 32
.LVL48:
.LBB263:
.LBB264:
.LBB265:
	.loc 5 157 0
	call0	_ZN3fdv17DisableInterruptsEv
.LVL49:
.LBB266:
	.loc 5 159 0
	l32i.n	a2, sp, 60
	call0	spi_flash_erase_sector
.LVL50:
.LBE266:
	.loc 5 160 0
	l32i.n	a2, sp, 52
	mov.n	a3, sp
	movi.n	a4, 0x24
	call0	spi_flash_write
.LVL51:
	.loc 5 161 0
	call0	_ZN3fdv16EnableInterruptsEv
.LVL52:
	j	.L6
.LVL53:
.L8:
.LBE265:
.LBE264:
.LBE263:
.LBE259:
.LBB267:
.LBB268:
.LBB269:
.LBB270:
	.loc 5 167 0
	call0	_ZN3fdv17DisableInterruptsEv
.LVL54:
	.loc 5 168 0
	l32i.n	a2, sp, 52
	mov.n	a3, sp
	movi.n	a4, 0x24
	call0	spi_flash_read
.LVL55:
	.loc 5 169 0
	call0	_ZN3fdv16EnableInterruptsEv
.LVL56:
.LBE270:
.LBE269:
.LBE268:
.LBB271:
.LBB272:
.LBB273:
	.loc 3 99 0
	l8ui	a3, sp, 0
.LBE273:
.LBE272:
.LBE271:
	.loc 2 87 0
	l32i.n	a14, a12, 8
.LVL57:
.LBB280:
.LBB276:
.LBB274:
	.loc 3 99 0
	mov.n	a13, sp
	bnez.n	a3, .L43
.LVL58:
.L25:
.LBE274:
.LBE276:
.LBB277:
.LBB278:
	.loc 3 85 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
	l32i.n	a4, a3, 4
	movi.n	a3, 0xd
	callx0	a4
.LVL59:
	.loc 3 86 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
	l32i.n	a4, a3, 4
	movi.n	a3, 0xa
	callx0	a4
.LVL60:
.LBE278:
.LBE277:
.LBE280:
.LBB281:
.LBB282:
.LBB283:
	.loc 3 99 0
	l8ui	a3, sp, 16
.LBE283:
.LBE282:
.LBE281:
	.loc 2 88 0
	l32i.n	a14, a12, 8
.LVL61:
.LBB290:
.LBB286:
.LBB284:
	.loc 3 99 0
	addi	a13, sp, 16
.LVL62:
	bnez.n	a3, .L44
	j	.L24
.LVL63:
.L43:
.LBE284:
.LBE286:
.LBE290:
.LBB291:
.LBB279:
.LBB275:
	.loc 3 100 0
	l32i.n	a2, a14, 0
	addi.n	a13, a13, 1
.LVL64:
	l32i.n	a4, a2, 4
	mov.n	a2, a14
	callx0	a4
.LVL65:
	.loc 3 99 0
	l8ui	a3, a13, 0
	bnez.n	a3, .L43
	j	.L25
.LVL66:
.L24:
.LBE275:
.LBE279:
.LBE291:
.LBB292:
.LBB287:
.LBB288:
	.loc 3 85 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
	l32i.n	a4, a3, 4
	movi.n	a3, 0xd
	callx0	a4
.LVL67:
	.loc 3 86 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
	l32i.n	a4, a3, 4
	movi.n	a3, 0xa
	callx0	a4
.LVL68:
.LBE288:
.LBE287:
.LBE292:
.LBB293:
.LBB294:
	.loc 3 111 0
	movi.n	a4, 0
.LBE294:
.LBE293:
	.loc 2 89 0
	l32i.n	a14, sp, 32
.LVL69:
.LBB313:
.LBB309:
	.loc 3 111 0
	s32i.n	a4, sp, 48
.LBE309:
.LBE313:
	.loc 2 89 0
	l32i.n	a4, a12, 8
.LVL70:
	s32i.n	a12, sp, 56
.LBB314:
.LBB310:
.LBB295:
	.loc 3 112 0
	movi.n	a15, 9
	mov.n	a12, a14
	mov.n	a14, a4
.LVL71:
	j	.L27
.LVL72:
.L44:
.LBE295:
.LBE310:
.LBE314:
.LBB315:
.LBB289:
.LBB285:
	.loc 3 100 0
	l32i.n	a2, a14, 0
	addi.n	a13, a13, 1
.LVL73:
	l32i.n	a4, a2, 4
	mov.n	a2, a14
	callx0	a4
.LVL74:
	.loc 3 99 0
	l8ui	a3, a13, 0
	bnez.n	a3, .L44
	j	.L24
.LVL75:
.L33:
	addi.n	a3, a3, 1
.LVL76:
	extui	a3, a3, 0, 8
.LVL77:
.LBE285:
.LBE289:
.LBE315:
.LBB316:
.LBB311:
.LBB307:
.LBB296:
.LBB297:
	.loc 3 115 0
	slli	a2, a3, 24
	.loc 3 116 0
	addx4	a13, a13, a13
.LVL78:
	.loc 3 115 0
	srai	a2, a2, 24
	.loc 3 116 0
	slli	a13, a13, 1
.LVL79:
	.loc 3 115 0
	bne	a5, a2, .L33
.LBE297:
	.loc 3 117 0
	mov.n	a2, a12
	mov.n	a3, a13
.LVL80:
	call0	__udivsi3
.LVL81:
	mov.n	a4, a2
.LVL82:
.LBB298:
	.loc 3 118 0
	beqz.n	a2, .L49
	j	.L32
.LVL83:
.L38:
.LBE298:
	.loc 3 117 0
	mov.n	a4, a12
.LBB300:
	.loc 3 115 0
	movi.n	a13, 1
.LVL84:
.L32:
.LBE300:
.LBB301:
.LBB299:
	.loc 3 121 0
	l32i.n	a2, a14, 0
	.loc 3 120 0
	addi	a3, a4, 48
	.loc 3 121 0
	l32i.n	a5, a2, 4
	extui	a3, a3, 0, 8
	s32i	a4, sp, 64
	mov.n	a2, a14
	callx0	a5
.LVL85:
	.loc 3 122 0
	movi.n	a5, 1
	l32i	a4, sp, 64
	s32i.n	a5, sp, 48
.LVL86:
.L37:
	addi.n	a6, a15, -1
	extui	a15, a6, 0, 8
.LVL87:
.LBE299:
.LBE301:
	.loc 3 124 0
	mull	a13, a4, a13
.LBE296:
	.loc 3 112 0
	slli	a5, a15, 24
	srai	a5, a5, 24
.LBB304:
	.loc 3 124 0
	sub	a12, a12, a13
.LVL88:
.LBE304:
	.loc 3 112 0
	beqi	a5, -1, .L31
.LVL89:
.L27:
.LBB305:
.LBB302:
	.loc 3 115 0
	beqz.n	a15, .L38
	slli	a5, a15, 24
	movi.n	a3, 0
	movi.n	a13, 1
	srai	a5, a5, 24
	j	.L33
.LVL90:
.L31:
	l32i.n	a12, sp, 56
.LVL91:
.LBE302:
.LBE305:
.LBE307:
.LBE311:
.LBE316:
.LBB317:
.LBB318:
	.loc 3 85 0
	movi.n	a3, 0xd
.LBE318:
.LBE317:
	.loc 2 89 0
	l32i.n	a13, a12, 8
.LVL92:
.LBB320:
.LBB319:
	.loc 3 85 0
	l32i.n	a4, a13, 0
	mov.n	a2, a13
	l32i.n	a4, a4, 4
	callx0	a4
.LVL93:
	.loc 3 86 0
	l32i.n	a3, a13, 0
	mov.n	a2, a13
	l32i.n	a4, a3, 4
	movi.n	a3, 0xa
	callx0	a4
.LVL94:
	j	.L6
.LVL95:
.L53:
.LBE319:
.LBE320:
.LBE267:
.LBB322:
.LBB236:
.LBB237:
	.loc 3 85 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
.LVL96:
	l32i.n	a4, a3, 4
	movi.n	a3, 0xd
	callx0	a4
.LVL97:
	.loc 3 86 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
	l32i.n	a4, a3, 4
	movi.n	a3, 0xa
	callx0	a4
.LVL98:
.LBE237:
.LBE236:
.LBE322:
.LBB323:
.LBB242:
.LBB241:
	.loc 3 99 0
	movi	a3, 0x68
	l32r	a13, .LC18
.LVL99:
.LBE241:
.LBE242:
.LBE323:
	.loc 2 68 0
	l32i.n	a14, a12, 8
.LVL100:
	j	.L34
.LVL101:
.L54:
.LBB324:
.LBB243:
.LBB244:
	.loc 3 85 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
.LVL102:
	l32i.n	a4, a3, 4
	movi.n	a3, 0xd
	callx0	a4
.LVL103:
	.loc 3 86 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
	l32i.n	a4, a3, 4
	movi.n	a3, 0xa
	callx0	a4
.LVL104:
.LBE244:
.LBE243:
.LBE324:
.LBB325:
.LBB249:
.LBB248:
	.loc 3 99 0
	movi	a3, 0x72
	l32r	a13, .LC20
.LVL105:
.LBE248:
.LBE249:
.LBE325:
	.loc 2 69 0
	l32i.n	a14, a12, 8
.LVL106:
	j	.L35
.LVL107:
.L55:
.LBB326:
.LBB250:
.LBB251:
	.loc 3 85 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
.LVL108:
	l32i.n	a4, a3, 4
	movi.n	a3, 0xd
	callx0	a4
.LVL109:
	.loc 3 86 0
	l32i.n	a3, a14, 0
	mov.n	a2, a14
	l32i.n	a4, a3, 4
	movi.n	a3, 0xa
	callx0	a4
.LVL110:
.LBE251:
.LBE250:
.LBE326:
.LBB327:
.LBB258:
.LBB255:
	.loc 3 99 0
	movi.n	a3, 0x31
	l32r	a13, .LC22
.LVL111:
.LBE255:
.LBE258:
.LBE327:
	.loc 2 70 0
	l32i.n	a14, a12, 8
.LVL112:
	j	.L36
.LVL113:
.L49:
.LBB328:
.LBB321:
.LBB312:
.LBB308:
.LBB306:
.LBB303:
	.loc 3 118 0
	l32i.n	a5, sp, 48
	bnez.n	a5, .L32
	mov.n	a4, a5
	j	.L37
.LBE303:
.LBE306:
.LBE308:
.LBE312:
.LBE321:
.LBE328:
.LBE232:
.LBE231:
.LBE230:
.LBE229:
.LBE332:
.LFE78:
	.size	_ZN5Task13runEv, .-_ZN5Task13runEv
	.text
	.literal_position
	.literal .LC23, _ZTVN3fdv4TaskE+8
	.literal .LC24, _ZN3fdv4Task5entryEPv
	.literal .LC25, .LC5
	.literal .LC26, _ZTV8MainTask+8
	.align	4
	.global	user_init
	.type	user_init, @function
user_init:
.LFB86:
	.loc 2 119 0
	addi	sp, sp, -32
.LCFI5:
	.loc 2 120 0
	movi.n	a2, 8
	.loc 2 119 0
	s32i.n	a0, sp, 28
	s32i.n	a12, sp, 24
	.loc 2 120 0
	call0	_Znwj
.LVL114:
	mov.n	a12, a2
.LVL115:
.LBB338:
.LBB339:
.LBB340:
.LBB341:
	.loc 1 49 0
	l32r	a2, .LC23
.LVL116:
	.loc 1 50 0
	l32r	a3, .LC25
	.loc 1 49 0
	s32i.n	a2, a12, 0
	.loc 1 50 0
	movi.n	a2, 0
	s32i.n	a2, sp, 0
	s32i.n	a2, sp, 4
	l32r	a2, .LC24
	mov.n	a5, a12
	addi.n	a7, a12, 4
	movi	a4, 0x100
	movi.n	a6, 2
	call0	xTaskGenericCreate
.LVL117:
.LBE341:
.LBE340:
	.loc 2 102 0
	l32r	a2, .LC26
.LBE339:
.LBE338:
	.loc 2 121 0
	l32i.n	a0, sp, 28
.LBB343:
.LBB342:
	.loc 2 102 0
	s32i.n	a2, a12, 0
.LBE342:
.LBE343:
	.loc 2 121 0
	l32i.n	a12, sp, 24
.LVL118:
	addi	sp, sp, 32
.LCFI6:
	ret.n
.LFE86:
	.size	user_init, .-user_init
	.weak	_ZTVN3fdv4TaskE
	.section	.rodata._ZTVN3fdv4TaskE,"aG",@progbits,_ZTVN3fdv4TaskE,comdat
	.align	8
	.type	_ZTVN3fdv4TaskE, @object
	.size	_ZTVN3fdv4TaskE, 12
_ZTVN3fdv4TaskE:
	.word	0
	.word	0
	.word	__cxa_pure_virtual
	.weak	_ZTV5Task1
	.section	.rodata._ZTV5Task1,"aG",@progbits,_ZTV5Task1,comdat
	.align	8
	.type	_ZTV5Task1, @object
	.size	_ZTV5Task1, 12
_ZTV5Task1:
	.word	0
	.word	0
	.word	_ZN5Task13runEv
	.weak	_ZTV8MainTask
	.section	.rodata._ZTV8MainTask,"aG",@progbits,_ZTV8MainTask,comdat
	.align	8
	.type	_ZTV8MainTask, @object
	.size	_ZTV8MainTask, 12
_ZTV8MainTask:
	.word	0
	.word	0
	.word	_ZN8MainTask3runEv
	.section	.debug_frame,"",@progbits
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x3
	.string	""
	.uleb128 0x1
	.sleb128 -4
	.uleb128 0
	.byte	0xc
	.uleb128 0x1
	.uleb128 0
	.align	4
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB74
	.4byte	.LFE74-.LFB74
	.byte	0x4
	.4byte	.LCFI0-.LFB74
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB79
	.4byte	.LFE79-.LFB79
	.byte	0x4
	.4byte	.LCFI2-.LFB79
	.byte	0xe
	.uleb128 0x50
	.byte	0x4
	.4byte	.LCFI3-.LCFI2
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB78
	.4byte	.LFE78-.LFB78
	.byte	0x4
	.4byte	.LCFI4-.LFB78
	.byte	0xe
	.uleb128 0x70
	.align	4
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB86
	.4byte	.LFE86-.LFB86
	.byte	0x4
	.4byte	.LCFI5-.LFB86
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI6-.LCFI5
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE6:
	.text
.Letext0:
	.file 6 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/espressif/c_types.h"
	.file 7 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/espressif/spi_flash.h"
	.file 8 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/freertos/projdefs.h"
	.file 9 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/freertos/portmacro.h"
	.file 10 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/freertos/task.h"
	.file 11 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/freertos/queue.h"
	.file 12 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/espressif/esp_system.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x184f
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF142
	.byte	0x4
	.4byte	.LASF143
	.4byte	.LASF144
	.4byte	.Ldebug_ranges0+0x2c8
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF2
	.byte	0x6
	.byte	0x9
	.4byte	0x30
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF0
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.4byte	.LASF1
	.uleb128 0x2
	.4byte	.LASF3
	.byte	0x6
	.byte	0xb
	.4byte	0x37
	.uleb128 0x2
	.4byte	.LASF4
	.byte	0x6
	.byte	0xc
	.4byte	0x54
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.4byte	.LASF7
	.byte	0x6
	.byte	0xe
	.4byte	0x5b
	.uleb128 0x2
	.4byte	.LASF8
	.byte	0x6
	.byte	0xf
	.4byte	0x78
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF9
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF11
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF12
	.uleb128 0x3
	.byte	0x4
	.byte	0x4
	.4byte	.LASF13
	.uleb128 0x3
	.byte	0x8
	.byte	0x4
	.4byte	.LASF14
	.uleb128 0x2
	.4byte	.LASF15
	.byte	0x6
	.byte	0x1d
	.4byte	0x54
	.uleb128 0x2
	.4byte	.LASF16
	.byte	0x6
	.byte	0x21
	.4byte	0xb8
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF17
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF18
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x6
	.4byte	0xda
	.uleb128 0x7
	.4byte	0xcd
	.byte	0
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.4byte	.LASF19
	.uleb128 0x8
	.byte	0x4
	.byte	0x7
	.byte	0x9
	.4byte	.LASF145
	.4byte	0x100
	.uleb128 0x9
	.4byte	.LASF20
	.sleb128 0
	.uleb128 0x9
	.4byte	.LASF21
	.sleb128 1
	.uleb128 0x9
	.4byte	.LASF22
	.sleb128 2
	.byte	0
	.uleb128 0x2
	.4byte	.LASF23
	.byte	0x7
	.byte	0xd
	.4byte	0xe1
	.uleb128 0x2
	.4byte	.LASF24
	.byte	0x8
	.byte	0x45
	.4byte	0x116
	.uleb128 0xa
	.byte	0x4
	.4byte	0xcf
	.uleb128 0x2
	.4byte	.LASF25
	.byte	0x9
	.byte	0x61
	.4byte	0x78
	.uleb128 0x2
	.4byte	.LASF26
	.byte	0xa
	.byte	0x5f
	.4byte	0xcd
	.uleb128 0xb
	.4byte	.LASF68
	.byte	0xc
	.byte	0xa
	.byte	0x77
	.4byte	0x163
	.uleb128 0xc
	.4byte	.LASF27
	.byte	0xa
	.byte	0x79
	.4byte	0xcd
	.byte	0
	.uleb128 0xc
	.4byte	.LASF28
	.byte	0xa
	.byte	0x7a
	.4byte	0x78
	.byte	0x4
	.uleb128 0xc
	.4byte	.LASF29
	.byte	0xa
	.byte	0x7b
	.4byte	0x78
	.byte	0x8
	.byte	0
	.uleb128 0x2
	.4byte	.LASF30
	.byte	0xa
	.byte	0x7c
	.4byte	0x132
	.uleb128 0xa
	.byte	0x4
	.4byte	0x174
	.uleb128 0xd
	.4byte	0x37
	.uleb128 0xa
	.byte	0x4
	.4byte	0x78
	.uleb128 0x2
	.4byte	.LASF31
	.byte	0xb
	.byte	0x53
	.4byte	0xcd
	.uleb128 0xe
	.string	"fdv"
	.byte	0x4
	.byte	0x27
	.4byte	0x7af
	.uleb128 0xf
	.4byte	.LASF146
	.byte	0x4
	.byte	0x4
	.byte	0xc7
	.4byte	0x2be
	.uleb128 0xc
	.4byte	.LASF32
	.byte	0x4
	.byte	0xf7
	.4byte	0x17f
	.byte	0
	.uleb128 0x10
	.4byte	.LASF33
	.byte	0x4
	.byte	0xcc
	.byte	0x1
	.4byte	0x1bd
	.4byte	0x1c8
	.uleb128 0x11
	.4byte	0x7af
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.uleb128 0x10
	.4byte	.LASF34
	.byte	0x4
	.byte	0xd1
	.byte	0x1
	.4byte	0x1d8
	.4byte	0x1e3
	.uleb128 0x11
	.4byte	0x7af
	.uleb128 0x11
	.4byte	0xbf
	.byte	0
	.uleb128 0x12
	.4byte	.LASF35
	.byte	0x4
	.byte	0xd6
	.4byte	.LASF37
	.4byte	0xda
	.byte	0x1
	.4byte	0x1fb
	.4byte	0x20b
	.uleb128 0x11
	.4byte	0x7af
	.uleb128 0x7
	.4byte	0x7b5
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.uleb128 0x12
	.4byte	.LASF36
	.byte	0x4
	.byte	0xdb
	.4byte	.LASF38
	.4byte	0xda
	.byte	0x1
	.4byte	0x223
	.4byte	0x22e
	.uleb128 0x11
	.4byte	0x7af
	.uleb128 0x7
	.4byte	0x7b5
	.byte	0
	.uleb128 0x12
	.4byte	.LASF39
	.byte	0x4
	.byte	0xe1
	.4byte	.LASF40
	.4byte	0xda
	.byte	0x1
	.4byte	0x246
	.4byte	0x256
	.uleb128 0x11
	.4byte	0x7af
	.uleb128 0x7
	.4byte	0x7bb
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.uleb128 0x12
	.4byte	.LASF41
	.byte	0x4
	.byte	0xe6
	.4byte	.LASF42
	.4byte	0xda
	.byte	0x1
	.4byte	0x26e
	.4byte	0x27e
	.uleb128 0x11
	.4byte	0x7af
	.uleb128 0x7
	.4byte	0x7bb
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.uleb128 0x13
	.4byte	.LASF59
	.byte	0x4
	.byte	0xeb
	.4byte	.LASF61
	.byte	0x1
	.4byte	0x292
	.4byte	0x298
	.uleb128 0x11
	.4byte	0x7af
	.byte	0
	.uleb128 0x12
	.4byte	.LASF43
	.byte	0x4
	.byte	0xf0
	.4byte	.LASF44
	.4byte	0x6d
	.byte	0x1
	.4byte	0x2b0
	.4byte	0x2b6
	.uleb128 0x11
	.4byte	0x7af
	.byte	0
	.uleb128 0x14
	.string	"T"
	.4byte	0x30
	.byte	0
	.uleb128 0x15
	.4byte	.LASF47
	.byte	0x4
	.byte	0x3
	.byte	0x3b
	.4byte	0x2be
	.4byte	0x4f3
	.uleb128 0x16
	.byte	0x3
	.byte	0x8f
	.4byte	0x499
	.uleb128 0x17
	.4byte	.LASF45
	.4byte	0x947
	.byte	0
	.byte	0x1
	.uleb128 0x18
	.4byte	.LASF46
	.byte	0x1
	.4byte	0x2ee
	.4byte	0x2f9
	.uleb128 0x11
	.4byte	0x7c1
	.uleb128 0x11
	.4byte	0xbf
	.byte	0
	.uleb128 0x18
	.4byte	.LASF47
	.byte	0x1
	.4byte	0x307
	.4byte	0x312
	.uleb128 0x11
	.4byte	0x7c1
	.uleb128 0x7
	.4byte	0x963
	.byte	0
	.uleb128 0x18
	.4byte	.LASF47
	.byte	0x1
	.4byte	0x320
	.4byte	0x326
	.uleb128 0x11
	.4byte	0x7c1
	.byte	0
	.uleb128 0x19
	.string	"put"
	.byte	0x3
	.byte	0x3f
	.4byte	.LASF87
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0
	.4byte	0x2be
	.byte	0x1
	.4byte	0x342
	.4byte	0x34d
	.uleb128 0x11
	.4byte	0x7c1
	.uleb128 0x7
	.4byte	0x25
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF48
	.byte	0x3
	.byte	0x40
	.4byte	.LASF54
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x1
	.4byte	0x2be
	.byte	0x1
	.4byte	0x369
	.4byte	0x374
	.uleb128 0x11
	.4byte	0x7c1
	.uleb128 0x7
	.4byte	0x25
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF41
	.byte	0x3
	.byte	0x41
	.4byte	.LASF50
	.4byte	0x62
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x2
	.4byte	0x2be
	.byte	0x1
	.4byte	0x394
	.4byte	0x39a
	.uleb128 0x11
	.4byte	0x7c1
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF49
	.byte	0x3
	.byte	0x42
	.4byte	.LASF51
	.4byte	0x62
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x3
	.4byte	0x2be
	.byte	0x1
	.4byte	0x3ba
	.4byte	0x3c0
	.uleb128 0x11
	.4byte	0x7c1
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF43
	.byte	0x3
	.byte	0x43
	.4byte	.LASF52
	.4byte	0x49
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x4
	.4byte	0x2be
	.byte	0x1
	.4byte	0x3e0
	.4byte	0x3e6
	.uleb128 0x11
	.4byte	0x7c1
	.byte	0
	.uleb128 0x1a
	.4byte	.LASF53
	.byte	0x3
	.byte	0x44
	.4byte	.LASF55
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x5
	.4byte	0x2be
	.byte	0x1
	.4byte	0x402
	.4byte	0x408
	.uleb128 0x11
	.4byte	0x7c1
	.byte	0
	.uleb128 0x1b
	.4byte	.LASF56
	.byte	0x3
	.byte	0x45
	.4byte	.LASF57
	.4byte	0xda
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x6
	.4byte	0x2be
	.byte	0x1
	.4byte	0x428
	.4byte	0x433
	.uleb128 0x11
	.4byte	0x7c1
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.uleb128 0x12
	.4byte	.LASF49
	.byte	0x3
	.byte	0x48
	.4byte	.LASF58
	.4byte	0x49
	.byte	0x1
	.4byte	0x44b
	.4byte	0x45b
	.uleb128 0x11
	.4byte	0x7c1
	.uleb128 0x7
	.4byte	0x969
	.uleb128 0x7
	.4byte	0x49
	.byte	0
	.uleb128 0x13
	.4byte	.LASF60
	.byte	0x3
	.byte	0x53
	.4byte	.LASF62
	.byte	0x1
	.4byte	0x46f
	.4byte	0x475
	.uleb128 0x11
	.4byte	0x7c1
	.byte	0
	.uleb128 0x13
	.4byte	.LASF48
	.byte	0x3
	.byte	0x5a
	.4byte	.LASF63
	.byte	0x1
	.4byte	0x489
	.4byte	0x499
	.uleb128 0x11
	.4byte	0x7c1
	.uleb128 0x7
	.4byte	0x96f
	.uleb128 0x7
	.4byte	0x49
	.byte	0
	.uleb128 0x13
	.4byte	.LASF48
	.byte	0x3
	.byte	0x61
	.4byte	.LASF64
	.byte	0x1
	.4byte	0x4ad
	.4byte	0x4b8
	.uleb128 0x11
	.4byte	0x7c1
	.uleb128 0x7
	.4byte	0x7c7
	.byte	0
	.uleb128 0x13
	.4byte	.LASF65
	.byte	0x3
	.byte	0x67
	.4byte	.LASF66
	.byte	0x1
	.4byte	0x4cc
	.4byte	0x4d7
	.uleb128 0x11
	.4byte	0x7c1
	.uleb128 0x7
	.4byte	0x7c7
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF67
	.byte	0x3
	.byte	0x6d
	.4byte	.LASF76
	.byte	0x1
	.4byte	0x4e7
	.uleb128 0x11
	.4byte	0x7c1
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF69
	.byte	0x1
	.byte	0x5
	.byte	0x50
	.4byte	0x540
	.uleb128 0x1d
	.4byte	.LASF147
	.byte	0x5
	.byte	0x61
	.4byte	0x6d
	.byte	0x3
	.uleb128 0x1e
	.4byte	.LASF70
	.byte	0x5
	.byte	0x5b
	.4byte	0x49
	.4byte	0x527
	.uleb128 0x14
	.string	"T"
	.4byte	0x7e9
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.uleb128 0x1f
	.4byte	.LASF89
	.byte	0x5
	.byte	0x53
	.4byte	0x6d
	.uleb128 0x14
	.string	"T"
	.4byte	0x7e9
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF71
	.byte	0x4
	.byte	0x5
	.byte	0x82
	.4byte	0x608
	.uleb128 0x20
	.4byte	.LASF93
	.byte	0x5
	.byte	0xaf
	.4byte	0x6d
	.byte	0
	.byte	0x3
	.uleb128 0x21
	.4byte	.LASF72
	.byte	0x5
	.byte	0x84
	.4byte	0x568
	.4byte	0x56e
	.uleb128 0x11
	.4byte	0x8a9
	.byte	0
	.uleb128 0x22
	.4byte	.LASF72
	.byte	0x5
	.byte	0x89
	.4byte	0x57d
	.4byte	0x588
	.uleb128 0x11
	.4byte	0x8a9
	.uleb128 0x7
	.4byte	0x8af
	.byte	0
	.uleb128 0x23
	.4byte	.LASF73
	.byte	0x5
	.byte	0x8f
	.4byte	.LASF74
	.4byte	0x81a
	.4byte	0x59f
	.4byte	0x5a5
	.uleb128 0x11
	.4byte	0x8b5
	.byte	0
	.uleb128 0x24
	.4byte	.LASF75
	.byte	0x5
	.byte	0x94
	.4byte	.LASF77
	.4byte	0x5b8
	.4byte	0x5c3
	.uleb128 0x11
	.4byte	0x8a9
	.uleb128 0x7
	.4byte	0x8af
	.byte	0
	.uleb128 0x25
	.string	"set"
	.byte	0x5
	.byte	0x9b
	.4byte	.LASF148
	.byte	0x3
	.4byte	0x5d7
	.4byte	0x5e2
	.uleb128 0x11
	.4byte	0x8a9
	.uleb128 0x7
	.4byte	0x8af
	.byte	0
	.uleb128 0x26
	.string	"get"
	.byte	0x5
	.byte	0xa4
	.4byte	.LASF112
	.4byte	0x81a
	.byte	0x3
	.4byte	0x5fa
	.4byte	0x600
	.uleb128 0x11
	.4byte	0x8b5
	.byte	0
	.uleb128 0x14
	.string	"T"
	.4byte	0x7e9
	.byte	0
	.uleb128 0xd
	.4byte	0x540
	.uleb128 0x15
	.4byte	.LASF78
	.byte	0x8
	.byte	0x1
	.byte	0x2c
	.4byte	0x60d
	.4byte	0x70f
	.uleb128 0x17
	.4byte	.LASF79
	.4byte	0x947
	.byte	0
	.byte	0x1
	.uleb128 0xc
	.4byte	.LASF32
	.byte	0x1
	.byte	0x56
	.4byte	0x127
	.byte	0x4
	.uleb128 0x18
	.4byte	.LASF78
	.byte	0x1
	.4byte	0x642
	.4byte	0x64d
	.uleb128 0x11
	.4byte	0x957
	.uleb128 0x7
	.4byte	0x95d
	.byte	0
	.uleb128 0x10
	.4byte	.LASF78
	.byte	0x1
	.byte	0x30
	.byte	0x1
	.4byte	0x65d
	.4byte	0x66d
	.uleb128 0x11
	.4byte	0x957
	.uleb128 0x7
	.4byte	0x49
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.uleb128 0x10
	.4byte	.LASF80
	.byte	0x1
	.byte	0x35
	.byte	0x1
	.4byte	0x67d
	.4byte	0x688
	.uleb128 0x11
	.4byte	0x957
	.uleb128 0x11
	.4byte	0xbf
	.byte	0
	.uleb128 0x13
	.4byte	.LASF81
	.byte	0x1
	.byte	0x3a
	.4byte	.LASF82
	.byte	0x1
	.4byte	0x69c
	.4byte	0x6a2
	.uleb128 0x11
	.4byte	0x957
	.byte	0
	.uleb128 0x13
	.4byte	.LASF83
	.byte	0x1
	.byte	0x3f
	.4byte	.LASF84
	.byte	0x1
	.4byte	0x6b6
	.4byte	0x6bc
	.uleb128 0x11
	.4byte	0x957
	.byte	0
	.uleb128 0x13
	.4byte	.LASF85
	.byte	0x1
	.byte	0x44
	.4byte	.LASF86
	.byte	0x1
	.4byte	0x6d0
	.4byte	0x6db
	.uleb128 0x11
	.4byte	0x957
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.uleb128 0x19
	.string	"run"
	.byte	0x1
	.byte	0x4b
	.4byte	.LASF88
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0
	.4byte	0x60d
	.byte	0x1
	.4byte	0x6f7
	.4byte	0x6fd
	.uleb128 0x11
	.4byte	0x957
	.byte	0
	.uleb128 0x27
	.4byte	.LASF90
	.byte	0x1
	.byte	0x50
	.4byte	.LASF149
	.uleb128 0x7
	.4byte	0xcd
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	0x60d
	.uleb128 0xd
	.4byte	0x2be
	.uleb128 0x28
	.4byte	.LASF92
	.4byte	0x782
	.uleb128 0x18
	.4byte	.LASF91
	.byte	0x1
	.4byte	0x730
	.4byte	0x73b
	.uleb128 0x11
	.4byte	0xaca
	.uleb128 0x11
	.4byte	0xbf
	.byte	0
	.uleb128 0x29
	.4byte	.LASF92
	.byte	0x3
	.byte	0x93
	.byte	0x1
	.4byte	0x74b
	.4byte	0x75b
	.uleb128 0x11
	.4byte	0xaca
	.uleb128 0x7
	.4byte	0x6d
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.uleb128 0x2a
	.4byte	.LASF94
	.byte	0x3
	.byte	0xcf
	.4byte	0x172f
	.uleb128 0x1c
	.4byte	.LASF95
	.byte	0x3
	.byte	0x9a
	.4byte	.LASF96
	.byte	0x1
	.4byte	0x776
	.uleb128 0x11
	.4byte	0xaca
	.uleb128 0x7
	.4byte	0x6d
	.byte	0
	.byte	0
	.uleb128 0x2b
	.4byte	.LASF97
	.byte	0x3
	.byte	0x33
	.4byte	.LASF99
	.uleb128 0x2b
	.4byte	.LASF98
	.byte	0x4
	.byte	0x2d
	.4byte	.LASF100
	.uleb128 0x2b
	.4byte	.LASF101
	.byte	0x4
	.byte	0x30
	.4byte	.LASF102
	.uleb128 0x2b
	.4byte	.LASF103
	.byte	0x4
	.byte	0x2f
	.4byte	.LASF104
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.4byte	0x195
	.uleb128 0x2c
	.byte	0x4
	.4byte	0x30
	.uleb128 0xa
	.byte	0x4
	.4byte	0x30
	.uleb128 0xa
	.byte	0x4
	.4byte	0x2be
	.uleb128 0xa
	.byte	0x4
	.4byte	0x7cd
	.uleb128 0xd
	.4byte	0x7d2
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF105
	.uleb128 0x2d
	.4byte	.LASF111
	.byte	0xc
	.byte	0x2
	.byte	0x27
	.4byte	0x60d
	.4byte	0x899
	.uleb128 0xb
	.4byte	.LASF106
	.byte	0x24
	.byte	0x2
	.byte	0x31
	.4byte	0x81a
	.uleb128 0xc
	.4byte	.LASF107
	.byte	0x2
	.byte	0x33
	.4byte	0x899
	.byte	0
	.uleb128 0xc
	.4byte	.LASF108
	.byte	0x2
	.byte	0x34
	.4byte	0x899
	.byte	0x10
	.uleb128 0x2e
	.string	"seq"
	.byte	0x2
	.byte	0x35
	.4byte	0x6d
	.byte	0x20
	.byte	0
	.uleb128 0xd
	.4byte	0x7e9
	.uleb128 0x2f
	.4byte	0x60d
	.byte	0
	.uleb128 0xc
	.4byte	.LASF109
	.byte	0x2
	.byte	0x2f
	.4byte	0x7c1
	.byte	0x8
	.uleb128 0x30
	.4byte	.LASF110
	.4byte	0x83e
	.4byte	0x849
	.uleb128 0x11
	.4byte	0x92b
	.uleb128 0x11
	.4byte	0xbf
	.byte	0
	.uleb128 0x30
	.4byte	.LASF111
	.4byte	0x856
	.4byte	0x861
	.uleb128 0x11
	.4byte	0x92b
	.uleb128 0x7
	.4byte	0x931
	.byte	0
	.uleb128 0x21
	.4byte	.LASF111
	.byte	0x2
	.byte	0x2a
	.4byte	0x870
	.4byte	0x87b
	.uleb128 0x11
	.4byte	0x92b
	.uleb128 0x7
	.4byte	0x7c1
	.byte	0
	.uleb128 0x31
	.string	"run"
	.byte	0x2
	.byte	0x38
	.4byte	.LASF113
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0
	.4byte	0x7d9
	.4byte	0x892
	.uleb128 0x11
	.4byte	0x92b
	.byte	0
	.byte	0
	.uleb128 0x32
	.4byte	0x7d2
	.4byte	0x8a9
	.uleb128 0x33
	.4byte	0xc6
	.byte	0xf
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.4byte	0x540
	.uleb128 0x2c
	.byte	0x4
	.4byte	0x81a
	.uleb128 0xa
	.byte	0x4
	.4byte	0x608
	.uleb128 0x2d
	.4byte	.LASF114
	.byte	0x8
	.byte	0x2
	.byte	0x66
	.4byte	0x60d
	.4byte	0x91a
	.uleb128 0x2f
	.4byte	0x60d
	.byte	0
	.uleb128 0x30
	.4byte	.LASF114
	.4byte	0x8de
	.4byte	0x8e9
	.uleb128 0x11
	.4byte	0x91a
	.uleb128 0x7
	.4byte	0x920
	.byte	0
	.uleb128 0x30
	.4byte	.LASF114
	.4byte	0x8f6
	.4byte	0x8fc
	.uleb128 0x11
	.4byte	0x91a
	.byte	0
	.uleb128 0x31
	.string	"run"
	.byte	0x2
	.byte	0x68
	.4byte	.LASF115
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0
	.4byte	0x8bb
	.4byte	0x913
	.uleb128 0x11
	.4byte	0x91a
	.byte	0
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.4byte	0x8bb
	.uleb128 0x2c
	.byte	0x4
	.4byte	0x926
	.uleb128 0xd
	.4byte	0x8bb
	.uleb128 0xa
	.byte	0x4
	.4byte	0x7d9
	.uleb128 0x2c
	.byte	0x4
	.4byte	0x937
	.uleb128 0xd
	.4byte	0x7d9
	.uleb128 0x34
	.4byte	0xbf
	.4byte	0x947
	.uleb128 0x35
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.4byte	0x94d
	.uleb128 0x36
	.byte	0x4
	.4byte	.LASF150
	.4byte	0x93c
	.uleb128 0xa
	.byte	0x4
	.4byte	0x60d
	.uleb128 0x2c
	.byte	0x4
	.4byte	0x70f
	.uleb128 0x2c
	.byte	0x4
	.4byte	0x714
	.uleb128 0xa
	.byte	0x4
	.4byte	0x25
	.uleb128 0xa
	.byte	0x4
	.4byte	0x975
	.uleb128 0xd
	.4byte	0x25
	.uleb128 0x37
	.4byte	0x499
	.byte	0x3
	.4byte	0x988
	.4byte	0x99d
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0x99d
	.uleb128 0x39
	.string	"str"
	.byte	0x3
	.byte	0x61
	.4byte	0x7c7
	.byte	0
	.uleb128 0xd
	.4byte	0x7c1
	.uleb128 0x37
	.4byte	0x45b
	.byte	0x3
	.4byte	0x9b0
	.4byte	0x9ba
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0x99d
	.byte	0
	.uleb128 0x37
	.4byte	0x688
	.byte	0x3
	.4byte	0x9c8
	.4byte	0x9d2
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0x9d2
	.byte	0
	.uleb128 0xd
	.4byte	0x957
	.uleb128 0x37
	.4byte	0x66d
	.byte	0x3
	.4byte	0x9e5
	.4byte	0x9f8
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0x9d2
	.uleb128 0x38
	.4byte	.LASF117
	.4byte	0x9f8
	.byte	0
	.uleb128 0xd
	.4byte	0xbf
	.uleb128 0x3a
	.4byte	0x8e9
	.byte	0x2
	.byte	0x66
	.byte	0x3
	.4byte	0xa0d
	.4byte	0xa17
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xa17
	.byte	0
	.uleb128 0xd
	.4byte	0x91a
	.uleb128 0x3a
	.4byte	0x312
	.byte	0x3
	.byte	0x3b
	.byte	0x3
	.4byte	0xa2c
	.4byte	0xa36
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0x99d
	.byte	0
	.uleb128 0x37
	.4byte	0x1ad
	.byte	0x3
	.4byte	0xa44
	.4byte	0xa59
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xa59
	.uleb128 0x3b
	.4byte	.LASF118
	.byte	0x4
	.byte	0xcc
	.4byte	0x6d
	.byte	0
	.uleb128 0xd
	.4byte	0x7af
	.uleb128 0x37
	.4byte	0x1c8
	.byte	0x3
	.4byte	0xa6c
	.4byte	0xa7f
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xa59
	.uleb128 0x38
	.4byte	.LASF117
	.4byte	0x9f8
	.byte	0
	.uleb128 0x37
	.4byte	0x861
	.byte	0x3
	.4byte	0xa8d
	.4byte	0xaa2
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xaa2
	.uleb128 0x3b
	.4byte	.LASF119
	.byte	0x2
	.byte	0x2a
	.4byte	0x7c1
	.byte	0
	.uleb128 0xd
	.4byte	0x92b
	.uleb128 0x3a
	.4byte	0x831
	.byte	0x2
	.byte	0x27
	.byte	0x3
	.4byte	0xab7
	.4byte	0xaca
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xaa2
	.uleb128 0x38
	.4byte	.LASF117
	.4byte	0x9f8
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.4byte	0x719
	.uleb128 0x3a
	.4byte	0x722
	.byte	0x3
	.byte	0x8f
	.byte	0x3
	.4byte	0xae0
	.4byte	0xaf3
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xaf3
	.uleb128 0x38
	.4byte	.LASF117
	.4byte	0x9f8
	.byte	0
	.uleb128 0xd
	.4byte	0xaca
	.uleb128 0x37
	.4byte	0x256
	.byte	0x3
	.4byte	0xb06
	.4byte	0xb26
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xa59
	.uleb128 0x3b
	.4byte	.LASF120
	.byte	0x4
	.byte	0xe6
	.4byte	0x7bb
	.uleb128 0x3b
	.4byte	.LASF121
	.byte	0x4
	.byte	0xe6
	.4byte	0x6d
	.byte	0
	.uleb128 0x37
	.4byte	0x22e
	.byte	0x3
	.4byte	0xb34
	.4byte	0xb54
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xa59
	.uleb128 0x3b
	.4byte	.LASF120
	.byte	0x4
	.byte	0xe1
	.4byte	0x7bb
	.uleb128 0x3b
	.4byte	.LASF121
	.byte	0x4
	.byte	0xe1
	.4byte	0x6d
	.byte	0
	.uleb128 0x37
	.4byte	0x298
	.byte	0x3
	.4byte	0xb62
	.4byte	0xb6c
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xa59
	.byte	0
	.uleb128 0x37
	.4byte	0x27e
	.byte	0x3
	.4byte	0xb7a
	.4byte	0xb84
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xa59
	.byte	0
	.uleb128 0x37
	.4byte	0x5e2
	.byte	0x3
	.4byte	0xb92
	.4byte	0xba9
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xba9
	.uleb128 0x3c
	.uleb128 0x3d
	.4byte	.LASF123
	.byte	0x5
	.byte	0xa6
	.4byte	0x7e9
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	0x8b5
	.uleb128 0x3e
	.4byte	0x50b
	.byte	0x3
	.4byte	0xbcb
	.uleb128 0x14
	.string	"T"
	.4byte	0x7e9
	.uleb128 0x3b
	.4byte	.LASF122
	.byte	0x5
	.byte	0x5b
	.4byte	0x6d
	.byte	0
	.uleb128 0x3e
	.4byte	0x527
	.byte	0x3
	.4byte	0xbf5
	.uleb128 0x14
	.string	"T"
	.4byte	0x7e9
	.uleb128 0x3b
	.4byte	.LASF122
	.byte	0x5
	.byte	0x53
	.4byte	0x6d
	.uleb128 0x3c
	.uleb128 0x3f
	.string	"ret"
	.byte	0x5
	.byte	0x55
	.4byte	0x6d
	.byte	0
	.byte	0
	.uleb128 0x37
	.4byte	0x559
	.byte	0x3
	.4byte	0xc03
	.4byte	0xc0d
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xc0d
	.byte	0
	.uleb128 0xd
	.4byte	0x8a9
	.uleb128 0x37
	.4byte	0x588
	.byte	0x3
	.4byte	0xc20
	.4byte	0xc2a
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xba9
	.byte	0
	.uleb128 0x37
	.4byte	0x5a5
	.byte	0x3
	.4byte	0xc38
	.4byte	0xc4d
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xc0d
	.uleb128 0x3b
	.4byte	.LASF123
	.byte	0x5
	.byte	0x94
	.4byte	0xc4d
	.byte	0
	.uleb128 0xd
	.4byte	0x8af
	.uleb128 0x40
	.4byte	0x6fd
	.4byte	.LFB74
	.4byte	.LFE74-.LFB74
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xc82
	.uleb128 0x41
	.4byte	.LASF151
	.byte	0x1
	.byte	0x50
	.4byte	0xcd
	.4byte	.LLST0
	.uleb128 0x42
	.4byte	.LVL1
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0
	.byte	0
	.uleb128 0x37
	.4byte	0x73b
	.byte	0x2
	.4byte	0xc90
	.4byte	0xcb0
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xaf3
	.uleb128 0x3b
	.4byte	.LASF124
	.byte	0x3
	.byte	0x93
	.4byte	0x6d
	.uleb128 0x3b
	.4byte	.LASF125
	.byte	0x3
	.byte	0x93
	.4byte	0x6d
	.byte	0
	.uleb128 0x37
	.4byte	0x64d
	.byte	0x2
	.4byte	0xcbe
	.4byte	0xcde
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0x9d2
	.uleb128 0x3b
	.4byte	.LASF126
	.byte	0x1
	.byte	0x30
	.4byte	0x49
	.uleb128 0x3b
	.4byte	.LASF127
	.byte	0x1
	.byte	0x30
	.4byte	0x6d
	.byte	0
	.uleb128 0x44
	.4byte	0x8fc
	.4byte	.LFB79
	.4byte	.LFE79-.LFB79
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xcf5
	.4byte	0xeec
	.uleb128 0x45
	.4byte	.LASF116
	.4byte	0xa17
	.4byte	.LLST1
	.uleb128 0x46
	.4byte	.LBB116
	.4byte	.LBE116-.LBB116
	.uleb128 0x47
	.4byte	.LASF119
	.byte	0x2
	.byte	0x6d
	.4byte	0x719
	.uleb128 0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x47
	.4byte	.LASF128
	.byte	0x2
	.byte	0x6f
	.4byte	0x7d9
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x48
	.4byte	0xc82
	.4byte	.LBB117
	.4byte	.LBE117-.LBB117
	.byte	0x2
	.byte	0x6d
	.4byte	0xda8
	.uleb128 0x49
	.4byte	0xca4
	.byte	0x80
	.uleb128 0x4a
	.4byte	0xc99
	.4byte	0x1c200
	.uleb128 0x4b
	.4byte	0xc90
	.4byte	.LLST2
	.uleb128 0x4c
	.4byte	0xa36
	.4byte	.LBB119
	.4byte	.Ldebug_ranges0+0
	.byte	0x3
	.byte	0x94
	.4byte	0xd8f
	.uleb128 0x49
	.4byte	0xa4d
	.byte	0x80
	.uleb128 0x4b
	.4byte	0xa44
	.4byte	.LLST3
	.uleb128 0x4d
	.4byte	.LVL6
	.4byte	0x173f
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x8
	.byte	0x80
	.byte	0
	.byte	0
	.uleb128 0x4d
	.4byte	.LVL8
	.4byte	0x766
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x4
	.byte	0x8
	.byte	0xe1
	.byte	0x39
	.byte	0x24
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x4c
	.4byte	0xa7f
	.4byte	.LBB125
	.4byte	.Ldebug_ranges0+0x20
	.byte	0x2
	.byte	0x6f
	.4byte	0xe34
	.uleb128 0x4b
	.4byte	0xa96
	.4byte	.LLST4
	.uleb128 0x4b
	.4byte	0xa8d
	.4byte	.LLST5
	.uleb128 0x4e
	.4byte	0xcb0
	.4byte	.LBB127
	.4byte	.LBE127-.LBB127
	.byte	0x2
	.byte	0x2b
	.uleb128 0x49
	.4byte	0xcd2
	.byte	0x2
	.uleb128 0x4f
	.4byte	0xcc7
	.2byte	0x100
	.uleb128 0x4b
	.4byte	0xcbe
	.4byte	.LLST5
	.uleb128 0x4d
	.4byte	.LVL10
	.4byte	0x175f
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x57
	.uleb128 0x2
	.byte	0x91
	.sleb128 -60
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x56
	.uleb128 0x1
	.byte	0x32
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x2
	.byte	0x91
	.sleb128 -64
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x3
	.byte	0xa
	.2byte	0x100
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC5
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	_ZN3fdv4Task5entryEPv
	.uleb128 0x43
	.uleb128 0x2
	.byte	0x71
	.sleb128 4
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x43
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4c
	.4byte	0x9ba
	.4byte	.LBB130
	.4byte	.Ldebug_ranges0+0x38
	.byte	0x2
	.byte	0x71
	.4byte	0xe5a
	.uleb128 0x4b
	.4byte	0x9c8
	.4byte	.LLST7
	.uleb128 0x50
	.4byte	.LVL12
	.4byte	0x17a9
	.byte	0
	.uleb128 0x48
	.4byte	0xaa7
	.4byte	.LBB135
	.4byte	.LBE135-.LBB135
	.byte	0x2
	.byte	0x6f
	.4byte	0xe99
	.uleb128 0x4b
	.4byte	0xab7
	.4byte	.LLST8
	.uleb128 0x4e
	.4byte	0x9d7
	.4byte	.LBB136
	.4byte	.LBE136-.LBB136
	.byte	0x2
	.byte	0x27
	.uleb128 0x4b
	.4byte	0x9e5
	.4byte	.LLST8
	.uleb128 0x50
	.4byte	.LVL13
	.4byte	0x17bb
	.byte	0
	.byte	0
	.uleb128 0x48
	.4byte	0xad0
	.4byte	.LBB138
	.4byte	.LBE138-.LBB138
	.byte	0x2
	.byte	0x71
	.4byte	0xed8
	.uleb128 0x4b
	.4byte	0xae0
	.4byte	.LLST10
	.uleb128 0x51
	.4byte	0xa5e
	.4byte	.LBB140
	.4byte	.Ldebug_ranges0+0x50
	.byte	0x3
	.byte	0x8f
	.uleb128 0x4b
	.4byte	0xa6c
	.4byte	.LLST11
	.uleb128 0x50
	.4byte	.LVL15
	.4byte	0x17cd
	.byte	0
	.byte	0
	.uleb128 0x50
	.4byte	.LVL3
	.4byte	0x782
	.uleb128 0x50
	.4byte	.LVL4
	.4byte	0x78d
	.byte	0
	.byte	0
	.uleb128 0x37
	.4byte	0x4b8
	.byte	0x3
	.4byte	0xefa
	.4byte	0xf0f
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0x99d
	.uleb128 0x39
	.string	"str"
	.byte	0x3
	.byte	0x67
	.4byte	0x7c7
	.byte	0
	.uleb128 0x37
	.4byte	0x5c3
	.byte	0x3
	.4byte	0xf1d
	.4byte	0xf3d
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0xc0d
	.uleb128 0x3b
	.4byte	.LASF123
	.byte	0x5
	.byte	0x9b
	.4byte	0xf3d
	.uleb128 0x3c
	.uleb128 0x3f
	.string	"i"
	.byte	0x5
	.byte	0x9e
	.4byte	0x49
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	0x8af
	.uleb128 0x37
	.4byte	0x4d7
	.byte	0x3
	.4byte	0xf50
	.4byte	0xfab
	.uleb128 0x38
	.4byte	.LASF116
	.4byte	0x99d
	.uleb128 0x3b
	.4byte	.LASF123
	.byte	0x3
	.byte	0x6d
	.4byte	0x6d
	.uleb128 0x3c
	.uleb128 0x3d
	.4byte	.LASF129
	.byte	0x3
	.byte	0x6f
	.4byte	0xda
	.uleb128 0x3c
	.uleb128 0x3f
	.string	"i"
	.byte	0x3
	.byte	0x70
	.4byte	0x3e
	.uleb128 0x3c
	.uleb128 0x3f
	.string	"d"
	.byte	0x3
	.byte	0x72
	.4byte	0x6d
	.uleb128 0x3f
	.string	"v"
	.byte	0x3
	.byte	0x75
	.4byte	0x6d
	.uleb128 0x52
	.4byte	0xf9c
	.uleb128 0x3f
	.string	"j"
	.byte	0x3
	.byte	0x73
	.4byte	0x3e
	.byte	0
	.uleb128 0x3c
	.uleb128 0x3f
	.string	"c"
	.byte	0x3
	.byte	0x78
	.4byte	0x25
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x53
	.4byte	0x87b
	.4byte	.LFB78
	.4byte	.LFE78-.LFB78
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xfc2
	.4byte	0x1673
	.uleb128 0x45
	.4byte	.LASF116
	.4byte	0xaa2
	.4byte	.LLST12
	.uleb128 0x54
	.4byte	.Ldebug_ranges0+0x68
	.4byte	0x1666
	.uleb128 0x47
	.4byte	.LASF130
	.byte	0x2
	.byte	0x3a
	.4byte	0x540
	.uleb128 0x4
	.byte	0x91
	.sleb128 -60
	.byte	0x93
	.uleb128 0x4
	.uleb128 0x4c
	.4byte	0xbf5
	.4byte	.LBB214
	.4byte	.Ldebug_ranges0+0x98
	.byte	0x2
	.byte	0x3a
	.4byte	0x102d
	.uleb128 0x55
	.4byte	0xc03
	.uleb128 0x6
	.byte	0xf2
	.4byte	.Ldebug_info0+4056
	.sleb128 0
	.uleb128 0x51
	.4byte	0xbcb
	.4byte	.LBB215
	.4byte	.Ldebug_ranges0+0x98
	.byte	0x5
	.byte	0x86
	.uleb128 0x49
	.4byte	0xbdc
	.byte	0x1
	.uleb128 0x56
	.4byte	.Ldebug_ranges0+0x98
	.uleb128 0x57
	.4byte	0xbe8
	.4byte	.LLST13
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x46
	.4byte	.LBB230
	.4byte	.LBE230-.LBB230
	.uleb128 0x58
	.string	"c"
	.byte	0x2
	.byte	0x3f
	.4byte	0x25
	.4byte	.LLST14
	.uleb128 0x4c
	.4byte	0xeec
	.4byte	.LBB233
	.4byte	.Ldebug_ranges0+0xc8
	.byte	0x2
	.byte	0x43
	.4byte	0x10da
	.uleb128 0x4b
	.4byte	0xf03
	.4byte	.LLST15
	.uleb128 0x4b
	.4byte	0xefa
	.4byte	.LLST16
	.uleb128 0x48
	.4byte	0x97a
	.4byte	.LBB234
	.4byte	.LBE234-.LBB234
	.byte	0x3
	.byte	0x69
	.4byte	0x109a
	.uleb128 0x4b
	.4byte	0x991
	.4byte	.LLST17
	.uleb128 0x4b
	.4byte	0x988
	.4byte	.LLST16
	.uleb128 0x42
	.4byte	.LVL29
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x4e
	.4byte	0x9a2
	.4byte	.LBB236
	.4byte	.LBE236-.LBB236
	.byte	0x3
	.byte	0x6a
	.uleb128 0x4b
	.4byte	0x9b0
	.4byte	.LLST19
	.uleb128 0x59
	.4byte	.LVL97
	.4byte	0x10c7
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3d
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x42
	.4byte	.LVL98
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3a
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4c
	.4byte	0xeec
	.4byte	.LBB238
	.4byte	.Ldebug_ranges0+0xe0
	.byte	0x2
	.byte	0x44
	.4byte	0x1171
	.uleb128 0x4b
	.4byte	0xf03
	.4byte	.LLST20
	.uleb128 0x4b
	.4byte	0xefa
	.4byte	.LLST21
	.uleb128 0x4c
	.4byte	0x97a
	.4byte	.LBB239
	.4byte	.Ldebug_ranges0+0x100
	.byte	0x3
	.byte	0x69
	.4byte	0x1131
	.uleb128 0x4b
	.4byte	0x991
	.4byte	.LLST22
	.uleb128 0x4b
	.4byte	0x988
	.4byte	.LLST21
	.uleb128 0x42
	.4byte	.LVL32
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x4e
	.4byte	0x9a2
	.4byte	.LBB243
	.4byte	.LBE243-.LBB243
	.byte	0x3
	.byte	0x6a
	.uleb128 0x4b
	.4byte	0x9b0
	.4byte	.LLST24
	.uleb128 0x59
	.4byte	.LVL103
	.4byte	0x115e
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3d
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x42
	.4byte	.LVL104
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3a
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4c
	.4byte	0xeec
	.4byte	.LBB245
	.4byte	.Ldebug_ranges0+0x118
	.byte	0x2
	.byte	0x45
	.4byte	0x1208
	.uleb128 0x4b
	.4byte	0xf03
	.4byte	.LLST25
	.uleb128 0x4b
	.4byte	0xefa
	.4byte	.LLST26
	.uleb128 0x4c
	.4byte	0x97a
	.4byte	.LBB246
	.4byte	.Ldebug_ranges0+0x138
	.byte	0x3
	.byte	0x69
	.4byte	0x11c8
	.uleb128 0x4b
	.4byte	0x991
	.4byte	.LLST27
	.uleb128 0x4b
	.4byte	0x988
	.4byte	.LLST26
	.uleb128 0x42
	.4byte	.LVL35
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x4e
	.4byte	0x9a2
	.4byte	.LBB250
	.4byte	.LBE250-.LBB250
	.byte	0x3
	.byte	0x6a
	.uleb128 0x4b
	.4byte	0x9b0
	.4byte	.LLST29
	.uleb128 0x59
	.4byte	.LVL109
	.4byte	0x11f5
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3d
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x42
	.4byte	.LVL110
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3a
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4c
	.4byte	0xeec
	.4byte	.LBB252
	.4byte	.Ldebug_ranges0+0x150
	.byte	0x2
	.byte	0x46
	.4byte	0x129f
	.uleb128 0x4b
	.4byte	0xf03
	.4byte	.LLST30
	.uleb128 0x4b
	.4byte	0xefa
	.4byte	.LLST31
	.uleb128 0x4c
	.4byte	0x97a
	.4byte	.LBB253
	.4byte	.Ldebug_ranges0+0x168
	.byte	0x3
	.byte	0x69
	.4byte	0x125f
	.uleb128 0x4b
	.4byte	0x991
	.4byte	.LLST32
	.uleb128 0x4b
	.4byte	0x988
	.4byte	.LLST31
	.uleb128 0x42
	.4byte	.LVL38
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x4e
	.4byte	0x9a2
	.4byte	.LBB256
	.4byte	.LBE256-.LBB256
	.byte	0x3
	.byte	0x6a
	.uleb128 0x4b
	.4byte	0x9b0
	.4byte	.LLST34
	.uleb128 0x59
	.4byte	.LVL40
	.4byte	0x128c
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3d
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x42
	.4byte	.LVL41
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3a
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x5a
	.4byte	.LBB259
	.4byte	.LBE259-.LBB259
	.4byte	0x13d1
	.uleb128 0x5b
	.string	"t"
	.byte	0x2
	.byte	0x4d
	.4byte	0x7e9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x48
	.4byte	0xc12
	.4byte	.LBB260
	.4byte	.LBE260-.LBB260
	.byte	0x2
	.byte	0x4d
	.4byte	0x1331
	.uleb128 0x4b
	.4byte	0xc20
	.4byte	.LLST35
	.uleb128 0x4e
	.4byte	0xb84
	.4byte	.LBB261
	.4byte	.LBE261-.LBB261
	.byte	0x5
	.byte	0x91
	.uleb128 0x4b
	.4byte	0xb92
	.4byte	.LLST35
	.uleb128 0x46
	.4byte	.LBB262
	.4byte	.LBE262-.LBB262
	.uleb128 0x5c
	.4byte	0xb9c
	.uleb128 0x50
	.4byte	.LVL45
	.4byte	0x798
	.uleb128 0x5d
	.4byte	.LVL46
	.4byte	0x17df
	.4byte	0x1325
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x8
	.byte	0x24
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0x91
	.sleb128 -60
	.byte	0x6
	.byte	0
	.uleb128 0x50
	.4byte	.LVL47
	.4byte	0x7a3
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4e
	.4byte	0xc2a
	.4byte	.LBB263
	.4byte	.LBE263-.LBB263
	.byte	0x2
	.byte	0x51
	.uleb128 0x4b
	.4byte	0xc41
	.4byte	.LLST37
	.uleb128 0x4b
	.4byte	0xc38
	.4byte	.LLST38
	.uleb128 0x4e
	.4byte	0xf0f
	.4byte	.LBB264
	.4byte	.LBE264-.LBB264
	.byte	0x5
	.byte	0x96
	.uleb128 0x4b
	.4byte	0xf26
	.4byte	.LLST37
	.uleb128 0x4b
	.4byte	0xf1d
	.4byte	.LLST38
	.uleb128 0x5a
	.4byte	.LBB266
	.4byte	.LBE266-.LBB266
	.4byte	0x139b
	.uleb128 0x57
	.4byte	0xf32
	.4byte	.LLST41
	.uleb128 0x4d
	.4byte	.LVL50
	.4byte	0x1804
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0x91
	.sleb128 -52
	.byte	0x6
	.byte	0
	.byte	0
	.uleb128 0x50
	.4byte	.LVL49
	.4byte	0x798
	.uleb128 0x5d
	.4byte	.LVL51
	.4byte	0x1819
	.4byte	0x13c5
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x8
	.byte	0x24
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0x91
	.sleb128 -60
	.byte	0x6
	.byte	0
	.uleb128 0x50
	.4byte	.LVL52
	.4byte	0x7a3
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x54
	.4byte	.Ldebug_ranges0+0x180
	.4byte	0x165b
	.uleb128 0x5b
	.string	"t"
	.byte	0x2
	.byte	0x56
	.4byte	0x7e9
	.uleb128 0x3
	.byte	0x91
	.sleb128 -112
	.uleb128 0x48
	.4byte	0xc12
	.4byte	.LBB268
	.4byte	.LBE268-.LBB268
	.byte	0x2
	.byte	0x56
	.4byte	0x145f
	.uleb128 0x4b
	.4byte	0xc20
	.4byte	.LLST42
	.uleb128 0x4e
	.4byte	0xb84
	.4byte	.LBB269
	.4byte	.LBE269-.LBB269
	.byte	0x5
	.byte	0x91
	.uleb128 0x4b
	.4byte	0xb92
	.4byte	.LLST42
	.uleb128 0x46
	.4byte	.LBB270
	.4byte	.LBE270-.LBB270
	.uleb128 0x5c
	.4byte	0xb9c
	.uleb128 0x50
	.4byte	.LVL54
	.4byte	0x798
	.uleb128 0x5d
	.4byte	.LVL55
	.4byte	0x17df
	.4byte	0x1453
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x8
	.byte	0x24
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0x91
	.sleb128 -60
	.byte	0x6
	.byte	0
	.uleb128 0x50
	.4byte	.LVL56
	.4byte	0x7a3
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4c
	.4byte	0xeec
	.4byte	.LBB271
	.4byte	.Ldebug_ranges0+0x198
	.byte	0x2
	.byte	0x57
	.4byte	0x14f6
	.uleb128 0x4b
	.4byte	0xf03
	.4byte	.LLST44
	.uleb128 0x4b
	.4byte	0xefa
	.4byte	.LLST45
	.uleb128 0x4c
	.4byte	0x97a
	.4byte	.LBB272
	.4byte	.Ldebug_ranges0+0x1b8
	.byte	0x3
	.byte	0x69
	.4byte	0x14b6
	.uleb128 0x4b
	.4byte	0x991
	.4byte	.LLST46
	.uleb128 0x4b
	.4byte	0x988
	.4byte	.LLST45
	.uleb128 0x42
	.4byte	.LVL65
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x4e
	.4byte	0x9a2
	.4byte	.LBB277
	.4byte	.LBE277-.LBB277
	.byte	0x3
	.byte	0x6a
	.uleb128 0x4b
	.4byte	0x9b0
	.4byte	.LLST48
	.uleb128 0x59
	.4byte	.LVL59
	.4byte	0x14e3
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3d
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x42
	.4byte	.LVL60
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3a
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4c
	.4byte	0xeec
	.4byte	.LBB281
	.4byte	.Ldebug_ranges0+0x1d8
	.byte	0x2
	.byte	0x58
	.4byte	0x158d
	.uleb128 0x4b
	.4byte	0xf03
	.4byte	.LLST49
	.uleb128 0x4b
	.4byte	0xefa
	.4byte	.LLST50
	.uleb128 0x4c
	.4byte	0x97a
	.4byte	.LBB282
	.4byte	.Ldebug_ranges0+0x200
	.byte	0x3
	.byte	0x69
	.4byte	0x154d
	.uleb128 0x4b
	.4byte	0x991
	.4byte	.LLST51
	.uleb128 0x4b
	.4byte	0x988
	.4byte	.LLST50
	.uleb128 0x42
	.4byte	.LVL74
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.uleb128 0x4e
	.4byte	0x9a2
	.4byte	.LBB287
	.4byte	.LBE287-.LBB287
	.byte	0x3
	.byte	0x6a
	.uleb128 0x4b
	.4byte	0x9b0
	.4byte	.LLST53
	.uleb128 0x59
	.4byte	.LVL67
	.4byte	0x157a
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3d
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.uleb128 0x42
	.4byte	.LVL68
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3a
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4c
	.4byte	0xf42
	.4byte	.LBB293
	.4byte	.Ldebug_ranges0+0x220
	.byte	0x2
	.byte	0x59
	.4byte	0x161b
	.uleb128 0x4b
	.4byte	0xf59
	.4byte	.LLST54
	.uleb128 0x4b
	.4byte	0xf50
	.4byte	.LLST55
	.uleb128 0x56
	.4byte	.Ldebug_ranges0+0x220
	.uleb128 0x57
	.4byte	0xf65
	.4byte	.LLST56
	.uleb128 0x56
	.4byte	.Ldebug_ranges0+0x230
	.uleb128 0x57
	.4byte	0xf71
	.4byte	.LLST57
	.uleb128 0x56
	.4byte	.Ldebug_ranges0+0x250
	.uleb128 0x57
	.4byte	0xf7b
	.4byte	.LLST58
	.uleb128 0x57
	.4byte	0xf84
	.4byte	.LLST59
	.uleb128 0x54
	.4byte	.Ldebug_ranges0+0x278
	.4byte	0x15f8
	.uleb128 0x57
	.4byte	0xf92
	.4byte	.LLST60
	.byte	0
	.uleb128 0x46
	.4byte	.LBB299
	.4byte	.LBE299-.LBB299
	.uleb128 0x57
	.4byte	0xf9d
	.4byte	.LLST61
	.uleb128 0x42
	.4byte	.LVL85
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7e
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x51
	.4byte	0x9a2
	.4byte	.LBB317
	.4byte	.Ldebug_ranges0+0x298
	.byte	0x2
	.byte	0x59
	.uleb128 0x4b
	.4byte	0x9b0
	.4byte	.LLST62
	.uleb128 0x59
	.4byte	.LVL93
	.4byte	0x1648
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3d
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.byte	0
	.uleb128 0x42
	.4byte	.LVL94
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x3a
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7d
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x50
	.4byte	.LVL43
	.4byte	0x1838
	.byte	0
	.byte	0
	.uleb128 0x42
	.4byte	.LVL24
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x9
	.byte	0xff
	.byte	0
	.byte	0
	.uleb128 0x5e
	.4byte	.LASF131
	.byte	0x2
	.byte	0x76
	.4byte	.LFB86
	.4byte	.LFE86-.LFB86
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x171b
	.uleb128 0x4c
	.4byte	0x9fd
	.4byte	.LBB338
	.4byte	.Ldebug_ranges0+0x2b0
	.byte	0x2
	.byte	0x78
	.4byte	0x170b
	.uleb128 0x4b
	.4byte	0xa0d
	.4byte	.LLST63
	.uleb128 0x4e
	.4byte	0xcb0
	.4byte	.LBB340
	.4byte	.LBE340-.LBB340
	.byte	0x2
	.byte	0x66
	.uleb128 0x49
	.4byte	0xcd2
	.byte	0x2
	.uleb128 0x4f
	.4byte	0xcc7
	.2byte	0x100
	.uleb128 0x4b
	.4byte	0xcbe
	.4byte	.LLST63
	.uleb128 0x4d
	.4byte	.LVL117
	.4byte	0x175f
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x57
	.uleb128 0x2
	.byte	0x7c
	.sleb128 4
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x56
	.uleb128 0x1
	.byte	0x32
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x3
	.byte	0xa
	.2byte	0x100
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x5
	.byte	0x3
	.4byte	.LC5
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	_ZN3fdv4Task5entryEPv
	.uleb128 0x43
	.uleb128 0x2
	.byte	0x71
	.sleb128 4
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x43
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x4d
	.4byte	.LVL114
	.4byte	0x183f
	.uleb128 0x43
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x38
	.byte	0
	.byte	0
	.uleb128 0x5f
	.4byte	.LASF132
	.byte	0x5
	.byte	0x2e
	.4byte	0x172a
	.4byte	0x14000
	.uleb128 0xd
	.4byte	0x6d
	.uleb128 0x32
	.4byte	0xaca
	.4byte	0x173f
	.uleb128 0x33
	.4byte	0xc6
	.byte	0
	.byte	0
	.uleb128 0x60
	.4byte	.LASF133
	.byte	0xb
	.2byte	0x5ee
	.4byte	0x17f
	.4byte	0x175f
	.uleb128 0x7
	.4byte	0x78
	.uleb128 0x7
	.4byte	0x78
	.uleb128 0x7
	.4byte	0x30
	.byte	0
	.uleb128 0x60
	.4byte	.LASF134
	.byte	0xa
	.2byte	0x5c4
	.4byte	0x7f
	.4byte	0x1798
	.uleb128 0x7
	.4byte	0x10b
	.uleb128 0x7
	.4byte	0x16e
	.uleb128 0x7
	.4byte	0x54
	.uleb128 0x7
	.4byte	0xcd
	.uleb128 0x7
	.4byte	0x78
	.uleb128 0x7
	.4byte	0x1798
	.uleb128 0x7
	.4byte	0x179
	.uleb128 0x7
	.4byte	0x179e
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.4byte	0x127
	.uleb128 0xa
	.byte	0x4
	.4byte	0x17a4
	.uleb128 0xd
	.4byte	0x163
	.uleb128 0x61
	.4byte	.LASF135
	.byte	0xa
	.2byte	0x2e6
	.4byte	0x17bb
	.uleb128 0x7
	.4byte	0x127
	.byte	0
	.uleb128 0x61
	.4byte	.LASF136
	.byte	0xa
	.2byte	0x1d7
	.4byte	0x17cd
	.uleb128 0x7
	.4byte	0x127
	.byte	0
	.uleb128 0x61
	.4byte	.LASF137
	.byte	0xb
	.2byte	0x3a9
	.4byte	0x17df
	.uleb128 0x7
	.4byte	0x17f
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF138
	.byte	0x7
	.byte	0x13
	.4byte	0x100
	.4byte	0x17fe
	.uleb128 0x7
	.4byte	0xad
	.uleb128 0x7
	.4byte	0x17fe
	.uleb128 0x7
	.4byte	0xad
	.byte	0
	.uleb128 0xa
	.byte	0x4
	.4byte	0xad
	.uleb128 0x1e
	.4byte	.LASF139
	.byte	0x7
	.byte	0x11
	.4byte	0x100
	.4byte	0x1819
	.uleb128 0x7
	.4byte	0xa2
	.byte	0
	.uleb128 0x1e
	.4byte	.LASF140
	.byte	0x7
	.byte	0x12
	.4byte	0x100
	.4byte	0x1838
	.uleb128 0x7
	.4byte	0xad
	.uleb128 0x7
	.4byte	0x17fe
	.uleb128 0x7
	.4byte	0xad
	.byte	0
	.uleb128 0x62
	.4byte	.LASF152
	.byte	0xc
	.byte	0x1c
	.uleb128 0x63
	.4byte	.LASF141
	.4byte	.LASF153
	.4byte	0xcd
	.uleb128 0x7
	.4byte	0xb8
	.byte	0
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x4
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x28
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x39
	.byte	0x1
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0x2
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x2f
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x2
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x8
	.byte	0
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x18
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x32
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x19
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x4c
	.uleb128 0xb
	.uleb128 0x4d
	.uleb128 0x18
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x4c
	.uleb128 0xb
	.uleb128 0x4d
	.uleb128 0x18
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x4c
	.uleb128 0xb
	.uleb128 0x4d
	.uleb128 0x18
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.uleb128 0x32
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x21
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x63
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x26
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x28
	.uleb128 0x2
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x63
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2a
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x2b
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x2c
	.uleb128 0x10
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2d
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x2f
	.uleb128 0x1c
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x31
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x4c
	.uleb128 0xb
	.uleb128 0x4d
	.uleb128 0x18
	.uleb128 0x1d
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x64
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x32
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x33
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x34
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x35
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x36
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x37
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x38
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x39
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3b
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3c
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x3d
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x40
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x41
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x42
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x43
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x44
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x45
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x46
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x47
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x48
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x49
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x4a
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x4b
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x4c
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4d
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x4e
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x4f
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x50
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x51
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x52
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x53
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x64
	.uleb128 0x13
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x54
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x55
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x56
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x57
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x58
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x59
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5a
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x5c
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5d
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5e
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5f
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x60
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x61
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x62
	.uleb128 0x2e
	.byte	0
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x63
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LVL0
	.4byte	.LVL1-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL1-1
	.4byte	.LFE74
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL2
	.4byte	.LVL3-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL3-1
	.4byte	.LVL17
	.2byte	0x1
	.byte	0x5f
	.4byte	.LVL17
	.4byte	.LFE79
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL4
	.4byte	.LVL7
	.2byte	0x3
	.byte	0x91
	.sleb128 -52
	.byte	0x9f
	.4byte	.LVL7
	.4byte	.LVL16
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL16
	.4byte	.LVL18
	.2byte	0x3
	.byte	0x91
	.sleb128 -52
	.byte	0x9f
	.4byte	.LVL18
	.4byte	.LFE79
	.2byte	0x3
	.byte	0x71
	.sleb128 -52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LVL5
	.4byte	.LVL18
	.2byte	0x3
	.byte	0x91
	.sleb128 -48
	.byte	0x9f
	.4byte	.LVL18
	.4byte	.LFE79
	.2byte	0x3
	.byte	0x71
	.sleb128 -48
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LVL8
	.4byte	.LVL16
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL16
	.4byte	.LVL18
	.2byte	0x3
	.byte	0x91
	.sleb128 -52
	.byte	0x9f
	.4byte	.LVL18
	.4byte	.LFE79
	.2byte	0x3
	.byte	0x71
	.sleb128 -52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LVL8
	.4byte	.LVL9
	.2byte	0x3
	.byte	0x91
	.sleb128 -64
	.byte	0x9f
	.4byte	.LVL9
	.4byte	.LVL10-1
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL10-1
	.4byte	.LVL18
	.2byte	0x3
	.byte	0x91
	.sleb128 -64
	.byte	0x9f
	.4byte	.LVL18
	.4byte	.LFE79
	.2byte	0x3
	.byte	0x71
	.sleb128 -64
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST7:
	.4byte	.LVL11
	.4byte	.LVL17
	.2byte	0x1
	.byte	0x5f
	.4byte	.LVL17
	.4byte	.LFE79
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST8:
	.4byte	.LVL12
	.4byte	.LVL18
	.2byte	0x3
	.byte	0x91
	.sleb128 -64
	.byte	0x9f
	.4byte	.LVL18
	.4byte	.LFE79
	.2byte	0x3
	.byte	0x71
	.sleb128 -64
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST10:
	.4byte	.LVL13
	.4byte	.LVL16
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL16
	.4byte	.LVL18
	.2byte	0x3
	.byte	0x91
	.sleb128 -52
	.byte	0x9f
	.4byte	.LVL18
	.4byte	.LFE79
	.2byte	0x3
	.byte	0x71
	.sleb128 -52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST11:
	.4byte	.LVL14
	.4byte	.LVL18
	.2byte	0x3
	.byte	0x91
	.sleb128 -48
	.byte	0x9f
	.4byte	.LVL18
	.4byte	.LFE79
	.2byte	0x3
	.byte	0x71
	.sleb128 -48
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST12:
	.4byte	.LVL19
	.4byte	.LVL23
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL23
	.4byte	.LFE78
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST13:
	.4byte	.LVL20
	.4byte	.LVL21
	.2byte	0x1
	.byte	0x55
	.4byte	.LVL22
	.4byte	.LFE78
	.2byte	0x2
	.byte	0x91
	.sleb128 -60
	.4byte	0
	.4byte	0
.LLST14:
	.4byte	.LVL25
	.4byte	.LVL27
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL42
	.4byte	.LVL43-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL44
	.4byte	.LVL45-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL53
	.4byte	.LVL54-1
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LLST15:
	.4byte	.LVL26
	.4byte	.LVL42
	.2byte	0x6
	.byte	0x3
	.4byte	.LC11
	.byte	0x9f
	.4byte	.LVL95
	.4byte	.LVL113
	.2byte	0x6
	.byte	0x3
	.4byte	.LC11
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST16:
	.4byte	.LVL26
	.4byte	.LVL30
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL95
	.4byte	.LVL100
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST17:
	.4byte	.LVL26
	.4byte	.LVL27
	.2byte	0x6
	.byte	0x3
	.4byte	.LC11
	.byte	0x9f
	.4byte	.LVL27
	.4byte	.LVL28
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL28
	.4byte	.LVL30
	.2byte	0x3
	.byte	0x7d
	.sleb128 -1
	.byte	0x9f
	.4byte	.LVL95
	.4byte	.LVL96
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL96
	.4byte	.LVL99
	.2byte	0x3
	.byte	0x7d
	.sleb128 -1
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST19:
	.4byte	.LVL95
	.4byte	.LVL100
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST20:
	.4byte	.LVL30
	.4byte	.LVL42
	.2byte	0x6
	.byte	0x3
	.4byte	.LC17
	.byte	0x9f
	.4byte	.LVL100
	.4byte	.LVL113
	.2byte	0x6
	.byte	0x3
	.4byte	.LC17
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST21:
	.4byte	.LVL30
	.4byte	.LVL33
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL100
	.4byte	.LVL106
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST22:
	.4byte	.LVL30
	.4byte	.LVL31
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL31
	.4byte	.LVL33
	.2byte	0x3
	.byte	0x7d
	.sleb128 -1
	.byte	0x9f
	.4byte	.LVL100
	.4byte	.LVL101
	.2byte	0x6
	.byte	0x3
	.4byte	.LC17
	.byte	0x9f
	.4byte	.LVL101
	.4byte	.LVL102
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL102
	.4byte	.LVL105
	.2byte	0x3
	.byte	0x7d
	.sleb128 -1
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST24:
	.4byte	.LVL101
	.4byte	.LVL106
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST25:
	.4byte	.LVL33
	.4byte	.LVL42
	.2byte	0x6
	.byte	0x3
	.4byte	.LC19
	.byte	0x9f
	.4byte	.LVL106
	.4byte	.LVL113
	.2byte	0x6
	.byte	0x3
	.4byte	.LC19
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST26:
	.4byte	.LVL33
	.4byte	.LVL36
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL106
	.4byte	.LVL112
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST27:
	.4byte	.LVL33
	.4byte	.LVL34
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL34
	.4byte	.LVL36
	.2byte	0x3
	.byte	0x7d
	.sleb128 -1
	.byte	0x9f
	.4byte	.LVL106
	.4byte	.LVL107
	.2byte	0x6
	.byte	0x3
	.4byte	.LC19
	.byte	0x9f
	.4byte	.LVL107
	.4byte	.LVL108
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL108
	.4byte	.LVL111
	.2byte	0x3
	.byte	0x7d
	.sleb128 -1
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST29:
	.4byte	.LVL107
	.4byte	.LVL112
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST30:
	.4byte	.LVL36
	.4byte	.LVL42
	.2byte	0x6
	.byte	0x3
	.4byte	.LC21
	.byte	0x9f
	.4byte	.LVL112
	.4byte	.LVL113
	.2byte	0x6
	.byte	0x3
	.4byte	.LC21
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST31:
	.4byte	.LVL36
	.4byte	.LVL42
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL112
	.4byte	.LVL113
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST32:
	.4byte	.LVL36
	.4byte	.LVL37
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL37
	.4byte	.LVL42
	.2byte	0x3
	.byte	0x7d
	.sleb128 -1
	.byte	0x9f
	.4byte	.LVL112
	.4byte	.LVL113
	.2byte	0x6
	.byte	0x3
	.4byte	.LC21
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST34:
	.4byte	.LVL39
	.4byte	.LVL42
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST35:
	.4byte	.LVL44
	.4byte	.LVL53
	.2byte	0x6
	.byte	0xf2
	.4byte	.Ldebug_info0+4056
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST37:
	.4byte	.LVL48
	.4byte	.LVL53
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LLST38:
	.4byte	.LVL48
	.4byte	.LVL53
	.2byte	0x6
	.byte	0xf2
	.4byte	.Ldebug_info0+4056
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST41:
	.4byte	.LVL49
	.4byte	.LVL50
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL50
	.4byte	.LVL53
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST42:
	.4byte	.LVL53
	.4byte	.LVL95
	.2byte	0x6
	.byte	0xf2
	.4byte	.Ldebug_info0+4056
	.sleb128 0
	.4byte	.LVL113
	.4byte	.LFE78
	.2byte	0x6
	.byte	0xf2
	.4byte	.Ldebug_info0+4056
	.sleb128 0
	.4byte	0
	.4byte	0
.LLST44:
	.4byte	.LVL57
	.4byte	.LVL95
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL113
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x51
	.4byte	0
	.4byte	0
.LLST45:
	.4byte	.LVL57
	.4byte	.LVL61
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL63
	.4byte	.LVL66
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST46:
	.4byte	.LVL57
	.4byte	.LVL58
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL58
	.4byte	.LVL62
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL63
	.4byte	.LVL66
	.2byte	0x1
	.byte	0x5d
	.4byte	0
	.4byte	0
.LLST48:
	.4byte	.LVL58
	.4byte	.LVL61
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST49:
	.4byte	.LVL61
	.4byte	.LVL62
	.2byte	0x4
	.byte	0x91
	.sleb128 -96
	.byte	0x9f
	.4byte	.LVL62
	.4byte	.LVL63
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL66
	.4byte	.LVL95
	.2byte	0x4
	.byte	0x91
	.sleb128 -96
	.byte	0x9f
	.4byte	.LVL113
	.4byte	.LFE78
	.2byte	0x4
	.byte	0x91
	.sleb128 -96
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST50:
	.4byte	.LVL61
	.4byte	.LVL63
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL66
	.4byte	.LVL69
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL72
	.4byte	.LVL75
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST51:
	.4byte	.LVL61
	.4byte	.LVL62
	.2byte	0x4
	.byte	0x91
	.sleb128 -96
	.byte	0x9f
	.4byte	.LVL62
	.4byte	.LVL63
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL66
	.4byte	.LVL75
	.2byte	0x1
	.byte	0x5d
	.4byte	0
	.4byte	0
.LLST53:
	.4byte	.LVL66
	.4byte	.LVL69
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST54:
	.4byte	.LVL70
	.4byte	.LVL71
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL71
	.4byte	.LVL72
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL75
	.4byte	.LVL91
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL113
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x5c
	.4byte	0
	.4byte	0
.LLST55:
	.4byte	.LVL70
	.4byte	.LVL72
	.2byte	0x1
	.byte	0x54
	.4byte	.LVL75
	.4byte	.LVL95
	.2byte	0x1
	.byte	0x5e
	.4byte	.LVL113
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x5e
	.4byte	0
	.4byte	0
.LLST56:
	.4byte	.LVL70
	.4byte	.LVL72
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL75
	.4byte	.LVL85
	.2byte	0x2
	.byte	0x91
	.sleb128 -64
	.4byte	.LVL85
	.4byte	.LVL86
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL86
	.4byte	.LVL95
	.2byte	0x2
	.byte	0x91
	.sleb128 -64
	.4byte	.LVL113
	.4byte	.LFE78
	.2byte	0x2
	.byte	0x91
	.sleb128 -64
	.4byte	0
	.4byte	0
.LLST57:
	.4byte	.LVL70
	.4byte	.LVL72
	.2byte	0x2
	.byte	0x39
	.byte	0x9f
	.4byte	.LVL75
	.4byte	.LVL87
	.2byte	0x1
	.byte	0x5f
	.4byte	.LVL87
	.4byte	.LVL88
	.2byte	0x3
	.byte	0x76
	.sleb128 1
	.byte	0x9f
	.4byte	.LVL88
	.4byte	.LVL89
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL89
	.4byte	.LVL90
	.2byte	0x1
	.byte	0x5f
	.4byte	.LVL90
	.4byte	.LVL93-1
	.2byte	0x1
	.byte	0x56
	.4byte	.LVL93-1
	.4byte	.LVL95
	.2byte	0x1
	.byte	0x5f
	.4byte	.LVL113
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x5f
	.4byte	0
	.4byte	0
.LLST58:
	.4byte	.LVL75
	.4byte	.LVL78
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL79
	.4byte	.LVL83
	.2byte	0x1
	.byte	0x5d
	.4byte	.LVL83
	.4byte	.LVL84
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL89
	.4byte	.LVL90
	.2byte	0x2
	.byte	0x31
	.byte	0x9f
	.4byte	.LVL113
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x5d
	.4byte	0
	.4byte	0
.LLST59:
	.4byte	.LVL82
	.4byte	.LVL83
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL113
	.4byte	.LFE78
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LLST60:
	.4byte	.LVL75
	.4byte	.LVL76
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL76
	.4byte	.LVL77
	.2byte	0x3
	.byte	0x73
	.sleb128 -1
	.byte	0x9f
	.4byte	.LVL79
	.4byte	.LVL80
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL83
	.4byte	.LVL84
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL89
	.4byte	.LVL90
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST61:
	.4byte	.LVL84
	.4byte	.LVL85-1
	.2byte	0x3
	.byte	0x74
	.sleb128 48
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST62:
	.4byte	.LVL92
	.4byte	.LVL95
	.2byte	0x1
	.byte	0x5d
	.4byte	0
	.4byte	0
.LLST63:
	.4byte	.LVL115
	.4byte	.LVL116
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL116
	.4byte	.LVL118
	.2byte	0x1
	.byte	0x5c
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x34
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.LFB74
	.4byte	.LFE74-.LFB74
	.4byte	.LFB79
	.4byte	.LFE79-.LFB79
	.4byte	.LFB78
	.4byte	.LFE78-.LFB78
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.4byte	.LBB119
	.4byte	.LBE119
	.4byte	.LBB123
	.4byte	.LBE123
	.4byte	.LBB124
	.4byte	.LBE124
	.4byte	0
	.4byte	0
	.4byte	.LBB125
	.4byte	.LBE125
	.4byte	.LBB133
	.4byte	.LBE133
	.4byte	0
	.4byte	0
	.4byte	.LBB130
	.4byte	.LBE130
	.4byte	.LBB134
	.4byte	.LBE134
	.4byte	0
	.4byte	0
	.4byte	.LBB140
	.4byte	.LBE140
	.4byte	.LBB143
	.4byte	.LBE143
	.4byte	0
	.4byte	0
	.4byte	.LBB213
	.4byte	.LBE213
	.4byte	.LBB329
	.4byte	.LBE329
	.4byte	.LBB330
	.4byte	.LBE330
	.4byte	.LBB331
	.4byte	.LBE331
	.4byte	.LBB332
	.4byte	.LBE332
	.4byte	0
	.4byte	0
	.4byte	.LBB214
	.4byte	.LBE214
	.4byte	.LBB225
	.4byte	.LBE225
	.4byte	.LBB226
	.4byte	.LBE226
	.4byte	.LBB227
	.4byte	.LBE227
	.4byte	.LBB228
	.4byte	.LBE228
	.4byte	0
	.4byte	0
	.4byte	.LBB233
	.4byte	.LBE233
	.4byte	.LBB322
	.4byte	.LBE322
	.4byte	0
	.4byte	0
	.4byte	.LBB238
	.4byte	.LBE238
	.4byte	.LBB323
	.4byte	.LBE323
	.4byte	.LBB324
	.4byte	.LBE324
	.4byte	0
	.4byte	0
	.4byte	.LBB239
	.4byte	.LBE239
	.4byte	.LBB242
	.4byte	.LBE242
	.4byte	0
	.4byte	0
	.4byte	.LBB245
	.4byte	.LBE245
	.4byte	.LBB325
	.4byte	.LBE325
	.4byte	.LBB326
	.4byte	.LBE326
	.4byte	0
	.4byte	0
	.4byte	.LBB246
	.4byte	.LBE246
	.4byte	.LBB249
	.4byte	.LBE249
	.4byte	0
	.4byte	0
	.4byte	.LBB252
	.4byte	.LBE252
	.4byte	.LBB327
	.4byte	.LBE327
	.4byte	0
	.4byte	0
	.4byte	.LBB253
	.4byte	.LBE253
	.4byte	.LBB258
	.4byte	.LBE258
	.4byte	0
	.4byte	0
	.4byte	.LBB267
	.4byte	.LBE267
	.4byte	.LBB328
	.4byte	.LBE328
	.4byte	0
	.4byte	0
	.4byte	.LBB271
	.4byte	.LBE271
	.4byte	.LBB280
	.4byte	.LBE280
	.4byte	.LBB291
	.4byte	.LBE291
	.4byte	0
	.4byte	0
	.4byte	.LBB272
	.4byte	.LBE272
	.4byte	.LBB276
	.4byte	.LBE276
	.4byte	.LBB279
	.4byte	.LBE279
	.4byte	0
	.4byte	0
	.4byte	.LBB281
	.4byte	.LBE281
	.4byte	.LBB290
	.4byte	.LBE290
	.4byte	.LBB292
	.4byte	.LBE292
	.4byte	.LBB315
	.4byte	.LBE315
	.4byte	0
	.4byte	0
	.4byte	.LBB282
	.4byte	.LBE282
	.4byte	.LBB286
	.4byte	.LBE286
	.4byte	.LBB289
	.4byte	.LBE289
	.4byte	0
	.4byte	0
	.4byte	.LBB293
	.4byte	.LBE293
	.4byte	.LBB313
	.4byte	.LBE313
	.4byte	.LBB314
	.4byte	.LBE314
	.4byte	.LBB316
	.4byte	.LBE316
	.4byte	.LBB321
	.4byte	.LBE321
	.4byte	0
	.4byte	0
	.4byte	.LBB296
	.4byte	.LBE296
	.4byte	.LBB304
	.4byte	.LBE304
	.4byte	.LBB305
	.4byte	.LBE305
	.4byte	.LBB306
	.4byte	.LBE306
	.4byte	0
	.4byte	0
	.4byte	.LBB297
	.4byte	.LBE297
	.4byte	.LBB300
	.4byte	.LBE300
	.4byte	.LBB302
	.4byte	.LBE302
	.4byte	0
	.4byte	0
	.4byte	.LBB317
	.4byte	.LBE317
	.4byte	.LBB320
	.4byte	.LBE320
	.4byte	0
	.4byte	0
	.4byte	.LBB338
	.4byte	.LBE338
	.4byte	.LBB343
	.4byte	.LBE343
	.4byte	0
	.4byte	0
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.LFB74
	.4byte	.LFE74
	.4byte	.LFB79
	.4byte	.LFE79
	.4byte	.LFB78
	.4byte	.LFE78
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF70:
	.string	"getSectorsCount<Task1::MyStore>"
.LASF151:
	.string	"params"
.LASF143:
	.string	"src/user_main.cpp"
.LASF22:
	.string	"SPI_FLASH_RESULT_TIMEOUT"
.LASF128:
	.string	"task1"
.LASF33:
	.string	"Queue"
.LASF66:
	.string	"_ZN3fdv6Serial7writelnEPKc"
.LASF37:
	.string	"_ZN3fdv5QueueIhE4sendERhm"
.LASF17:
	.string	"unsigned int"
.LASF50:
	.string	"_ZN3fdv6Serial4peekEv"
.LASF79:
	.string	"_vptr$Task"
.LASF125:
	.string	"rxBufferLength"
.LASF61:
	.string	"_ZN3fdv5QueueIhE5clearEv"
.LASF76:
	.string	"_ZN3fdv6Serial11writeUInt32Em"
.LASF144:
	.string	"C:\\\\sviluppo\\\\ESP8266\\\\projects\\\\ESPWebFramework"
.LASF25:
	.string	"portTickType"
.LASF52:
	.string	"_ZN3fdv6Serial9availableEv"
.LASF40:
	.string	"_ZN3fdv5QueueIhE7receiveEPhm"
.LASF150:
	.string	"__vtbl_ptr_type"
.LASF86:
	.string	"_ZN3fdv4Task5delayEm"
.LASF78:
	.string	"Task"
.LASF29:
	.string	"ulParameters"
.LASF103:
	.string	"EnableInterrupts"
.LASF84:
	.string	"_ZN3fdv4Task6resumeEv"
.LASF35:
	.string	"send"
.LASF115:
	.string	"_ZN8MainTask3runEv"
.LASF113:
	.string	"_ZN5Task13runEv"
.LASF96:
	.string	"_ZN3fdv14HardwareSerial8reconfigEm"
.LASF140:
	.string	"spi_flash_write"
.LASF8:
	.string	"uint32_t"
.LASF3:
	.string	"int8_t"
.LASF110:
	.string	"~Task1"
.LASF13:
	.string	"float"
.LASF89:
	.string	"allocate<Task1::MyStore>"
.LASF88:
	.string	"_ZN3fdv4Task3runEv"
.LASF44:
	.string	"_ZN3fdv5QueueIhE9availableEv"
.LASF7:
	.string	"int16_t"
.LASF12:
	.string	"long long unsigned int"
.LASF106:
	.string	"MyStore"
.LASF98:
	.string	"DisableWatchDog"
.LASF137:
	.string	"vQueueDelete"
.LASF132:
	.string	"FLASHDATABASE"
.LASF69:
	.string	"FlashAllocator"
.LASF45:
	.string	"_vptr$Serial"
.LASF93:
	.string	"m_data"
.LASF97:
	.string	"DisableStdOut"
.LASF42:
	.string	"_ZN3fdv5QueueIhE4peekEPhm"
.LASF148:
	.string	"_ZN3fdv10FlashValueIN5Task17MyStoreEE3setERKS2_"
.LASF94:
	.string	"s_serials"
.LASF83:
	.string	"resume"
.LASF59:
	.string	"clear"
.LASF114:
	.string	"MainTask"
.LASF107:
	.string	"nome"
.LASF67:
	.string	"writeUInt32"
.LASF26:
	.string	"xTaskHandle"
.LASF111:
	.string	"Task1"
.LASF92:
	.string	"HardwareSerial"
.LASF73:
	.string	"operator const Task1::MyStore"
.LASF81:
	.string	"suspend"
.LASF56:
	.string	"waitForData"
.LASF58:
	.string	"_ZN3fdv6Serial4readEPht"
.LASF21:
	.string	"SPI_FLASH_RESULT_ERR"
.LASF109:
	.string	"m_serial"
.LASF95:
	.string	"reconfig"
.LASF147:
	.string	"s_pos"
.LASF145:
	.string	"16SpiFlashOpResult"
.LASF101:
	.string	"DisableInterrupts"
.LASF105:
	.string	"char"
.LASF54:
	.string	"_ZN3fdv6Serial5writeEh"
.LASF39:
	.string	"receive"
.LASF112:
	.string	"_ZNK3fdv10FlashValueIN5Task17MyStoreEE3getEv"
.LASF47:
	.string	"Serial"
.LASF15:
	.string	"uint16"
.LASF131:
	.string	"user_init"
.LASF20:
	.string	"SPI_FLASH_RESULT_OK"
.LASF63:
	.string	"_ZN3fdv6Serial5writeEPKht"
.LASF65:
	.string	"writeln"
.LASF2:
	.string	"uint8_t"
.LASF51:
	.string	"_ZN3fdv6Serial4readEv"
.LASF133:
	.string	"xQueueGenericCreate"
.LASF36:
	.string	"sendFromISR"
.LASF32:
	.string	"m_handle"
.LASF11:
	.string	"long long int"
.LASF48:
	.string	"write"
.LASF64:
	.string	"_ZN3fdv6Serial5writeEPKc"
.LASF77:
	.string	"_ZN3fdv10FlashValueIN5Task17MyStoreEEaSERKS2_"
.LASF99:
	.string	"_ZN3fdv13DisableStdOutEv"
.LASF153:
	.string	"_Znwj"
.LASF80:
	.string	"~Task"
.LASF28:
	.string	"ulLengthInBytes"
.LASF19:
	.string	"bool"
.LASF134:
	.string	"xTaskGenericCreate"
.LASF102:
	.string	"_ZN3fdv17DisableInterruptsEv"
.LASF91:
	.string	"~HardwareSerial"
.LASF75:
	.string	"operator="
.LASF16:
	.string	"uint32"
.LASF30:
	.string	"xMemoryRegion"
.LASF87:
	.string	"_ZN3fdv6Serial3putEh"
.LASF118:
	.string	"queueLength"
.LASF141:
	.string	"operator new"
.LASF68:
	.string	"xMEMORY_REGION"
.LASF4:
	.string	"uint16_t"
.LASF136:
	.string	"vTaskDelete"
.LASF23:
	.string	"SpiFlashOpResult"
.LASF116:
	.string	"this"
.LASF152:
	.string	"system_restart"
.LASF46:
	.string	"~Serial"
.LASF146:
	.string	"Queue<unsigned char>"
.LASF6:
	.string	"short int"
.LASF142:
	.string	"GNU C++ 4.8.2 -fpreprocessed -mlongcalls -mtext-section-literals -g -Os -O2 -fno-inline-functions -fno-exceptions -fno-rtti"
.LASF10:
	.string	"long int"
.LASF43:
	.string	"available"
.LASF85:
	.string	"delay"
.LASF127:
	.string	"priority"
.LASF71:
	.string	"FlashValue<Task1::MyStore>"
.LASF139:
	.string	"spi_flash_erase_sector"
.LASF108:
	.string	"cognome"
.LASF138:
	.string	"spi_flash_read"
.LASF55:
	.string	"_ZN3fdv6Serial5flushEv"
.LASF49:
	.string	"read"
.LASF117:
	.string	"__in_chrg"
.LASF53:
	.string	"flush"
.LASF126:
	.string	"stackDepth"
.LASF18:
	.string	"sizetype"
.LASF9:
	.string	"long unsigned int"
.LASF74:
	.string	"_ZNK3fdv10FlashValueIN5Task17MyStoreEEcvKS2_Ev"
.LASF119:
	.string	"serial"
.LASF27:
	.string	"pvBaseAddress"
.LASF90:
	.string	"entry"
.LASF31:
	.string	"xQueueHandle"
.LASF0:
	.string	"unsigned char"
.LASF149:
	.string	"_ZN3fdv4Task5entryEPv"
.LASF72:
	.string	"FlashValue"
.LASF124:
	.string	"baud_rate"
.LASF129:
	.string	"printZero"
.LASF135:
	.string	"vTaskSuspend"
.LASF100:
	.string	"_ZN3fdv15DisableWatchDogEv"
.LASF38:
	.string	"_ZN3fdv5QueueIhE11sendFromISRERh"
.LASF120:
	.string	"item"
.LASF1:
	.string	"signed char"
.LASF121:
	.string	"msTimeOut"
.LASF5:
	.string	"short unsigned int"
.LASF24:
	.string	"pdTASK_CODE"
.LASF62:
	.string	"_ZN3fdv6Serial12writeNewLineEv"
.LASF34:
	.string	"~Queue"
.LASF14:
	.string	"double"
.LASF122:
	.string	"itemsCount"
.LASF130:
	.string	"mystore"
.LASF57:
	.string	"_ZN3fdv6Serial11waitForDataEm"
.LASF82:
	.string	"_ZN3fdv4Task7suspendEv"
.LASF41:
	.string	"peek"
.LASF123:
	.string	"value"
.LASF104:
	.string	"_ZN3fdv16EnableInterruptsEv"
.LASF60:
	.string	"writeNewLine"
	.ident	"GCC: (GNU) 4.8.2"

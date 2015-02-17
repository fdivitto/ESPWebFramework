	.file	"fdvserial.cpp"
	.text
.Ltext0:
	.section	.irom0.text,"ax",@progbits
	.literal_position
	.align	4
	.global	_ZN3fdv16dummy_write_charEc
	.type	_ZN3fdv16dummy_write_charEc, @function
_ZN3fdv16dummy_write_charEc:
.LFB56:
	.file 1 "src/fdvserial.cpp"
	.loc 1 51 0
.LVL0:
	ret.n
.LFE56:
	.size	_ZN3fdv16dummy_write_charEc, .-_ZN3fdv16dummy_write_charEc
	.text
	.literal_position
	.literal .LC0, 1610612744
	.literal .LC1, 1610612764
	.literal .LC2, 1610612752
	.literal .LC3, 1610612736
	.literal .LC4, _ZN3fdv14HardwareSerial9s_serialsE
	.align	4
	.global	_ZN3fdv25HardwareSerial_rx_handlerEv
	.type	_ZN3fdv25HardwareSerial_rx_handlerEv, @function
_ZN3fdv25HardwareSerial_rx_handlerEv:
.LFB58:
	.loc 1 70 0
	.loc 1 70 0
	addi	sp, sp, -32
.LCFI0:
	s32i.n	a15, sp, 12
.LBB22:
	.loc 1 71 0
	l32r	a15, .LC0
.LBE22:
	.loc 1 70 0
	s32i.n	a12, sp, 24
.LBB33:
	.loc 1 71 0
	memw
	l32i.n	a2, a15, 0
.LVL1:
.LBE33:
	.loc 1 70 0
	s32i.n	a14, sp, 16
	s32i.n	a0, sp, 28
	s32i.n	a13, sp, 20
.LBB34:
.LBB23:
.LBB24:
.LBB25:
	.loc 1 77 0
	l32r	a12, .LC1
	l32r	a14, .LC3
.LBE25:
.LBE24:
.LBE23:
	.loc 1 73 0
	beqz.n	a2, .L2
.L20:
.LBB32:
.LBB31:
	.loc 1 75 0
	bbci	a2, 0, .L4
.LBB29:
	.loc 1 77 0 discriminator 1
	memw
	l32i.n	a2, a12, 0
.LVL2:
	l32r	a13, .LC4
	extui	a2, a2, 0, 8
	bnez.n	a2, .L16
.L6:
	.loc 1 82 0
	l32r	a2, .LC2
	movi.n	a3, 1
	memw
	s32i.n	a3, a2, 0
.LBE29:
	j	.L4
.L16:
.LBB30:
.LBB26:
.LBB27:
.LBB28:
	.file 2 "src/fdvserial.h"
	.loc 2 161 0
	l32i.n	a2, a13, 0
.LBE28:
.LBE27:
	.loc 1 79 0
	memw
	l32i.n	a3, a14, 0
.LVL3:
	.loc 1 80 0
	l32i.n	a4, a2, 0
	extui	a3, a3, 0, 8
.LVL4:
	l32i.n	a4, a4, 0
	callx0	a4
.LVL5:
.LBE26:
	.loc 1 77 0
	memw
	l32i.n	a2, a12, 0
	extui	a2, a2, 0, 8
	bnez.n	a2, .L16
	j	.L6
.LVL6:
.L4:
.LBE30:
.LBE31:
	.loc 1 84 0
	memw
	l32i.n	a2, a15, 0
.LVL7:
.LBE32:
	.loc 1 73 0
	bnez.n	a2, .L20
.L2:
.LBE34:
	.loc 1 86 0
	l32i.n	a0, sp, 28
	l32i.n	a12, sp, 24
	l32i.n	a13, sp, 20
	l32i.n	a14, sp, 16
	l32i.n	a15, sp, 12
	addi	sp, sp, 32
.LCFI1:
	ret.n
.LFE58:
	.size	_ZN3fdv25HardwareSerial_rx_handlerEv, .-_ZN3fdv25HardwareSerial_rx_handlerEv
	.section	.irom0.text
	.literal_position
	.literal .LC5, 1610612764
	.literal .LC7, 1610612736
	.align	4
	.global	_ZN3fdv14HardwareSerial5writeEh
	.type	_ZN3fdv14HardwareSerial5writeEh, @function
_ZN3fdv14HardwareSerial5writeEh:
.LFB60:
	.loc 1 132 0
.LVL8:
	l32r	a4, .LC5
	.loc 1 132 0
	extui	a3, a3, 0, 8
.LBB35:
.LBB36:
	.loc 1 136 0
	movi	a5, 0x7d
.LVL9:
.L24:
	.loc 1 135 0
	memw
	l32i.n	a2, a4, 0
.LVL10:
	.loc 1 136 0
	extui	a2, a2, 16, 8
.LVL11:
	bltu	a5, a2, .L24
.LBE36:
	.loc 1 139 0
	l32r	a2, .LC7
	memw
	s32i.n	a3, a2, 0
	ret.n
.LBE35:
.LFE60:
	.size	_ZN3fdv14HardwareSerial5writeEh, .-_ZN3fdv14HardwareSerial5writeEh
	.section	.text._ZN3fdv14HardwareSerial3putEh,"axG",@progbits,_ZN3fdv14HardwareSerial3putEh,comdat
	.literal_position
	.align	4
	.weak	_ZN3fdv14HardwareSerial3putEh
	.type	_ZN3fdv14HardwareSerial3putEh, @function
_ZN3fdv14HardwareSerial3putEh:
.LFB50:
	.loc 2 165 0
.LVL12:
	addi	sp, sp, -48
.LCFI2:
.LVL13:
.LBB40:
.LBB41:
	.file 3 "src/fdvsync.h"
	.loc 3 221 0
	movi.n	a6, 0
	.loc 3 222 0
	l32i.n	a2, a2, 4
.LVL14:
.LBE41:
.LBE40:
	.loc 2 165 0
	s8i	a3, sp, 16
.LBB44:
.LBB42:
	.loc 3 222 0
	mov.n	a4, sp
	addi	a3, sp, 16
.LVL15:
	mov.n	a5, a6
.LBE42:
.LBE44:
	.loc 2 165 0
	s32i.n	a0, sp, 44
.LBB45:
.LBB43:
	.loc 3 221 0
	s32i.n	a6, sp, 0
	.loc 3 222 0
	call0	xQueueGenericSendFromISR
.LVL16:
.LBE43:
.LBE45:
	.loc 2 168 0
	l32i.n	a0, sp, 44
	addi	sp, sp, 48
.LCFI3:
.LVL17:
	ret.n
.LFE50:
	.size	_ZN3fdv14HardwareSerial3putEh, .-_ZN3fdv14HardwareSerial3putEh
	.section	.text._ZN3fdv14HardwareSerial4peekEv,"axG",@progbits,_ZN3fdv14HardwareSerial4peekEv,comdat
	.literal_position
	.align	4
	.weak	_ZN3fdv14HardwareSerial4peekEv
	.type	_ZN3fdv14HardwareSerial4peekEv, @function
_ZN3fdv14HardwareSerial4peekEv:
.LFB51:
	.loc 2 170 0
.LVL18:
	addi	sp, sp, -32
.LCFI4:
.LVL19:
.LBB46:
.LBB47:
.LBB48:
	.loc 3 232 0
	l32i.n	a2, a2, 4
.LVL20:
	mov.n	a3, sp
	movi.n	a4, 0
	movi.n	a5, 1
.LBE48:
.LBE47:
.LBE46:
	.loc 2 170 0
	s32i.n	a0, sp, 28
.LBB51:
.LBB50:
.LBB49:
	.loc 3 232 0
	call0	xQueueGenericReceive
.LVL21:
.LBE49:
.LBE50:
	.loc 2 174 0
	l8ui	a4, sp, 0
	movi.n	a3, -1
.LBE51:
	.loc 2 176 0
	l32i.n	a0, sp, 28
.LBB52:
	.loc 2 174 0
	movnez	a3, a4, a2
.LBE52:
	.loc 2 176 0
	mov.n	a2, a3
	addi	sp, sp, 32
.LCFI5:
.LVL22:
	ret.n
.LFE51:
	.size	_ZN3fdv14HardwareSerial4peekEv, .-_ZN3fdv14HardwareSerial4peekEv
	.global	__udivsi3
	.section	.text._ZN3fdv14HardwareSerial11waitForDataEm,"axG",@progbits,_ZN3fdv14HardwareSerial11waitForDataEm,comdat
	.literal_position
	.align	4
	.weak	_ZN3fdv14HardwareSerial11waitForDataEm
	.type	_ZN3fdv14HardwareSerial11waitForDataEm, @function
_ZN3fdv14HardwareSerial11waitForDataEm:
.LFB55:
	.loc 2 196 0
.LVL23:
	addi	sp, sp, -32
.LCFI6:
	s32i.n	a12, sp, 24
	mov.n	a12, a2
.LVL24:
.LBB53:
.LBB54:
.LBB55:
	.loc 3 232 0
	mov.n	a2, a3
.LVL25:
	movi.n	a3, 0xa
.LVL26:
.LBE55:
.LBE54:
.LBE53:
	.loc 2 196 0
	s32i.n	a0, sp, 28
.LBB60:
.LBB58:
.LBB56:
	.loc 3 232 0
	call0	__udivsi3
.LVL27:
	mov.n	a4, a2
	l32i.n	a2, a12, 4
	mov.n	a3, sp
	movi.n	a5, 1
	call0	xQueueGenericReceive
.LVL28:
.LBE56:
.LBE58:
.LBE60:
	.loc 2 200 0
	l32i.n	a0, sp, 28
.LBB61:
.LBB59:
.LBB57:
	.loc 3 232 0
	mov.n	a4, a2
	movi.n	a3, 1
	movi.n	a2, 0
	movnez	a2, a3, a4
.LBE57:
.LBE59:
.LBE61:
	.loc 2 200 0
	l32i.n	a12, sp, 24
.LVL29:
	addi	sp, sp, 32
.LCFI7:
.LVL30:
	ret.n
.LFE55:
	.size	_ZN3fdv14HardwareSerial11waitForDataEm, .-_ZN3fdv14HardwareSerial11waitForDataEm
	.section	.text._ZN3fdv14HardwareSerial4readEv,"axG",@progbits,_ZN3fdv14HardwareSerial4readEv,comdat
	.literal_position
	.align	4
	.weak	_ZN3fdv14HardwareSerial4readEv
	.type	_ZN3fdv14HardwareSerial4readEv, @function
_ZN3fdv14HardwareSerial4readEv:
.LFB52:
	.loc 2 178 0
.LVL31:
	addi	sp, sp, -32
.LCFI8:
.LVL32:
.LBB62:
.LBB63:
.LBB64:
	.loc 3 227 0
	movi.n	a4, 0
	l32i.n	a2, a2, 4
.LVL33:
	mov.n	a3, sp
	mov.n	a5, a4
.LBE64:
.LBE63:
.LBE62:
	.loc 2 178 0
	s32i.n	a0, sp, 28
.LBB67:
.LBB66:
.LBB65:
	.loc 3 227 0
	call0	xQueueGenericReceive
.LVL34:
.LBE65:
.LBE66:
	.loc 2 182 0
	l8ui	a4, sp, 0
	movi.n	a3, -1
.LBE67:
	.loc 2 184 0
	l32i.n	a0, sp, 28
.LBB68:
	.loc 2 182 0
	movnez	a3, a4, a2
.LBE68:
	.loc 2 184 0
	mov.n	a2, a3
	addi	sp, sp, 32
.LCFI9:
.LVL35:
	ret.n
.LFE52:
	.size	_ZN3fdv14HardwareSerial4readEv, .-_ZN3fdv14HardwareSerial4readEv
	.section	.text._ZN3fdv14HardwareSerial9availableEv,"axG",@progbits,_ZN3fdv14HardwareSerial9availableEv,comdat
	.literal_position
	.align	4
	.weak	_ZN3fdv14HardwareSerial9availableEv
	.type	_ZN3fdv14HardwareSerial9availableEv, @function
_ZN3fdv14HardwareSerial9availableEv:
.LFB53:
	.loc 2 186 0
.LVL36:
.LBB69:
.LBB70:
	.loc 3 242 0
	l32i.n	a2, a2, 4
.LVL37:
.LBE70:
.LBE69:
	.loc 2 186 0
	addi	sp, sp, -16
.LCFI10:
	s32i.n	a0, sp, 12
.LBB72:
.LBB71:
	.loc 3 242 0
	call0	uxQueueMessagesWaiting
.LVL38:
.LBE71:
.LBE72:
	.loc 2 189 0
	l32i.n	a0, sp, 12
	extui	a2, a2, 0, 16
	addi	sp, sp, 16
.LCFI11:
	ret.n
.LFE53:
	.size	_ZN3fdv14HardwareSerial9availableEv, .-_ZN3fdv14HardwareSerial9availableEv
	.section	.text._ZN3fdv14HardwareSerial5flushEv,"axG",@progbits,_ZN3fdv14HardwareSerial5flushEv,comdat
	.literal_position
	.align	4
	.weak	_ZN3fdv14HardwareSerial5flushEv
	.type	_ZN3fdv14HardwareSerial5flushEv, @function
_ZN3fdv14HardwareSerial5flushEv:
.LFB54:
	.loc 2 191 0
.LVL39:
.LBB73:
.LBB74:
	.loc 3 237 0
	l32i.n	a2, a2, 4
.LVL40:
.LBE74:
.LBE73:
	.loc 2 191 0
	addi	sp, sp, -16
.LCFI12:
.LBB77:
.LBB75:
	.loc 3 237 0
	movi.n	a3, 0
.LBE75:
.LBE77:
	.loc 2 191 0
	s32i.n	a0, sp, 12
.LBB78:
.LBB76:
	.loc 3 237 0
	call0	xQueueGenericReset
.LVL41:
.LBE76:
.LBE78:
	.loc 2 194 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
.LCFI13:
	ret.n
.LFE54:
	.size	_ZN3fdv14HardwareSerial5flushEv, .-_ZN3fdv14HardwareSerial5flushEv
	.section	.irom0.text
	.literal_position
	.literal .LC8, _ZN3fdv16dummy_write_charEc
	.align	4
	.global	_ZN3fdv13DisableStdOutEv
	.type	_ZN3fdv13DisableStdOutEv, @function
_ZN3fdv13DisableStdOutEv:
.LFB57:
	.loc 1 56 0
	.loc 1 57 0
	l32r	a2, .LC8
	.loc 1 56 0
	addi	sp, sp, -16
.LCFI14:
	s32i.n	a0, sp, 12
	.loc 1 57 0
	call0	os_install_putc1
.LVL42:
	.loc 1 58 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
.LCFI15:
	ret.n
.LFE57:
	.size	_ZN3fdv13DisableStdOutEv, .-_ZN3fdv13DisableStdOutEv
	.literal_position
	.literal .LC9, 1610612764
	.literal .LC10, 16711680
	.literal .LC11, 1610614808
	.literal .LC12, 1610614804
	.literal .LC13, 1610612768
	.literal .LC14, -32769
	.literal .LC15, 1610612772
	.literal .LC16, -8388609
	.literal .LC17, 80000000
	.literal .LC18, 393216
	.literal .LC19, -393217
	.literal .LC20, 1610612752
	.literal .LC21, -16711681
	.literal .LC22, -2113924095
	.literal .LC23, 1610612748
	.literal .LC24, _ZN3fdv25HardwareSerial_rx_handlerEv
	.align	4
	.global	_ZN3fdv14HardwareSerial8reconfigEm
	.type	_ZN3fdv14HardwareSerial8reconfigEm, @function
_ZN3fdv14HardwareSerial8reconfigEm:
.LFB59:
	.loc 1 90 0
.LVL43:
	addi	sp, sp, -16
.LCFI16:
	l32r	a4, .LC9
	l32r	a2, .LC10
.LVL44:
	s32i.n	a0, sp, 12
	s32i.n	a12, sp, 8
	s32i.n	a13, sp, 4
	s32i.n	a14, sp, 0
.L38:
.LBB79:
	.loc 1 92 0 discriminator 1
	memw
	l32i.n	a12, a4, 0
	and	a12, a12, a2
	bnez.n	a12, .L38
	.loc 1 94 0
	l32r	a2, .LC11
	movi	a5, -0x81
	memw
	l32i.n	a6, a2, 0
	.loc 1 95 0
	l32r	a4, .LC12
	.loc 1 94 0
	and	a5, a6, a5
	memw
	s32i.n	a5, a2, 0
	.loc 1 95 0
	memw
	l32i.n	a6, a4, 0
	movi	a5, -0x131
	and	a6, a6, a5
	memw
	s32i.n	a6, a4, 0
	memw
	l32i.n	a6, a4, 0
	.loc 1 99 0
	l32r	a13, .LC13
	.loc 1 95 0
	memw
	s32i.n	a6, a4, 0
	.loc 1 96 0
	memw
	l32i.n	a4, a2, 0
	.loc 1 100 0
	l32r	a14, .LC15
	.loc 1 96 0
	and	a5, a4, a5
	memw
	s32i.n	a5, a2, 0
	memw
	l32i.n	a4, a2, 0
	memw
	s32i.n	a4, a2, 0
	.loc 1 99 0
	memw
	l32i.n	a4, a13, 0
	l32r	a2, .LC14
	and	a2, a4, a2
	memw
	s32i.n	a2, a13, 0
	.loc 1 100 0
	memw
	l32i.n	a5, a14, 0
	l32r	a4, .LC16
	.loc 1 102 0
	l32r	a2, .LC17
	.loc 1 100 0
	and	a4, a5, a4
	memw
	s32i.n	a4, a14, 0
	.loc 1 102 0
	call0	__udivsi3
.LVL45:
	mov.n	a3, a2
	mov.n	a2, a12
	call0	uart_div_modify
.LVL46:
	.loc 1 106 0
	movi.n	a2, 0x1c
	memw
	s32i.n	a2, a13, 0
	.loc 1 109 0
	memw
	l32i.n	a3, a13, 0
	l32r	a2, .LC18
	.loc 1 123 0
	l32r	a4, .LC23
	.loc 1 109 0
	or	a2, a3, a2
	memw
	s32i.n	a2, a13, 0
	.loc 1 110 0
	memw
	l32i.n	a3, a13, 0
	l32r	a2, .LC19
	and	a2, a3, a2
	memw
	s32i.n	a2, a13, 0
.LVL47:
	.loc 1 116 0
	l32r	a2, .LC20
	movi	a3, 0x1ff
	memw
	s32i.n	a3, a2, 0
	.loc 1 117 0
	memw
	l32i.n	a3, a14, 0
	l32r	a2, .LC21
	and	a2, a3, a2
.LVL48:
	.loc 1 120 0
	l32r	a3, .LC22
	or	a2, a2, a3
.LVL49:
	.loc 1 121 0
	memw
	s32i.n	a2, a14, 0
	.loc 1 123 0
	memw
	l32i.n	a3, a4, 0
	movi	a2, -0x200
.LVL50:
	and	a2, a3, a2
	memw
	s32i.n	a2, a4, 0
.LVL51:
	.loc 1 124 0
	memw
	l32i.n	a5, a4, 0
	movi.n	a2, 1
	or	a5, a5, a2
	.loc 1 125 0
	l32r	a3, .LC24
	movi.n	a2, 5
	.loc 1 124 0
	memw
	s32i.n	a5, a4, 0
	.loc 1 125 0
	call0	_xt_isr_attach
.LVL52:
	.loc 1 127 0
	movi.n	a2, 0x20
	call0	_xt_isr_unmask
.LVL53:
.LBE79:
	.loc 1 128 0
	l32i.n	a0, sp, 12
	l32i.n	a12, sp, 8
	l32i.n	a13, sp, 4
	l32i.n	a14, sp, 0
	addi	sp, sp, 16
.LCFI17:
	ret.n
.LFE59:
	.size	_ZN3fdv14HardwareSerial8reconfigEm, .-_ZN3fdv14HardwareSerial8reconfigEm
	.weak	_ZTVN3fdv14HardwareSerialE
	.section	.rodata._ZTVN3fdv14HardwareSerialE,"aG",@progbits,_ZTVN3fdv14HardwareSerialE,comdat
	.align	8
	.type	_ZTVN3fdv14HardwareSerialE, @object
	.size	_ZTVN3fdv14HardwareSerialE, 36
_ZTVN3fdv14HardwareSerialE:
	.word	0
	.word	0
	.word	_ZN3fdv14HardwareSerial3putEh
	.word	_ZN3fdv14HardwareSerial5writeEh
	.word	_ZN3fdv14HardwareSerial4peekEv
	.word	_ZN3fdv14HardwareSerial4readEv
	.word	_ZN3fdv14HardwareSerial9availableEv
	.word	_ZN3fdv14HardwareSerial5flushEv
	.word	_ZN3fdv14HardwareSerial11waitForDataEm
	.global	_ZN3fdv14HardwareSerial9s_serialsE
	.section	.bss
	.align	4
	.type	_ZN3fdv14HardwareSerial9s_serialsE, @object
	.size	_ZN3fdv14HardwareSerial9s_serialsE, 4
_ZN3fdv14HardwareSerial9s_serialsE:
	.zero	4
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
	.4byte	.LFB56
	.4byte	.LFE56-.LFB56
	.align	4
.LEFDE0:
.LSFDE2:
	.4byte	.LEFDE2-.LASFDE2
.LASFDE2:
	.4byte	.Lframe0
	.4byte	.LFB58
	.4byte	.LFE58-.LFB58
	.byte	0x4
	.4byte	.LCFI0-.LFB58
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI1-.LCFI0
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE2:
.LSFDE4:
	.4byte	.LEFDE4-.LASFDE4
.LASFDE4:
	.4byte	.Lframe0
	.4byte	.LFB60
	.4byte	.LFE60-.LFB60
	.align	4
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB50
	.4byte	.LFE50-.LFB50
	.byte	0x4
	.4byte	.LCFI2-.LFB50
	.byte	0xe
	.uleb128 0x30
	.byte	0x4
	.4byte	.LCFI3-.LCFI2
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB51
	.4byte	.LFE51-.LFB51
	.byte	0x4
	.4byte	.LCFI4-.LFB51
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI5-.LCFI4
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB55
	.4byte	.LFE55-.LFB55
	.byte	0x4
	.4byte	.LCFI6-.LFB55
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI7-.LCFI6
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB52
	.4byte	.LFE52-.LFB52
	.byte	0x4
	.4byte	.LCFI8-.LFB52
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.4byte	.LCFI9-.LCFI8
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE12:
.LSFDE14:
	.4byte	.LEFDE14-.LASFDE14
.LASFDE14:
	.4byte	.Lframe0
	.4byte	.LFB53
	.4byte	.LFE53-.LFB53
	.byte	0x4
	.4byte	.LCFI10-.LFB53
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI11-.LCFI10
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE14:
.LSFDE16:
	.4byte	.LEFDE16-.LASFDE16
.LASFDE16:
	.4byte	.Lframe0
	.4byte	.LFB54
	.4byte	.LFE54-.LFB54
	.byte	0x4
	.4byte	.LCFI12-.LFB54
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI13-.LCFI12
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE16:
.LSFDE18:
	.4byte	.LEFDE18-.LASFDE18
.LASFDE18:
	.4byte	.Lframe0
	.4byte	.LFB57
	.4byte	.LFE57-.LFB57
	.byte	0x4
	.4byte	.LCFI14-.LFB57
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI15-.LCFI14
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE18:
.LSFDE20:
	.4byte	.LEFDE20-.LASFDE20
.LASFDE20:
	.4byte	.Lframe0
	.4byte	.LFB59
	.4byte	.LFE59-.LFB59
	.byte	0x4
	.4byte	.LCFI16-.LFB59
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI17-.LCFI16
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE20:
	.text
.Letext0:
	.file 4 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/espressif/c_types.h"
	.file 5 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/freertos/portmacro.h"
	.file 6 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/freertos/queue.h"
	.file 7 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/espressif/esp_misc.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xc71
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF98
	.byte	0x4
	.4byte	.LASF99
	.4byte	.LASF100
	.4byte	.Ldebug_ranges0+0x108
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.4byte	.LASF2
	.byte	0x4
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
	.byte	0x4
	.byte	0xc
	.4byte	0x49
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x2
	.4byte	.LASF6
	.byte	0x4
	.byte	0xe
	.4byte	0x50
	.uleb128 0x2
	.4byte	.LASF7
	.byte	0x4
	.byte	0xf
	.4byte	0x6d
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF8
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.4byte	.LASF9
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x3
	.byte	0x4
	.byte	0x4
	.4byte	.LASF12
	.uleb128 0x3
	.byte	0x8
	.byte	0x4
	.4byte	.LASF13
	.uleb128 0x2
	.4byte	.LASF14
	.byte	0x4
	.byte	0x18
	.4byte	0x30
	.uleb128 0x2
	.4byte	.LASF15
	.byte	0x4
	.byte	0x21
	.4byte	0xad
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF16
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF17
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x3
	.byte	0x1
	.byte	0x2
	.4byte	.LASF18
	.uleb128 0x6
	.uleb128 0x2
	.4byte	.LASF19
	.byte	0x5
	.byte	0x61
	.4byte	0x6d
	.uleb128 0x2
	.4byte	.LASF20
	.byte	0x5
	.byte	0xc1
	.4byte	0xe2
	.uleb128 0x7
	.byte	0x4
	.4byte	0xcb
	.uleb128 0x2
	.4byte	.LASF21
	.byte	0x6
	.byte	0x53
	.4byte	0xc2
	.uleb128 0x8
	.string	"fdv"
	.byte	0x3
	.byte	0x27
	.4byte	0x605
	.uleb128 0x9
	.4byte	.LASF101
	.byte	0x4
	.byte	0x3
	.byte	0xc7
	.4byte	0x227
	.uleb128 0xa
	.4byte	.LASF34
	.byte	0x3
	.byte	0xf7
	.4byte	0xe8
	.byte	0
	.uleb128 0xb
	.4byte	.LASF22
	.byte	0x3
	.byte	0xcc
	.byte	0x1
	.4byte	0x126
	.4byte	0x131
	.uleb128 0xc
	.4byte	0x605
	.uleb128 0xd
	.4byte	0x62
	.byte	0
	.uleb128 0xb
	.4byte	.LASF23
	.byte	0x3
	.byte	0xd1
	.byte	0x1
	.4byte	0x141
	.4byte	0x14c
	.uleb128 0xc
	.4byte	0x605
	.uleb128 0xc
	.4byte	0xb4
	.byte	0
	.uleb128 0xe
	.4byte	.LASF24
	.byte	0x3
	.byte	0xd6
	.4byte	.LASF26
	.4byte	0xc4
	.byte	0x1
	.4byte	0x164
	.4byte	0x174
	.uleb128 0xc
	.4byte	0x605
	.uleb128 0xd
	.4byte	0x60b
	.uleb128 0xd
	.4byte	0x62
	.byte	0
	.uleb128 0xe
	.4byte	.LASF25
	.byte	0x3
	.byte	0xdb
	.4byte	.LASF27
	.4byte	0xc4
	.byte	0x1
	.4byte	0x18c
	.4byte	0x197
	.uleb128 0xc
	.4byte	0x605
	.uleb128 0xd
	.4byte	0x60b
	.byte	0
	.uleb128 0xe
	.4byte	.LASF28
	.byte	0x3
	.byte	0xe1
	.4byte	.LASF29
	.4byte	0xc4
	.byte	0x1
	.4byte	0x1af
	.4byte	0x1bf
	.uleb128 0xc
	.4byte	0x605
	.uleb128 0xd
	.4byte	0x611
	.uleb128 0xd
	.4byte	0x62
	.byte	0
	.uleb128 0xe
	.4byte	.LASF30
	.byte	0x3
	.byte	0xe6
	.4byte	.LASF31
	.4byte	0xc4
	.byte	0x1
	.4byte	0x1d7
	.4byte	0x1e7
	.uleb128 0xc
	.4byte	0x605
	.uleb128 0xd
	.4byte	0x611
	.uleb128 0xd
	.4byte	0x62
	.byte	0
	.uleb128 0xf
	.4byte	.LASF48
	.byte	0x3
	.byte	0xeb
	.4byte	.LASF50
	.byte	0x1
	.4byte	0x1fb
	.4byte	0x201
	.uleb128 0xc
	.4byte	0x605
	.byte	0
	.uleb128 0xe
	.4byte	.LASF32
	.byte	0x3
	.byte	0xf0
	.4byte	.LASF33
	.4byte	0x62
	.byte	0x1
	.4byte	0x219
	.4byte	0x21f
	.uleb128 0xc
	.4byte	0x605
	.byte	0
	.uleb128 0x10
	.string	"T"
	.4byte	0x30
	.byte	0
	.uleb128 0x11
	.4byte	.LASF36
	.byte	0x4
	.byte	0x2
	.byte	0x3b
	.4byte	0x227
	.4byte	0x443
	.uleb128 0x12
	.byte	0x2
	.byte	0x8f
	.4byte	0x3e9
	.uleb128 0x13
	.4byte	.LASF35
	.4byte	0x650
	.byte	0
	.byte	0x1
	.uleb128 0x14
	.4byte	.LASF36
	.byte	0x1
	.4byte	0x257
	.4byte	0x262
	.uleb128 0xc
	.4byte	0x617
	.uleb128 0xd
	.4byte	0x660
	.byte	0
	.uleb128 0x14
	.4byte	.LASF36
	.byte	0x1
	.4byte	0x270
	.4byte	0x276
	.uleb128 0xc
	.4byte	0x617
	.byte	0
	.uleb128 0x15
	.string	"put"
	.byte	0x2
	.byte	0x3f
	.4byte	.LASF64
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0
	.4byte	0x227
	.byte	0x1
	.4byte	0x292
	.4byte	0x29d
	.uleb128 0xc
	.4byte	0x617
	.uleb128 0xd
	.4byte	0x25
	.byte	0
	.uleb128 0x16
	.4byte	.LASF37
	.byte	0x2
	.byte	0x40
	.4byte	.LASF43
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x1
	.4byte	0x227
	.byte	0x1
	.4byte	0x2b9
	.4byte	0x2c4
	.uleb128 0xc
	.4byte	0x617
	.uleb128 0xd
	.4byte	0x25
	.byte	0
	.uleb128 0x17
	.4byte	.LASF30
	.byte	0x2
	.byte	0x41
	.4byte	.LASF39
	.4byte	0x57
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x2
	.4byte	0x227
	.byte	0x1
	.4byte	0x2e4
	.4byte	0x2ea
	.uleb128 0xc
	.4byte	0x617
	.byte	0
	.uleb128 0x17
	.4byte	.LASF38
	.byte	0x2
	.byte	0x42
	.4byte	.LASF40
	.4byte	0x57
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x3
	.4byte	0x227
	.byte	0x1
	.4byte	0x30a
	.4byte	0x310
	.uleb128 0xc
	.4byte	0x617
	.byte	0
	.uleb128 0x17
	.4byte	.LASF32
	.byte	0x2
	.byte	0x43
	.4byte	.LASF41
	.4byte	0x3e
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x4
	.4byte	0x227
	.byte	0x1
	.4byte	0x330
	.4byte	0x336
	.uleb128 0xc
	.4byte	0x617
	.byte	0
	.uleb128 0x16
	.4byte	.LASF42
	.byte	0x2
	.byte	0x44
	.4byte	.LASF44
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x5
	.4byte	0x227
	.byte	0x1
	.4byte	0x352
	.4byte	0x358
	.uleb128 0xc
	.4byte	0x617
	.byte	0
	.uleb128 0x17
	.4byte	.LASF45
	.byte	0x2
	.byte	0x45
	.4byte	.LASF46
	.4byte	0xc4
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x6
	.4byte	0x227
	.byte	0x1
	.4byte	0x378
	.4byte	0x383
	.uleb128 0xc
	.4byte	0x617
	.uleb128 0xd
	.4byte	0x62
	.byte	0
	.uleb128 0xe
	.4byte	.LASF38
	.byte	0x2
	.byte	0x48
	.4byte	.LASF47
	.4byte	0x3e
	.byte	0x1
	.4byte	0x39b
	.4byte	0x3ab
	.uleb128 0xc
	.4byte	0x617
	.uleb128 0xd
	.4byte	0x666
	.uleb128 0xd
	.4byte	0x3e
	.byte	0
	.uleb128 0xf
	.4byte	.LASF49
	.byte	0x2
	.byte	0x53
	.4byte	.LASF51
	.byte	0x1
	.4byte	0x3bf
	.4byte	0x3c5
	.uleb128 0xc
	.4byte	0x617
	.byte	0
	.uleb128 0xf
	.4byte	.LASF37
	.byte	0x2
	.byte	0x5a
	.4byte	.LASF52
	.byte	0x1
	.4byte	0x3d9
	.4byte	0x3e9
	.uleb128 0xc
	.4byte	0x617
	.uleb128 0xd
	.4byte	0x66c
	.uleb128 0xd
	.4byte	0x3e
	.byte	0
	.uleb128 0xf
	.4byte	.LASF37
	.byte	0x2
	.byte	0x61
	.4byte	.LASF53
	.byte	0x1
	.4byte	0x3fd
	.4byte	0x408
	.uleb128 0xc
	.4byte	0x617
	.uleb128 0xd
	.4byte	0x61d
	.byte	0
	.uleb128 0xf
	.4byte	.LASF54
	.byte	0x2
	.byte	0x67
	.4byte	.LASF55
	.byte	0x1
	.4byte	0x41c
	.4byte	0x427
	.uleb128 0xc
	.4byte	0x617
	.uleb128 0xd
	.4byte	0x61d
	.byte	0
	.uleb128 0x18
	.4byte	.LASF56
	.byte	0x2
	.byte	0x6d
	.4byte	.LASF102
	.byte	0x1
	.4byte	0x437
	.uleb128 0xc
	.4byte	0x617
	.uleb128 0xd
	.4byte	0x62
	.byte	0
	.byte	0
	.uleb128 0x11
	.4byte	.LASF57
	.byte	0x8
	.byte	0x2
	.byte	0x8f
	.4byte	0x227
	.4byte	0x5d4
	.uleb128 0x19
	.4byte	0x227
	.byte	0
	.byte	0x1
	.uleb128 0xa
	.4byte	.LASF58
	.byte	0x2
	.byte	0xcd
	.4byte	0xfe
	.byte	0x4
	.uleb128 0x1a
	.4byte	.LASF103
	.byte	0x1
	.byte	0x42
	.4byte	0x62f
	.uleb128 0x1b
	.4byte	.LASF57
	.byte	0x2
	.byte	0x93
	.byte	0x1
	.4byte	0x481
	.4byte	0x491
	.uleb128 0xc
	.4byte	0x63f
	.uleb128 0xd
	.4byte	0x62
	.uleb128 0xd
	.4byte	0x62
	.byte	0
	.uleb128 0xf
	.4byte	.LASF59
	.byte	0x1
	.byte	0x59
	.4byte	.LASF60
	.byte	0x1
	.4byte	0x4a5
	.4byte	0x4b0
	.uleb128 0xc
	.4byte	0x63f
	.uleb128 0xd
	.4byte	0x62
	.byte	0
	.uleb128 0x16
	.4byte	.LASF37
	.byte	0x1
	.byte	0x83
	.4byte	.LASF61
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x1
	.4byte	0x443
	.byte	0x1
	.4byte	0x4cc
	.4byte	0x4d7
	.uleb128 0xc
	.4byte	0x63f
	.uleb128 0xd
	.4byte	0x25
	.byte	0
	.uleb128 0x1c
	.4byte	.LASF62
	.byte	0x2
	.byte	0x9f
	.4byte	.LASF63
	.4byte	0x63f
	.byte	0x1
	.4byte	0x4f1
	.uleb128 0xd
	.4byte	0x62
	.byte	0
	.uleb128 0x15
	.string	"put"
	.byte	0x2
	.byte	0xa5
	.4byte	.LASF65
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0
	.4byte	0x443
	.byte	0x1
	.4byte	0x50d
	.4byte	0x518
	.uleb128 0xc
	.4byte	0x63f
	.uleb128 0xd
	.4byte	0x25
	.byte	0
	.uleb128 0x17
	.4byte	.LASF30
	.byte	0x2
	.byte	0xaa
	.4byte	.LASF66
	.4byte	0x57
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x2
	.4byte	0x443
	.byte	0x1
	.4byte	0x538
	.4byte	0x53e
	.uleb128 0xc
	.4byte	0x63f
	.byte	0
	.uleb128 0x17
	.4byte	.LASF38
	.byte	0x2
	.byte	0xb2
	.4byte	.LASF67
	.4byte	0x57
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x3
	.4byte	0x443
	.byte	0x1
	.4byte	0x55e
	.4byte	0x564
	.uleb128 0xc
	.4byte	0x63f
	.byte	0
	.uleb128 0x17
	.4byte	.LASF32
	.byte	0x2
	.byte	0xba
	.4byte	.LASF68
	.4byte	0x3e
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x4
	.4byte	0x443
	.byte	0x1
	.4byte	0x584
	.4byte	0x58a
	.uleb128 0xc
	.4byte	0x63f
	.byte	0
	.uleb128 0x16
	.4byte	.LASF42
	.byte	0x2
	.byte	0xbf
	.4byte	.LASF69
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x5
	.4byte	0x443
	.byte	0x1
	.4byte	0x5a6
	.4byte	0x5ac
	.uleb128 0xc
	.4byte	0x63f
	.byte	0
	.uleb128 0x1d
	.4byte	.LASF45
	.byte	0x2
	.byte	0xc4
	.4byte	.LASF70
	.4byte	0xc4
	.byte	0x1
	.uleb128 0x2
	.byte	0x10
	.uleb128 0x6
	.4byte	0x443
	.byte	0x1
	.4byte	0x5c8
	.uleb128 0xc
	.4byte	0x63f
	.uleb128 0xd
	.4byte	0x62
	.byte	0
	.byte	0
	.uleb128 0x1e
	.4byte	0x227
	.uleb128 0x1f
	.4byte	.LASF71
	.byte	0x1
	.byte	0x32
	.4byte	.LASF104
	.4byte	0x5ee
	.uleb128 0xd
	.4byte	0x628
	.byte	0
	.uleb128 0x20
	.4byte	.LASF72
	.byte	0x1
	.byte	0x45
	.4byte	.LASF74
	.uleb128 0x20
	.4byte	.LASF73
	.byte	0x1
	.byte	0x37
	.4byte	.LASF75
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0xfe
	.uleb128 0x21
	.byte	0x4
	.4byte	0x30
	.uleb128 0x7
	.byte	0x4
	.4byte	0x30
	.uleb128 0x7
	.byte	0x4
	.4byte	0x227
	.uleb128 0x7
	.byte	0x4
	.4byte	0x623
	.uleb128 0x1e
	.4byte	0x628
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.4byte	.LASF76
	.uleb128 0x22
	.4byte	0x63f
	.4byte	0x63f
	.uleb128 0x23
	.4byte	0xbb
	.byte	0
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x443
	.uleb128 0x24
	.4byte	0xb4
	.4byte	0x650
	.uleb128 0x25
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0x656
	.uleb128 0x26
	.byte	0x4
	.4byte	.LASF105
	.4byte	0x645
	.uleb128 0x21
	.byte	0x4
	.4byte	0x5d4
	.uleb128 0x7
	.byte	0x4
	.4byte	0x25
	.uleb128 0x7
	.byte	0x4
	.4byte	0x672
	.uleb128 0x1e
	.4byte	0x25
	.uleb128 0x27
	.4byte	0x4d7
	.byte	0x3
	.4byte	0x68d
	.uleb128 0x28
	.4byte	.LASF77
	.byte	0x2
	.byte	0x9f
	.4byte	0x62
	.byte	0
	.uleb128 0x29
	.4byte	0x1bf
	.byte	0x3
	.4byte	0x69b
	.4byte	0x6bb
	.uleb128 0x2a
	.4byte	.LASF80
	.4byte	0x6bb
	.uleb128 0x28
	.4byte	.LASF78
	.byte	0x3
	.byte	0xe6
	.4byte	0x611
	.uleb128 0x28
	.4byte	.LASF79
	.byte	0x3
	.byte	0xe6
	.4byte	0x62
	.byte	0
	.uleb128 0x1e
	.4byte	0x605
	.uleb128 0x29
	.4byte	0x197
	.byte	0x3
	.4byte	0x6ce
	.4byte	0x6ee
	.uleb128 0x2a
	.4byte	.LASF80
	.4byte	0x6bb
	.uleb128 0x28
	.4byte	.LASF78
	.byte	0x3
	.byte	0xe1
	.4byte	0x611
	.uleb128 0x28
	.4byte	.LASF79
	.byte	0x3
	.byte	0xe1
	.4byte	0x62
	.byte	0
	.uleb128 0x29
	.4byte	0x201
	.byte	0x3
	.4byte	0x6fc
	.4byte	0x706
	.uleb128 0x2a
	.4byte	.LASF80
	.4byte	0x6bb
	.byte	0
	.uleb128 0x29
	.4byte	0x1e7
	.byte	0x3
	.4byte	0x714
	.4byte	0x71e
	.uleb128 0x2a
	.4byte	.LASF80
	.4byte	0x6bb
	.byte	0
	.uleb128 0x2b
	.4byte	0x5d9
	.4byte	.LFB56
	.4byte	.LFE56-.LFB56
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x73d
	.uleb128 0x2c
	.string	"c"
	.byte	0x1
	.byte	0x32
	.4byte	0x628
	.uleb128 0x1
	.byte	0x52
	.byte	0
	.uleb128 0x2d
	.4byte	0x5ee
	.4byte	.LFB58
	.4byte	.LFE58-.LFB58
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x798
	.uleb128 0x2e
	.4byte	.Ldebug_ranges0+0
	.uleb128 0x2f
	.4byte	.LASF81
	.byte	0x1
	.byte	0x47
	.4byte	0x62
	.4byte	.LLST0
	.uleb128 0x30
	.4byte	.LBB26
	.4byte	.LBE26-.LBB26
	.uleb128 0x2f
	.4byte	.LASF82
	.byte	0x1
	.byte	0x4f
	.4byte	0x25
	.4byte	.LLST1
	.uleb128 0x31
	.4byte	0x677
	.4byte	.LBB27
	.4byte	.LBE27-.LBB27
	.byte	0x1
	.byte	0x50
	.uleb128 0x32
	.4byte	0x681
	.4byte	.LLST2
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x33
	.4byte	0x4b0
	.4byte	.LFB60
	.4byte	.LFE60-.LFB60
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x7af
	.4byte	0x7e1
	.uleb128 0x34
	.4byte	.LASF80
	.4byte	0x7e1
	.4byte	.LLST3
	.uleb128 0x2c
	.string	"b"
	.byte	0x1
	.byte	0x83
	.4byte	0x25
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x30
	.4byte	.LBB36
	.4byte	.LBE36-.LBB36
	.uleb128 0x2f
	.4byte	.LASF83
	.byte	0x1
	.byte	0x87
	.4byte	0x62
	.4byte	.LLST4
	.byte	0
	.byte	0
	.uleb128 0x1e
	.4byte	0x63f
	.uleb128 0x29
	.4byte	0x174
	.byte	0x3
	.4byte	0x7f4
	.4byte	0x816
	.uleb128 0x2a
	.4byte	.LASF80
	.4byte	0x6bb
	.uleb128 0x28
	.4byte	.LASF78
	.byte	0x3
	.byte	0xdb
	.4byte	0x816
	.uleb128 0x35
	.uleb128 0x36
	.4byte	.LASF106
	.byte	0x3
	.byte	0xdd
	.4byte	0x74
	.byte	0
	.byte	0
	.uleb128 0x1e
	.4byte	0x60b
	.uleb128 0x33
	.4byte	0x4f1
	.4byte	.LFB50
	.4byte	.LFE50-.LFB50
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x832
	.4byte	0x89a
	.uleb128 0x34
	.4byte	.LASF80
	.4byte	0x7e1
	.4byte	.LLST5
	.uleb128 0x37
	.4byte	.LASF84
	.byte	0x2
	.byte	0xa5
	.4byte	0x25
	.4byte	.LLST6
	.uleb128 0x38
	.4byte	0x7e6
	.4byte	.LBB40
	.4byte	.Ldebug_ranges0+0x20
	.byte	0x2
	.byte	0xa7
	.uleb128 0x32
	.4byte	0x7fd
	.4byte	.LLST7
	.uleb128 0x32
	.4byte	0x7f4
	.4byte	.LLST8
	.uleb128 0x2e
	.4byte	.Ldebug_ranges0+0x20
	.uleb128 0x39
	.4byte	0x809
	.uleb128 0x2
	.byte	0x91
	.sleb128 -48
	.uleb128 0x3a
	.4byte	.LVL16
	.4byte	0xb91
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x33
	.4byte	0x518
	.4byte	.LFB51
	.4byte	.LFE51-.LFB51
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x8b1
	.4byte	0x915
	.uleb128 0x34
	.4byte	.LASF80
	.4byte	0x7e1
	.4byte	.LLST9
	.uleb128 0x2e
	.4byte	.Ldebug_ranges0+0x40
	.uleb128 0x3c
	.string	"ret"
	.byte	0x2
	.byte	0xac
	.4byte	0x25
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x38
	.4byte	0x68d
	.4byte	.LBB47
	.4byte	.Ldebug_ranges0+0x60
	.byte	0x2
	.byte	0xad
	.uleb128 0x3d
	.4byte	0x6af
	.byte	0
	.uleb128 0x32
	.4byte	0x6a4
	.4byte	.LLST10
	.uleb128 0x32
	.4byte	0x69b
	.4byte	.LLST11
	.uleb128 0x3a
	.4byte	.LVL21
	.4byte	0xbc3
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x3e
	.4byte	0x5ac
	.4byte	.LFB55
	.4byte	.LFE55-.LFB55
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x92c
	.4byte	0x99b
	.uleb128 0x34
	.4byte	.LASF80
	.4byte	0x7e1
	.4byte	.LLST12
	.uleb128 0x37
	.4byte	.LASF85
	.byte	0x2
	.byte	0xc4
	.4byte	0x62
	.4byte	.LLST13
	.uleb128 0x2e
	.4byte	.Ldebug_ranges0+0x78
	.uleb128 0x3c
	.string	"b"
	.byte	0x2
	.byte	0xc6
	.4byte	0x25
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x38
	.4byte	0x68d
	.4byte	.LBB54
	.4byte	.Ldebug_ranges0+0x78
	.byte	0x2
	.byte	0xc7
	.uleb128 0x32
	.4byte	0x6af
	.4byte	.LLST14
	.uleb128 0x32
	.4byte	0x6a4
	.4byte	.LLST15
	.uleb128 0x32
	.4byte	0x69b
	.4byte	.LLST16
	.uleb128 0x3a
	.4byte	.LVL28
	.4byte	0xbc3
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x1
	.byte	0x31
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x33
	.4byte	0x53e
	.4byte	.LFB52
	.4byte	.LFE52-.LFB52
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x9b2
	.4byte	0xa16
	.uleb128 0x34
	.4byte	.LASF80
	.4byte	0x7e1
	.4byte	.LLST17
	.uleb128 0x2e
	.4byte	.Ldebug_ranges0+0x98
	.uleb128 0x3c
	.string	"ret"
	.byte	0x2
	.byte	0xb4
	.4byte	0x25
	.uleb128 0x2
	.byte	0x91
	.sleb128 -32
	.uleb128 0x38
	.4byte	0x6c0
	.4byte	.LBB63
	.4byte	.Ldebug_ranges0+0xb8
	.byte	0x2
	.byte	0xb5
	.uleb128 0x3d
	.4byte	0x6e2
	.byte	0
	.uleb128 0x32
	.4byte	0x6d7
	.4byte	.LLST18
	.uleb128 0x32
	.4byte	0x6ce
	.4byte	.LLST19
	.uleb128 0x3a
	.4byte	.LVL34
	.4byte	0xbc3
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x55
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x54
	.uleb128 0x1
	.byte	0x30
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x2
	.byte	0x71
	.sleb128 0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x33
	.4byte	0x564
	.4byte	.LFB53
	.4byte	.LFE53-.LFB53
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa2d
	.4byte	0xa5d
	.uleb128 0x34
	.4byte	.LASF80
	.4byte	0x7e1
	.4byte	.LLST20
	.uleb128 0x38
	.4byte	0x6ee
	.4byte	.LBB69
	.4byte	.Ldebug_ranges0+0xd0
	.byte	0x2
	.byte	0xbc
	.uleb128 0x32
	.4byte	0x6fc
	.4byte	.LLST21
	.uleb128 0x3f
	.4byte	.LVL38
	.4byte	0xbe8
	.byte	0
	.byte	0
	.uleb128 0x33
	.4byte	0x58a
	.4byte	.LFB54
	.4byte	.LFE54-.LFB54
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xa74
	.4byte	0xaaa
	.uleb128 0x34
	.4byte	.LASF80
	.4byte	0x7e1
	.4byte	.LLST22
	.uleb128 0x38
	.4byte	0x706
	.4byte	.LBB73
	.4byte	.Ldebug_ranges0+0xe8
	.byte	0x2
	.byte	0xc1
	.uleb128 0x32
	.4byte	0x714
	.4byte	.LLST23
	.uleb128 0x3a
	.4byte	.LVL41
	.4byte	0xbfe
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x1
	.byte	0x30
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2b
	.4byte	0x5f9
	.4byte	.LFB57
	.4byte	.LFE57-.LFB57
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xad1
	.uleb128 0x3a
	.4byte	.LVL42
	.4byte	0xc19
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x5
	.byte	0x3
	.4byte	_ZN3fdv16dummy_write_charEc
	.byte	0
	.byte	0
	.uleb128 0x3e
	.4byte	0x491
	.4byte	.LFB59
	.4byte	.LFE59-.LFB59
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xae8
	.4byte	0xb82
	.uleb128 0x34
	.4byte	.LASF80
	.4byte	0x7e1
	.4byte	.LLST24
	.uleb128 0x37
	.4byte	.LASF86
	.byte	0x1
	.byte	0x59
	.4byte	0x62
	.4byte	.LLST25
	.uleb128 0x30
	.4byte	.LBB79
	.4byte	.LBE79-.LBB79
	.uleb128 0x40
	.4byte	.LASF87
	.byte	0x1
	.byte	0x70
	.4byte	0x672
	.byte	0x2
	.uleb128 0x40
	.4byte	.LASF88
	.byte	0x1
	.byte	0x71
	.4byte	0x672
	.byte	0x14
	.uleb128 0x40
	.4byte	.LASF89
	.byte	0x1
	.byte	0x72
	.4byte	0x672
	.byte	0x1
	.uleb128 0x2f
	.4byte	.LASF90
	.byte	0x1
	.byte	0x73
	.4byte	0x62
	.4byte	.LLST26
	.uleb128 0x41
	.4byte	.LVL46
	.4byte	0xc3b
	.4byte	0xb54
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x7c
	.sleb128 0
	.byte	0
	.uleb128 0x41
	.4byte	.LVL52
	.4byte	0xc51
	.4byte	0xb70
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x53
	.uleb128 0x5
	.byte	0x3
	.4byte	_ZN3fdv25HardwareSerial_rx_handlerEv
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x1
	.byte	0x35
	.byte	0
	.uleb128 0x3a
	.4byte	.LVL53
	.4byte	0xc67
	.uleb128 0x3b
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x2
	.byte	0x8
	.byte	0x20
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x42
	.4byte	0x466
	.4byte	.LASF107
	.uleb128 0x5
	.byte	0x3
	.4byte	_ZN3fdv14HardwareSerial9s_serialsE
	.uleb128 0x43
	.4byte	.LASF91
	.byte	0x6
	.2byte	0x525
	.4byte	0x74
	.4byte	0xbb6
	.uleb128 0xd
	.4byte	0xe8
	.uleb128 0xd
	.4byte	0xbb6
	.uleb128 0xd
	.4byte	0xbbd
	.uleb128 0xd
	.4byte	0x74
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0xbbc
	.uleb128 0x44
	.uleb128 0x7
	.byte	0x4
	.4byte	0x74
	.uleb128 0x43
	.4byte	.LASF92
	.byte	0x6
	.2byte	0x38c
	.4byte	0x74
	.4byte	0xbe8
	.uleb128 0xd
	.4byte	0xe8
	.uleb128 0xd
	.4byte	0xbb6
	.uleb128 0xd
	.4byte	0xcc
	.uleb128 0xd
	.4byte	0x74
	.byte	0
	.uleb128 0x43
	.4byte	.LASF93
	.byte	0x6
	.2byte	0x39b
	.4byte	0x6d
	.4byte	0xbfe
	.uleb128 0xd
	.4byte	0xe8
	.byte	0
	.uleb128 0x43
	.4byte	.LASF94
	.byte	0x6
	.2byte	0x678
	.4byte	0x74
	.4byte	0xc19
	.uleb128 0xd
	.4byte	0xe8
	.uleb128 0xd
	.4byte	0x74
	.byte	0
	.uleb128 0x45
	.4byte	.LASF95
	.byte	0x7
	.byte	0x17
	.4byte	0xc2a
	.uleb128 0xd
	.4byte	0xc2a
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.4byte	0xc30
	.uleb128 0x46
	.4byte	0xc3b
	.uleb128 0xd
	.4byte	0x628
	.byte	0
	.uleb128 0x45
	.4byte	.LASF96
	.byte	0x1
	.byte	0x2b
	.4byte	0xc51
	.uleb128 0xd
	.4byte	0xb4
	.uleb128 0xd
	.4byte	0xad
	.byte	0
	.uleb128 0x45
	.4byte	.LASF97
	.byte	0x5
	.byte	0xc3
	.4byte	0xc67
	.uleb128 0xd
	.4byte	0x97
	.uleb128 0xd
	.4byte	0xd7
	.byte	0
	.uleb128 0x47
	.4byte	.LASF108
	.byte	0x5
	.byte	0xba
	.uleb128 0xd
	.4byte	0xa2
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
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x34
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x10
	.uleb128 0x2f
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
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
	.uleb128 0x12
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
	.uleb128 0x13
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
	.uleb128 0x14
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
	.uleb128 0x1c
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xb
	.uleb128 0x32
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1a
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x32
	.uleb128 0xb
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
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
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
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
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
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
	.uleb128 0x21
	.uleb128 0x10
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x22
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x23
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x18
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x26
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
	.uleb128 0x27
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
	.uleb128 0x28
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
	.uleb128 0x29
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
	.uleb128 0x2a
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
	.uleb128 0x2b
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
	.uleb128 0x2c
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
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x2d
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
	.uleb128 0x2116
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x2e
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x2f
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x30
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x31
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
	.uleb128 0x32
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0x33
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
	.uleb128 0x34
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
	.uleb128 0x35
	.uleb128 0xb
	.byte	0x1
	.byte	0
	.byte	0
	.uleb128 0x36
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
	.uleb128 0x37
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
	.uleb128 0x38
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
	.uleb128 0x39
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3a
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x3b
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x3c
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
	.uleb128 0x3d
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x3e
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
	.uleb128 0x3f
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x40
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
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x41
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
	.uleb128 0x42
	.uleb128 0x34
	.byte	0
	.uleb128 0x47
	.uleb128 0x13
	.uleb128 0x6e
	.uleb128 0xe
	.uleb128 0x2
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0x43
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
	.uleb128 0x44
	.uleb128 0x26
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x45
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
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x46
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x47
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
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LVL1
	.4byte	.LVL2
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL7
	.4byte	.LFE58
	.2byte	0x1
	.byte	0x52
	.4byte	0
	.4byte	0
.LLST1:
	.4byte	.LVL3
	.4byte	.LVL4
	.2byte	0x1
	.byte	0x53
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL3
	.4byte	.LVL6
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LVL8
	.4byte	.LVL9
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL9
	.4byte	.LFE60
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST4:
	.4byte	.LVL10
	.4byte	.LVL11
	.2byte	0x8
	.byte	0x72
	.sleb128 0
	.byte	0x8
	.byte	0xff
	.byte	0x40
	.byte	0x24
	.byte	0x1a
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST5:
	.4byte	.LVL12
	.4byte	.LVL14
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL14
	.4byte	.LFE50
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST6:
	.4byte	.LVL12
	.4byte	.LVL15
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL15
	.4byte	.LVL16-1
	.2byte	0x2
	.byte	0x73
	.sleb128 0
	.4byte	.LVL16-1
	.4byte	.LVL17
	.2byte	0x2
	.byte	0x91
	.sleb128 -32
	.4byte	.LVL17
	.4byte	.LFE50
	.2byte	0x2
	.byte	0x71
	.sleb128 -32
	.4byte	0
	.4byte	0
.LLST7:
	.4byte	.LVL13
	.4byte	.LVL15
	.2byte	0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x9f
	.4byte	.LVL15
	.4byte	.LVL16-1
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL16-1
	.4byte	.LVL17
	.2byte	0x3
	.byte	0x91
	.sleb128 -32
	.byte	0x9f
	.4byte	.LVL17
	.4byte	.LFE50
	.2byte	0x3
	.byte	0x71
	.sleb128 -32
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST8:
	.4byte	.LVL12
	.4byte	.LVL14
	.2byte	0x3
	.byte	0x72
	.sleb128 4
	.byte	0x9f
	.4byte	.LVL14
	.4byte	.LFE50
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x23
	.uleb128 0x4
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST9:
	.4byte	.LVL18
	.4byte	.LVL20
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL20
	.4byte	.LFE51
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST10:
	.4byte	.LVL19
	.4byte	.LVL22
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL22
	.4byte	.LFE51
	.2byte	0x3
	.byte	0x71
	.sleb128 -32
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST11:
	.4byte	.LVL18
	.4byte	.LVL20
	.2byte	0x3
	.byte	0x72
	.sleb128 4
	.byte	0x9f
	.4byte	.LVL20
	.4byte	.LFE51
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x23
	.uleb128 0x4
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST12:
	.4byte	.LVL23
	.4byte	.LVL25
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL25
	.4byte	.LVL29
	.2byte	0x1
	.byte	0x5c
	.4byte	.LVL29
	.4byte	.LFE55
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST13:
	.4byte	.LVL23
	.4byte	.LVL26
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL26
	.4byte	.LVL27-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL27-1
	.4byte	.LFE55
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST14:
	.4byte	.LVL24
	.4byte	.LVL26
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL26
	.4byte	.LVL27-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL27-1
	.4byte	.LFE55
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST15:
	.4byte	.LVL24
	.4byte	.LVL30
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL30
	.4byte	.LFE55
	.2byte	0x3
	.byte	0x71
	.sleb128 -32
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST16:
	.4byte	.LVL24
	.4byte	.LVL25
	.2byte	0x3
	.byte	0x72
	.sleb128 4
	.byte	0x9f
	.4byte	.LVL25
	.4byte	.LVL29
	.2byte	0x3
	.byte	0x7c
	.sleb128 4
	.byte	0x9f
	.4byte	.LVL29
	.4byte	.LFE55
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x23
	.uleb128 0x4
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST17:
	.4byte	.LVL31
	.4byte	.LVL33
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL33
	.4byte	.LFE52
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST18:
	.4byte	.LVL32
	.4byte	.LVL35
	.2byte	0x1
	.byte	0x51
	.4byte	.LVL35
	.4byte	.LFE52
	.2byte	0x3
	.byte	0x71
	.sleb128 -32
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST19:
	.4byte	.LVL31
	.4byte	.LVL33
	.2byte	0x3
	.byte	0x72
	.sleb128 4
	.byte	0x9f
	.4byte	.LVL33
	.4byte	.LFE52
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x23
	.uleb128 0x4
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST20:
	.4byte	.LVL36
	.4byte	.LVL37
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL37
	.4byte	.LFE53
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST21:
	.4byte	.LVL36
	.4byte	.LVL37
	.2byte	0x3
	.byte	0x72
	.sleb128 4
	.byte	0x9f
	.4byte	.LVL37
	.4byte	.LFE53
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x23
	.uleb128 0x4
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST22:
	.4byte	.LVL39
	.4byte	.LVL40
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL40
	.4byte	.LFE54
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST23:
	.4byte	.LVL39
	.4byte	.LVL40
	.2byte	0x3
	.byte	0x72
	.sleb128 4
	.byte	0x9f
	.4byte	.LVL40
	.4byte	.LFE54
	.2byte	0x6
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x23
	.uleb128 0x4
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST24:
	.4byte	.LVL43
	.4byte	.LVL44
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL44
	.4byte	.LFE59
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST25:
	.4byte	.LVL43
	.4byte	.LVL45-1
	.2byte	0x1
	.byte	0x53
	.4byte	.LVL45-1
	.4byte	.LFE59
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x53
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST26:
	.4byte	.LVL47
	.4byte	.LVL48
	.2byte	0x2
	.byte	0x30
	.byte	0x9f
	.4byte	.LVL48
	.4byte	.LVL49
	.2byte	0x9
	.byte	0x72
	.sleb128 0
	.byte	0xd
	.4byte	0x82000001
	.byte	0x21
	.byte	0x9f
	.4byte	.LVL49
	.4byte	.LVL50
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL50
	.4byte	.LVL51
	.2byte	0x2
	.byte	0x7e
	.sleb128 0
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x6c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.Ltext0
	.4byte	.Letext0-.Ltext0
	.4byte	.LFB56
	.4byte	.LFE56-.LFB56
	.4byte	.LFB60
	.4byte	.LFE60-.LFB60
	.4byte	.LFB50
	.4byte	.LFE50-.LFB50
	.4byte	.LFB51
	.4byte	.LFE51-.LFB51
	.4byte	.LFB55
	.4byte	.LFE55-.LFB55
	.4byte	.LFB52
	.4byte	.LFE52-.LFB52
	.4byte	.LFB53
	.4byte	.LFE53-.LFB53
	.4byte	.LFB54
	.4byte	.LFE54-.LFB54
	.4byte	.LFB57
	.4byte	.LFE57-.LFB57
	.4byte	.LFB59
	.4byte	.LFE59-.LFB59
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.4byte	.LBB22
	.4byte	.LBE22
	.4byte	.LBB33
	.4byte	.LBE33
	.4byte	.LBB34
	.4byte	.LBE34
	.4byte	0
	.4byte	0
	.4byte	.LBB40
	.4byte	.LBE40
	.4byte	.LBB44
	.4byte	.LBE44
	.4byte	.LBB45
	.4byte	.LBE45
	.4byte	0
	.4byte	0
	.4byte	.LBB46
	.4byte	.LBE46
	.4byte	.LBB51
	.4byte	.LBE51
	.4byte	.LBB52
	.4byte	.LBE52
	.4byte	0
	.4byte	0
	.4byte	.LBB47
	.4byte	.LBE47
	.4byte	.LBB50
	.4byte	.LBE50
	.4byte	0
	.4byte	0
	.4byte	.LBB53
	.4byte	.LBE53
	.4byte	.LBB60
	.4byte	.LBE60
	.4byte	.LBB61
	.4byte	.LBE61
	.4byte	0
	.4byte	0
	.4byte	.LBB62
	.4byte	.LBE62
	.4byte	.LBB67
	.4byte	.LBE67
	.4byte	.LBB68
	.4byte	.LBE68
	.4byte	0
	.4byte	0
	.4byte	.LBB63
	.4byte	.LBE63
	.4byte	.LBB66
	.4byte	.LBE66
	.4byte	0
	.4byte	0
	.4byte	.LBB69
	.4byte	.LBE69
	.4byte	.LBB72
	.4byte	.LBE72
	.4byte	0
	.4byte	0
	.4byte	.LBB73
	.4byte	.LBE73
	.4byte	.LBB77
	.4byte	.LBE77
	.4byte	.LBB78
	.4byte	.LBE78
	.4byte	0
	.4byte	0
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.LFB56
	.4byte	.LFE56
	.4byte	.LFB60
	.4byte	.LFE60
	.4byte	.LFB50
	.4byte	.LFE50
	.4byte	.LFB51
	.4byte	.LFE51
	.4byte	.LFB55
	.4byte	.LFE55
	.4byte	.LFB52
	.4byte	.LFE52
	.4byte	.LFB53
	.4byte	.LFE53
	.4byte	.LFB54
	.4byte	.LFE54
	.4byte	.LFB57
	.4byte	.LFE57
	.4byte	.LFB59
	.4byte	.LFE59
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF91:
	.string	"xQueueGenericSendFromISR"
.LASF93:
	.string	"uxQueueMessagesWaiting"
.LASF29:
	.string	"_ZN3fdv5QueueIhE7receiveEPhm"
.LASF97:
	.string	"_xt_isr_attach"
.LASF11:
	.string	"long long unsigned int"
.LASF86:
	.string	"baud_rate"
.LASF26:
	.string	"_ZN3fdv5QueueIhE4sendERhm"
.LASF44:
	.string	"_ZN3fdv6Serial5flushEv"
.LASF102:
	.string	"_ZN3fdv6Serial11writeUInt32Em"
.LASF70:
	.string	"_ZN3fdv14HardwareSerial11waitForDataEm"
.LASF98:
	.string	"GNU C++ 4.8.2 -fpreprocessed -mlongcalls -mtext-section-literals -g -Os -O2 -fno-inline-functions -fno-exceptions -fno-rtti"
.LASF92:
	.string	"xQueueGenericReceive"
.LASF82:
	.string	"recByte"
.LASF6:
	.string	"int16_t"
.LASF10:
	.string	"long long int"
.LASF1:
	.string	"signed char"
.LASF60:
	.string	"_ZN3fdv14HardwareSerial8reconfigEm"
.LASF58:
	.string	"m_queue"
.LASF28:
	.string	"receive"
.LASF61:
	.string	"_ZN3fdv14HardwareSerial5writeEh"
.LASF9:
	.string	"long int"
.LASF35:
	.string	"_vptr$Serial"
.LASF81:
	.string	"uart_intr_status"
.LASF33:
	.string	"_ZN3fdv5QueueIhE9availableEv"
.LASF27:
	.string	"_ZN3fdv5QueueIhE11sendFromISRERh"
.LASF14:
	.string	"uint8"
.LASF89:
	.string	"UART_RX_FifoFullIntrThresh"
.LASF3:
	.string	"uint16_t"
.LASF13:
	.string	"double"
.LASF103:
	.string	"s_serials"
.LASF80:
	.string	"this"
.LASF51:
	.string	"_ZN3fdv6Serial12writeNewLineEv"
.LASF64:
	.string	"_ZN3fdv6Serial3putEh"
.LASF15:
	.string	"uint32"
.LASF34:
	.string	"m_handle"
.LASF46:
	.string	"_ZN3fdv6Serial11waitForDataEm"
.LASF40:
	.string	"_ZN3fdv6Serial4readEv"
.LASF84:
	.string	"value"
.LASF71:
	.string	"dummy_write_char"
.LASF105:
	.string	"__vtbl_ptr_type"
.LASF16:
	.string	"unsigned int"
.LASF8:
	.string	"long unsigned int"
.LASF54:
	.string	"writeln"
.LASF43:
	.string	"_ZN3fdv6Serial5writeEh"
.LASF45:
	.string	"waitForData"
.LASF62:
	.string	"getSerial"
.LASF30:
	.string	"peek"
.LASF4:
	.string	"short unsigned int"
.LASF65:
	.string	"_ZN3fdv14HardwareSerial3putEh"
.LASF108:
	.string	"_xt_isr_unmask"
.LASF99:
	.string	"src/fdvserial.cpp"
.LASF55:
	.string	"_ZN3fdv6Serial7writelnEPKc"
.LASF57:
	.string	"HardwareSerial"
.LASF18:
	.string	"bool"
.LASF85:
	.string	"timeOutMs"
.LASF21:
	.string	"xQueueHandle"
.LASF78:
	.string	"item"
.LASF75:
	.string	"_ZN3fdv13DisableStdOutEv"
.LASF47:
	.string	"_ZN3fdv6Serial4readEPht"
.LASF20:
	.string	"_xt_isr"
.LASF37:
	.string	"write"
.LASF17:
	.string	"sizetype"
.LASF48:
	.string	"clear"
.LASF90:
	.string	"reg_val"
.LASF24:
	.string	"send"
.LASF69:
	.string	"_ZN3fdv14HardwareSerial5flushEv"
.LASF104:
	.string	"_ZN3fdv16dummy_write_charEc"
.LASF77:
	.string	"uart"
.LASF12:
	.string	"float"
.LASF23:
	.string	"~Queue"
.LASF67:
	.string	"_ZN3fdv14HardwareSerial4readEv"
.LASF32:
	.string	"available"
.LASF106:
	.string	"xHigherPriorityTaskWoken"
.LASF0:
	.string	"unsigned char"
.LASF100:
	.string	"C:\\\\sviluppo\\\\ESP8266\\\\projects\\\\ESPWebFramework"
.LASF49:
	.string	"writeNewLine"
.LASF66:
	.string	"_ZN3fdv14HardwareSerial4peekEv"
.LASF5:
	.string	"short int"
.LASF63:
	.string	"_ZN3fdv14HardwareSerial9getSerialEm"
.LASF19:
	.string	"portTickType"
.LASF41:
	.string	"_ZN3fdv6Serial9availableEv"
.LASF7:
	.string	"uint32_t"
.LASF72:
	.string	"HardwareSerial_rx_handler"
.LASF94:
	.string	"xQueueGenericReset"
.LASF76:
	.string	"char"
.LASF31:
	.string	"_ZN3fdv5QueueIhE4peekEPhm"
.LASF96:
	.string	"uart_div_modify"
.LASF53:
	.string	"_ZN3fdv6Serial5writeEPKc"
.LASF50:
	.string	"_ZN3fdv5QueueIhE5clearEv"
.LASF22:
	.string	"Queue"
.LASF25:
	.string	"sendFromISR"
.LASF101:
	.string	"Queue<unsigned char>"
.LASF42:
	.string	"flush"
.LASF87:
	.string	"UART_RX_TimeOutIntrThresh"
.LASF79:
	.string	"msTimeOut"
.LASF74:
	.string	"_ZN3fdv25HardwareSerial_rx_handlerEv"
.LASF2:
	.string	"uint8_t"
.LASF39:
	.string	"_ZN3fdv6Serial4peekEv"
.LASF95:
	.string	"os_install_putc1"
.LASF52:
	.string	"_ZN3fdv6Serial5writeEPKht"
.LASF83:
	.string	"fifo_cnt"
.LASF38:
	.string	"read"
.LASF56:
	.string	"writeUInt32"
.LASF88:
	.string	"UART_TX_FifoEmptyIntrThresh"
.LASF73:
	.string	"DisableStdOut"
.LASF68:
	.string	"_ZN3fdv14HardwareSerial9availableEv"
.LASF107:
	.string	"_ZN3fdv14HardwareSerial9s_serialsE"
.LASF59:
	.string	"reconfig"
.LASF36:
	.string	"Serial"
	.ident	"GCC: (GNU) 4.8.2"

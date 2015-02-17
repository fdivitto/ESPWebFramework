	.file	"fdvsync.cpp"
	.text
.Ltext0:
	.section	.irom0.text,"ax",@progbits
	.literal_position
	.align	4
	.global	_ZN3fdv15DisableWatchDogEv
	.type	_ZN3fdv15DisableWatchDogEv, @function
_ZN3fdv15DisableWatchDogEv:
.LFB37:
	.file 1 "src/fdvsync.cpp"
	.loc 1 46 0
	addi	sp, sp, -16
.LCFI0:
	s32i.n	a0, sp, 12
	.loc 1 47 0
	call0	ets_wdt_disable
.LVL0:
	.loc 1 48 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
.LCFI1:
	ret.n
.LFE37:
	.size	_ZN3fdv15DisableWatchDogEv, .-_ZN3fdv15DisableWatchDogEv
	.literal_position
	.align	4
	.global	_ZN3fdv14EnableWatchDogEv
	.type	_ZN3fdv14EnableWatchDogEv, @function
_ZN3fdv14EnableWatchDogEv:
.LFB38:
	.loc 1 52 0
	addi	sp, sp, -16
.LCFI2:
	s32i.n	a0, sp, 12
	.loc 1 53 0
	call0	ets_wdt_enable
.LVL1:
	.loc 1 54 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
.LCFI3:
	ret.n
.LFE38:
	.size	_ZN3fdv14EnableWatchDogEv, .-_ZN3fdv14EnableWatchDogEv
	.literal_position
	.align	4
	.global	_ZN3fdv16EnableInterruptsEv
	.type	_ZN3fdv16EnableInterruptsEv, @function
_ZN3fdv16EnableInterruptsEv:
.LFB39:
	.loc 1 58 0
	addi	sp, sp, -16
.LCFI4:
	s32i.n	a0, sp, 12
	.loc 1 59 0
	call0	ets_intr_unlock
.LVL2:
	.loc 1 60 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
.LCFI5:
	ret.n
.LFE39:
	.size	_ZN3fdv16EnableInterruptsEv, .-_ZN3fdv16EnableInterruptsEv
	.literal_position
	.align	4
	.global	_ZN3fdv17DisableInterruptsEv
	.type	_ZN3fdv17DisableInterruptsEv, @function
_ZN3fdv17DisableInterruptsEv:
.LFB40:
	.loc 1 64 0
	addi	sp, sp, -16
.LCFI6:
	s32i.n	a0, sp, 12
	.loc 1 65 0
	call0	ets_intr_lock
.LVL3:
	.loc 1 66 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
.LCFI7:
	ret.n
.LFE40:
	.size	_ZN3fdv17DisableInterruptsEv, .-_ZN3fdv17DisableInterruptsEv
	.literal_position
	.align	4
	.global	_ZN3fdv9millisISREv
	.type	_ZN3fdv9millisISREv, @function
_ZN3fdv9millisISREv:
.LFB41:
	.loc 1 70 0
	addi	sp, sp, -16
.LCFI8:
	s32i.n	a0, sp, 12
	.loc 1 71 0
	call0	xTaskGetTickCountFromISR
.LVL4:
	.loc 1 72 0
	l32i.n	a0, sp, 12
	.loc 1 71 0
	addx4	a2, a2, a2
	.loc 1 72 0
	slli	a2, a2, 1
	addi	sp, sp, 16
.LCFI9:
	ret.n
.LFE41:
	.size	_ZN3fdv9millisISREv, .-_ZN3fdv9millisISREv
	.literal_position
	.align	4
	.global	_ZN3fdv6millisEv
	.type	_ZN3fdv6millisEv, @function
_ZN3fdv6millisEv:
.LFB42:
	.loc 1 76 0
	addi	sp, sp, -16
.LCFI10:
	s32i.n	a0, sp, 12
	.loc 1 77 0
	call0	xTaskGetTickCount
.LVL5:
	.loc 1 78 0
	l32i.n	a0, sp, 12
	.loc 1 77 0
	addx4	a2, a2, a2
	.loc 1 78 0
	slli	a2, a2, 1
	addi	sp, sp, 16
.LCFI11:
	ret.n
.LFE42:
	.size	_ZN3fdv6millisEv, .-_ZN3fdv6millisEv
	.literal_position
	.align	4
	.global	_ZN3fdv10millisDiffEmm
	.type	_ZN3fdv10millisDiffEmm, @function
_ZN3fdv10millisDiffEmm:
.LFB43:
	.loc 1 84 0
.LVL6:
	.loc 1 89 0
	sub	a4, a3, a2
	.loc 1 85 0
	bgeu	a3, a2, .L9
	.loc 1 87 0
	addi.n	a4, a4, -1
.L9:
	.loc 1 90 0
	mov.n	a2, a4
.LVL7:
	ret.n
.LFE43:
	.size	_ZN3fdv10millisDiffEmm, .-_ZN3fdv10millisDiffEmm
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
	.4byte	.LFB37
	.4byte	.LFE37-.LFB37
	.byte	0x4
	.4byte	.LCFI0-.LFB37
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
	.4byte	.LFB38
	.4byte	.LFE38-.LFB38
	.byte	0x4
	.4byte	.LCFI2-.LFB38
	.byte	0xe
	.uleb128 0x10
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
	.4byte	.LFB39
	.4byte	.LFE39-.LFB39
	.byte	0x4
	.4byte	.LCFI4-.LFB39
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI5-.LCFI4
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE4:
.LSFDE6:
	.4byte	.LEFDE6-.LASFDE6
.LASFDE6:
	.4byte	.Lframe0
	.4byte	.LFB40
	.4byte	.LFE40-.LFB40
	.byte	0x4
	.4byte	.LCFI6-.LFB40
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI7-.LCFI6
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE6:
.LSFDE8:
	.4byte	.LEFDE8-.LASFDE8
.LASFDE8:
	.4byte	.Lframe0
	.4byte	.LFB41
	.4byte	.LFE41-.LFB41
	.byte	0x4
	.4byte	.LCFI8-.LFB41
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI9-.LCFI8
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB42
	.4byte	.LFE42-.LFB42
	.byte	0x4
	.4byte	.LCFI10-.LFB42
	.byte	0xe
	.uleb128 0x10
	.byte	0x4
	.4byte	.LCFI11-.LCFI10
	.byte	0xe
	.uleb128 0
	.align	4
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB43
	.4byte	.LFE43-.LFB43
	.align	4
.LEFDE12:
	.text
.Letext0:
	.file 2 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/espressif/c_types.h"
	.file 3 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/freertos/portmacro.h"
	.file 4 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/freertos/task.h"
	.file 5 "src/fdvsync.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x21c
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF35
	.byte	0x4
	.4byte	.LASF36
	.4byte	.LASF37
	.4byte	.Ldebug_ranges0+0
	.4byte	0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF1
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF2
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF3
	.uleb128 0x3
	.4byte	.LASF13
	.byte	0x2
	.byte	0xf
	.4byte	0x4c
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF4
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.4byte	.LASF5
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF7
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.4byte	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x4
	.4byte	.LASF9
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF10
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF12
	.uleb128 0x3
	.4byte	.LASF14
	.byte	0x3
	.byte	0x61
	.4byte	0x4c
	.uleb128 0x5
	.string	"fdv"
	.byte	0x5
	.byte	0x27
	.4byte	0x10d
	.uleb128 0x6
	.4byte	.LASF15
	.byte	0x1
	.byte	0x2d
	.4byte	.LASF17
	.uleb128 0x6
	.4byte	.LASF16
	.byte	0x1
	.byte	0x33
	.4byte	.LASF18
	.uleb128 0x6
	.4byte	.LASF19
	.byte	0x1
	.byte	0x39
	.4byte	.LASF20
	.uleb128 0x6
	.4byte	.LASF21
	.byte	0x1
	.byte	0x3f
	.4byte	.LASF22
	.uleb128 0x7
	.4byte	.LASF23
	.byte	0x1
	.byte	0x45
	.4byte	.LASF25
	.4byte	0x41
	.uleb128 0x7
	.4byte	.LASF24
	.byte	0x1
	.byte	0x4b
	.4byte	.LASF26
	.4byte	0x41
	.uleb128 0x8
	.4byte	.LASF38
	.byte	0x1
	.byte	0x53
	.4byte	.LASF39
	.4byte	0x41
	.uleb128 0x9
	.4byte	0x41
	.uleb128 0x9
	.4byte	0x41
	.byte	0
	.byte	0
	.uleb128 0xa
	.4byte	0xa8
	.4byte	.LFB37
	.4byte	.LFE37-.LFB37
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x12a
	.uleb128 0xb
	.4byte	.LVL0
	.4byte	0x1eb
	.byte	0
	.uleb128 0xa
	.4byte	0xb3
	.4byte	.LFB38
	.4byte	.LFE38-.LFB38
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x147
	.uleb128 0xb
	.4byte	.LVL1
	.4byte	0x1f2
	.byte	0
	.uleb128 0xa
	.4byte	0xbe
	.4byte	.LFB39
	.4byte	.LFE39-.LFB39
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x164
	.uleb128 0xb
	.4byte	.LVL2
	.4byte	0x1f9
	.byte	0
	.uleb128 0xa
	.4byte	0xc9
	.4byte	.LFB40
	.4byte	.LFE40-.LFB40
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x181
	.uleb128 0xb
	.4byte	.LVL3
	.4byte	0x200
	.byte	0
	.uleb128 0xa
	.4byte	0xd4
	.4byte	.LFB41
	.4byte	.LFE41-.LFB41
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x19e
	.uleb128 0xb
	.4byte	.LVL4
	.4byte	0x207
	.byte	0
	.uleb128 0xa
	.4byte	0xe3
	.4byte	.LFB42
	.4byte	.LFE42-.LFB42
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1bb
	.uleb128 0xb
	.4byte	.LVL5
	.4byte	0x213
	.byte	0
	.uleb128 0xa
	.4byte	0xf2
	.4byte	.LFB43
	.4byte	.LFE43-.LFB43
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x1eb
	.uleb128 0xc
	.4byte	.LASF27
	.byte	0x1
	.byte	0x53
	.4byte	0x41
	.4byte	.LLST0
	.uleb128 0xd
	.4byte	.LASF28
	.byte	0x1
	.byte	0x53
	.4byte	0x41
	.uleb128 0x1
	.byte	0x53
	.byte	0
	.uleb128 0xe
	.4byte	.LASF29
	.byte	0x1
	.byte	0x24
	.uleb128 0xe
	.4byte	.LASF30
	.byte	0x1
	.byte	0x23
	.uleb128 0xe
	.4byte	.LASF31
	.byte	0x1
	.byte	0x26
	.uleb128 0xe
	.4byte	.LASF32
	.byte	0x1
	.byte	0x25
	.uleb128 0xf
	.4byte	.LASF33
	.byte	0x4
	.2byte	0x417
	.4byte	0x92
	.uleb128 0xf
	.4byte	.LASF34
	.byte	0x4
	.2byte	0x407
	.4byte	0x92
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
	.uleb128 0x3
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
	.uleb128 0x6
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
	.uleb128 0x7
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0x8
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
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
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
	.uleb128 0xb
	.uleb128 0x4109
	.byte	0
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0x18
	.byte	0
	.byte	0
	.uleb128 0xe
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
	.uleb128 0xf
	.uleb128 0x2e
	.byte	0
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
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.4byte	.LVL6
	.4byte	.LVL7
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL7
	.4byte	.LFE43
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x4c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0
	.2byte	0
	.2byte	0
	.4byte	.LFB37
	.4byte	.LFE37-.LFB37
	.4byte	.LFB38
	.4byte	.LFE38-.LFB38
	.4byte	.LFB39
	.4byte	.LFE39-.LFB39
	.4byte	.LFB40
	.4byte	.LFE40-.LFB40
	.4byte	.LFB41
	.4byte	.LFE41-.LFB41
	.4byte	.LFB42
	.4byte	.LFE42-.LFB42
	.4byte	.LFB43
	.4byte	.LFE43-.LFB43
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.4byte	.LFB37
	.4byte	.LFE37
	.4byte	.LFB38
	.4byte	.LFE38
	.4byte	.LFB39
	.4byte	.LFE39
	.4byte	.LFB40
	.4byte	.LFE40
	.4byte	.LFB41
	.4byte	.LFE41
	.4byte	.LFB42
	.4byte	.LFE42
	.4byte	.LFB43
	.4byte	.LFE43
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF39:
	.string	"_ZN3fdv10millisDiffEmm"
.LASF29:
	.string	"ets_wdt_disable"
.LASF22:
	.string	"_ZN3fdv17DisableInterruptsEv"
.LASF14:
	.string	"portTickType"
.LASF12:
	.string	"bool"
.LASF18:
	.string	"_ZN3fdv14EnableWatchDogEv"
.LASF30:
	.string	"ets_wdt_enable"
.LASF8:
	.string	"float"
.LASF36:
	.string	"src/fdvsync.cpp"
.LASF0:
	.string	"unsigned char"
.LASF17:
	.string	"_ZN3fdv15DisableWatchDogEv"
.LASF25:
	.string	"_ZN3fdv9millisISREv"
.LASF2:
	.string	"short unsigned int"
.LASF16:
	.string	"EnableWatchDog"
.LASF35:
	.string	"GNU C++ 4.8.2 -fpreprocessed -mlongcalls -mtext-section-literals -g -Os -O2 -fno-inline-functions -fno-exceptions -fno-rtti"
.LASF9:
	.string	"double"
.LASF23:
	.string	"millisISR"
.LASF4:
	.string	"long unsigned int"
.LASF10:
	.string	"unsigned int"
.LASF21:
	.string	"DisableInterrupts"
.LASF32:
	.string	"ets_intr_lock"
.LASF26:
	.string	"_ZN3fdv6millisEv"
.LASF7:
	.string	"long long unsigned int"
.LASF20:
	.string	"_ZN3fdv16EnableInterruptsEv"
.LASF37:
	.string	"C:\\\\sviluppo\\\\ESP8266\\\\projects\\\\ESPWebFramework"
.LASF31:
	.string	"ets_intr_unlock"
.LASF11:
	.string	"sizetype"
.LASF6:
	.string	"long long int"
.LASF33:
	.string	"xTaskGetTickCountFromISR"
.LASF3:
	.string	"short int"
.LASF27:
	.string	"time1"
.LASF28:
	.string	"time2"
.LASF38:
	.string	"millisDiff"
.LASF19:
	.string	"EnableInterrupts"
.LASF13:
	.string	"uint32_t"
.LASF5:
	.string	"long int"
.LASF24:
	.string	"millis"
.LASF1:
	.string	"signed char"
.LASF34:
	.string	"xTaskGetTickCount"
.LASF15:
	.string	"DisableWatchDog"
	.ident	"GCC: (GNU) 4.8.2"

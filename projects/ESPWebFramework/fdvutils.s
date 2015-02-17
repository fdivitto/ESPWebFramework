	.file	"fdvutils.cpp"
	.text
.Ltext0:
	.section	.irom0.text,"ax",@progbits
	.literal_position
	.align	4
	.global	_Znwj
	.type	_Znwj, @function
_Znwj:
.LFB0:
	.file 1 "src/fdvutils.cpp"
	.loc 1 48 0
.LVL0:
	addi	sp, sp, -16
.LCFI0:
	s32i.n	a0, sp, 12
	.loc 1 49 0
	call0	malloc
.LVL1:
	.loc 1 50 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
.LCFI1:
	ret.n
.LFE0:
	.size	_Znwj, .-_Znwj
	.literal_position
	.align	4
	.global	_Znaj
	.type	_Znaj, @function
_Znaj:
.LFB1:
	.loc 1 53 0
.LVL2:
	addi	sp, sp, -16
.LCFI2:
	s32i.n	a0, sp, 12
	.loc 1 54 0
	call0	malloc
.LVL3:
	.loc 1 55 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
.LCFI3:
	ret.n
.LFE1:
	.size	_Znaj, .-_Znaj
	.literal_position
	.align	4
	.global	_ZdlPv
	.type	_ZdlPv, @function
_ZdlPv:
.LFB2:
	.loc 1 58 0
.LVL4:
	addi	sp, sp, -16
.LCFI4:
	s32i.n	a0, sp, 12
	.loc 1 59 0
	call0	free
.LVL5:
	.loc 1 60 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
.LCFI5:
	ret.n
.LFE2:
	.size	_ZdlPv, .-_ZdlPv
	.literal_position
	.align	4
	.global	_ZdaPv
	.type	_ZdaPv, @function
_ZdaPv:
.LFB3:
	.loc 1 63 0
.LVL6:
	addi	sp, sp, -16
.LCFI6:
	s32i.n	a0, sp, 12
	.loc 1 64 0
	call0	free
.LVL7:
	.loc 1 65 0
	l32i.n	a0, sp, 12
	addi	sp, sp, 16
.LCFI7:
	ret.n
.LFE3:
	.size	_ZdaPv, .-_ZdaPv
	.literal_position
	.align	4
	.global	abort
	.type	abort, @function
abort:
.LFB4:
	.loc 1 72 0
.L6:
	j	.L6
.LFE4:
	.size	abort, .-abort
	.literal_position
	.align	4
	.global	__cxa_pure_virtual
	.type	__cxa_pure_virtual, @function
__cxa_pure_virtual:
.LFB5:
	.loc 1 77 0
.L8:
	j	.L8
.LFE5:
	.size	__cxa_pure_virtual, .-__cxa_pure_virtual
	.literal_position
	.align	4
	.global	__cxa_deleted_virtual
	.type	__cxa_deleted_virtual, @function
__cxa_deleted_virtual:
.LFB6:
	.loc 1 82 0
.L10:
	j	.L10
.LFE6:
	.size	__cxa_deleted_virtual, .-__cxa_deleted_virtual
	.global	__dso_handle
	.section	.bss
	.align	4
	.type	__dso_handle, @object
	.size	__dso_handle, 4
__dso_handle:
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
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.byte	0x4
	.4byte	.LCFI0-.LFB0
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
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.byte	0x4
	.4byte	.LCFI2-.LFB1
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
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.byte	0x4
	.4byte	.LCFI4-.LFB2
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
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.byte	0x4
	.4byte	.LCFI6-.LFB3
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
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.align	4
.LEFDE8:
.LSFDE10:
	.4byte	.LEFDE10-.LASFDE10
.LASFDE10:
	.4byte	.Lframe0
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.align	4
.LEFDE10:
.LSFDE12:
	.4byte	.LEFDE12-.LASFDE12
.LASFDE12:
	.4byte	.Lframe0
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.align	4
.LEFDE12:
	.text
.Letext0:
	.file 2 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/espressif/c_types.h"
	.file 3 "C:/sviluppo/ESP8266/projects/ESPWebFramework/../../SDK/esp_iot_rtos_sdk-master/include/espressif/esp_libc.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x1ed
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.4byte	.LASF24
	.byte	0x4
	.4byte	.LASF25
	.4byte	.LASF26
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
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x4
	.4byte	.LASF27
	.byte	0x2
	.byte	0x2f
	.4byte	0x6b
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF11
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF12
	.uleb128 0x6
	.4byte	.LASF28
	.byte	0x1
	.byte	0x47
	.byte	0x1
	.uleb128 0x7
	.4byte	.LASF13
	.byte	0x1
	.byte	0x2f
	.4byte	.LASF15
	.4byte	0x8b
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.uleb128 0x1
	.byte	0x9c
	.4byte	0xda
	.uleb128 0x8
	.4byte	.LASF17
	.byte	0x1
	.byte	0x2f
	.4byte	0x79
	.4byte	.LLST0
	.uleb128 0x9
	.4byte	.LVL1
	.4byte	0x1ce
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0
	.byte	0
	.uleb128 0x7
	.4byte	.LASF14
	.byte	0x1
	.byte	0x34
	.4byte	.LASF16
	.4byte	0x8b
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x118
	.uleb128 0x8
	.4byte	.LASF17
	.byte	0x1
	.byte	0x34
	.4byte	0x79
	.4byte	.LLST1
	.uleb128 0x9
	.4byte	.LVL3
	.4byte	0x1ce
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF18
	.byte	0x1
	.byte	0x39
	.4byte	.LASF20
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x152
	.uleb128 0xc
	.string	"ptr"
	.byte	0x1
	.byte	0x39
	.4byte	0x8b
	.4byte	.LLST2
	.uleb128 0x9
	.4byte	.LVL5
	.4byte	0x1e3
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0
	.byte	0
	.uleb128 0xb
	.4byte	.LASF19
	.byte	0x1
	.byte	0x3e
	.4byte	.LASF21
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.uleb128 0x1
	.byte	0x9c
	.4byte	0x18c
	.uleb128 0xc
	.string	"ptr"
	.byte	0x1
	.byte	0x3e
	.4byte	0x8b
	.4byte	.LLST3
	.uleb128 0x9
	.4byte	.LVL7
	.4byte	0x1e3
	.uleb128 0xa
	.uleb128 0x1
	.byte	0x52
	.uleb128 0x3
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0
	.byte	0
	.uleb128 0xd
	.4byte	0x94
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xe
	.4byte	.LASF22
	.byte	0x1
	.byte	0x4c
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xe
	.4byte	.LASF23
	.byte	0x1
	.byte	0x51
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.uleb128 0x1
	.byte	0x9c
	.uleb128 0xf
	.4byte	.LASF29
	.byte	0x1
	.byte	0x27
	.4byte	0x8b
	.uleb128 0x5
	.byte	0x3
	.4byte	__dso_handle
	.uleb128 0x10
	.4byte	.LASF30
	.byte	0x3
	.byte	0x2b
	.4byte	0x8b
	.4byte	0x1e3
	.uleb128 0x11
	.4byte	0x79
	.byte	0
	.uleb128 0x12
	.4byte	.LASF31
	.byte	0x3
	.byte	0x2c
	.uleb128 0x11
	.4byte	0x8b
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
	.uleb128 0x4
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
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
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
	.uleb128 0x20
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x7
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
	.uleb128 0x8
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
	.uleb128 0x9
	.uleb128 0x4109
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x410a
	.byte	0
	.uleb128 0x2
	.uleb128 0x18
	.uleb128 0x2111
	.uleb128 0x18
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
	.uleb128 0x6e
	.uleb128 0xe
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
	.uleb128 0xc
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
	.uleb128 0x17
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0x2e
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
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
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x6
	.uleb128 0x40
	.uleb128 0x18
	.uleb128 0x2117
	.uleb128 0x19
	.byte	0
	.byte	0
	.uleb128 0xf
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
	.uleb128 0x3f
	.uleb128 0x19
	.uleb128 0x2
	.uleb128 0x18
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
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3c
	.uleb128 0x19
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.4byte	.LFE0
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
	.4byte	.LFE1
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST2:
	.4byte	.LVL4
	.4byte	.LVL5-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL5-1
	.4byte	.LFE2
	.2byte	0x4
	.byte	0xf3
	.uleb128 0x1
	.byte	0x52
	.byte	0x9f
	.4byte	0
	.4byte	0
.LLST3:
	.4byte	.LVL6
	.4byte	.LVL7-1
	.2byte	0x1
	.byte	0x52
	.4byte	.LVL7-1
	.4byte	.LFE3
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
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.4byte	.LFB1
	.4byte	.LFE1-.LFB1
	.4byte	.LFB2
	.4byte	.LFE2-.LFB2
	.4byte	.LFB3
	.4byte	.LFE3-.LFB3
	.4byte	.LFB4
	.4byte	.LFE4-.LFB4
	.4byte	.LFB5
	.4byte	.LFE5-.LFB5
	.4byte	.LFB6
	.4byte	.LFE6-.LFB6
	.4byte	0
	.4byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.4byte	.LFB0
	.4byte	.LFE0
	.4byte	.LFB1
	.4byte	.LFE1
	.4byte	.LFB2
	.4byte	.LFE2
	.4byte	.LFB3
	.4byte	.LFE3
	.4byte	.LFB4
	.4byte	.LFE4
	.4byte	.LFB5
	.4byte	.LFE5
	.4byte	.LFB6
	.4byte	.LFE6
	.4byte	0
	.4byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF12:
	.string	"bool"
.LASF27:
	.string	"size_t"
.LASF21:
	.string	"_ZdaPv"
.LASF29:
	.string	"__dso_handle"
.LASF2:
	.string	"short unsigned int"
.LASF25:
	.string	"src/fdvutils.cpp"
.LASF8:
	.string	"float"
.LASF22:
	.string	"__cxa_pure_virtual"
.LASF16:
	.string	"_Znaj"
.LASF4:
	.string	"long unsigned int"
.LASF23:
	.string	"__cxa_deleted_virtual"
.LASF0:
	.string	"unsigned char"
.LASF24:
	.string	"GNU C++ 4.8.2 -fpreprocessed -mlongcalls -mtext-section-literals -g -Os -O2 -fno-inline-functions -fno-exceptions -fno-rtti"
.LASF9:
	.string	"double"
.LASF10:
	.string	"unsigned int"
.LASF18:
	.string	"operator delete"
.LASF7:
	.string	"long long unsigned int"
.LASF13:
	.string	"operator new"
.LASF26:
	.string	"C:\\\\sviluppo\\\\ESP8266\\\\projects\\\\ESPWebFramework"
.LASF11:
	.string	"sizetype"
.LASF31:
	.string	"free"
.LASF6:
	.string	"long long int"
.LASF19:
	.string	"operator delete []"
.LASF3:
	.string	"short int"
.LASF5:
	.string	"long int"
.LASF15:
	.string	"_Znwj"
.LASF28:
	.string	"abort"
.LASF20:
	.string	"_ZdlPv"
.LASF1:
	.string	"signed char"
.LASF14:
	.string	"operator new []"
.LASF17:
	.string	"size"
.LASF30:
	.string	"malloc"
	.ident	"GCC: (GNU) 4.8.2"

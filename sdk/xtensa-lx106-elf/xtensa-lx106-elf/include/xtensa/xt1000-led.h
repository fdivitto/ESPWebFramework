/*
 *  leds.h  --  XT1000 16-segment LED related definitions
 *
 *  Copyright 2002 Tensilica Inc.
 */

#ifndef _leds_h_included_
#define _leds_h_included_

#include <xtensa/xt1000.h>


#define XT1000_LED_PAUSECLKS	50000	/* in core clock cycles (!) */

/*  LED values:  */
#define XT1000_LED_BLANK	0xFFFF
#define XT1000_LED_UNKNOWN	0x77CC	/* three horizontal bars for unknown char */

/*
 *  Set the LED register.
 *  Note that bits are active low, ie. 0=on, 1=off.  See leds.c for details.
 *  This register is always accessed as unsigned (32-bit access), so the same
 *  code works in both big-endian and little-endian cores.
 *  Note: the updates to _led_shadow and to the LED register are not atomic,
 *	so if an interrupt comes in between setting _led_shadow and setting the LED
 *	register, the LED register and _led_shadow may become inconsistent.
 *	Applications should disable interrupts or otherwise protect accesses
 *	to the LED register themselves if this is needed.
 */
#ifdef XT1000_LED_VADDR
#define XT1000_SETLED(value)	(*(volatile unsigned*)XT1000_LED_VADDR = _led_shadow = (value))
#else
#define XT1000_SETLED(value)	(_led_shadow = (value))
#endif
/*#define LED_REG	(*(volatile unsigned*)XT1000_LED_VADDR)*/	/* LED register */

/*
 *  Set selected LED segments, according to corresponding mask and value bits
 *  and the following table:
 *	mask bit	value bit	action
 *	   0		   0		<nothing>
 *	   0		   1		<toggle>
 *	   1		   0		<set to OFF>
 *	   1		   1		<set to ON>
 */
#define XT1000_WRITELED(mask,value)	XT1000_SETLED((_led_shadow | (mask)) ^ (value))

/*  The LED register is write-only, so we keep around a copy to read it:  */
extern volatile unsigned _led_shadow;	/* current LED reg contents, if written only via XT1000_SETLED() */

extern const unsigned short _LedSegments[];
extern const unsigned short _LedRotate[];

extern void led_display_char( char c );
extern void led_display_string( const char *s );
extern void led_display_digit( int d );
extern void led_display_sequence( const short *seq );
extern void led_display_ok( void );
extern void led_blank( void );
extern void led_pause( int i );


#endif /*_leds_h_included_*/


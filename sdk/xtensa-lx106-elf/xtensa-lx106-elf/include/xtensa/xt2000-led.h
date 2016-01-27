/*
 *  leds.h  --  XT2000 8-Character led
 *
 *  Copyright 2002 Tensilica Inc.
 */

#ifndef _leds_h_included_
#define _leds_h_included_

#include <xtensa/xt2000.h>


#define XT2000_LED_PAUSECLKS	50000	/* in core clock cycles (!) */


/*+*----------------------------------------------------------------------------
/ Function: xt2000_led_display_char
/
/ Description:  Sets the first character on the led display.  The remaining
/		elements on the LED will be blanked out.
/
/ Parameters: c -- The character to be
/
/ Returns: nothing.
/-**----------------------------------------------------------------------------*/

extern void xt2000_led_display_char( const char c );



/*+*----------------------------------------------------------------------------
/ Function: xt2000_led_display_string
/
/ Description:  Sets the leds on the XT2000.  The first 8 characters in
/		the supplied string will be used, the remaining characters
/		will be ignored.
/
/ Parameters: str -- Pointer to the string to be displayed.
/
/ Returns: nothing.
/-**----------------------------------------------------------------------------*/

extern void xt2000_led_display_string( const char *s );




/*+*----------------------------------------------------------------------------
/ Function: xt2000_led_display_ok
/
/ Description: Display an Ok on the led
/
/ Parameters: none
/
/ Returns: nothing.
/-**----------------------------------------------------------------------------*/

extern void xt2000_led_display_ok( void );



/*+*----------------------------------------------------------------------------
/ Function: xt2000_led_blank
/
/ Description: Blanks the led display
/
/ Parameters: none
/
/ Returns: nothing.
/-**----------------------------------------------------------------------------*/

extern void xt2000_led_blank( void );




extern void xt2000_led_pause( int i );


#endif /*_leds_h_included_*/


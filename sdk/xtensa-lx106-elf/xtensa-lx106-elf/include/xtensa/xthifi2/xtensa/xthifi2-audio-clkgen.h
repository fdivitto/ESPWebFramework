/*******************************************************************************

Copyright (c) 2009 by Tensilica Inc.  ALL RIGHTS RESERVED.
These coded instructions, statements, and computer programs are the
copyrighted works and confidential proprietary information of Tensilica Inc.
They may not be modified, copied, reproduced, distributed, or disclosed to
third parties in any manner, medium, or form, in whole or in part, without
the prior written consent of Tensilica Inc.
--------------------------------------------------------------------------------

xthifi2-audio-clkgen.h       Part of board-support-package for XT-HiFi2 board.

Interface (API) to Audio clock generation mechanism.
AIC and HDMI devices are configured as slaves and accept 
bit clock and word clock from the FPGA. These clocks need
to be configured in accordence with sampling frequency.
AIC and HDMI device drivers use the commands listed below
in order to program the clock generator.
*******************************************************************************/

#ifndef _AUDIO_CLKGEN_H
#define _AUDIO_CLKGEN_H

#define AUDIO_CLK_GENERATOR_TWI_ADDR        0x78
#define BASE_OSCILLATOR_TWI_ADDR            0xD2

/* Audio clock generator register addreses */
#define AUDIO_CLK_GENERATOR_POWER_UP_REG    0x00
#define AUDIO_CLK_GENERATOR_SAMP_FREQ_REG   0x01
#define BASE_OSCILLATOR_M_REG               0x84
#define BASE_OSCILLATOR_N_L_REG             0x85
#define BASE_OSCILLATOR_N_H_REG             0x86

/* Sampling frequencies supported by audio clock generator */
typedef enum {
 clk_gen_samp_freq_48k = 0,
 clk_gen_samp_freq_96k,
 clk_gen_samp_freq_32k,
 clk_gen_samp_freq_24k,
 clk_gen_samp_freq_16k,
 clk_gen_samp_freq_12k,
 clk_gen_samp_freq_8k,

 clk_gen_samp_freq_88_2k,
 clk_gen_samp_freq_44_1k,
 clk_gen_samp_freq_22_05k,
 clk_gen_samp_freq_11_025k,
} clk_gen_samp_freq_t; 

/* Audio output device */
typedef enum {
 audio_out_hdmi = 0,
 audio_out_aic = 1,
} audio_out_t;

#endif /* _AUDIO_CLKGEN_H */

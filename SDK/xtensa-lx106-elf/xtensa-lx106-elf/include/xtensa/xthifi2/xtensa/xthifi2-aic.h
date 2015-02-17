/*******************************************************************************

Copyright (c) 2009 by Tensilica Inc.  ALL RIGHTS RESERVED.
These coded instructions, statements, and computer programs are the
copyrighted works and confidential proprietary information of Tensilica Inc.
They may not be modified, copied, reproduced, distributed, or disclosed to
third parties in any manner, medium, or form, in whole or in part, without
the prior written consent of Tensilica Inc.
--------------------------------------------------------------------------------

xthifi2-aic.h       Part of board-support-package for XT-HiFi2 board.

Interface (API) to driver for Texas Instruments TLV320AIC31 Audio Codec.
This API could move toward a generic API for different audio DAC devices.

Currently it is associated with a specific board and assumes a single AIC 
device and 2 channels (stereo), and allocates 4x4KB buffers in local DRAM
(that consumes the entire 16 KB local DRAM on the the XT-HiFi2's core).
If the buffer space needs to be larger, it must be placed in system RAM
(currently the driver source must be changed and the driver recompiled -
 later the API needs to allow the application to provide the buffers).

The audio format is PCM with each sample being a signed 32-bit integer,
big-endian, with successive samples alternating left and right. Note that
the XT-HiFi2 board has a little-endian processor.

*******************************************************************************/

#ifndef _AIC_H
#define _AIC_H

/* Buffer size hard-coded for now. Should go in driver-specific layer. */
#define AIC_FRAME_SAMPLES   1024    // Must be a multiple of 16
#define AIC_FRAME_SIZE      (sizeof(int) * AIC_FRAME_SAMPLES)   // bytes

/* Error codess. */
typedef enum {
    aic_err_ok = 0,
    aic_err_fail,
} aic_err_t;

/* Supported sampling frequencies. */
typedef enum {
    aic_samp_freq_8k,
    aic_samp_freq_11_025k,    
    aic_samp_freq_12k,
    aic_samp_freq_16k,
    aic_samp_freq_22_05k,
    aic_samp_freq_24k,
    aic_samp_freq_32k,
    aic_samp_freq_44_1k,
    aic_samp_freq_48k,
    aic_samp_freq_88_2k,
    aic_samp_freq_96k,
} aic_samp_freq_t;

/* Initialize driver. Specify sampling frequency (from aic_samp_freq_t). 
   Volume is initially 0dB (full volume) and the stream is not muted. */
extern aic_err_t    aic_open(aic_samp_freq_t freq);

/* Release device and resources. */
extern void         aic_close(void);

/* Mute (1) or unmute (0) or ask mute status of audio stream. */
extern int          aic_is_muted(void);
extern aic_err_t    aic_set_mute(int mute);

/* Set or ask current audio volume (dB relative to full volume, always -ve). */
extern int          aic_volume(void);
extern aic_err_t    aic_set_volume(int vol);

/* Read an audio frame of size AIC_FRAME_SIZE from device. 
   This function returns only when the buffer is full. */
extern aic_err_t    aic_read(int* data);

/* Write an audio frame of size AIC_FRAME_SIZE to device. */
extern aic_err_t    aic_write(int* data);

#endif /* _AIC_H */


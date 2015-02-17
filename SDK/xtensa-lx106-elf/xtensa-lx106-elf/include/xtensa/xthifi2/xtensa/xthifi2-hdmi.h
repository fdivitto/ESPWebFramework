/*******************************************************************************

Copyright (c) 2009 by Tensilica Inc.  ALL RIGHTS RESERVED.
These coded instructions, statements, and computer programs are the
copyrighted works and confidential proprietary information of Tensilica Inc.
They may not be modified, copied, reproduced, distributed, or disclosed to
third parties in any manner, medium, or form, in whole or in part, without
the prior written consent of Tensilica Inc.
--------------------------------------------------------------------------------

xthifi2-hdmi.h       Part of board-support-package for XT-HiFi2 board.

Interface (API) to driver for Analog Devices AD9889B High Definition 
Multimedia Interface (HDMI) transmitter.

This API could move toward a generic API for different HDMI devices.

Currently it is associated with a specific board and assumes a single HDMI 
device configurable as 2,4,6 or 8 audio channels. It and allocates 4x4KB 
buffers in local DRAM (that consumes the entire 16 KB local DRAM on the 
the XT-HiFi2's core).Later the API needs to allow the application to provide 
the buffers.

The audio format is PCM with each sample being a signed 32-bit integer,
big-endian, with samples in interleaved format. Note that the XT-HiFi2 board 
has a little-endian processor.

*******************************************************************************/

#ifndef _HDMI_H
#define _HDMI_H

/* Buffer size hard-coded for now. Should go in driver-specific layer. */
#define HDMI_FRAME_SAMPLES   1024    // Must be a multiple of 16
//#define HDMI_FRAME_SAMPLES   4096    // Must be a multiple of 16
#define HDMI_FRAME_SIZE      (sizeof(int) * HDMI_FRAME_SAMPLES)   // bytes

/* Error codess. */
typedef enum {
    hdmi_err_ok = 0,
    hdmi_err_fail,
} hdmi_err_t;

/* Supported sampling frequencies. */
typedef enum {
    hdmi_samp_freq_32k,
    hdmi_samp_freq_44_1k,
    hdmi_samp_freq_48k,
    hdmi_samp_freq_88_2k,
    hdmi_samp_freq_96k,
} hdmi_samp_freq_t;

/* Supported Number of channels for audio output */
typedef enum {
    hdmi_num_chan_2 = 2,
    hdmi_num_chan_4 = 4,
    hdmi_num_chan_6 = 6,
    hdmi_num_chan_8 = 8,
} hdmi_num_chan_t;

/* Initialize driver. Specify sampling frequency (from hdmi_samp_freq_t). 
   Specify number of audio channels (from hdmi_num_chan_t). */
extern hdmi_err_t    hdmi_open(hdmi_samp_freq_t freq, 
                               hdmi_num_chan_t num_channels);

/* Release device and resources. */
extern void          hdmi_close(void);

/* Read an audio frame of size HDMI_FRAME_SIZE from device. 
   This function returns only when the buffer is full. */
extern hdmi_err_t    hdmi_read(int* data);

/* Write an audio frame of size HDMI_FRAME_SIZE to device. */
extern hdmi_err_t    hdmi_write(int* data);

#endif /* _HDMI_H */


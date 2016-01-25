# this directory
ROOT_DIR :=$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST)))) 

# let's assume the SDK is up there.
SDKBASE := $(shell dirname $(shell dirname $(ROOT_DIR)))/SDK/

# homebrew installs the toolchain, but neglects to put it in your $PATH
ifeq ($(shell uname), Darwin)
	SHELL 			:= $(shell which zsh)
	PORT 				:= $(lastword $(wildcard /dev/tty.*))
	BIN_EXEC 		:= /opt/xtensa-lx106-elf/bin/
	export PATH := $(BIN_EXEC)subst:$(PATH)
else
	PORT 				:= COM7
	# get SDK path from environment variable ESP8266SDK
	SDKBASE  		:= $(subst \,/,$(ESP8266SDK))
endif

XELF 			 := xtensa-lx106-elf

AR          = $(BIN_EXEC)$(XELF)-ar
CC          = $(BIN_EXEC)$(XELF)-g++
CPP         = $(BIN_EXEC)$(XELF)-g++
LD          = $(BIN_EXEC)$(XELF)-g++
NM          = $(BIN_EXEC)xt-nm
OBJCOPY     = $(BIN_EXEC)$(XELF)-objcopy
OD          = $(BIN_EXEC)$(XELF)-objdump

ESPTOOL     = python $(SDKBASE)esptool.py

RTOS       := esp_iot_rtos_sdk-master
INCLUDES   := -I $(SDKBASE)$(RTOS)/include            \
              -I $(SDKBASE)$(RTOS)/include/espressif  \
              -I $(SDKBASE)$(RTOS)/extra_include      \
              -I $(SDKBASE)$(RTOS)/include/lwip       \
              -I $(SDKBASE)$(RTOS)/include/lwip/lwip  \
              -I $(SDKBASE)$(RTOS)/include/lwip/ipv4  \
              -I $(SDKBASE)$(RTOS)/include/lwip/ipv6  \
              -I $(SDKBASE)$(XELF)/xtensa-lx106-elf/include

# don't change -Os (or add other -O options) otherwise FLASHMEM and FSTR data will be duplicated in RAM
CFLAGS      = -g -save-temps -Os -Wpointer-arith -Wundef -Werror -Wl,-EL 	\
              -nostdlib -mlongcalls -mtext-section-literals 							\
              -fno-exceptions -fno-rtti -fno-inline-functions             \
              -fno-threadsafe-statics -fno-use-cxa-atexit                 \
              -DICACHE_FLASH -D__ets__

LDFLAGS     = -nostdlib -Wl,--no-check-sections -u call_user_start -Wl,-static -Wl,--gc-sections
LD_SCRIPT   = eagle.app.v6.ld

SDK_LIBDIR := -L$(SDKBASE)esp_iot_rtos_sdk-master/lib
ELF_LIBDIR := -L$(SDKBASE)xtensa-lx106-elf/lib

SDK_LDDIR   = $(SDKBASE)esp_iot_rtos_sdk-master/ld

# linking libgccirom.a instead of libgcc.a causes reset when working with flash memory (ie spi_flash_erase_sector)
# linking libcirom.a causes conflicts with come std c routines (like strstr, strchr...)
LIBS        = -lminic -lm -lgcc -lhal -lphy -lpp -lnet80211 -lwpa -lmain -lfreertos -llwip

OBJ  				= user_main.o fdvserial.o fdvsync.o fdvutils.o fdvflash.o fdvprintf.o fdvdebug.o fdvstrings.o \
							fdvnetwork.o fdvcollections.o fdvconfmanager.o fdvdatetime.o fdvserialserv.o fdvtask.o fdvgpio.o

SRCDIR 			= ./src/
WWW_DIR			= ./webcontent/
WWW_ADDRS		= 0x6D000
WWW_MAXSIZE	= 57344

TARGET_OUT 			= app.out

.PHONY: all flash clean flashweb flashdump flasherase

all: $(TARGET_OUT)

$(TARGET_OUT): libuser.a
	$(LD) $(ELF_LIBDIR) $(SDK_LIBDIR) -T$(SDK_LDDIR)/$(LD_SCRIPT) -Wl,-M >out.map $(LDFLAGS) -Wl,--start-group $(LIBS) libuser.a -Wl,--end-group -o $@
	$(OD) -h -j .data -j .rodata -j .bss -j .text -j .irom0.text $@
	$(OD) -t -j .text $@ >_text_content.map
	$(OD) -t -j .irom0.text $@ >_irom0_text_content.map
	$(ESPTOOL) elf2image $@

libuser.a: $(OBJ)
	$(AR) cru $@ $^
	
%.o: $(SRCDIR)%.c $(wildcard $(SRCDIR)*.h)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: $(SRCDIR)%.cpp $(wildcard $(SRCDIR)*.h)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

flash:  $(TARGET_OUT)-0x00000.bin $(TARGET_OUT)-0x11000.bin flashweb
	-$(ESPTOOL) --port $(PORT) write_flash 0x11000 $(TARGET_OUT)-0x11000.bin 0x00000 $(TARGET_OUT)-0x00000.bin

flashweb:
	python binarydir.py $(WWW_DIR) webcontent.bin $(WWW_MAXSIZE)
	-$(ESPTOOL) --port $(PORT) write_flash $(WWW_ADDRS) webcontent.bin

flashdump:
	-$(ESPTOOL) --port $(PORT) read_flash 0x0000 0x80000 flash.dump
	xxd flash.dump > flash.hex

flasherase:
	$(ESPTOOL) --port $(PORT) erase_flash
	
clean:
	-rm -f *.(a|o|out|bin|ii|s|expand|map|dump|hex)
	


# get SDK path from environment variable ESP8266SDK
SDKBASE = $(subst \,/,$(ESP8266SDK))

AR      = xtensa-lx106-elf-ar
CC      = xtensa-lx106-elf-g++
CPP     = xtensa-lx106-elf-g++
LD      = xtensa-lx106-elf-g++
NM      = xt-nm
OBJCOPY = xtensa-lx106-elf-objcopy
OD      = xtensa-lx106-elf-objdump

INCLUDES =  -I $(SDKBASE)esp_iot_rtos_sdk-master/include
INCLUDES += -I $(SDKBASE)esp_iot_rtos_sdk-master/include/espressif
INCLUDES += -I $(SDKBASE)esp_iot_rtos_sdk-master/extra_include
INCLUDES += -I $(SDKBASE)esp_iot_rtos_sdk-master/include/lwip
INCLUDES += -I $(SDKBASE)esp_iot_rtos_sdk-master/include/lwip/lwip
INCLUDES += -I $(SDKBASE)esp_iot_rtos_sdk-master/include/lwip/ipv4
INCLUDES += -I $(SDKBASE)esp_iot_rtos_sdk-master/include/lwip/ipv6
INCLUDES += -I $(SDKBASE)xtensa-lx106-elf/xtensa-lx106-elf/include

CFLAGS    = -g -save-temps -Os -O2 -Wpointer-arith -Wundef -Werror -Wl,-EL -fno-inline-functions -nostdlib -mlongcalls -mtext-section-literals
CFLAGS   += -D__ets__ 
CFLAGS   += -DICACHE_FLASH
CFLAGS   += -fno-exceptions -fno-rtti

LDFLAGS     = -nostdlib -Wl,--no-check-sections -u call_user_start -Wl,-static
LDFLAGS    += -Wl,--gc-sections

LD_SCRIPT   = eagle.app.v6.ld

SDK_LIBDIR  = -L$(SDKBASE)esp_iot_rtos_sdk-master/lib
SDK_LDDIR   = $(SDKBASE)esp_iot_rtos_sdk-master/ld

#LIBS        = -lcirom -lgccirom -lhal -lphy -lpp -lnet80211 -lwpa -lmain -lfreertos -llwip -ludhcp
# linking libgccirom.a instead of libgcc.a causes reset when working with flash memory (ie spi_flash_erase_sector)
LIBS        = -lgcc -lcirom -lhal -lphy -lpp -lnet80211 -lwpa -lmain -lfreertos -llwip -ludhcp




ESPTOOL     = python $(SDKBASE)esptool.py
ESPPORT     = COM3


.PHONY: all flash clean iromlibs


TARGET_OUT = app.out


all: $(TARGET_OUT)


# create libgccirom.a from libgcc.a
# create libcirom.a from libc.a
iromlibs:
	@echo "Creating irom version of libgcc and libc..."
	$(OBJCOPY) --rename-section .text=.irom0.text --rename-section .literal=.irom0.literal $(SDKBASE)xtensa-lx106-elf/lib/gcc/xtensa-lx106-elf/4.8.2/libgcc.a $(SDKBASE)xtensa-lx106-elf/lib/gcc/xtensa-lx106-elf/4.8.2/libgccirom.a
	$(OBJCOPY) --rename-section .text=.irom0.text --rename-section .literal=.irom0.literal $(SDKBASE)xtensa-lx106-elf/xtensa-lx106-elf/lib/libc.a $(SDKBASE)xtensa-lx106-elf/xtensa-lx106-elf/lib/libcirom.a


# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.


OBJ  = user_main.o fdvserial.o fdvsync.o fdvutils.o fdvflash.o

SRCDIR = ./src/

%.o: $(SRCDIR)%.c $(wildcard *.h)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: $(SRCDIR)%.cpp $(wildcard *.h)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	

libuser.a: $(OBJ)
	$(AR) cru $@ $^


$(TARGET_OUT): libuser.a
	$(LD) $(SDK_LIBDIR) -T$(SDK_LDDIR)/$(LD_SCRIPT) -Wl,-M >out.map $(LDFLAGS) -Wl,--start-group $(LIBS) libuser.a -Wl,--end-group -o $@
	$(OD) -h $@
	$(ESPTOOL) elf2image $@


flash:  $(TARGET_OUT)-0x00000.bin $(TARGET_OUT)-0x40000.bin
	-$(ESPTOOL) --port $(ESPPORT) write_flash 0x00000 $(TARGET_OUT)-0x00000.bin 0x40000 $(TARGET_OUT)-0x40000.bin


clean:
	rm -f *.a
	rm -f *.o
	rm -f *.out
	rm -f *.bin
	rm -f *.ii
	rm -f *.s
	rm -f *.expand
	rm -f *.map
	


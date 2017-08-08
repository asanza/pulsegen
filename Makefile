include common.mk

TARGET = dist/blinky

LIBS += -Lsrc/platform -lc -lplat
LDFLAGS = -Wl,-Tsrc/platform/arch/bsp/STM32F769NIHx_FLASH.ld
LDFLAGS += -Wl,--gc-sections

LDFLAGS += -Wl,--warn-common
LDFLAGS += -Wl,--check-sections -Wl,--Map=$(TARGET).map
LDFLAGS += -Wl,--cref --specs=nano.specs --specs=nosys.specs


INC = -Isrc/platform/include
INC += -Isrc/platform/libs/lwip/src/include
INC += -Isrc/apps/anybus/abcc_adapt
INC += -Isrc/apps/anybus/abcc_abp
INC += -Isrc/apps/anybus/abcc_drv/inc
INC += -Isrc/apps/anybus/abcc_obj
INC += -Isrc/apps/anybus/abcc_obj/nw_obj
INC += -Isrc/apps/anybus/DevelopHelperFiles
INC += -Isrc/apps/anybus/UTIL
INC += -Isrc/apps/anybus

SRCS = src/apps/main.c src/apps/webiface/src/webiface.c
SRCS += $(call rwildcard,src/apps/anybus,*.c)

CFLAGS += $(INC) -DPROFINET -DELBUS_1 -D_DEBUG
CPPFLAGS += $(INC)

DIRS = src/platform

.PHONY: all $(DIRS)

all: $(DIRS)
	$(vecho) "CC $<"
	$(Q) $(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $(TARGET).elf $(LIBS)
	arm-none-eabi-size $(TARGET).elf
	arm-none-eabi-objcopy $(TARGET).elf -O binary $(TARGET).bin

web:
#	cd apps/webiface/makefsdata && ./makefsdata -11

$(DIRS):
	$(MAKE) --directory=$@


flash: all
	openocd -f tools/flash.openocd

winflash: all
	sh tools/winflash.sh

test:
	cd test && rake test:all

clean:
	$(MAKE) -C $(DIRS) clean
	rm -vf $(TARGET).elf *.o $(TARGET).bin

-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

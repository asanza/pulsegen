include common.mk

TARGET = dist/pulsegen

LIBS +=
LDFLAGS += -Wl,-Tsrc/hal/STM32F107RCTx_FLASH.ld

LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--check-sections -Wl,--Map=$(TARGET).map
LDFLAGS += -Wl,--warn-common


INC  = -Isrc/hal/support/CMSIS/Include
INC += -Isrc/hal/support/CMSIS/Device/ST/STM32F1xx/Include
INC += -Isrc/hal/support/STM32F1xx_HAL_Driver/Inc
INC += -Isrc/hal/include
INC += -Isrc/os/include
INC += -Isrc/os/portable/GCC/ARM_CM3
INC += -Isrc/gfx/include
INC += -Isrc/pulsegen/include
INC += -Isrc/sys/include

SRCS += $(call rwildcard,src/hal/support/STM32F1xx_HAL_Driver/Src,*.c)
SRCS += $(call rwildcard,src/hal/src,*.c)

SRCS += $(call rwildcard,src/os/src,*.c)
SRCS += src/os/portable/GCC/ARM_CM3/port.c
SRCS += src/os/portable/MemMang/heap_1.c
SRCS += $(call rwildcard,src/sys/src,*.c)

SRCS += $(call rwildcard,src/gfx/src,*.c)

CPPSRCS  = $(call rwildcard,src/pulsegen/src,*.cc)
CPPSRCS += src/main.cc src/controller.cc
CPPSRCS += $(call rwildcard,src/gfx/src,*.cc)

ASMSRC = $(call rwildcard,src/hal/src,*.s)

DIRS =

OBJS  = $(patsubst %.c,%.o, $(SRCS))
OBJS += $(patsubst %.cc,%.o, $(CPPSRCS))
OBJS += $(patsubst %.s, %.o, $(ASMSRC))

DEPS = $(patsubst %.o,%.d,$(OBJS))


.PHONY: all $(DIRS)

all: $(OBJS)
	$(vecho) "CC $<"
	$(Q) $(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET).elf $(LIBS)
	arm-none-eabi-size $(TARGET).elf
	arm-none-eabi-objcopy $(TARGET).elf -O binary $(TARGET).bin


%.o: %.c
	$(vecho) "CC $<"
	$(Q) $(CC) -c $(CFLAGS) $< -o $@

%.o: %.cc
	$(vecho) "C++ $<"
	$(Q) $(CPP) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

%.o: %.s
	$(vecho) "AS $<"
	$(Q) $(AS) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

$(DEPS): ;
.PRECIOUS: $(DEPS)

flash: all
	openocd -f tools/flash.openocd

winflash: all
	sh tools/winflash.sh

test:
	cd test && rake test:all

clean:
	rm -vf $(TARGET).elf $(TARGET).bin
	rm -vf $(OBJS)
	rm -vf $(DEPS)

-include $(DEPS)

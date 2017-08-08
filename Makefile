include common.mk

TARGET = dist/pulsegen

LIBS +=
LDFLAGS = -Wl,-Tsrc/hal/STM32F107RCTx_FLASH.ld
LDFLAGS += -Wl,--gc-sections

LDFLAGS += -Wl,--warn-common
LDFLAGS += -Wl,--check-sections -Wl,--Map=$(TARGET).map
LDFLAGS += -Wl,--cref --specs=nano.specs --specs=nosys.specs


INC  = -Isrc/hal/support/CMSIS/Include
INC += -Isrc/hal/support/CMSIS/Device/ST/STM32F1xx/Include
INC += -Isrc/hal/support/STM32F1xx_HAL_Driver/Inc

SRCS  = src/main.c
SRCS += $(call rwildcard,src/hal/support/STM32F1xx_HAL_Driver/Src,*.c)
CPPSRCS =
ASMSRC = src/hal/startup_stm32f107xc.s

CFLAGS += $(INC) -Wfatal-errors  -DSTM32F107xC
CPPFLAGS += $(INC) -Wfatal-errors

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

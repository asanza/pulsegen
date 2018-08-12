include common.mk

TARGET = dist/pulsegen

FREERTOS_PATH = src/os/amazon-freertos/lib

LIBS +=
LDFLAGS += -Wl,-Tsrc/hal/STM32F107RCTx_FLASH.ld

LDFLAGS += -Wl,--gc-sections
LDFLAGS += -Wl,--check-sections -Wl,--Map=$(TARGET).map
LDFLAGS += -Wl,--warn-common


INC  = -Isrc/hal/support/CMSIS/Include
INC += -Isrc/hal/support/CMSIS/Device/ST/STM32F1xx/Include
INC += -Isrc/hal/support/STM32F1xx_HAL_Driver/Inc
INC += -Isrc/hal/include
INC += -I$(FREERTOS_PATH)/include
INC += -I$(FREERTOS_PATH)/FreeRTOS/portable/GCC/ARM_CM3
INC += -Isrc/gfx/include
INC += -Isrc/pulsegen/include
INC += -Isrc/os
INC += -I$(FREERTOS_PATH)/include/private
INC += -Isrc/sys/include
INC += -Isrc/hal/support/embedd/include

SRCS += $(call rwildcard,src/hal/support/STM32F1xx_HAL_Driver/Src,*.c)
SRCS += $(call rwildcard,src/hal/support/embedd/src,*.c)
SRCS += $(call rwildcard,src/hal/src,*.c)


SRCS += $(FREERTOS_PATH)/FreeRTOS/event_groups.c \
		$(FREERTOS_PATH)/FreeRTOS/list.c \
		$(FREERTOS_PATH)/FreeRTOS/queue.c \
		$(FREERTOS_PATH)/FreeRTOS/stream_buffer.c \
		$(FREERTOS_PATH)/FreeRTOS/tasks.c \
		$(FREERTOS_PATH)/FreeRTOS/timers.c 
SRCS += $(FREERTOS_PATH)/FreeRTOS/portable/GCC/ARM_CM3/port.c
SRCS += $(FREERTOS_PATH)/FreeRTOS/portable/MemMang/heap_1.c
SRCS += $(call rwildcard,src/sys/src,*.c)
SRCS += $(call rwildcard,src/pulsegen/src,*.c)

SRCS += $(call rwildcard,src/gfx/src,*.c)
SRCS += src/main.c

ASMSRC = $(call rwildcard,src/hal/src,*.s)

DIRS =

OBJS  = $(patsubst %.c,%.o, $(SRCS))
# OBJS += $(patsubst %.cc,%.o, $(CPPSRCS))
OBJS += $(patsubst %.s, %.o, $(ASMSRC))

DEPS = $(patsubst %.o,%.d,$(OBJS))


.PHONY: all $(DIRS)

all: $(OBJS)
	$(vecho) "CC $<"
	$(Q) $(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(TARGET).elf $(LIBS)
	arm-none-eabi-size $(TARGET).elf
	arm-none-eabi-objcopy $(TARGET).elf -O binary $(TARGET).bin


flash: all
	openocd -f tools/flash.openocd

debug:
	tools/jlink.sh

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

clean:
	rm -vf $(TARGET).elf $(TARGET).bin
	rm -vf $(OBJS)
	rm -vf $(DEPS)

-include $(DEPS)

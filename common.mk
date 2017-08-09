# Common makefile definitions
#
CPU = -mcpu=cortex-m3
FPU =
FLOAT-ABI =
OPT = -O0 -ggdb -gdwarf-2

MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

PART = STM32F769xx

### Build flags for all targets
CFLAGS = $(MCU) -D$(PART) -ffunction-sections -fdata-sections -std=gnu11
CFLAGS += -Wall -Wno-variadic-macros -Wno-packed-bitfield-compat
CFLAGS += $(OPT) -DUSE_FULL_LL_DRIVER
CFLAGS += -nostartfiles -gdwarf-2 -g3

# Generate dependency information
CFLAGS += -MMD -MP

LDFLAGS = $(MCU) -specs=nano.specs

ARFLAGS = #$(PLUGIN)#--plugin=$(shell arm-none-eabi-gcc --print-file-name=liblto_plugin.so)

#LDFLAGS = $(CPU) $(FPU) -mthumb -nostartfiles -Wl,

TRGT	= arm-none-eabi-
CC		= $(TRGT)gcc -std=gnu11
CPP		= $(TRGT)g++
LD		= $(TRGT)ld
CP		= $(TRGT)objcopy
AS		= $(TRGT)gcc -x assembler-with-cpp
AR		= $(TRGT)ar
OD		= $(TRGT)objdump
SZ		= $(TRGT)size
HEX		= $(CP) -O ihex
BIN		= $(CP) -O binary

rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

ifeq ("$(V)","1")
Q :=
vecho := @true
else
Q := @
vecho := @echo
endif

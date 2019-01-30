TARGET = libtcrt0
# Specify the compiler to use
CC=arm-none-eabi-gcc
# Specify the assembler to use
AS=arm-none-eabi-as
# Specity the linker to use
LD=arm-none-eabi-ld
AR=arm-none-eabi-ar

CCFLAGS = -mcpu=cortex-m3 -mthumb -g  -O0 

LDFLAGS = -T linker_script.ld --cref -Map main.map -nostartfiles

CSRC =  semihost.c \
		sysinit.c

# List the object files involved in this project
OBJS  =	$(patsubst %.c,%.o, $(CSRC))
OBJS += init.o

# The default 'target' (output) is main.elf and it depends on the object files being there.
# These object files are linked together to create main.elf
$(TARGET).a : $(OBJS)
	$(AR) rcs $(TARGET).a $(OBJS) 
# The object file main.o depends on main.c.  main.c is compiled to make main.o
%.o: %.c
	$(CC) -c $(CCFLAGS) $< -o $@

%.o: %s
	$(AS) -c $(CCFLAGS) $< -o $@

# if someone types in 'make clean' then remove all object files and executables
# associated wit this project
clean: 
	rm $(OBJS) 
	rm $(TARGET).a 

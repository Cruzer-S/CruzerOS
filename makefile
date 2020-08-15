ARCH = armv7-a
MCPU = cortex-a8

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy

LINKER_SCRIPT = ./cruzeros.ld
MAP_FILE = build/cruzeros.map

ASM_SRCS = $(wildcard boot/*.S)
ASM_OBJS = $(patsubst boot/%.S, build/%.os, $(ASM_SRCS))

C_SRCS = $(wildcard boot/*.c)
C_OBJS = $(patsubst boot/%.c, build/%.o, $(C_SRCS))

INC_DIRS = -I include

cruzeros = build/cruzeros.axf
cruzeros_bin = build/cruzeros.bin

.PHONY: all clean run debug gdb

all: $(cruzeros)

clean:
	@rm -fr build

run: $(cruzeros)
	qemu-system-arm -M realview-pb-a8 -kernel $(cruzeros)

debug: $(cruzeros)
	qemu-system-arm -M realview-pb-a8 -kernel $(cruzeros) -S -gdb tcp::1234,ipv4

gdb:
	arm-none-eabi-gdb

$(cruzeros): $(ASM_OBJS) $(C_OBJS) $(LINKER_SCRIPT)
	$(LD) -n -T $(LINKER_SCRIPT) -o $(cruzeros) $(ASM_OBJS) \
		$(C_OBJS) -Map=$(MAP_FILE)
	$(OC) -O binary $(cruzeros) $(cruzeros_bin)

build/%.os: $(ASM_SRCS)
	mkdir -p $(shell dirname $@)
	$(CC) -mcpu=$(MCPU) $(INC_DIRS) -c -g -o $@ $<

build/%.o: $(C_SRCS)
	mkdir -p $(shell dirname $@)
	$(CC) -mcpu=$(MCPU) $(INC_DIRS) -c -g -o $@ $<

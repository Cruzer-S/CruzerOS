ARCH = armv7-a
MCPU = cortex-a8

CC = arm-none-eabi-gcc
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OC = arm-none-eabi-objcopy

LINKER_SCRIPT = ./cruzeros.ld

ASM_SRCS = $(wildcard boot/*.S)
ASM_OBJS = $(patsubst boot/%.S, build/%.o, $(ASM_SRCS))

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

$(cruzeros): $(ASM_OBJS) $(LINKER_SCRIPT)
	$(LD) -n -T $(LINKER_SCRIPT) -o $(cruzeros) $(ASM_OBJS)
	$(OC) -O binary $(cruzeros) $(cruzeros_bin)

build/%.o: boot/%.S
	mkdir -p $(shell dirname $@)
	$(AS) -march=$(ARCH) -mcpu=$(MCPU) -g -o $@ $<

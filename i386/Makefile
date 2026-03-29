CC = i686-elf-gcc
AS = i686-elf-as
CFLAGS ?= -O2
CFLAGS := $(CLFAGS) -std=gnu99 -ffreestanding -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc
OBJ = LineKernel.o boot.o LineRenderer.o ps2_keyboard.o bios_tools.o serial.o

all: LineKernel

run: all
	qemu-system-i386 -kernel LineKernel

LineKernel: $(OBJ)
	$(CC) -o LineKernel $(LDFLAGS) $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

LineRenderer.o: LineRenderer.c
	$(CC) -c LineRenderer.c -o LineRenderer.o $(CFLAGS)

ps2_keyboard.o: ps2_keyboard.c
	$(CC) -c ps2_keyboard.c -o ps2_keyboard.o $(CFLAGS)

bios_tools.o: bios_tools.c
	$(CC) -c bios_tools.c -o bios_tools.o $(CFLAGS)

boot.o: boot.s
	$(AS) boot.s -o boot.o

check: all
	grub-file --is-x86-multiboot LineKernel

iso: check
	cp -r ../iso .
	cp LineKernel iso/boot/LineKernel
	grub-mkrescue -o LineKernel.iso iso

clean:
	rm -r iso *.iso *.o LineKernel || true

.PHONY: clean all iso check

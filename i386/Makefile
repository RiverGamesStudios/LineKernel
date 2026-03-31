CC = i686-elf-gcc
AS = i686-elf-as
CFLAGS ?= -O2
CFLAGS := $(CLFAGS) -std=gnu99 -ffreestanding -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc
OBJ = LineKernel.o boot.o LineRenderer.o ps2_keyboard.o bios_tools.o serial.o str.o version.o

all: LineKernel LineKernel.gz

run: all
	qemu-system-i386 -kernel LineKernel

LineKernel: $(OBJ)
	$(CC) -o LineKernel $(LDFLAGS) $(OBJ)

LineKernel.gz: LineKernel
	gzip -k LineKernel

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

boot.o: boot.s
	$(AS) boot.s -o boot.o

check: all
	grub-file --is-x86-multiboot LineKernel

iso: check
	cp -r ../iso .
	cp LineKernel.gz iso/boot/LineKernel.gz
	grub-mkrescue -o LineKernel.iso iso

clean:
	rm -r iso *.iso *.o *.gz LineKernel || true

.PHONY: clean all iso check

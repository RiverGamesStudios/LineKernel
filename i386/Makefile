CC = i686-elf-gcc
AS = i686-elf-as
CFLAGS ?= -O2
CFLAGS := $(CLFAGS) -std=gnu99 -ffreestanding -Wall -Wextra -Wpedantic
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib
OBJ = LineKernel.o boot.o LineRenderer.o ps2_keyboard.o bios_tools.o serial.o str.o version.o ide.o RiverAdvice.o

all: LineKernel LineKernel.gz

run: all
	qemu-system-i386 -m 2G -kernel LineKernel $(DTYPE) $(DISK)

LineKernel: $(OBJ)
	$(CC) -o LineKernel $(LDFLAGS) $(OBJ) -lgcc

LineKernel.gz: LineKernel
	gzip -9 -n -f -k LineKernel

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

boot.o: boot.s
	$(AS) boot.s -o boot.o

check: all
	grub-file --is-x86-multiboot LineKernel

LineKernel.iso: check
	cp -r ../iso .
	cp LineKernel.gz iso/boot/LineKernel.gz
	grub-mkrescue -o LineKernel.iso iso
	rm -r ./iso

run-iso: LineKernel.iso
	qemu-system-i386 -cdrom LineKernel.iso $(DTYPE) $(DISK)

clean:
	rm -r iso *.iso *.o *.gz LineKernel || true

.PHONY: clean all iso check

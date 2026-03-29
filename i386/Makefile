GCC = i686-elf-gcc
AS = i686-elf-as
CFLAGS ?= -O2
CFLAGS := $(CLFAGS) -std=gnu99 -ffreestanding -Wall -Wextra
LDFLAGS = -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

all: LineKernel

run: all
	qemu-system-i386 -kernel LineKernel

LineKernel: LineKernel.o boot.o LineRenderer.o ps2_keyboard.o
	$(GCC) -o LineKernel $(LDFLAGS) boot.o LineRenderer.o ps2_keyboard.o LineKernel.o

LineKernel.o: LineKernel.c
	$(GCC) -c LineKernel.c -o LineKernel.o $(CFLAGS)

LineRenderer.o: LineRenderer.c
	$(GCC) -c LineRenderer.c -o LineRenderer.o $(CFLAGS)

ps2_keyboard.o: ps2_keyboard.c
	$(GCC) -c ps2_keyboard.c -o ps2_keyboard.o $(CFLAGS)

boot.o: boot.s
	$(AS) boot.s -o boot.o

clean:
	rm *.o LineKernel || true

.PHONY: clean all

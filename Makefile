ARCH ?= i386
include $(ARCH)/Makefile

include kernel/Makefile
CFLAGS ?= -O2
CFLAGS := $(CLFAGS) -Ikernel -Ithird-party -I$(ARCH) -DARCH_$(ARCH) -DARCH=\"$(ARCH)\" -std=gnu99 -ffreestanding -Wall -Wextra -Wpedantic
OBJ = $(ARCH_OBJ) $(KERNEL_OBJ)

all: LineKernel LineKernel.gz

# todo: remove -lgcc
LineKernel: $(OBJ)
	$(CC) -o LineKernel $(LDFLAGS) $(OBJ) -lgcc

LineKernel.gz: LineKernel
	gzip -9 -n -f -k LineKernel

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.s
	$(AS) $< -o $@

run: all
	$(QEMU) -m 2G -kernel LineKernel $(DTYPE) $(DISK)

LineKernel.iso:
	cp -r ../iso .
	cp LineKernel.gz iso/boot/LineKernel.gz
	grub-mkrescue -o LineKernel.iso iso
	rm -r ./iso

run-iso: LineKernel.iso
	$(QEMU) -cdrom LineKernel.iso $(DTYPE) $(DISK)

clean:
	rm -f LineKernel LineKernel.gz $(OBJ)

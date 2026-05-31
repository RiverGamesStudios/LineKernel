VERSION = 0.1.0.983

ARCH ?= i386
include $(ARCH)/Makefile

include kernel/Makefile
CFLAGS ?= -O2
CFLAGS += -Ikernel -Ithird-party -I$(ARCH) -DARCH_$(ARCH) -DARCH=\"$(ARCH)\" -DVERSION=\"$(VERSION)\" -std=gnu99 -ffreestanding -Wall -Wextra -Wpedantic -fstack-protector-all $(ARCH_CFLAGS)
OBJ = $(ARCH_OBJ) $(KERNEL_OBJ)

all: LineKernel LineKernel.gz

kernel/kconfig.h: .config
	python3 ./tools/config2header.py .config > kernel/kconfig.h

Kconfig: Kconfig.template
	cp Kconfig.template Kconfig
	sed -i "s/{ARCH}/$(ARCH)/g" Kconfig
	sed -i "s/{VERSION}/$(VERSION)/g" Kconfig

menuconfig: Kconfig
	kconfig-mconf Kconfig

xconfig: Kconfig
	kconfig-qconf Kconfig

# todo: remove -lgcc
LineKernel: $(OBJ)
	$(CC) -o LineKernel $(LDFLAGS) $(OBJ) -lgcc

LineKernel.gz: LineKernel
	gzip -9 -n -f -k LineKernel

%.o: %.c kernel/kconfig.h
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
	rm -f LineKernel LineKernel.gz $(OBJ) kernel/kconfig.h

distclean: clean
	rm -rf Kconfig .config .config.old kernel/LineKernel.qcow2 docs/

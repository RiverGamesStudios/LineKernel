# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: Copyright (C) 2026 River Games

VERSION = 0.1.0.983

ifneq ("$(wildcard kernel/kconfig.mk)","")
	include kernel/kconfig.mk
endif

ARCH ?= i386
include $(ARCH)/Makefile
ifneq (x$(META_ARCH),x)
	include $(META_ARCH)/Makefile
endif

include kernel/Makefile
CFLAGS ?= -O2
CFLAGS += -Ikernel -Ithird-party -I$(ARCH) -I$(META_ARCH) -DARCH_$(ARCH) -DARCH=\"$(ARCH)\" -DVERSION=\"$(VERSION)\" -std=gnu99 -ffreestanding -Wall -Wextra -Wpedantic -Wmissing-declarations -fstack-protector-all $(ARCH_CFLAGS)
OBJ = $(ARCH_OBJ) $(META_ARCH_OBJ) $(KERNEL_OBJ)

all:
	make kernel/kconfig.mk kernel/kconfig.h
	make LineKernel LineKernel.gz

kernel/kconfig.h: .config
	python3 ./tools/config2header.py .config > kernel/kconfig.h

kernel/kconfig.mk: .config
	python3 ./tools/config2makefile.py .config > kernel/kconfig.mk

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

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.s
	$(AS) $< -o $@

run: all
	$(QEMU) -m 2G -kernel LineKernel $(QEMUARGS)

LineKernel.iso: all
	cp LineKernel.gz iso/boot/LineKernel.gz
	grub-mkrescue -o LineKernel.iso iso

run-iso: LineKernel.iso
	$(QEMU) -cdrom LineKernel.iso $(QEMUARGS)

clean:
	rm -f LineKernel LineKernel.gz iso/boot/LineKernel.gz LineKernel.iso $(OBJ) kernel/kconfig.h kernel/kconfig.mk

distclean: clean
	rm -rf Kconfig .config .config.old kernel/LineKernel.qcow2 docs/

.PHONY: all Kconfig run run-iso clean distclean

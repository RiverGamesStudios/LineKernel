# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: Copyright (C) 2026 River Games

VERSION = 0.1.0.983

ifneq ("$(wildcard kernel/kconfig.mk)","")
	include kernel/kconfig.mk
endif

ARCH ?= i386
include $(ARCH)/Makefile
include arches/$(ARCH).mk
ifneq (x$(META_ARCH),x)
	include $(META_ARCH)/Makefile
endif

include kernel/Makefile
ifneq ($(META_ARCH),)
	META_ARCH_FLAGS = -I$(META_ARCH) -DMETA_ARCH_$(META_ARCH)
else
	META_ARCH_FLAGS =
endif

CC = $(CCPREFIX)gcc
AS = $(CCPREFIX)as
QEMU = $(ARCH_QEMU)
CFLAGS ?= -O2 -pipe
CFLAGS += -Ikernel -Ithird-party -I$(ARCH) $(META_ARCH_FLAGS) -Iinclude -DARCH_$(ARCH) -DARCH=\"$(ARCH)\" -DVERSION=\"$(VERSION)\" -std=gnu99 -ffreestanding -Wall -Wextra -Wmissing-declarations -fstack-protector-all $(ARCH_CFLAGS)
OBJ = $(ARCH_OBJ) $(META_ARCH_OBJ) $(KERNEL_OBJ)

MENUCONFIG ?= kconfig-mconf
CONSOLECONFIG ?= kconfig-conf
XCONFIG ?= kconfig-qconf

all:
	make kernel/kconfig.mk kernel/kconfig.h
	make LineKernel LineKernel.gz

tools/config2%: ./tools/config2%.c
	cc $< -o $@

kernel/kconfig.h: .config tools/config2header
	tools/config2header .config > kernel/kconfig.h

kernel/kconfig.mk: .config tools/config2makefile
	tools/config2makefile .config > kernel/kconfig.mk

Kconfig: Kconfig.template
	cp Kconfig.template Kconfig
	sed -i "s/{ARCH}/$(ARCH)/g" Kconfig
	sed -i "s/{VERSION}/$(VERSION)/g" Kconfig

menuconfig: Kconfig
	$(MENUCONFIG) Kconfig

allyesconfig: Kconfig
	$(CONSOLECONFIG) Kconfig --allyesconfig

allnoconfig: Kconfig
	$(CONSOLECONFIG) Kconfig --allnoconfig

xconfig: Kconfig
	$(XCONFIG) Kconfig

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
	rm -f LineKernel LineKernel.gz iso/boot/LineKernel.gz LineKernel.iso $(OBJ) kernel/kconfig.h kernel/kconfig.mk tools/config2header tools/config2makefile

distclean: clean
	rm -rf Kconfig .config .config.old kernel/LineKernel.qcow2 docs/

.PHONY: all Kconfig run run-iso clean distclean

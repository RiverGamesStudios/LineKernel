# SPDX-License-Identifier: GPL-3.0-or-later
# SPDX-FileCopyrightText: Copyright (C) 2026 River Games
CC = riscv64-unknown-elf-gcc
AS = riscv64-unknown-elf-as
ifeq (x$(CONFIG_VIRT_MACHINE), xy)
	LINKSCRIPT = virt
endif
LDFLAGS = -T riscv64/$(LINKSCRIPT).ld -ffreestanding -O2 -nostdlib
ARCH_CFLAGS = -mcmodel=medany
ARCH_OBJ = riscv64/boot.o riscv64/power.o riscv64/uart.o
QEMU = qemu-system-riscv64 -machine virt -bios none

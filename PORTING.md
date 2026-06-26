# How to port an architecture to LineKernel
1. Create proper `boot.s`, `linker.ld` for arch.
2. Create a Makefile with `CC`, `AS`, `LDFLAGS`, `ARCH_OBJ`, and `QEMU`.
3. Create Kconfig for enabling/disabling features specific to the arch.
4. You probably want a console backend. Write one for serial or whatever your arch uses.
5. Get a kernel command line so you can specify what drive/what filesystem

# Requirements
These functions/variables MUST be defined.

- `void reboot(void);` and `void poweroff(void);` function, even if it does nothing. This should be in `power.c`.
- `void halt(void);` function. This should halt the CPU, stalling it forever. This should be in `power.c`.

# Meta-arches
There are meta-arches which architectures are derivatives from.
`x86` is the only meta-arch as of now.

<!--
SPDX-License-Identifier: CC0-1.0
SPDX-FileCopyrightText: Copyright (C) 2026 River Games
-->

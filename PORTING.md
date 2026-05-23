# How to port an architecture to LineKernel
1. Create proper `boot.s`, `linker.ld` for arch.
2. Create a Makefile with `CC`, `AS`, `LDFLAGS`, `ARCH_OBJ`, and `QEMU`.
3. Create Kconfig for enabling/disabling features specific to the arch.
4. You probably want a console backend. Write one for serial or whatever your arch uses.

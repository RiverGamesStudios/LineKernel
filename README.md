## LineKernel
LineKernel is the LineCoreOS kernel.

It is a kernel unlike POSIX, DOS, or NT.

This kernel is for the LineCoreOS [x86](https://wiki.rivergames.ca/wiki/History_of_LineCoreOS#x86) version (not Post-Warpix or Pre-Warpix).

## Compiling
### Dependencies
+ [Cross-compile a GCC](https://wiki.osdev.org/GCC_Cross-Compiler) for the architecture needed (for `i386` it would be `i686-elf`).

### Makefile Configurations
+ **For i386**
    + `make i386` - Compile using i686-elf for i386
    + `make run-i386` - Run an i386 kernel image in QEMU (faster)
    + `make iso-i386` - Make a bootable i386 ISO
    + `make run-iso-i386` - Run the i386 ISO in QEMU (slower, but more similar to running on real hardware)

x86_64 and other arches are ***not*** supported yet.

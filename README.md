## [<img src="https://colebohte.github.io/fs/LK_COLOUR.png" alt="drawing" width="512"/>](https://wiki.rivergames.ca/wiki/LineKernel)
[LineKernel](https://wiki.rivergames.ca/wiki/LineKernel) is a kernel unlike any other UNIX-Like kernel. LineKernel is a Monolithic kernel designed for x86(_64) built from scratch for the [LineCore Operating System](https://wiki.rivergames.ca/wiki/LineCoreOS).

This kernel is for the LineCoreOS [x86(_64)](https://wiki.rivergames.ca/wiki/History_of_LineCoreOS#x86) version.

### Features in Development
- Kernel

## Compiling
### Dependencies
+ [Cross-compile a GCC](https://wiki.osdev.org/GCC_Cross-Compiler) for the architecture needed (for `i386` it would be `i686-elf`).
+ QEMU

### Makefile Configurations
+ **For i386**
    + `make i386` - Compile using i686-elf for i386
    + `make run-i386` - Run an i386 kernel image in QEMU (faster)
    + `make iso-i386` - Make a bootable i386 ISO
    + `make run-iso-i386` - Run the i386 ISO in QEMU (slower, but more similar to running on real hardware)

x86_64 and other architectures are ***<u>not</u>*** supported ***<u>yet</u>***.

<sup>(c) 2026 River Games Studios ~ LineKernel (Project Estuary)</sup>

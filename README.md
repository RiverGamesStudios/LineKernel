## LineCoreOS for x86(_64)
LineCoreOS is an Operating System written from scratch to run on x86 and x86_64

## Philosophy
LineCoreOS is an Operating System originally designed in Turbowarp (A Scratch Mod). It was designed as a semi-modular Operating System based around the idea of being not tied to any other OS Family such as UNIX-Like or DOS-Like.

## History
LineCoreOS has had 3 major development steps; Pre-Warpix, Post-Warpix & x86(_64)

+ **Pre-Warpix** was a very barebones, early and limited installation of the OS.

+ **Post-Warpix** is currently in active development along-side x86(_64), it is the current Turbowarp implementation of the LineCore Operating System.

+ **x86(_64)** is the implementation of LineCoreOS designed to run on real i386 and 64-bit hardware.

### What was "Warpix"?
Warpix was a UNIX Inspired Turbowarp Operating System, It was designed after the 2nd Developer Beta of "Pre-Warpix". It was never released, but a lot of the code was borrowed for modern "Post-Warpix" edition of LineCoreOS. Features borrowed include `grab`, LineRender for Turbowarp, and `init`.

We now use Warpix to describe the gap in Old LineCoreOS and Modern LineCoreOS

**Fun Fact**: The Modern **rivergamesstudios/linecoreos** repository is just a rename of **rivergamesstudios/warpix**

## Compiling
### Dependencies
+ [Cross-compile a GCC](https://wiki.osdev.org/GCC_Cross-Compiler) for the architecture needed (for `i386` it would be `i686-elf`).

### Makefile Configurations
+ **For i386**
    + `make i386` - Compile using i686-elf for i386
    + `make run-i386` - Run an i386 kernel image in QEMU
    + `make iso-i386` - Make a bootable i386 ISO
    + `make run-iso-i386` - Run the i386 ISO in QEMU
+ **For x86_64**
    + Nothing here yet, **x86_64** is not developed

### Building (***UNFINISHED***)

**It is strongly advised to build this on a UNIX-Like System**<br>

**Use `make clean` before recompiling**

1. Make changes in `config.h` and save.
2. [Cross-compile a GCC](https://wiki.osdev.org/GCC_Cross-Compiler) for the architecture needed (for `i386` it would be `i686-elf`).
3. Compile using `make <arch>` (ex. `make i386`)
4. Run using `make run-<arch>` (ex. `make run-i386`)
- Anything past this point is **optional** but useful
5. Build a bootable ISO file using `make iso-<arch>` (ex. `make iso-i386`)
6. Boot the ISO using `make run-iso-<arch>` (ex. `make run-iso-i386`)

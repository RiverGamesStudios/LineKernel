# LineKernel

## Dependencies

- **`i686-elf-gcc`**: Cross-compiler for the i686-elf target. If not installed, run `bash build_toolchain.sh` to build and install it (requires a Debian-based system; this may take several minutes to an hour to complete).
- **`qemu-system-i386`**: Install with `sudo apt install qemu-system-x86` (or equivalent for your package manager).

## Building

1. Make any necessary changes in `config.h`.
2. Run `make i386` to compile the kernel for i386.

## Running

Run `make run-i386` to emulate the kernel using QEMU.

### Compiling
To start, make your changes in `config.h`.
Then, [cross-compile a GCC](https://wiki.osdev.org/GCC_Cross-Compiler) for the architecture needed (for `i386` it would be `i686-elf`).
Now, you can compile it with `make i386`.
Run with `make run-i386`.

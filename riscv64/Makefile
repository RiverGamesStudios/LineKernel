CC = riscv64-unknown-elf-gcc
AS = riscv64-unknown-elf-as
LDFLAGS = -T riscv64/linker.ld -ffreestanding -O2 -nostdlib
ARCH_CFLAGS = -mcmodel=medany
ARCH_OBJ = riscv64/boot.o riscv64/power.o riscv64/uart.o riscv64/bios_tools.o
QEMU = qemu-system-riscv64 -machine virt -bios none

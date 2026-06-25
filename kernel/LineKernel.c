/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#include "kernelcheck.h"
#include "version.h"
#include "LineRenderer.h"
#include "LineInput.h"
#include "LineDrive.h"
#include "LineFilesystem.h"
#include "version.h"
#include "printf.h"
#ifdef CONFIG_PS2_KEYBOARD
#include "ps2_keyboard.h"
#endif
#ifdef CONFIG_SERIAL_CONSOLE
#include "serial.h"
#endif
#ifdef CONFIG_UART
#include "uart.h"
#endif

#ifdef META_ARCH_x86
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#endif
#ifdef CONFIG_FLOPPY
#include "floppy.h"
#endif

/* TODO: Set this by kernel command line */
drivesformat_t drive = fdrive1;
filesystemformat_t fs = fat12;
int has_working_drive = 0;

void initialize_start(void);
void kernel_main(void);

void initialize_start(void)
{
	terminal_initialize();
	terminal_writestring("Booting LineKernel v" VERSION "...\n\n");
	terminal_writestring("LineRenderer initialized.\n");

#ifdef META_ARCH_x86
	/* Initialize basic GDT, IDT, and Timer (PIT) */
	gdt_init();
	terminal_writestring("GDT initialized.\n");
	idt_init();
	terminal_writestring("IDT initialized.\n");
	timer_init(1000);
	terminal_writestring("System Timer (PIT) initialized at 1000Hz.\n");

	/* Enable hardware interrupts */
	__asm__ volatile("sti");
	terminal_writestring("Interrupts enabled.\n");
#endif

	keyboard_init();
	terminal_writestring("Keyboard input initialized.\n");

#ifdef CONFIG_DRIVE
	terminal_writestring("Initializing storage drive...\n");
	if (drive_init(drive) == 0) {
		printf("Drive %s initialized successfully.\n", drive_name(drive));
		printf("Checking for %s filesystem...\n", filesystem_name(fs));
		has_working_drive = check_filesystem(drive, fs);
		if (has_working_drive == 1) {
			printf("%s filesystem detected on %s.\n", filesystem_name(fs), drive_name(drive));
		} else {
			printf("Filesystem not found.\n");
		}
	} else {
		printf("Failed to initialize drive %s.\n", drive_name(drive));
	}
#endif
}

void kernel_main(void)
{
	initialize_start();

	terminal_writestring("Core services initialized.\n\n");
	we_are_running();

	for (;;) {
		terminal_write_for_char(get_char());
	}
}

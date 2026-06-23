/* SPDX-License-Identifier: GPL-3.0-or-later
 * SPDX-FileCopyrightText: Copyright (C) 2026 River Games */

#include "LineInput.h"
#include "kernelcheck.h"
#include "version.h"
#include "LineRenderer.h"
#include "version.h"
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

int has_working_floppy = 0;

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

#ifdef CONFIG_FLOPPY
	terminal_writestring("Initializing floppy drive...\n");
	if (floppy_init() == 0) {
		terminal_writestring("Floppy drive fdrive1 initialized successfully.\n");
		terminal_writestring("Detecting floppy media...\n");
		has_working_floppy = floppy_detect_fat12(0);
	} else {
		terminal_writestring("Failed to initialize floppy drive fdrive1.\n");
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

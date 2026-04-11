#if defined(__linux__) || defined(__GNU__)
#error "Not cross-compiling!!!"
#endif

#if !defined(__i386__)
#error "Only compiles for i386!!!"
#endif

#include "config.h"
#include "version.h"
#include "LineRenderer.h"
#include "version.h"
#include "ide.h"
#ifdef ps2_keyboard
#include "ps2_keyboard.h"
#endif // ps2_keyboard
#ifdef serial_console
#include "serial.h"
#endif // serial_console

void initialize_start(void)
{
	terminal_initialize();
#ifdef verbose_log
	terminal_writestring("Booting LineKernel v" VERSION "...\n\n");
	terminal_writestring("LineRenderer initialized.\n");
#endif // verbose_log

#ifdef ps2_keyboard
	keyboard_init();
#ifdef verbose_log
	terminal_writestring("PS/2 keyboard controller initialized.\n");
#endif // verbose_log
#endif // ps2_keyboard

#ifdef ide
#ifdef verbose_log
	terminal_writestring("Initializing PCI IDE Controller...\n");
#endif // verbose_log
	ide_initialize(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
#ifdef verbose_log
	terminal_writestring("PCI IDE Controller initialized.\n");
#endif // verbose_log
#endif // ide
}

void kernel_main(void)
{
	initialize_start();

#ifdef verbose_log
	terminal_writestring("Core services initialized.\n\n");
#endif // verbose_log

#ifdef verbose_log
	we_are_running();
#endif // verbose_log

#ifdef verbose_log
	terminal_writestring("Hello, LineKernel!\n");
#endif // verbose_log

	char c;
	int ready;

	for (;;) {
#ifdef ps2_keyboard
		ready = is_kbd_ready_to_read();
		if (ready == 0) {
			c = keyboard_read_scancode_to_ascii_right_now();
			terminal_write_for_char(c);
		}
#endif // ps2_keyboard

#ifdef serial_console
		ready = serial_received();
		if (ready != 0) {
			c = read_serial_right_now();
			c = serial_sane_control_codes(c);
			terminal_write_for_char(c);
		}
#endif // serial_console
	}
}

#include "kernelcheck.h"
#include "config.h"
#include "version.h"
#include "LineRenderer.h"
#include "RiverAdvice.h"
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
	terminal_writestring("Welcome to LineKernel v" VERSION ".\n\n");
	terminal_writestring("LineRenderer initialized.\n");

#ifdef ps2_keyboard
	keyboard_init();
	terminal_writestring("PS/2 keyboard controller initialized.\n");
#endif // ps2_keyboard

#ifdef ide
	terminal_writestring("Initializing PCI IDE Controller...\n");
	ide_initialize(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
	terminal_writestring("PCI IDE Controller initialized.\n");
#endif // ide
}

void kernel_main(void)
{
	initialize_start();

	terminal_writestring("Core services initialized.\n\n");
	terminal_writestring("A word of advice: ");
	river_words(7);
	we_are_running();

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

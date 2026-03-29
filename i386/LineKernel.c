#if defined(__linux__) || defined(__GNU__)
#error "Not cross-compiling!!!"
#endif

#if !defined(__i386__)
#error "Only compiles for i386!!!"
#endif

#include "config.h"
#include "LineRenderer.h"
#ifdef ps2_keyboard
#include "ps2_keyboard.h"
#endif // ps2_keyboard
#ifdef serial_console
#include "serial.h"
#endif // serial_console

void initialize_start(void)
{
	terminal_initialize();
#ifdef ps2_keyboard
	keyboard_init();
#endif // ps2_keyboard
}

void kernel_main(void)
{
	initialize_start();

	terminal_writestring("Hello, LineKernel!\n");

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
			terminal_write_for_char(c);
		}
#endif // serial_console
	}
}

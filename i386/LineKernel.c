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

#ifdef ps2_keyboard
	for (;;) {
		char c = keyboard_read_scancode_to_ascii();
		if (c == '\b') {
			// Not handling backspace cursor movement yet.
		}
		else if (c == '\n') {
			terminal_newline();
		}
		else if (c != 0) {
			terminal_putchar(c);
		}
	}
#endif // ps2_keyboard
}

// this is a kernel :)
// yours truly, the grue

#if defined(__linux__) || defined(__GNU__)
#error "Not cross-compiling!!!"
#endif

#if !defined(__i386__)
#error "Only compiles for i386!!!"
#endif

#include "LineRenderer.h"
#include "ps2_keyboard.h"

void kernel_main(void)
{
	terminal_initialize();
	keyboard_init();

	terminal_writestring("Hello, LineKernel!\nType to see what happens... (btw, no shift or backspace :))\n");

	for (;;) {
		uint8_t scancode = keyboard_read_scancode();
		char c = keyboard_to_ascii(scancode);
		if (c == '\b') {
			// Not handling backspace cursor movement yet.
		}
		else if (c != 0) {
			terminal_putchar(c);
		}
	}
}

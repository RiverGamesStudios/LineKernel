#include "version.h"

void we_are_running(void)
{
	terminal_writestring("Flags: ");
#ifdef vga_console
	terminal_writestring("vga_console ");
#endif // vga_console
#ifdef ps2_keyboard
	terminal_writestring("ps2_keyboard ");
#endif // vga_console
#ifdef ide
	terminal_writestring("ide ");
#endif // ide
	terminal_writestring("\n");
	terminal_writestring("Target: " ARCH);
	terminal_writestring("\n\n");
}

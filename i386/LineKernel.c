#if defined(__linux__) || defined(__GNU__)
#error "Not cross-compiling!!!"
#endif

#if !defined(__i386__)
#error "Only compiles for i386!!!"
#endif

#include "LineRenderer.h"

void kernel_main(void)
{
	/* This is a placeholder */
	terminal_log("Starting Terminal Initialization", "INFO");
	terminal_initialize();
	terminal_log("Terminal Initialized", "OK");

	terminal_log("Starting Kernel", "INFO");
	
	// Test ANSI escape sequences
	terminal_writestring("\x1b[32mHello, LineKernel in green!\x1b[0m\n");
	terminal_writestring("\x1b[31mError message in red!\x1b[0m\n");
	terminal_writestring("\x1b[2J\x1b[H"); // Clear screen and move to home
	terminal_writestring("\x1b[10;20H"); // Move cursor to row 10, col 20
	terminal_writestring("Cursor positioned here!\n");
	
	terminal_log("ANSI Support Test Complete", "OK");
}

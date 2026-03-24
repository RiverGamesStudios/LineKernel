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
	terminal_initialize();
	terminal_writestring("Initializing Terminal...\n");

	terminal_writestring("Hello, LineKernel!\n");
}

#if defined(__linux__) || defined(__GNU__)
#error "Not cross-compiling!!!"
#endif

#if !defined(__i386__)
#error "Only compiles for i386!!!"
#endif

#include "LineRenderer.h"

void kernel_main(void)
{
	terminal_initialize();

	terminal_writestring("Hello, LineKernel!\n");
}

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
	terminal_writestring("\n");
	terminal_writestring("This is the epitimy of colebohte's brain at 10:47PM on a monday.\n");
	terminal_writestring("I wrote these 2 lines, the first one was NexusSFan\n");
}

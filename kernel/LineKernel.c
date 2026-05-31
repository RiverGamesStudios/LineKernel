#include "LineInput.h"
#include "kernelcheck.h"
#include "version.h"
#include "LineRenderer.h"
#include "version.h"
#include "panic.h"
#include "power.h"
#ifdef CONFIG_PS2_KEYBOARD
#include "ps2_keyboard.h"
#endif
#ifdef CONFIG_SERIAL_CONSOLE
#include "serial.h"
#endif
#ifdef CONFIG_UART
#include "uart.h"
#endif

void initialize_start(void)
{
	terminal_initialize();
	terminal_writestring("Booting LineKernel v" VERSION "...\n\n");
	terminal_writestring("LineRenderer initialized.\n");

#ifdef CONFIG_PS2_KEYBOARD
	keyboard_init();
	terminal_writestring("PS/2 keyboard controller initialized.\n");
#endif
}

void kernel_main(void)
{
	initialize_start();

	terminal_writestring("Core services initialized.\n\n");
	we_are_running();

	for (;;) {
		// todo: LineInput
		terminal_write_for_char(get_char());
	}
}

#include "LineInput.h"
#include "kernelcheck.h"
#include "version.h"
#include "LineRenderer.h"
#include "version.h"
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

	keyboard_init();
	terminal_writestring("Keyboard input initialized.\n");
}

void kernel_main(void)
{
	initialize_start();

	terminal_writestring("Core services initialized.\n\n");
	we_are_running();

	for (;;) {
		terminal_write_for_char(get_char());
	}
}

#include "kernelcheck.h"
#include "version.h"
#include "LineRenderer.h"
#include "version.h"
#include "power.h"
#ifdef CONFIG_IDE
#include "ide.h"
#endif
#ifdef CONFIG_PS2_KEYBOARD
#include "ps2_keyboard.h"
#endif
#ifdef CONFIG_SERIAL_CONSOLE
#include "serial.h"
#endif

int ready_to_read_uart(void);
char get_uart_input(void);

void initialize_start(void)
{
	terminal_initialize();
	terminal_writestring("Booting LineKernel v" VERSION "...\n\n");
	terminal_writestring("LineRenderer initialized.\n");

#ifdef CONFIG_PS2_KEYBOARD
	keyboard_init();
	terminal_writestring("PS/2 keyboard controller initialized.\n");
#endif

#ifdef CONFIG_IDE
	terminal_writestring("Initializing PCI IDE Controller...\n");
	ide_initialize(0x1F0, 0x3F6, 0x170, 0x376, 0x000);
	terminal_writestring("PCI IDE Controller initialized.\n");
#endif
}

void kernel_main(void)
{
	initialize_start();

	terminal_writestring("Core services initialized.\n\n");
	we_are_running();

	char c;
	int ready;

	for (;;) {
		// todo: LineInput
#ifdef CONFIG_PS2_KEYBOARD
		ready = is_kbd_ready_to_read();
		if (ready == 0) {
			c = keyboard_read_scancode_to_ascii_right_now();
			terminal_write_for_char(c);
		}
#endif

#ifdef CONFIG_SERIAL_CONSOLE
		ready = serial_received();
		if (ready != 0) {
			c = read_serial_right_now();
			c = serial_sane_control_codes(c);
			terminal_write_for_char(c);
		}
#endif

#ifdef CONFIG_UART
		ready = get_uart_input();
		if (ready != 0) {
			c = ready;
			terminal_write_for_char(c);
		}
#endif
	}
}

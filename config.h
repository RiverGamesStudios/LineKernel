#ifndef __CONFIG_H__
#define __CONFIG_H__

/* This is the config file for LineKernel. It most likely shouldn't be changed unless absolutely needed. */

/* Default background colors for LineRenderer */
#define LineRenderer_DEFAULTFOREGROUND VGA_COLOR_LIGHT_GREY
#define LineRenderer_DEFAULTBACKGROUND VGA_COLOR_BLACK

/* Enable PCI IDE controller? */
#define ide

/* Enable VGA console? */
#define vga_console

/* Enable verbose boot log? */
#define verbose_log

/* Define for keyboard support */
#define ps2_keyboard

/* Define for cursor in the console */
#define console_cursor

/* Enable serial? */
#define serial_console

#endif

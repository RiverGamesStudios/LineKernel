#ifndef __CONFIG_H__
#define __CONFIG_H__

/* This is the config file for LineKernel. It most likely shouldn't be changed unless absolutely needed. */

/** LineRenderer **/
/* Default background colors for LineRenderer */
#define TERM_DEFAULTFOREGROUND VGA_COLOR_LIGHT_GREY
#define TERM_DEFAULTBACKGROUND VGA_COLOR_BLACK
/* Width/height for LineRenderer terminal */
#define TERM_WIDTH 80
#define TERM_HEIGHT 25

/* Enable PCI IDE controller? */
#define ide

/* Enable GPT partition table? */
#define gpt

/* Enable VGA console? */
#define vga_console

/* Define for keyboard support */
#define ps2_keyboard

/* Define for cursor in the console */
#define console_cursor

/* Enable serial? */
#define serial_console

#endif

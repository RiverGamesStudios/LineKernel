#include "panic.h"

#define STANDARD_ERROR_ART 3
#ifdef ARCH_riscv64
#define ARCH_ERROR_ART 1
#else
#define ARCH_ERROR_ART 0
#endif

#define ERROR_ART STANDARD_ERROR_ART + ARCH_ERROR_ART

char* error_art[ERROR_ART] = {
/* https://www.asciiart.eu/art/3f48d10c283c85d8 */
		"   +--------------+\n"
		"   |.------------.|\n"
		"   ||   Panic!   ||\n"
		"   ||   in the   ||\n"
		"   ||   Kernel   ||\n"
		"   ||            ||\n"
		"   |+------------+|\n"
		"   +-..--------..-+\n"
		"   .--------------.\n"
		"  / /============\\ \\\n"
		" / /==============\\ \\\n"
		"/____________________\\\n"
		"\\____________________/\n",

/* https://www.asciiart.eu/art/a5b14e0367b64925 */
		"BBBBBBBBBBBBBBBBBBBBBBBBBBB\n"
		"BMB-River Games---------B B\n"
		"BBB---------------------BBB\n"
		"BBB-----LineCoreOS------BBB\n"
		"BBB---------------------BBB\n"
		"BBB--------installation-BBB\n"
		"BBB----------disk #1/3--BBB\n"
		"BBBBBBBBBBBBBBBBBBBBBBBBBBB\n"
		"BBBBB++++++++++++++++BBBBBB\n"
		"BBBBB++BBBBB+++++++++BBBBBB\n"
		"BBBBB++BBBBB+++++++++BBBBBB\n"
		"BBBBB++BBBBB+++++++++BBBBBB\n"
		"BBBBB++++++++++++++++BBBBBB\n",

/* https://www.asciiart.eu/art/37bc7fd33d1e26f6 */
		" ______________\n"
		"||            ||\n"
		"||            ||\n"
		"||            ||\n"
		"||            ||\n"
		"||____________||\n"
		"|______________|\n"
		" \\\\############\\\\\n"
		"  \\\\############\\\\\n"
		"   \\      ____    \\   \n"
		"    \\_____\\___\\____\\\n"

#ifdef ARCH_riscv64
,
		" ____________________________\n"
		"< This seems kinda RISC-y... >\n"
		" ----------------------------\n"
		"        \\   ^__^\n"
		"         \\  (oo)\\_______\n"
		"            (__)\\       )\\/\\\n"
		"                ||----w |\n"
		"                ||     ||\n"
#endif
};

char* random_error_message(void)
{
	int fake_rand = rand();

	if (fake_rand) {
		return error_art[fake_rand % ERROR_ART];
	} else {
		return "\n";
	}
}

void panic(const char* format, ...)
{
	terminal_writestring(random_error_message());
	terminal_writestring("KERNEL PANIC!\n");
	terminal_writestring("Reason:\n");
	va_list arg;
	va_start(arg, format);
	vprintf(format, arg);
	va_end(arg);
	halt();
}

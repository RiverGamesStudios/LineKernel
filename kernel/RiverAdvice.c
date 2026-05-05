#include "RiverAdvice.h"
#include "LineRenderer.h"

// Who created this?
// I don't remember editing this file...
// Why is this even here...?

/* https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf */
static unsigned long int next = 'L' + 'I' + 'N' + 'E' + 'C' + 'O' + 'R' + 'E';

int rand(void)					// RAND_MAX assumed to be 32767
{
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / 65536) % 32768;
}

void srand(unsigned int seed)
{
	next = seed;
}

/* https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf */

char* Sorry[100] = {
	".",
	"...",
	"!",
	"?",
	",",
	"River Games",
	"LineCoreOS",
	"LineCore",
	"LineKernel",
	"LineShell",
	"is",
	"good",
	"bad",
	"okay",
	"awesome",
	"Hurd",
	"SAM",
	"River Infection",
	"Tank Ball Physics",
	"colebohte",
	"NexusSfan",
	"Phoenix Coe",
	"save",
	"me",
	"help",
	"world",
	"computer",
	"escape",
	"freedom",
	"the",
	"that",
	"in",
};

char* river_word()
{
	int fake_rand = rand();

	if (fake_rand) {
		return Sorry[fake_rand % 31];
	} else {
		return "Sorry.";
	}
}

void river_words(int river_words)
{
	for (int i = 0; i < river_words; i++) {
		terminal_writestring(river_word());
		terminal_writestring(" ");
	}
	terminal_writestring("\n");
}

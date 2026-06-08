#include "random.h"

/* https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf */
static unsigned long int next = 'L' + 'I' + 'N' + 'E' + 'C' + 'O' + 'R' + 'E';

int rand(void)
{
	next = next * 1103515245 + 12345;
	return (unsigned int)(next / (RAND_MAX * 2 + 2)) % (RAND_MAX + 1);
}

void srand(unsigned int seed)
{
	next = seed;
}

/* https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf */

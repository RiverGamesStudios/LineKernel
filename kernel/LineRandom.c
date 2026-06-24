#include "LineRandom.h"
#include "printf.h"

/* TODO: Move RDSEED and RDRAND to a different file. It works here, but we should move it later. */

/* Obviously none of this is designed for security */

#ifdef CONFIG_RDSEED
int check_rdseed(void)
{
	uint32_t eax, ebx, ecx, edx;

	eax = 7;
	ecx = 0;

    __asm__ volatile (
        "pushl %%ebx\n\t"   
        "cpuid\n\t"
        "movl %%ebx, %1\n\t"
        "popl %%ebx"        
        : "=a"(eax), "=r"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(7), "c"(0)
    );

	if (ebx & (1 << 18)) {
		return 1;
	} else {
		return 0;
	}
}

rand_t rand_rdseed(void)
{
	rand_t seed_out;
	uint8_t ok;

	__asm__ volatile (
		"rdseed %0; setc %1"
		: "=r"(seed_out), "=qm"(ok)
		:
		: "cc"
	);

	/* CVE-2025-62626 */
	if (ok == 1 && seed_out != 0) {
		return seed_out % RAND_MAX;
	} else {
		return 0;
	}
}
#endif

#ifdef CONFIG_RDRAND
int check_rdrand(void)
{
	uint32_t eax, ebx, ecx, edx;

	eax = 1;
	ecx = 0;

    __asm__ volatile (
        "pushl %%ebx\n\t"
        "cpuid\n\t"
        "movl %%ebx, %1\n\t"
        "popl %%ebx"
        : "=a"(eax), "=r"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(1), "c"(0)
    );

	if (ebx & (1 << 30)) {
		return 1;
	} else {
		return 0;
	}
}

rand_t rand_rdrand(void)
{
	rand_t seed_out;
	uint8_t ok;

	__asm__ volatile (
		"rdseed %0; setc %1"
		: "=r"(seed_out), "=qm"(ok)
		:
		: "cc"
	);

	if (ok == 1) {
		return seed_out % RAND_MAX;
	} else {
		return 0;
	}
}
#endif

/* https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf */
static unsigned long int next = 'L' + 'I' + 'N' + 'E' + 'C' + 'O' + 'R' + 'E';

rand_t rand_crand(void)
{
	next = next * 1103515245 + 12345;
	return (rand_t)(next / (RAND_MAX * 2 + 2)) % (RAND_MAX + 1);
}
/* https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf */

randtype_t get_rand_type(void)
{
#ifdef CONFIG_RDSEED
	if (check_rdseed()) return RAND_RDSEED;
#endif
#ifdef CONFIG_RDRAND
	if (check_rdrand()) return RAND_RDRAND;
#endif
	return RAND_CRAND;
}

int rand(void)
{
	switch (get_rand_type()) {
#ifdef CONFIG_RDSEED
		case RAND_RDSEED:
			return rand_rdseed();
#endif
#ifdef CONFIG_RDRAND
		case RAND_RDRAND:
			return rand_rdrand();
#endif
		case RAND_CRAND:
			return rand_crand();
		default:
			return 0;
		}
}

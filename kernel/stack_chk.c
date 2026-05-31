#include <stdint.h>
#include "panic.h"

#if UINT32_MAX == UINTPTR_MAX
#define STACK_CHK_GUARD 0xc3859a69
#else
#define STACK_CHK_GUARD 0xba2637b8b1a55f4e
#endif


uintptr_t __stack_chk_guard = STACK_CHK_GUARD;

__attribute__((noreturn))
void __stack_chk_fail(void)
{
	panic("Stack smashing detected");
}

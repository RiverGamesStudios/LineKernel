#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include <stdint.h>

#define SYS_print1 0
#define SYS_print2 1

int sys_print1(void);
int sys_print2(uintptr_t read);

#ifdef ARCH_i386
static inline long syscall3(long num, long arg1, long arg2, long arg3)
{
	long ret;
	__asm__ volatile (
		"int $0x80"
		: "=a"(ret)
		: "a"(num), "b"(arg1), "c"(arg2), "d"(arg3)
		: "memory"
	);
	return ret;
}
#else
#error "Doesn't support syscalls!"
#endif

#endif

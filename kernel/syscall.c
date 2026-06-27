#include "syscall.h"
#include "LineRenderer.h"

typedef int (*syscall_t)(long, long, long, long, long, long);

int sys_print1(void)
{
	terminal_writestring("Line!\n");
	return 0;
}

int sys_print2(uintptr_t read)
{
	terminal_writestring((char*)read);
	return 0;
}

void* syscall_table[] = {
	[SYS_print1] = sys_print1,
	[SYS_print2] = sys_print2,
};

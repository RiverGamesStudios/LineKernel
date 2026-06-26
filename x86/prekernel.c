#include "prekernel.h"

void multiboot_pre_main(uint32_t magic, multiboot_info_t* mbi)
{
	char* cmdline_str_;

	if (magic != 0x2BADB002)
		return;

	if (mbi->flags & (1 << 2)) {
		cmdline_str_ = (char *)(uintptr_t) mbi->cmdline;
		strlcpy(cmdline_str, cmdline_str_, strlen(cmdline_str_) + 1);
		parse_cmdline(cmdline_str_);
	}

	kernel_main();
}

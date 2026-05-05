#if defined(__linux__) || defined(__GNU__)
#error "Not cross-compiling!!!"
#endif

#if !defined(__i386__) && defined(ARCH_i386)
#error "Only compiles for i386!!!"
#endif

#include "config.h"

#if !defined(ARCH_i386)
#if defined(ide) || defined(vga_console)
#error "IDE, VGA console is not supported on non-i386 modes!!!"
#endif
#endif

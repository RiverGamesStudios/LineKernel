#ifndef __LINERANDOM_H__
#define __LINERANDOM_H__

#include "kconfig.h"
#include <stdint.h>

/* I'll have to figure out a way to do this with uint64_t. */
#define RAND_MAX UINT16_MAX
typedef uint32_t rand_t;

rand_t rand_crand(void);

int rand(void);

typedef enum {
    RAND_CRAND,
} randtype_t;

randtype_t get_rand_type(void);

#endif

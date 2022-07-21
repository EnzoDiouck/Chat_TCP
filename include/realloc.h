#ifndef __REALLOC_H__
#define __REALLOC_H__

#include "memcpy.h"
#include <stdlib.h>

void *std_realloc(void *ptr, size_t original_size, size_t new_size);

#endif /* __REALLOC_H__ */

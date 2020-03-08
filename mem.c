#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mem.h"


void mem_icopy(void **data, void *buf, size_t size)
{
    memcpy(*data, buf, size);
    *data += size;
}
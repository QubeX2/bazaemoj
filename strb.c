#include "strb.h"

void strb_init(struct strb *sb, size_t alloc)
{
    sb->alloc = sb->len = 0;
    sb->bud = NULL;

}

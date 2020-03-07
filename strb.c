#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "strb.h"
#include "memory.h"

char strb_slopbuf[1] = { '\0' };

void strb_init(struct strb *sb, size_t alloc)
{
    sb->alloc = sb->len = 0;
    sb->buf = strb_slopbuf;
    if(alloc)
        strb_grow(sb, alloc);

}

void strb_grow(struct strb *sb, size_t amount)
{
    if(!sb->alloc) {
        MALLOC(sb->buf, amount);
        sb->alloc = amount;
    } else if(sb->alloc + amount > 0) {
        REALLOC(sb->buf, sb->alloc + amount);
        sb->buf[sb->alloc + amount] = '\0';
        sb->alloc += amount;
    }
}

void strb_free(struct strb *sb)
{
    if(sb->alloc) { 
        free(sb->buf);
        strb_init(sb, 0);
    }
}

void strb_set(struct strb *sb, char *data)
{
    if(sb->alloc < strlen(data) + 1) {
        strb_grow(sb, strlen(data) + 1);
    }
    memcpy(sb->buf, data, strlen(data));
    sb->len = strlen(data) + 1;
    sb->buf[sb->len - 1] = '\0';
}

void strb_dump(struct strb *sb)
{
    printf("strb->alloc = %zu\nstrb->len = %zu\nstrb->buf = \"%s\"\n\n", sb->alloc, sb->len, sb->buf);
}

void strb_trim(struct strb *sb)
{
    strb_rtrim(sb);
    strb_ltrim(sb);
}

void strb_rtrim(struct strb *sb)
{
    while(sb->len > 0 && isspace((unsigned char)sb->buf[sb->len - 1]))
        sb->len--;
    sb->buf[sb->len] = '\0';
}

void strb_ltrim(struct strb *sb)
{
    char *b = sb->buf;
    while(sb->len > 0 && isspace(*b)) {
        b++;
        sb->len--;
    }
    memmove(sb->buf, b, sb->len);
    sb->buf[sb->len] = '\0';
}



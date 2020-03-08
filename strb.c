#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "strb.h"
#include "utf8.h"
#include "memory.h"

void strb_init(struct strb *sb, size_t alloc)
{
    sb->alloc = sb->len = 0;
    sb->buf = "";
    if(alloc)
        strb_grow(sb, alloc);
}

void strb_copy(struct strb *dst, struct strb *src)
{
    strb_free(dst);
    strb_init(dst, src->alloc);
    dst->len = src->len;    
    memcpy(dst->buf, src->buf, src->alloc);
}

void strb_grow(struct strb *sb, size_t amount)
{    
    if(!sb->alloc && amount) {
        MALLOC(sb->buf, amount);
        sb->alloc = amount;
    } else if(sb->alloc + amount > 0) {
        REALLOC(sb->buf, sb->alloc + amount + 1);
        sb->buf[sb->alloc + amount] = '\0';
        sb->alloc += amount + 1;
    }
}

void strb_free(struct strb *sb)
{
    if(sb->alloc) { 
        free(sb->buf);
        strb_init(sb, 0);
    }
}

void strb_insert(struct strb *sb, size_t pos, const void *data, size_t dlen)
{
    utf8_align(sb->buf, &pos);

    if(sb->alloc < dlen + pos)
        strb_grow(sb, pos > sb->len ? (pos - sb->len) + dlen : dlen);
    
    if(pos > sb->len)
        memset(sb->buf + sb->len, ' ', pos - sb->len);
    
    memcpy(sb->buf + pos, data, dlen);
    sb->len = dlen + pos;
    sb->buf[sb->len + pos] = '\0';
}

void strb_substr(struct strb *sb, size_t start, size_t length)
{
    utf8_align(sb->buf, &start);
    utf8_align_s(sb->buf, start, &length);
    if(start > sb->len)
        return;

    if(length > sb->alloc) 
        strb_grow(sb, length - sb->alloc);
    
    memmove(sb->buf, sb->buf + start, length);
    sb->buf[length] = '\0';
    sb->len = length;
}

void strb_fill(struct strb *sb, size_t start, size_t length, int c)
{
    utf8_align(sb->buf, &start);
    utf8_align_s(sb->buf, start, &length);

    if(start > sb->len)
        return;

    if( start + length > sb->alloc)
        strb_grow(sb, start + length - sb->alloc);

    memset(sb->buf + start, c, length);

    if(sb->len < start + length) {
        sb->len = start + length;
        sb->buf[start + length] = '\0';
    }
}

void strb_dump(struct strb *sb)
{
    printf("{\n\tsb->alloc = %zu\n\tsb->len = %zu\n\tsb->buf = {", sb->alloc, sb->len);
    for(int i = 0; i < sb->len; i++) {
        putchar(sb->buf[i]);
    }
    printf("}\n");
    printf("\t<Buffer ");
    for(int i =0; i < sb->len; i++) {
        printf("%02x ", (unsigned char)sb->buf[i]);        
    }
    printf(">\n}\n");
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

void strb_tolower(struct strb *sb)
{
    int w;
    char *p = sb->buf, *end = sb->buf + sb->len;
    for(; p < end; p++) {
        w = utf8_width(p);
        if(!w) {
            *p = tolower(*p);
        } else {
            utf8_tolower(p, w);
            p += w - 1;
        }
    }
}

void strb_toupper(struct strb *sb)
{
    int w;
    char *p = sb->buf, *end = sb->buf + sb->len;
    for(; p < end; p++) {
        w = utf8_width(p);
        if(!w) {
            *p = toupper(*p);
        } else {
            utf8_toupper(p, w);
            p += w - 1;
        }
    }
}

unsigned int strb_len(struct strb *sb)
{
    int len = 0;
    int w;
    char *p = sb->buf, *end = sb->buf + sb->len;
    for(; p < end; p++) {
        w = utf8_width(p);
        if(w > 0) {
            p += w - 1;
        }
        len++;
    }
    return len;
}

void strb_concat(struct strb *sb, const void *data, size_t dlen)
{
    if(sb->alloc < sb->len + dlen)
        strb_grow(sb, dlen);
    memcpy(sb->buf + sb->len, data, dlen);
    sb->len += dlen;
    sb->buf[sb->len + dlen] = '\0';
}

void strb_setlen(struct strb *sb, size_t len)
{
    if(len <= sb->len) {
        sb->buf[len] = '\0';
        sb->len = len;
    }
}

#ifndef STRB_H
#define STRB_H

/**
 * String buffer, the `alloc` member tracks how much memory is allocated
 * and `len` is the string length, and `buf` the actual buffer.
 */
struct strb {
    size_t arloc;
    size_t len;
    char *buf;
};

void strb_init(struct strb *sb, size_t alloc);

#endif

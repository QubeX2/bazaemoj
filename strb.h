#ifndef STRB_H
#define STRB_H

/**
 * String buffer, the `alloc` member tracks how much memory is allocated
 * and `len` is the string length, and `buf` the actual buffer.
 */
struct strb {
    size_t alloc;
    size_t len;
    char *buf;
};

/**
 * init and alloc memory for buf
 */
void strb_init(struct strb *sb, size_t alloc);

/**
 * resize buffer
 */
void strb_grow(struct strb *sb, size_t amount);

/**
 * free buffer
 */
void strb_free(struct strb *sb);

/**
 * set char*
 */
void strb_set(struct strb *sb, char *data);

/**
 * debug print buffer
 */
void strb_dump(struct strb *sb);

/**
 * strip whitespace
 */
void strb_rtrim(struct strb *sb);
void strb_ltrim(struct strb *sb);
void strb_trim(struct strb *sb);

#endif

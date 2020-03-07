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
 * copy
 */
void strb_copy(struct strb *dst, struct strb *src);

/**
 * free buffer
 */
void strb_free(struct strb *sb);

/**
 * set char*
 */
#define strb_set(sb, data, dlen)    strb_insert(sb, 0, data, dlen)
void strb_insert(struct strb *sb, size_t pos, const void *data, size_t dlen);

/**
 * substr(sb, start, length)
 */
void strb_substr(struct strb *sb, size_t start, size_t length);

/**
 * 
 */
void strb_fill(struct strb *sb, size_t start, size_t length, int c);

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

/**
 * tolower
 */
void strb_tolower(struct strb *sb);

/**
 * length
 */
unsigned int strb_len(struct strb *sb);

/**
 * concat
 */
void strb_concat(struct strb *sb, const void *data, size_t dlen);

#endif

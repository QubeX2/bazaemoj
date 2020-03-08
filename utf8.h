#ifndef UTF8_H_I
#define UTF8_H_I

#define U_LEN_K 18

/**
 * gets the width of an utf8 character in sizeof(char)
 */

unsigned int utf8_width(char *s);

/*
 *
 */
#define utf8_align(s, pos)   utf8_align_s(s, 0, pos)
void utf8_align_s(char *s, size_t start, size_t *pos);

/**
 * small implementation of upper and lower case of utf8 chars
 */
void utf8_tolower(char *s, unsigned int width);
void utf8_toupper(char *s, unsigned int width);

#endif
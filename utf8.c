#include <string.h>
#include "utf8.h"

unsigned int utf8_width(char *s)
{
    int width = 0;
    int is_start = 0;
    char *p = s, *end = s + (unsigned long)strlen(s);
    for(; p < end; p++) {
        if(!is_start && (unsigned char)*p >= 0xC2 && (unsigned char)*p <= 0xDF) {
            width++;
            is_start = 1;
        } else if(is_start && (unsigned char)*p >= 0x80 && (unsigned char)*p <= 0xBF) {
            width++;
        } else if(is_start) {
            return width;
        } else {
            return width;
        }
    }
    return width;
}

void utf8_tolower(char *s, unsigned int width)
{
    const int LEN = 4;
    char *fc[LEN] = { "Å", "Ä", "Ö", "Ü" };
    char *rc[LEN] = { "å", "ä", "ö", "ü" };

    for(int i = 0; i<LEN; i++) {
        if(!memcmp(s, fc[i], width)) {
            memcpy(s, rc[i], strlen(rc[i]));
            return;
        }
    }

}
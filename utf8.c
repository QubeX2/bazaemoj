#include <string.h>
#include <stdio.h>
#include "utf8.h"

void utf8_align_s(char *s, size_t start, size_t *pos) {
    if(start == 0 && *pos == 0)
        return;

    int w = 0;
    size_t k = 0;
    size_t c = *pos;
    char *p = s + start, *end = s + (unsigned long)strlen(s);
    for(; p < end; p++) {
        w = utf8_width(p);
        if(w) {
            *pos += w - 1;
            p += w - 1;
        }   
        k++;
        if(c == k) {
            return;
        }
    }
}


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

static char *UC[U_LEN_K] = { 
    "Å", "Ä", "Ö", "Ü", "É", "È", "Ó", "Ò", "Á", "À", 
    "Ú", "Ù", "Ÿ", "Ï", "Ë", "Ý", "Í", "Ì"
};
static char *LC[U_LEN_K] = { 
    "å", "ä", "ö", "ü", "é", "È", "ó", "ò", "á", "à", 
    "ú", "ù", "ÿ", "ï", "ë", "ý", "í", "ì"
};

void utf8_tolower(char *s, unsigned int width)
{
    for(int i = 0; i < U_LEN_K; i++) {
        if(!memcmp(s, UC[i], width)) {
            memcpy(s, LC[i], utf8_width(LC[i]));
            return;
        }
    }
}

void utf8_toupper(char *s, unsigned int width)
{
    for(int i = 0; i < U_LEN_K; i++) {
        if(!memcmp(s, LC[i], width)) {
            memcpy(s, UC[i], utf8_width(UC[i]));
            return;
        }
    }
}
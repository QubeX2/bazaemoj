#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strb.h"


int main(int argc, char **argv)
{
    struct strb b;
    struct strb c;

    char *name = "ABBA";
    char *name2 = "LILLA";

    strb_init(&b, 0); 
    strb_set(&b, name, strlen(name));
    strb_concat(&b, name2, strlen(name2));
    strb_dump(&b);
    strb_substr(&b, 2, 4);
    strb_dump(&b);
    strb_fill(&b, 2, 14, '-');
    strb_dump(&b);

    strb_copy(&c, &b);
    strb_dump(&c);


    return 0;
}

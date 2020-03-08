#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strb.h"


int main(int argc, char **argv)
{
    struct strb b;

    char *name = "ABBÖ";
    char *name2 = "M";

    strb_init(&b, 0); 
    strb_set(&b, name, strlen(name));
    strb_insert(&b, 4, name2, strlen(name2));
    strb_dump(&b);
    strb_substr(&b, 0, 4);
    strb_dump(&b);

    return 0;
}

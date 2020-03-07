#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strb.h"

int main(int argc, char **argv)
{
    struct strb b;
    strb_init(&b, 0); 
    strb_set(&b, "ABBA      ");
    strb_dump(&b);
    strb_rtrim(&b);
    strb_dump(&b);
    strb_free(&b);

    return 0;
}

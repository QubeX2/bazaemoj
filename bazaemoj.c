#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strb.h"
#include "emoj.h"

int main(int argc, char **argv)
{
    struct emoj em;

    emoj_init(&em);
    emoj_dump(&em);

    return 0;
}

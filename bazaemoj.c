#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "err.h"
#include "baza.h"
#include "mem.h"

int main(int argc, char **argv)
{
    if(argc == 2 && !strcmp(argv[1], "shell")) {
        shell_run();
    }
    return 0;
}

#include <stdio.h>
#include <string.h>
#include "shell.h"
#include "err.h"

int main(int argc, char **argv)
{
    if(argc == 2 && !strcmp(argv[1], "shell")) {
        shell_run();
    }
    shell_cmd_lss();
    return 0;
}

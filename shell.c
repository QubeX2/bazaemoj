#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "emoj.h"
#include "shell.h"
#include "baza.h"
#include "mem.h"

void shell_run()
{
    char cmd[512];
    for(;;) {
        printf("Enter CMD: ");
        shell_get_console(cmd);

        if(!strcmp(cmd, "quit") || !strcmp(cmd, "exit") || !strcmp(cmd, "x") || !strcmp(cmd, "q")) {
            break;
        } else if (!strcmp(cmd, "adds")) {
            shell_cmd_adds();
        } else if (!strcmp(cmd, "lss")) {
            shell_cmd_lss();
        }
    }
    printf("Exiting shell.\n");
}

void shell_get_console(char *line) 
{
    char ch;
    int i = 0;
    while( (ch = getchar()) != '\n')
        line[i++] = ch;
    line[i] = '\0';
}

void shell_cmd_lss()
{
    size_t size = 0;
    size_t pos = 0;
    struct emoj_tag *et;
    void *data;
    while( (data = baza_read_obj("./tags.emoj", pos, &size)) != NULL ) {
        et = baza_et_make(data);
        printf("ID: %d, TYPE: %s, NAME: %s\n", et->id, et->name, et->type == 1 ? "sense" : "event");
        FREE(data);
        FREE(et);
        pos += size;
    }
}

void shell_cmd_adds()
{
    char name[80];
    char desc[80];
    char signt[80];
    int sign = 0;
    printf("\nAdd Emotion\n");
    printf("Name:> ");
    shell_get_console(name);
    printf("Description:> ");
    shell_get_console(desc);
    printf("Sign (+/-):> ");
    shell_get_console(signt);
    
    if(strlen(signt) > 0 && signt[0] == '+')
        sign = 1;
    else if(strlen(signt) > 0 && signt[0] == '-')
        sign = -1;

    struct emoj_tag tag;
    emoj_tag_init(&tag, TAG_TYPE_SENSE, name, desc, sign);

    size_t sz;
    void *data = baza_et_data(&tag, &sz);
    baza_write_obj("./tags.emoj", data, sz);
    FREE(data);
}

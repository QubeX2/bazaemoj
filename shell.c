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
        } else if (!strcmp(cmd, "addt")) {
            shell_cmd_addt();
        } else if (!strcmp(cmd, "lst")) {
            shell_cmd_lst();
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

void shell_cmd_lst()
{
    size_t size = 0;
    size_t pos = 0;
    void *data;
    struct emoj_tag *et = emoj_tag_new();
    while( (data = baza_obj_read("./tags.emoj", pos, &size)) != NULL ) {
        baza_et_load(et, data);
        printf("ID: %d, NAME: %s, TYPE: %s, SIGN: %c\n", et->id, et->name, et->type == 1 ? "sense" : "event", et->sign == 0 ? ' ' : (et->sign == 1 ? '+' : '-'));
        FREE(data);
        pos += size;
    }
    FREE(et);
}

void shell_cmd_addt()
{
    char name[80];
    char type[80];
    char sign[80];
    struct emoj_tag *et = emoj_tag_new();
    emoj_tag_init(et);    
    
    printf("\nAdd Tag\n");
    
    printf("Name:> ");
    shell_get_console(name);
    MALLOC(et->name, strlen(name) + 1);
    strcpy(et->name, name);

    printf("Type (s/e):> ");
    shell_get_console(type);
    et->type = strlen(type) == 0 ? 0 : (strlen(type) > 0 && type[0] == 'e' ? TAG_TYPE_EVENT : TAG_TYPE_SENSE);

    printf("Sign (+/-):> ");
    shell_get_console(sign);    
    et->sign = strlen(sign) == 0 ? 0 : (strlen(sign) > 0 && sign[0] == '-' ? -1 : 1);


    size_t sz;
    void *data = baza_et_data(et, &sz);
    baza_obj_write("./tags.emoj", data, sz);
    FREE(data);
    emoj_tag_free(et);
    FREE(et);
}

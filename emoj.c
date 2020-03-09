#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "emoj.h"
#include "strb.h"
#include "mem.h"
#include "baza.h"

void emoj_init(struct emoj *em) 
{
    time_t t;
    struct tm *tm;
    time(&t);
    tm = localtime(&t);
    em->id = 0;
    em->timestamp = t;
    sprintf(em->datetime, "%d-%02d-%02d %02d:%02d:%02d", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    em->desc = "";
    MALLOC(em->list, sizeof(struct emoj_sense));
}

void emoj_free(struct emoj *em)
{
    free(em->list);
}

void emoj_dump(struct emoj *em)
{
    printf("em->id = %d\n", em->id);
    printf("em->timestamp = %ld\n", em->timestamp);
    printf("em->datetime = %s\n", em->datetime);
    putchar('\n');
}

void emoj_tag_init(struct emoj_tag *et)
{
    struct baza_conf *bc = baza_conf_read();
    if(bc == NULL) {
        bc = baza_conf_new();
    }
    et->id = bc->next_tag_id++;
    baza_conf_write(bc);
    FREE(bc);
    et->type = 0;
    et->sign = 0;
}

struct emoj_tag *emoj_tag_new()
{
    struct emoj_tag *et;
    MALLOC(et, sizeof(struct emoj_tag));
    return et;
}


void emoj_tag_dump(struct emoj_tag *et)
{
    printf("et->id = %d\n", et->id);
    printf("et->type = %d\n", et->type);
    printf("et->name = %s\n", et->name);
    printf("et->sign = %d\n", et->sign);

}

void emoj_tag_free(struct emoj_tag *et)
{
    FREE(et->name);
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "emoj.h"
#include "strb.h"
#include "mem.h"

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
    MALLOC(em->strb, sizeof(struct strb));
    MALLOC(em->sense_list, sizeof(struct emoj_sens));
    MALLOC(em->event_list, sizeof(struct emoj_event));
    strb_init(em->strb, 0);
}

void emoj_free(struct emoj *em)
{
    strb_free(em->strb);
    free(em->sense_list);
    free(em->event_list);
}

void emoj_dump(struct emoj *em)
{
    printf("em->id = %d\n", em->id);
    printf("em->timestamp = %ld\n", em->timestamp);
    printf("em->datetime = %s\n", em->datetime);
    strb_dump(em->strb);
    putchar('\n');
}

void emoj_tag_init(struct emoj_tag *et, tag_type_t type, char *name, char *desc, int sign)
{
    MALLOC(et->name, strlen(name) + 1);
    strcpy(et->name, name);
    MALLOC(et->desc, strlen(desc) + 1);
    strcpy(et->desc, desc);
    et->type = type;
    et->sign = sign;
}

void emoj_tag_dump(struct emoj_tag *et)
{
    printf("et->id = %d\n", et->id);
    printf("et->type = %d\n", et->type);
    printf("et->name = %s\n", et->name);
    printf("et->desc = %s\n", et->desc);
    printf("et->sign = %d\n", et->sign);

}
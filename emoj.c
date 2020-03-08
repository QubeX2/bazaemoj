#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "emoj.h"
#include "strb.h"
#include "memory.h"

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

void emoj_dump(struct emoj *em)
{
    printf("em->id = %d\n", em->id);
    printf("em->timestamp = %ld\n", em->timestamp);
    printf("em->datetime = %s\n", em->datetime);
    strb_dump(em->strb);
    putchar('\n');
}

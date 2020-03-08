#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "baza.h"
#include "emoj.h"
#include "mem.h"
#include "err.h"

void baza_write(char *file, void *data, size_t size)
{
    FILE *fp;

    if ( (fp = fopen(file, "ab")) == NULL ) {
        err("Error: cant open file sense.emojt")
        return;
    }
    fwrite(data, size, 1, fp);
    fclose(fp);
}

void *baza_rec_emoj_tag(struct emoj_tag *et, size_t *out) 
{
    void *data;
    size_t size = (sizeof(size_t) * 3) + sizeof(unsigned int) + sizeof(tag_type_t) + sizeof(int) + strlen(et->name) + 1 + strlen(et->desc) + 1;
    MALLOC(data, size);
    void *pd = data;
    *out = size;

    size_t nl = strlen(et->name) + 1;
    size_t dl = strlen(et->desc) + 1;

    mem_icopy(&data, &size, sizeof(size_t));
    mem_icopy(&data, &et->id, sizeof(unsigned int));
    mem_icopy(&data, &et->type, sizeof(tag_type_t));
    mem_icopy(&data, &et->sign, sizeof(int));
    mem_icopy(&data, &nl, sizeof(size_t));
    mem_icopy(&data, et->name, nl);
    mem_icopy(&data, &dl, sizeof(size_t));
    mem_icopy(&data, et->desc, dl);

    return pd;
}

void baza_dump(void *data, size_t size)
{
    printf("<Buffer (%ld) ", size);
    for(int i = 0;i < size; i++) {
        printf("%02x ", ((unsigned char*)data)[i]);        
    }
    printf(">\n\n");
}
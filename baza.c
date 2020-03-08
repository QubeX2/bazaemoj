#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "baza.h"
#include "emoj.h"
#include "mem.h"
#include "err.h"

void baza_write_obj(char *file, void *data, size_t size)
{
    FILE *fp;

    if ( (fp = fopen(file, "ab")) == NULL ) {
        printf("Error: can't open file %s\n", file);
        return;
    }
    fwrite(data, size, 1, fp);
    fclose(fp);
}

void *baza_read_obj(char *file, size_t pos, size_t *out)
{
    FILE *fp;
    size_t size;

    if ( (fp = fopen(file, "rb")) == NULL ) {
        printf("Error: can't open file %s\n", file);
        return NULL;
    }
    fseek(fp, pos, SEEK_SET);
    fread(&size, sizeof(size_t), 1, fp);
    *out = size;
    fseek(fp, pos, SEEK_SET);
    void *data;
    MALLOC(data, size);
    fread(data, size, 1, fp);
    fclose(fp);
    return data;
}

struct emoj_tag *baza_et_make(void *data)
{
    size_t size;
    int nl, dl;
    memcpy(&size, data, sizeof(size_t));
    struct emoj_tag *et;
    MALLOC(et, sizeof(struct emoj_tag));
    data += sizeof(size_t);
    mem_iscopy(&et->id, &data, sizeof(unsigned int));
    mem_iscopy(&et->type, &data, sizeof(tag_type_t));
    mem_iscopy(&et->sign, &data, sizeof(int));
    mem_iscopy(&nl, &data, sizeof(size_t));
    MALLOC(et->name, nl);
    mem_iscopy(et->name, &data, nl);
    mem_iscopy(&dl, &data, sizeof(size_t));
    MALLOC(et->desc, dl);
    mem_iscopy(et->desc, &data, dl);
    return et;
}

void *baza_et_data(struct emoj_tag *et, size_t *out) 
{
    void *data;
    size_t size = (sizeof(size_t) * 3) + sizeof(unsigned int) + sizeof(tag_type_t) + sizeof(int) + strlen(et->name) + 1 + strlen(et->desc) + 1;
    MALLOC(data, size);
    void *pd = data;
    *out = size;

    size_t nl = strlen(et->name) + 1;
    size_t dl = strlen(et->desc) + 1;

    mem_idcopy(&data, &size, sizeof(size_t));
    mem_idcopy(&data, &et->id, sizeof(unsigned int));
    mem_idcopy(&data, &et->type, sizeof(tag_type_t));
    mem_idcopy(&data, &et->sign, sizeof(int));
    mem_idcopy(&data, &nl, sizeof(size_t));
    mem_idcopy(&data, et->name, nl);
    mem_idcopy(&data, &dl, sizeof(size_t));
    mem_idcopy(&data, et->desc, dl);

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "baza.h"
#include "emoj.h"
#include "mem.h"
#include "err.h"

void baza_conf_write(struct baza_conf *bc)
{
    FILE *fp;

    if( (fp = fopen("./conf.emjd", "wb")) == NULL ) {
        printf("Error: can't open file conf.emoj\n");
        return;
    }
    fwrite(bc, sizeof(struct baza_conf), 1, fp);
    fclose(fp);
}

struct baza_conf *baza_conf_read()
{
    FILE *fp;
    if( (fp = fopen("./conf.emjd", "rb")) == NULL ) {
        return NULL;
    }

    struct baza_conf *bc = baza_conf_new();
    fread(bc, sizeof(struct baza_conf), 1, fp);
    fclose(fp);
    return bc;
}

struct baza_conf *baza_conf_new()
{
    struct baza_conf *bc;
    MALLOC(bc, sizeof(struct baza_conf));
    bc->next_tag_id = 1;
    bc->next_sense_id = 1;
    bc->next_emoj_id = 1;
    return bc;
}


void baza_obj_write(char *file, void *data, size_t size)
{
    FILE *fp;

    if ( (fp = fopen(file, "ab")) == NULL ) {
        printf("Error: can't open file %s\n", file);
        return;
    }
    fwrite(data, size, 1, fp);
    fclose(fp);
}

void *baza_obj_read(char *file, size_t pos, size_t *out)
{
    FILE *fp;
    size_t size;

    if ( (fp = fopen(file, "rb")) == NULL ) {
        printf("Error: can't open file %s\n", file);
        return NULL;
    }
    fseek(fp, 0L, SEEK_END);
    if(pos >= ftell(fp)) 
        return NULL;

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

void baza_et_load(struct emoj_tag *et, void *data)
{
    size_t size;
    int nl;
    memcpy(&size, data, sizeof(size_t));
    data += sizeof(size_t);
    mem_iscopy(&et->id, &data, sizeof(unsigned int));
    mem_iscopy(&et->type, &data, sizeof(tag_type_t));
    mem_iscopy(&et->sign, &data, sizeof(int));
    mem_iscopy(&nl, &data, sizeof(size_t));
    MALLOC(et->name, nl);
    mem_iscopy(et->name, &data, nl);
}

void *baza_et_data(struct emoj_tag *et, size_t *out) 
{
    void *data;
    size_t size = (sizeof(size_t) * 3) + sizeof(unsigned int) + sizeof(tag_type_t) + sizeof(int) + strlen(et->name) + 1;
    MALLOC(data, size);
    void *pd = data;
    *out = size;

    size_t nl = strlen(et->name) + 1;

    mem_idcopy(&data, &size, sizeof(size_t));
    mem_idcopy(&data, &et->id, sizeof(unsigned int));
    mem_idcopy(&data, &et->type, sizeof(tag_type_t));
    mem_idcopy(&data, &et->sign, sizeof(int));
    mem_idcopy(&data, &nl, sizeof(size_t));
    mem_idcopy(&data, et->name, nl);

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
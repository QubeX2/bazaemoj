#ifndef BAZA_H_I
#define BAZA_H_I

#include "emoj.h"

struct baza_conf {
    size_t next_tag_id;
    size_t next_sense_id;
    size_t next_emoj_id;
};

/**
 * object read and write
 */
void baza_obj_write(char *file, void *data, size_t size);
void *baza_obj_read(char *file, size_t pos, size_t *out_size);

/**
 * 
 */
void baza_idx_write(char *file, void *data, size_t size);
void *baza_idx_read(char *file);

/**
 * size_t: object
 * unsigned int: id
 * tag_type_t: type
 * int: sign
 * size_t: strlen(et->name) + 1
 * et->name + 1
 */
void *baza_et_data(struct emoj_tag *et, size_t *size);
void baza_et_load(struct emoj_tag *et, void *data);

/**
 * alloc memory for struct baza_conf
 */
struct baza_conf *baza_conf_new();

/**
 * write config
 */
void baza_conf_write(struct baza_conf *bc);

/**
 * read config allocates memory
 */
struct baza_conf *baza_conf_read();


/**
 * dump data
 */
void baza_dump(void *data, size_t size);

#endif
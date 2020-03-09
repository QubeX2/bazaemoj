#ifndef BAZA_H_I
#define BAZA_H_I

#include "emoj.h"

struct baza_conf {
    size_t next_tag_id;
    size_t next_sense_id;
    size_t next_emoj_id;
};


/**
 * 
 */
size_t baza_next_id();

/**
 * file handlin
 */
void baza_obj_write(char *file, void *data, size_t size);
void *baza_obj_read(char *file, size_t pos, size_t *out_size);

/**
 * size_t: object
 * unsigned int: id
 * tag_type_t: typeg
 * int: sign
 * size_t: strlen(et->name) + 1
 * et->name + 1
 * size_t: strlen(et->desc) + 1
 * et->desc + 1
 */
void *baza_et_data(struct emoj_tag *et, size_t *size);
void baza_et_load(struct emoj_tag *et, void *data);

/**
 * 
 */
struct baza_conf *baza_conf_new();

/**
 * 
 */
void baza_conf_write(struct baza_conf *bc);

/**
 * 
 */
struct baza_conf *baza_conf_read();


/**
 * 
 */
void baza_dump(void *data, size_t size);

#endif
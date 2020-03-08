#ifndef BAZA_H_I
#define BAZA_H_I

#include "emoj.h"

/**
 * 
 */
size_t baza_next_id();

/**
 * file handlin
 */
void baza_write_obj(char *file, void *data, size_t size);
void *baza_read_obj(char *file, size_t *out_size);

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
void *baza_rec_emoj_tag(struct emoj_tag *et, size_t *size);

/**
 * 
 */
void baza_dump(void *data, size_t size);

#endif
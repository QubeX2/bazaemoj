#ifndef EMOJ_H_I
#define EMOJ_H_I

#include <time.h>

typedef enum { TAG_TYPE_SENSE = 1, TAG_TYPE_EVENT = 2 } tag_type_t;

struct emoj_tag {
    unsigned int id;
    tag_type_t type; // 1 = sens, 2 = event
    int sign;       // 1 or -1 : positive or negative
    char *name;
};

struct emoj_sense {
    unsigned int tid;
    unsigned int val; // 1 - 5
    struct emoj_sense *first;
    struct emoj_sense *next;
};

struct emoj {
    unsigned int id;
    time_t timestamp;
    char datetime[20];          // date YYYY-MM-DD HH:MM:SS
    char *desc;
    struct emoj_sense *list;
};

/**
 * 
 */
void emoj_init(struct emoj *em);

/**
 * 
 */
void emoj_free(struct emoj *em);

/**
 * 
 */
void emoj_dump(struct emoj *em);

/**
 * 
 */
void emoj_tag_init(struct emoj_tag *et);

/**
 * 
 */
void emoj_tag_dump(struct emoj_tag *et);

/**
 * 
 */
struct emoj_tag *emoj_tag_new();

/**
 * 
 */
void emoj_tag_free(struct emoj_tag *et);

#endif
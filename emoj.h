#ifndef EMOJ_H_I
#define EMOJ_H_I

#include <time.h>

struct emoj_tag {
    unsigned int id;
    unsigned int type; // 1 = sens, 2 = event
    int sign;       // 1 or -1 : positive or negative
    char *name;
    char *desc;
};

struct emoj_sens {
    struct emoj_tag *tag;
    unsigned int val; // 1 - 5
    struct emoj_sens *first;
    struct emoj_sens *next;
};

struct emoj_event {
    struct emoj_tag *tag;
    struct emoj_event *first;
    struct emoj_event *next;
};

struct emoj {
    unsigned int id;
    time_t timestamp;
    char datetime[20];          // date YYYY-MM-DD HH:MM:SS
    char *desc;
    struct strb *strb;
    struct emoj_sens *sense_list;
    struct emoj_event *event_list;
};

/**
 * 
 */
void emoj_init(struct emoj *em);

/**
 * 
 */
void emoj_dump(struct emoj *em);

#endif
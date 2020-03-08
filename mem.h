#ifndef MEM_H_I
#define MEM_H_I

#include <stdlib.h>
#include <stdio.h>



#define ERROR_ALLOC_MESSAGE "Insufficient memory"

#define MALLOC(p, n) \
do \
{ \
  if ( !( (p) = malloc(sizeof(*(p)) * (n)) ) ) \
  { \
    fprintf(stderr, ERROR_ALLOC_MESSAGE); \
    exit(EXIT_FAILURE); \
  } \
} \
while(0)

#define CALLOC(p, n) \
do \
{ \
  if ( !( (p) = calloc((n), sizeof(*(p))) ) ) \
  { \
    fprintf(stderr, ERROR_ALLOC_MESSAGE); \
    exit(EXIT_FAILURE); \
  } \
} \
while(0)

#define REALLOC(p, n) \
do \
{ \
  if ( !( (p) = realloc((p), sizeof(*(p)) * (n)) ) ) \
  { \
    fprintf(stderr, ERROR_ALLOC_MESSAGE); \
    exit(EXIT_FAILURE); \
  } \
} \
while(0)

#define FREE(p) \
do \
{ \
  free(p); \
  p = NULL; \
} \
while(0)

/**
 * copies and increments either destination or source
 * hence _idcopy and _iscopy
 */
void mem_idcopy(void **data, void *buf, size_t size);
void mem_iscopy(void *data, void **buf, size_t size);

#endif
#ifndef DBUFF_H
#define DBUFF_H

#include <stdint.h>

#define DBUFF_EMPTY ((dbuff_t) {NULL, 0, 0})

typedef struct dbuff_t {
    void *buffer;
    size_t used;
    size_t capacity;
}
dbuff_t;

void dbuff_free(dbuff_t *dbuff);

void dbuff_

#endif
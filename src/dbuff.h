#ifndef DBUFF_H
#define DBUFF_H

#include <stdint.h>

// empty dbuff object.
#define DBUFF_EMPTY ((dbuff_t) {NULL, 0, 0})

/* dynamic buffer.
values should not be directly modified.*/
typedef struct dbuff_t {
    void *buffer;
    size_t capacity;
    size_t used;
}
dbuff_t;

// frees memory used by dbuff.
void dbuff_free(dbuff_t *dbuff);

// get the addres of the first free byte in 'dbuff'.
void *dbuff_get_top(const dbuff_t *dbuff);

/* reserves at least 'size' free bytes in 'dbuff'.
returns the same as 'dbuff_get_top' after reallocation.*/
void *dbuff_allocate(dbuff_t *dbuff, size_t size);

// removes unused space in 'dbuff'.
void dbuff_compact(dbuff_t *dbuff);

// appends 'size' bytes from 'item' onto 'dbuff', allocating space if necessary.
void dbuff_push(dbuff_t *dbuff, const void *item, size_t size);

/* removes 'size' bytes from 'dbuff', copies them to 'item' if not NULL.
does not reallocate.
does nothing if 'dbuff' holds less than 'size' bytes.*/
void dbuff_pop(dbuff_t *dbuff, void *item, size_t size);

#endif
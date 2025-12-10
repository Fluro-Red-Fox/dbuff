#ifndef DBUFF_H
#define DBUFF_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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

//

void dbuff_free(dbuff_t *dbuff) {
    free(dbuff->buffer);
    dbuff->buffer = NULL;
    dbuff->used = 0;
    dbuff->capacity = 0;
}

void *dbuff_get_top(const dbuff_t *dbuff) {
    return (uint8_t *) dbuff->buffer + dbuff->used;
}

void *dbuff_allocate(dbuff_t *dbuff, size_t size) {
    if (dbuff->capacity - dbuff->used < size) {
        dbuff->capacity = 1;
        while (dbuff->capacity < dbuff->used + size) {
            dbuff->capacity *= 2;
        }
        dbuff->buffer = realloc(dbuff->buffer, dbuff->capacity);
    }
    return dbuff_get_top(dbuff);
}

void dbuff_compact(dbuff_t *dbuff) {
    dbuff->buffer = realloc(dbuff->buffer, dbuff->used);
}

void dbuff_push(dbuff_t *dbuff, const void *item, size_t size) {
    memcpy(dbuff_allocate(dbuff, size), item, size);
    dbuff->used += size;
}

void dbuff_pop(dbuff_t *dbuff, void *item, size_t size) {
    if (size > dbuff->used) {
        return;
    }
    if (item) {
        memcpy(item, (uint8_t *) dbuff->buffer + dbuff->used - size, size);
    }
    dbuff->used -= size;
}

#endif
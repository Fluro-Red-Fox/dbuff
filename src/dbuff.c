#include <stdlib.h>
#include <string.h>

#include "dbuff.h"

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
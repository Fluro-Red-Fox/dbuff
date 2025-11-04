#include <stdlib.h>
#include <stdio.h>

#include "test.h"
#include "dbuff.h"

int main() {
    START_TEST
    {
        TEST_UNIT(DBUFF_EMPTY)
        dbuff_t dbuff = DBUFF_EMPTY;
        TEST(dbuff.buffer == NULL)
        TEST(dbuff.capacity == 0)
        TEST(dbuff.used == 0)
    } {
        TEST_UNIT(allocate then free)
        dbuff_t dbuff = DBUFF_EMPTY;
        void *result = dbuff_allocate(&dbuff, 10);
        TEST(dbuff.buffer != NULL)
        TEST(dbuff.buffer == result)
        TEST(dbuff.capacity == 16)
        TEST(dbuff.used == 0)
        void *prev_buffer = dbuff.buffer;
        result = dbuff_allocate(&dbuff, 50);
        TEST(dbuff.buffer != NULL)
        TEST(dbuff.buffer == result)
        TEST(dbuff.buffer != prev_buffer)
        TEST(dbuff.capacity == 64)
        TEST(dbuff.used == 0)
        dbuff_free(&dbuff);
        TEST(dbuff.buffer == NULL)
        TEST(dbuff.capacity == 0)
        TEST(dbuff.used == 0)
    } {
        TEST_UNIT(allocate then push)
        dbuff_t dbuff = DBUFF_EMPTY;
        int x = 123456;
        dbuff_allocate(&dbuff, sizeof(int));
        void *prev_buffer = dbuff.buffer;
        dbuff_push(&dbuff, &x, sizeof(int));
        TEST(dbuff.buffer != NULL)
        TEST(dbuff.buffer == prev_buffer)
        TEST(dbuff.capacity == sizeof(int))
        TEST(dbuff.used == sizeof(int))
        prev_buffer = dbuff.buffer;
        dbuff_push(&dbuff, &x, sizeof(int));
        TEST(dbuff.buffer != NULL)
        TEST(dbuff.buffer != prev_buffer)
        TEST(dbuff.capacity == sizeof(int) * 2)
        TEST(dbuff.used == sizeof(int) * 2)
        dbuff_free(&dbuff);
    }

    END_TEST
}
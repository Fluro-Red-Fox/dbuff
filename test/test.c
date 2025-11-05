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
        result = dbuff_allocate(&dbuff, 50);
        TEST(dbuff.buffer != NULL)
        TEST(dbuff.buffer == result)
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
        TEST(((int *) dbuff.buffer)[0] == x)
        dbuff_push(&dbuff, &x, sizeof(int));
        TEST(dbuff.buffer != NULL)
        TEST(dbuff.capacity == sizeof(int) * 2)
        TEST(dbuff.used == sizeof(int) * 2)
        TEST(((int *) dbuff.buffer)[0] == x)
        TEST(((int *) dbuff.buffer)[1] == x)
        dbuff_free(&dbuff);
    } {
        TEST_UNIT(push then pop)
        dbuff_t dbuff = DBUFF_EMPTY;
        int vals[] = {1, 2, 3, 4};
        dbuff_push(&dbuff, vals, sizeof(vals));
        TEST(dbuff.buffer != NULL)
        TEST(dbuff.capacity == sizeof(int) * 4)
        TEST(dbuff.used == sizeof(int) * 4)
        dbuff_pop(&dbuff, NULL, sizeof(int));
        TEST(dbuff.buffer != NULL)
        TEST(dbuff.buffer != vals)
        TEST(dbuff.capacity == sizeof(int) * 4)
        TEST(dbuff.used == sizeof(int) * 3)
        for (int i = 0; i < 3; i++) {
            TEST(((int *) dbuff.buffer)[i] == vals[i])
        }
        int t = 0;
        void *prev_buffer = dbuff.buffer;
        dbuff_pop(&dbuff, &t, sizeof(int));
        TEST(dbuff.buffer != NULL)
        TEST(dbuff.buffer == prev_buffer)
        TEST(dbuff.capacity == sizeof(int) * 4)
        TEST(dbuff.used == sizeof(int) * 2)
        TEST(((int *) dbuff.buffer)[0] == vals[0])
        TEST(((int *) dbuff.buffer)[1] == vals[1])
        TEST(t == vals[2])
        dbuff_free(&dbuff);
    } {
        TEST_UNIT(push then compact)
        dbuff_t dbuff = DBUFF_EMPTY;
        int vals[] = {1, 2, 3, 4, 5, 6};
        dbuff_push(&dbuff, vals, sizeof(vals));
        dbuff_compact(&dbuff);
        TEST(dbuff.buffer != NULL)
        TEST(dbuff.capacity == 32)
        TEST(dbuff.used == sizeof(vals))
        dbuff_free(&dbuff);
    } {
        TEST_UNIT(get top)
        dbuff_t dbuff = DBUFF_EMPTY;
        int x;
        dbuff_allocate(&dbuff, sizeof(int) * 2);
        dbuff_push(&dbuff, &x, sizeof(int));
        void *result = dbuff_get_top(&dbuff);
        TEST(result - dbuff.buffer == sizeof(int))
        dbuff_free(&dbuff);
    }
    END_TEST
}
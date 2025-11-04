#ifndef TEST_H
#define TEST_H

#include <stdio.h>

int tests_passed;
int tests_failed;

#define START_TEST tests_passed = 0; tests_failed = 0; printf("testing %s\n", __FILE__);
#define TEST_UNIT(name) printf("unit: %s\n", #name);
#define TEST(cond) if (cond) {tests_passed++;} else {printf("  (failed) ln:%d %s\n", __LINE__, #cond); tests_failed++;}
#define END_TEST printf("test result:\n  passed: %d\n  failed: %d\n", tests_passed, tests_failed);

#endif
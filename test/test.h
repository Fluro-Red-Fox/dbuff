#ifndef TEST_H
#define TEST_H

#include <stdio.h>

int tests_passed;
int tests_failed;
char *test_unit_name;

#define START_TEST tests_passed = 0; tests_failed = 0; test_unit_name = NULL; printf("testing %s\n", __FILE__);
#define TEST_UNIT(name) test_unit_name = #name;
#define TEST(cond) if (cond) {tests_passed++;} else {if (test_unit_name) {printf("unit: %s\n", test_unit_name); test_unit_name = NULL;} printf("  (failed) ln:%d %s\n", __LINE__, #cond); tests_failed++;}
#define END_TEST printf("test result:\n  passed: %d\n  failed: %d\n", tests_passed, tests_failed);

#endif
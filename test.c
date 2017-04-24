#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "test.h"
#include "dll.h"

typedef int (*test_t)(FILE* );

#define ASSERT(c,s) do { \
    if(!(c)) { \
        fprintf(printFile, s "\n"); \
        return 1; \
    } \
} while(0)

int test1(FILE* printFile) {
    (void)printFile;

    dll* dll = dll_new();

    ASSERT(dll->head == NULL, "head is not NULL");
    ASSERT(dll->tail == NULL, "tail is not NULL");

    dll_insert(dll, data_new(33, "aap"));

    ASSERT(dll->head, "head not set");
    ASSERT(dll->tail, "tail not set");
    ASSERT(dll->head->prev == NULL, "inserted node's prev is not NULL");
    ASSERT(dll->head->next == NULL, "inserted node's next is not NULL");
    ASSERT(dll->head->data->age == 33, "node not correctly inserted (age)");
    ASSERT(!strcmp(dll->head->data->name, "aap"), "node not correctly inserted (name)");

    dll_delete(dll);

    return 0;
}

int test2(FILE* printFile) {
    (void)printFile;

    dll* dll = dll_new();

    dll_insert(dll, data_new(33, "aap"));

    ASSERT(dll->head, "head not set");
    ASSERT(dll->tail, "tail not set");
    ASSERT(dll->head->prev == NULL, "inserted node's prev is not NULL");
    ASSERT(dll->head->next == NULL, "inserted node's next is not NULL");
    ASSERT(dll->head->data->age == 33, "node not correctly inserted (age)");
    ASSERT(!strcmp(dll->head->data->name, "aap"), "node not correctly inserted (name)");

    dll_insert(dll, data_new(44, "noot"));

    ASSERT(dll->head, "head not set");
    ASSERT(dll->tail, "tail not set");
    ASSERT(dll->head->prev == NULL, "chain error");
    ASSERT(dll->head->next == dll->tail, "chain error");
    ASSERT(dll->tail->prev == dll->head, "chain error");
    ASSERT(dll->tail->next == NULL, "chain error");
    ASSERT(dll->head->data->age == 33, "node not correctly inserted (age)");
    ASSERT(!strcmp(dll->head->data->name, "aap"), "node not correctly inserted (name)");
    ASSERT(dll->tail->data->age == 44, "node not correctly inserted (age)");
    ASSERT(!strcmp(dll->tail->data->name, "noot"), "node not correctly inserted (name)");

    data* dat = data_new(44, "noot");
    dll_erase(dll, dat);
    data_delete(dat);

    ASSERT(dll->head, "head not set");
    ASSERT(dll->tail, "tail not set");
    ASSERT(dll->head->prev == NULL, "inserted node's prev is not NULL");
    ASSERT(dll->head->next == NULL, "inserted node's next is not NULL");
    ASSERT(dll->head->data->age == 33, "node not correctly inserted (age)");
    ASSERT(!strcmp(dll->head->data->name, "aap"), "node not correctly inserted (name)");

    dll_delete(dll);

    return 0;
}

int test3(FILE* printFile) {
    (void)printFile;

    dll* dll = dll_new();

    dll_insert(dll, data_new(33, "aap"));
    dll_insert(dll, data_new(44, "noot"));
    dll_insert(dll, data_new(22, "mies"));

    ASSERT(dll->head, "head not set");
    ASSERT(dll->tail, "tail not set");
    ASSERT(dll->head->prev == NULL, "head's prev is not NULL");
    ASSERT(dll->tail->next == NULL, "tail's next is not NULL");
    ASSERT(dll->head->data->age == 33, "node not correctly inserted (age)");
    ASSERT(!strcmp(dll->head->data->name, "aap"), "node not correctly inserted (name)");
    ASSERT(dll->tail->data->age == 22, "node not correctly inserted (age)");
    ASSERT(!strcmp(dll->tail->data->name, "mies"), "node not correctly inserted (name)");

    return 0;
}

int test4(FILE* printFile) {
    (void)printFile;

    // Add a test here if you want

    return 0;
}

int test5(FILE* printFile) {
    (void)printFile;

    // Add a test here if you want

    return 0;
}

test_t tests[] = {test1, test2, test3, test4, test5};

void test(FILE* printFile) {
    fprintf(printFile, "Testing...\n");
    int max = sizeof(tests)/sizeof(*tests);
    int lmax = 1 + log10(max);
    for(int i = 0; i < max; ++i) {
        int r = tests[i](printFile);
        fprintf(printFile, "[%*i/%i] ", lmax, i+1, max);
        if(r) {
            fprintf(printFile, "FAIL\n");
        } else {
            fprintf(printFile, "PASS\n");
        }
    }
}

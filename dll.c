#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dll.h"

int data_compare(data* d1, data* d2) {
    assert(d1);
    assert(d2);
    if(d1->age < d2->age) return -1;
    if(d1->age > d2->age) return 1;
    return strcmp(d1->name, d2->name);
}

void data_print(data* d, FILE* f) {
    fprintf(f, "%i %s", d->age, d->name);
}

data* data_new(int age, char const* name) {
    data* d = (data*)calloc(1, sizeof(data));
    d->age = age;
    strncpy(d->name, name, NAME_LENGTH);
    return d;
}

void data_delete(data* d) {
    free(d);
}

dll* dll_new() {
    dll* list = (dll*)malloc(sizeof(dll));
    if(list == NULL) {
        fprintf(stderr, "Could not allocate memory");
        exit(-1);
    }

    list->head = NULL;
    list->tail = NULL;
    return list;
}

void dll_insert(dll* dll, data* data) {
    assert(dll != NULL);
    assert(data != NULL);

    node* n = (node*)malloc(sizeof(node));
    n->data = data;
    n->next = NULL;

    if(dll->tail == NULL) {
        n->prev = NULL;
        dll->head = dll->tail = n;
    } else {
        n->prev = dll->tail;
        n->prev->next = n;
        dll->tail = n;
    }
}

void dll_erase(dll* dll, data* data) {
    assert(dll != NULL);
    assert(data != NULL);

    node* node = dll->head;
    while(node != NULL) {
        if(data_compare(node->data, data) == 0) {
            if(node->prev) {
                node->prev->next = node->next;
            }
            if(node->next) {
                node->next->prev = node->prev;
            }
            free(node->data);
            free(node);
            break;
        }

        node = node->next;
    }
}

void dll_print(dll* dll, FILE* printFile) {
    assert(dll != NULL);
    assert(printFile != NULL);

    node* node = dll->head;
    while(node != NULL) {
        data_print(node->data, printFile);
        fprintf(printFile, "\n");
        node = node->next;
    }
}

void dll_reverse(dll* dll) {
    assert(dll != NULL);

    node* n = dll->tail;
    while(n != NULL) {
        node* old_prev = n->prev;
        n->prev = n->next;
        n = n->next = old_prev;
    }
}

void dll_delete(dll* dll) {
    assert(dll != NULL);

    node* n = dll->head;
    while(n != NULL) {
        node* next = n->next;
        free(n->data);
        free(n);
        n = next;
    }

    free(dll);
}

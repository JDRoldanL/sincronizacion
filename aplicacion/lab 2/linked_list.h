#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct book{
    int id;
    char *name;
    int num_pages;
    int pub_year;
} book;

// basic node structure
typedef struct __node_t{
    book libro;
    struct __node_t *next;
} node_t;
// basic list structure (one used per list)

typedef struct __list_t{
    node_t *head;
    pthread_mutex_t lock;
}list_t;

void List_Init(list_t *L);

void List_Insert(list_t *L, book bk);

int List_Lookup(list_t *L, int key);

int List_Delete(list_t *L, int key);

void List_Print(list_t *L);

int List_Available(list_t *L);

#endif
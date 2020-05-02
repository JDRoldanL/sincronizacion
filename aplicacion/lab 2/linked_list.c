#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void List_Init(list_t *L){
    L->head = NULL;
    L->last = NULL;
    pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, book bk){
    // synchronization not needed
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL){
        perror("malloc");
        return;
    }
    new->libro = bk;
    // just lock critical section
    pthread_mutex_lock(&L->lock);
    if(L->head == NULL){
        L->head = new;
        L->last = new;
    }else{
        L->last->next = new;
        L->last = new;
    }
    pthread_mutex_unlock(&L->lock);
}

void List_Print(list_t *L){
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr != NULL){
        printf("id: %d, name: %s, n pag: %d, año: %d\n", curr->libro.id, curr->libro.name, curr->libro.num_pages, curr->libro.pub_year);
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
}
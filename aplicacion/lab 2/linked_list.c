#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void List_Init(list_t *L)
{
    L->head = NULL;
    pthread_mutex_init(&L->lock, NULL);
}

void List_Insert(list_t *L, book* bk){
    // synchronization not needed
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL){
        perror("malloc");
        return;
    }
    new->libro = bk;
    // just lock critical section
    pthread_mutex_lock(&L->lock);
    new->next = L->head;
    L->head = new;
    if(L->head->next != NULL){
        printf("head: %d, next: %d\n", L->head->libro->id, L->head->next->libro->id);
    }
    pthread_mutex_unlock(&L->lock);
}

int List_Lookup(list_t *L, int key)
{
    int rv = -1;
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr)
    {
        if (curr->libro->id == key)
        {
            rv = 0;
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
    return rv; // now both success and failure
}

int List_Delete(list_t *L, int key)
{
    int rv = -1;
    pthread_mutex_lock(&L->lock);
    node_t *prev = NULL;
    node_t *curr = L->head;

    if(curr==L->head && curr->libro->id == key){
        L->head=L->head->next;
        rv = 0;
    }

    prev = curr;
    curr = curr->next;

    while (curr && rv==-1){

        if (curr->libro->id == key){
            prev->next = curr->next;
            rv = 0;
            break;
        }
        prev = curr;
        curr = curr->next;

    }
    pthread_mutex_unlock(&L->lock);
    return rv; // now both success and failure
}

void List_Print(list_t *L){
    pthread_mutex_lock(&L->lock);
    node_t *curr = L->head;
    while (curr != NULL){
        printf("id: %d, name: %s, n pag: %d, año: %d\n",curr->libro->id,curr->libro->name,curr->libro->num_pages,curr->libro->pub_year);
        curr = curr->next;
    }
    pthread_mutex_unlock(&L->lock);
}
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "linked_list.h"
#include <string.h>

#define THRESHOLD 1024

list_t books;

/* Global variables */
// code here (if you required it)...
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) { 

    List_Init(&books);
    for(int i=0;i<100;i++){
        char tmp1[50];
        snprintf(tmp1, 50, "%d", i);
        char temp2[50] = "book_";
        strcat(temp2,tmp1);
        book bk={i,temp2,100,2020};
        List_Insert(&books,&bk);
    }
    node_t *curr = books.head;
    while (curr != NULL){
        printf("id: %d, name: %s, n pag: %d, año: %d\n",curr->libro->id,curr->libro->name,curr->libro->num_pages,curr->libro->pub_year);
        curr = curr->next;
    }
    return 0;
}
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

int main(int argc, char *argv[]){
    List_Init(&books);
    for(int i = 0; i < 100; i++){
        char tmp1[50] = "";
        char *tmp2 = malloc(sizeof(char)*50);
        strcpy(tmp2, "book_");
        snprintf(tmp1, 50, "%d", i);
        strcat(tmp2,tmp1);
        book bk = {i,tmp2,100,2020};
        List_Insert(&books,bk);
    }
    List_Print(&books);
    return 0;
}
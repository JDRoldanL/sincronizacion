#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "linked_list.h"
#include <string.h>

#define THRESHOLD 1024

list_t books;

void *adding(void *);

/* Global variables */
// code here (if you required it)...
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[]) { 

    List_Init(&books);
    for(int i=0;i<100;i++){
        char tmp[50];
        itoa(i,tmp,10);
        char* name=strcat("book_",tmp);
        book bk={i,name,100,2020};
        List_Insert(&books,&bk);
        List_Print(&books);
    }
    
    return 0;
}

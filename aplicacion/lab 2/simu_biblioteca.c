#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "linked_list.h"
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_BOOKS 10000

list_t books;
int successTotal = 0;
int failTotal = 0;
int available = 0;
int success[4] = {0,0,0,0};
int fail[4] = {0,0,0,0};

/* Global variables */
// code here (if you required it)...
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *simOffice(void *);

int main(int argc, char *argv[]){
    List_Init(&books);
    struct timeval tvi, tvf;
    for(int i = 0; i < MAX_BOOKS; i++){
        char tmp1[50] = "";
        char *tmp2 = malloc(sizeof(char)*50);
        strcpy(tmp2, "book_");
        snprintf(tmp1, 50, "%d", i);
        strcat(tmp2,tmp1);
        book bk = {i,tmp2,100,2020};
        List_Insert(&books,bk);
    }

    //List_Print(&books);


    pthread_t hilos[4];
    gettimeofday(&tvi, NULL);

    //Creacion hilos
   for (int i = 0; i < 4; i++){
        int *d = (int *)malloc(sizeof(int *));
        *d = i;
        pthread_create(&hilos[i], NULL, simOffice, d);
    }

    //Join hilos
    for (int i = 0; i < 4; i++){
        pthread_join(hilos[i], NULL);
    }

    successTotal = success[0] + success[1] + success[2] + success[3];
    failTotal = fail[0] + fail[1] + fail[2] + fail[3];
    int available = List_Available(&books);
    printf("Total exito: %d\nTotal Fallo: %d\nLibros disponibles: %d\n", successTotal, failTotal, available);
    gettimeofday(&tvf, NULL);
    long tiempoTotalSec = (tvf.tv_sec - tvi.tv_sec);
    int tiempoTotalMicroSec = (tvf.tv_usec - tvi.tv_usec);
    if(tiempoTotalMicroSec < 0){
        tiempoTotalSec--;
        tiempoTotalMicroSec = 1000000+tiempoTotalMicroSec;
    }
    printf("El tiempo tomado para la ejecucion del programa es: %ld segundos con %d microsegundos\n", tiempoTotalSec, tiempoTotalMicroSec); 

    return 0;
}



void *simOffice(void *arg){
    int *numOffice = (int *)arg;
    int buscarLibro;
    srand(time(NULL)); 
    for (int i = 0; i < 1000; i++){
        buscarLibro = rand() % MAX_BOOKS;
        int rv = List_Delete(&books, buscarLibro);
        if(rv == 0){
            success[*numOffice] += 1;
        }else{
            fail[*numOffice] += 1;
        }
    }
    printf("Office %d has finished its workload, successful loans %d, failed loans %d\n", *numOffice, success[*numOffice], fail[*numOffice]);
    return NULL;
}

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include "counter.h"


/* structs */
// code here (if you required it)...

/* start_routine header */
// code here...
void *adding(void *);
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER; 

/* Global variables */
// code here (if you required it)...
counter_t counter;

int main(int argc, char *argv[]) { 

    if(argc != 3){
        printf("Faltan argumentos");
        return 0;
    }
    /* get the command's line parameters */
    // code here...
    int numHilos = atoi(argv[2]);
    long int maxCnt = atoi(argv[1]);


    /* Declaration of struct timeval variables */
    // code here...
    struct timeval tvi, tvf;

    /* Initializing conter */
    // code here...
    counter.value = 0;

    /* Threads handlers */
    // code here...
    pthread_t hilos[numHilos];

    /* Thread creation */
    // code here...

    /* Time starts counting */
    // code here...
    gettimeofday(&tvi, NULL);

    /* Creating a Threads */
    // code here...
    for (int i = 0; i < numHilos; i++){
        pthread_create(&hilos[i], NULL, adding, &maxCnt);
    }

    /* Threads joins */
    // code here...
    for (int i = 0; i < numHilos; i++){
        pthread_join(hilos[i], NULL);
    }

    /* Time stops counting here */
    // code here...
    gettimeofday(&tvf, NULL);

    /* get the end time */
    // code here...
    

    /* get the elapset time (end_time - start_time) */
    // code here...
    long tiempoTotalSec = (tvf.tv_sec - tvi.tv_sec);
    int tiempoTotalMicroSec = (tvf.tv_usec - tvi.tv_usec);
    if(tiempoTotalMicroSec < 0){
        tiempoTotalSec--;
        tiempoTotalMicroSec = 1000000+tiempoTotalMicroSec;
    }
    /* print the results (number threads employed, counter value, elasep time) */
    // code here...
    printf("El numero de hilos usados es: %d.\nEl valor del contador es: %d.\nEl tiempo tomado para la ejecucion del programa es: %ld segundos con %d microsegundos\n", numHilos, counter.value, tiempoTotalSec, tiempoTotalMicroSec);    

    return 0;
}

/* start_routine definition */
// code here... counter.value < *a
void *adding(void *count){
    int *a = (int *)count;
    while (counter.value < *a){
        pthread_mutex_lock(&m);
        if (counter.value < *a){
            increment(&counter);   
        }
        pthread_mutex_unlock(&m);
    }
    return NULL;
}
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    struct timeval tvi, tvf;
    gettimeofday(&tvi, NULL); //Inicia
    sleep(1);
    gettimeofday(&tvf, NULL); // Termina
    long tiempoTotalSec = (tvf.tv_sec - tvi.tv_sec);
    int tiempoTotalMicroSec = (tvf.tv_usec - tvi.tv_usec);
    printf("El tiempo total es de: %ld segundos con %d microsegundos\n", tiempoTotalSec, tiempoTotalMicroSec);
    
    return 0;
}
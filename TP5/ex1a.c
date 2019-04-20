#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "tfun.c"



int main(int argc, char** argv){
    long int li = 0;
    long times = strtol(argv[1], NULL, 10);
    pthread_t pt[3];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

    sarg_t arg0 = {&li, times, 0, &lock};
    sarg_t arg1 = {&li, times, 1, &lock};
    sarg_t arg2 = {&li, times, 2, &lock};

    pthread_create(pt, NULL, sfun, (void *)(&arg0));
    pthread_create(pt + 1, NULL, sfun, (void *)(&arg1));
    pthread_create(pt + 2, NULL, sfun, (void *)(&arg2));

    for(int i = 0; i < 3; i++)
    {
        pthread_join(pt[i], NULL);
    }
    
    printf("counter: %ld\n", li);

} 

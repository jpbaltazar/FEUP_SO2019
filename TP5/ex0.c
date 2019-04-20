#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct _farg{
    long int* p;
    long n;
    pthread_mutex_t* lock;
} farg;

void* fun(void *args){
    long m = ((farg*)args)->n;
    long *pointer = ((farg*)args)->p;
    pthread_mutex_t* lock = ((farg*)args)->lock;
    for(int i = 0; i < m; i++){
        pthread_mutex_lock(lock);
        *pointer += 1;
        pthread_mutex_unlock(lock);
    }
}

int main(int argc, char **argv, char **envp){
    long int counter = 0;
    pthread_t threads[3];
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    farg arg = {&counter, strtol(argv[1], NULL, 10), &lock};

    for(int i = 0; i < 3; i++)
    {
        pthread_create(threads + i, NULL, fun, &arg);
    } 

    for(int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], NULL);
    } 

    printf("counter: %ld\n", counter);
}
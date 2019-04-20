#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>


void *fun(void *args){
    printf("PID: %d, TID: %ld\n", getpid(), syscall(SYS_gettid));
    int *returnInt =  malloc(sizeof(int));
    int *argval = (int *)args;
    *returnInt = *argval;
    return (void *)returnInt;
}

int main(int argc, char** argv){
    pthread_t threads[3];
    int arga[] = {1, 2, 3};
    int *argReturn[3];
    for(int i = 0; i < 3; i++)
    {
        pthread_create((threads + i), NULL, fun, (void *)(arga+i));
    }
    
    for(int i = 0; i < 3; i++)
    {
        pthread_join(threads[i], (void **)(argReturn + i));
        printf("result: %d\n", *argReturn[i]);
        free(argReturn[i]);
    }

    return 0;
}

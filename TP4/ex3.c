#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

void *fun(void *args){
    printf("TID: %ld, argPassed %d\n", syscall(SYS_gettid), *((int *)args));
    return args;
}

int main(int argc, char** argv){
    long n = strtol(argv[1], NULL, 10);
    printf("n = %ld\n", n);
    pthread_t *threads = malloc(sizeof(pthread_t) * n);
    int *arga = malloc(sizeof(int) * n);
    int **argRet = malloc(sizeof(int*) * n);

    for(int i = 0; i < n; i++){
        arga[i] = i;
        pthread_create(threads + i, NULL, fun, (void *)(arga+i));
        printf("thread %d ", i);

    }

    for(int i = 0; i < n; i++)
    {
        pthread_join(threads[i], (void **)(argRet + i));
        printf("result: %d\n", *argRet[i]); //HERE
    }

    free(argRet);
    free(threads);
    free(arga);

    return 0;
}

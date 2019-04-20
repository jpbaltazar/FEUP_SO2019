#include <pthread.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct _arg_t{
    int in;
    int tn;
    int tnumber;
    int *array;
}arg_t;

void* fun(void* args){
    arg_t* argv = (arg_t*)args;
    for(int i = argv->tnumber; i < argv->in; i+=argv->tn)
    {
        argv->array[i] = i;
    }
    return NULL;
}

int main(int argc, char** argv){
    long in = strtol(argv[1], NULL, 10);
    long tn = strtol(argv[2], NULL, 10);
    printf("Filling a %ld integer array with %ld threads\n", in, tn);
    pthread_t *threads = malloc(sizeof(pthread_t) * tn);
    int* array = malloc(sizeof(int) * in);

    arg_t *arg = malloc(sizeof(arg_t) * tn);

    for(int i = 0; i < tn; i++)
    {   
        arg[i] = (arg_t){in, tn, i, array};
        pthread_create(threads + i, NULL, fun, (void *)(arg+i));
    }
    
    for(int i = 0; i < tn; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("array:\n");
    for(int i = 0; i < in; i++)
        printf("%d\n", array[i]);

    free(threads);
    free(array);
}
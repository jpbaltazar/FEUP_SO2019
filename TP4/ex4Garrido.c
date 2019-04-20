#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG 0

typedef struct _argt{
    int iterations, nThreads, arraySize;
    int *v; 
}args_c;

typedef struct _args{
    args_c *commonArgs;
    int ThreadN;
    pthread_t ThreadID;
}args_s;


void *arrayInitializer(void *args){
    args_s *Args = (args_s *) args;
    args_c *commonArgs = Args->commonArgs;
    int t_mult_iter = (Args->ThreadN)*(commonArgs->iterations);
    #if (DEBUG == 1)
    printf("threadN %d\n", Args->threadN);
    printf("Iterations %d\n", Args->iterations);
    printf("t_mult_iter: %d\n", t_mult_iter);
    #endif
    for(int i = 0; (i < commonArgs->iterations) && ( (i+t_mult_iter) < commonArgs->arraySize); i++){
        commonArgs->v[(i+t_mult_iter)] = i+t_mult_iter;
        #if (DEBUG == 1)
        printf("THREADN: %d | Iteration: %d  |  Number: %d \n", Args->ThreadN, i, commonArgs->v[(i+t_mult_iter)]);
        #endif
    }
}

void printArray(int *v, int arraySize){
    for(int i = 0; i < arraySize; i++){
        printf("Iteration: %d  |  Number: %d \n", i, v[i]);
    }
}

int main(int argc, char const *argv[]){
    assert(argc > 2);
    args_c Args;
    Args.nThreads = strtol(argv[2], NULL, 10);
    Args.arraySize = strtol(argv[1], NULL, 10);
    Args.iterations = Args.arraySize/Args.nThreads+1;
    Args.v = malloc(Args.arraySize * sizeof(int) );
    args_s *ArgsArray = malloc( sizeof(args_s) * Args.nThreads );
    for(int i = 0; i < Args.nThreads; i++){
        ArgsArray[i].ThreadN = i;
        ArgsArray[i].commonArgs = &Args;
        pthread_create(&(ArgsArray[i].ThreadID), NULL, arrayInitializer, (void *) &(ArgsArray[i]) );
    }
    
    for(int i = 0; i < Args.nThreads; i++){
        #if (DEBUG == 1)
        printf("JOIN %d\n", i);
        #endif
        pthread_join(ArgsArray[i].ThreadID, NULL);
    }
    #if (DEBUG == 0)
    printArray(Args.v, Args.arraySize);
    #endif
    
    free(Args.v);
    free(ArgsArray);
    
    return 0;
}

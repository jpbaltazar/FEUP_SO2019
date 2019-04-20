#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>



typedef struct _argx{
    int *m, *n, *mReady, *nReady;
    pthread_mutex_t lockn, lockm;
    pthread_cond_t mAccess, nAccess;
} argx;

void *reader(void *arg){
    argx *a = (argx *)arg;
    int *m = a->m, *n = a->n, localm = 0, localn = 0;
    for(int i = 0; i < 50000000; i++)
    {
        if(i%1000000){
            localm = *m;


            localn = *n;
        }
    }
    
    return NULL;
}

void *writer(void *arg){
    argx *a = (argx *)arg;
    int *m = a->m;
    int *n = a->n;
    for(int i = 0; i < 50000000; i++)
    {
        pthread_mutex_lock(&(a->lockm));
        (*m)++;
        pthread_mutex_unlock(&(a->lockm));

        pthread_mutex_lock(&(a->lockn));
        (*n)++;
        pthread_mutex_unlock(&(a->lockn));
    }

    return NULL;
}

int main(int argc, char *argv[]){
    int m = 0, n = 0, mReady = 0, nReady = 0;
    pthread_t threads[4];
    argx argexample = {&m, &n, &mReady, &nReady, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER};
    argx args[4] = {argexample, argexample, argexample, argexample};
    for(int i = 0; i < 2; i++)
    {
        pthread_create(threads + i, NULL, writer, (void *)(args + i));
        pthread_create(threads + i + 1, NULL, reader, (void *)(args + i + 1));
    }
    

    for(int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
    printf("ended m:%d n:%d\n", m, n);
}
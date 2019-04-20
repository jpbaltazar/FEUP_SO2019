#include <stdio.h>
#include <pthread.h>

typedef struct _ar{
    long int* n;
    pthread_mutex_t* mtp;
} ar;

void *func(void* arg){
    ar* a = (ar*)arg;

    pthread_mutex_lock(a->mtp);
    *(a->n) += 1;
    printf("%ld\n", *(a->n));
    pthread_mutex_unlock(a->mtp);
    return NULL;
}

int main(int argc, char* argv){
    long int li = 0;
    pthread_t pt[3];
    pthread_mutex_t mt = PTHREAD_MUTEX_INITIALIZER;
    ar arg = {&li, &mt};
    pthread_create(pt, NULL, func, (void *)&arg);    
    pthread_create(pt + 1, NULL, func, (void *)&arg);
    pthread_create(pt + 2, NULL, func, (void *)&arg);

    pthread_join(pt[0], NULL);
    pthread_join(pt[1], NULL);
    pthread_join(pt[2], NULL);
}
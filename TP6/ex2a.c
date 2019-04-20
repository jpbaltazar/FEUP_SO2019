#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

//Heavily inspired by: https://github.com/weirdNox/FEUP/blob/master/Ano3/SO/set06/2a.c

typedef struct _RawArg{

}RawArg;

typedef struct _Lock{
    pthread_mutex_t lock;
    pthread_cond_t writeCond;
    int currReaders;
}Lock;

volatile int m, n;
Lock lock;

void reader_lock(void){
    pthread_mutex_lock(&lock.lock);
    ++lock.currReaders;
    pthread_mutex_unlock(&lock.lock);
}

void reader_unlock(void){
    pthread_mutex_lock(&lock.lock);
    if(--lock.currReaders == 0){
        pthread_cond_signal(&lock.writeCond);
    }
    pthread_mutex_unlock(&lock.lock);
}

void writer_lock(void){
    pthread_mutex_lock(&lock.lock);
    while(lock.currReaders)
        pthread_cond_wait(&lock.writeCond, &lock.lock);
}

void writer_unlock(void){
    pthread_mutex_unlock(&lock.lock);
}

void *writer(void *arg){
    for(int i = 0; i < 50000000; ++i)
    {
        writer_lock();
        ++m;
        ++n;
        writer_unlock();
    }

    return NULL;
}

void *reader(void *arg){
    for(int i = 0; i < 50000000; i++)
    {
        reader_lock(); //YTFFFFF?????
        if(i%1000000 == 0){
            printf("m: %9d\tn: %9d\t%d\n", m, n, i/1000000);
        }
        reader_unlock(); //YTFFFFF?????
    }
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t threads[4];
    RawArg argexample = {};
    RawArg args[4] = {argexample, argexample, argexample, argexample};
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
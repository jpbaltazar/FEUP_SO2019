#include <stdio.h>
#include <pthread.h>

typedef struct _voidarg{
    int a, b;
}voidarg;

void *sum(void *arg){
    voidarg *aaa = (voidarg*) arg;
    int *res = malloc(sizeof(int));
    *res = aaa->a + aaa->b;
    printf("%d\n", res);
    return res;
}

void *sub(void *arg){
    voidarg *aaa = (voidarg*) arg;
    int *res = malloc(sizeof(int));
    *res = aaa->a - aaa->b;
    printf("%d\n", res);
    return res;
}

void *mul(void *arg){
    voidarg *aaa = (voidarg*) arg;
    int *res = malloc(sizeof(int));
    *res = aaa->a * aaa->b;
    printf("%d\n", res);
    return res;
}

void *divi(void *arg){
    voidarg *aaa = (voidarg*) arg;
    int *res = malloc(sizeof(int));
    *res = aaa->a / aaa->b;
    printf("%d\n", res);
    return res;
}

int main(int argc, char** argv){
    pthread_t pt[4];

    voidarg arg = {2, 3};

    void *(*fp[4])(void *) = {sum, sub, mul, divi};
    int res = 0;
    for(int i = 0; i < 4; i++)
    {
        pthread_create(pt + i, NULL, fp[i], (void *)&arg);    
    }
    
    for(int i = 0; i < 4; i++)
    {
        pthread_join(*(pt + i), &res); 
        printf(res);  
    }
    return 0;
}
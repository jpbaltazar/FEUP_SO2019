#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/*
phtread_cond_t
phtread_cond_wait(phtread_cond_t *, pthread_mutex_t *)
pthread_cond_signal(pthread_cond_t *)
*/

typedef struct _stack_el{
		char *str;              /* String to be printed in show() */
		int n;                  /* Integer to be printed in show() */
} stack_el;

typedef struct _stack{
		stack_el ** sp;	/* Pointer to array of fixed size for storing the stack elements */
		int size;               /* Number of elements in the array */
		int top;                /* Pointer to the top of the stack: initially 0 */
        pthread_mutex_t lock;
        pthread_cond_t nfull;
        pthread_cond_t nempty;
}stack;

typedef struct _arg_t{
    stack *sp;
    stack_el *el;
}arg_t;

stack *init(int size){
    stack *sp = (stack *)malloc(sizeof(stack));
    if(sp == NULL){
        return NULL;
    }
    sp->sp = (stack_el**)malloc(size * sizeof(stack_el*));
    if(sp->sp == NULL){
        free(sp);
        return NULL;
    }
    sp->size = size;
    sp->top = 0;
    sp->lock = PTHREAD_MUTEX_INITIALIZER;
    //sp->nfull = PTHREAD_COND_INITIALIZER;
    //sp->nempty = PTHREAD_COND_INITIALIZER;
    return sp;
}

void* tpush(void * arg){
    arg_t* argx = (arg_t*)arg;
    stack* sp = argx->sp;
    stack_el* el = argx->el;
    pthread_mutex_lock(&(sp->lock));
    while(sp->size <= sp->top) 
        pthread_cond_wait(&(sp->nfull), &(sp->lock));
    sp->sp[sp->top] = el;
    sp->top++;
    pthread_cond_signal(&(sp->nempty));
    pthread_mutex_unlock(&(sp->lock));
    return NULL;
}

void* tpop(void * arg){
    arg_t* argx = (arg_t*)arg;
    stack* sp = argx->sp;
    pthread_mutex_lock(&(sp->lock));
    while(sp->top <= 0)
        pthread_cond_wait(&(sp->nempty), &(sp->lock));
    sp->top--;
    argx->el = sp->sp[sp->top];
    sp->sp[sp->top] = NULL;
    pthread_cond_signal(&(sp->nfull));
    pthread_mutex_unlock(&(sp->lock));
    return &(argx->el);
}

void* tshow(void * arg){
    arg_t* argx = (arg_t*)arg;
    stack* sp = argx->sp;
    pthread_mutex_lock(&(sp->lock));
    printf("Show:\n");
    for(int i = 0; i < sp->top; i++)
    {
        printf("\t%s %d\n", sp->sp[i]->str, sp->sp[i]->n);
    }
    printf("end\n");
    pthread_mutex_unlock(&(sp->lock));
    return NULL;
}

int push(stack *sp, stack_el *el){
    pthread_t thread;
    arg_t argx = {sp, el};
    pthread_create(&thread, NULL, tpush, &argx);
    pthread_join(thread, NULL);
    return 1;
}

stack_el *pop(stack *sp){
    pthread_t thread;
    arg_t argx = {sp, NULL};
    pthread_create(&thread, NULL, tpop, &argx);
    pthread_join(thread, (void **)&(argx.el));
    return argx.el;
}

void show(stack *sp){
    pthread_t thread;
    arg_t argx = {sp, NULL};
    pthread_create(&thread, NULL, tshow, &argx);
    pthread_join(thread, (void **)&(argx.el));
}

void freeStack(stack *sp){
    for(int i = 0; i < sp->top; i++)
    {
        //free(sp->sp[i]); alocado localmente n precisa
    }
    free(sp);
}


int main(int argc, char** argv){
    stack_el stel[5]  = {{"hi", 0}, {"hello", 1}, {"salutations", 2}, {"greetings", 3}, {"good day", 4}};
    stack* st = init(5);
    for(int i = 0; i < 5; i++)
    {
        if(push(st, stel + i) == -1) return -1;
    }
    show(st);
    stack_el* p = pop(st);

    printf("removed: %s %d\n", p->str, p->n);
    //free(p); alocado localmente n precisa
    show(st);

    freeStack(st);
    printf("FINISHED\n");
}
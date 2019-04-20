#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex;

typedef struct _stack_el{
	char *str;              /* String to be printed in show() */
	int n;                  /* Integer to be printed in show() */
	struct _stack_el *next;  /* Link to next stack element */
} stack_el;

typedef struct _Arg {
    stack_el** headp;
    stack_el* stel;
}Arg;

void *_push(void *arg){
    Arg* ar = (Arg *)arg;
    pthread_mutex_lock(&mutex);
    ar->stel->next = *(ar->headp);
    *(ar->headp) = ar->stel;
    pthread_mutex_unlock(&mutex);
}

void *_pop(void *arg){
    Arg* ar = (Arg *)arg;
    stack_el* head = *(ar->headp);

    stack_el* res = malloc(sizeof(stack_el));
    pthread_mutex_lock(&mutex);
    res = head;
    head = res->next;
    pthread_mutex_unlock(&mutex);
    return res;
}

void *_show(void* arg){
    Arg* ar = (Arg *)arg;
    stack_el* pt = *(ar->headp);
    pthread_mutex_lock(&mutex);
    while (pt != NULL)
    {
        printf("%s, %d\n", pt->str, pt->n);
        pt = pt->next;
    } 
    pthread_mutex_unlock(&mutex);
}

void push(void *arg){
    pthread_t thread;
    pthread_create(&thread, NULL, _push, arg);
    pthread_join(thread, NULL);
}

stack_el pop(void *arg){
    pthread_t thread;
    stack_el* res;
    pthread_create(&thread, NULL, _pop, arg);
    pthread_join(thread, (void *)&res);
}

void show(void *arg){
    pthread_t thread;
    pthread_create(&thread, NULL, _show, arg);
    pthread_join(thread, NULL);
}

int main(int argc, char* argv){
    stack_el stkel[3] = {{"hi", 1, (stkel+1)},
                        {"salutations", 2, (stkel+2)},
                        {"hello", 3, NULL}};
    
    stack_el stkarg[3] = {{"goodbye", 1, (stkel+1)},
                        {"au revoir", 2, (stkel+2)},
                        {"Ciao", 3, NULL}};
    
    stack_el* head = stkel;
    stack_el* tail = (stkel+2);
    stack_el new = {"greetings", 4, NULL};
    Arg a = {&head, &new};
    push((void *)&a);
    show((void *)&a);
    printf("\n");
    pop((void *)&a);
    Arg b = {&head, &new};
    show((void *)&a);
}
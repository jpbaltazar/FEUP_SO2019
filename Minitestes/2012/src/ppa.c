/* ppa.c
 *  The Hungry Birds Problem - create threads without arguments and wait for their finishing (no values received)!

Program invocation:
	./ppa <n. babybirds> <n. food portions> <n. refills>

Invocation example:
     ./ppa 3 5 10000
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define MAXBABIES 100

int finish = 0;	// termination of simulation (flagged by parent bird)
int foodbits = 0;	// is the current number of bits of food in the "food-teat"

struct checkerarg {	// conveys info to checker
	int f;	// number of bits of food of each refill
	long r;	// number of refills - parent bird can then retire!
	int *working;	// ptr to binary state of parent bird
	int *eating;	// ptr to number of babies that are eating at a time
	pthread_mutex_t *mut; // for overall concurrency control to shared data
};
struct parentarg {	// conveys info to parent bird
	int f;	// number of bits of food of each refill
	long r;	// number of refills - parent bird can then retire!
	int *working;	// ptr to binary state of parent bird
};
struct babyarg {	// conveys info to baby birds
	int id;	// baby identification
	int *eating;	// ptr to number of babies that are eating at a time
};

void *checker(void *);	// checker thread
void *parent(void *);	// parent thread
void *baby(void *);	// baby thread


int main(int argc, char *argv[]) {

setbuf(stdout, NULL);
	int B;	// number of babies
	int F;	// number of bits of food of each refill
	long R;	// number of refills - parent bird can then retire!
	int working = 0;	// represents the binary state of parent bird:
	int eating = 0;	// number of babies that are eating at a time
	struct parentarg pa;	// conveys info to parent bird (and checker!)
	struct checkerarg ca;	// conveys info to parent bird (and checker!)
	struct babyarg ba[MAXBABIES];	// conveys baby identification
	pthread_t tchecker, tparent, tbaby[MAXBABIES];

if( argc != 4) {
	printf("Program invoked with wrong number of arguments.\n");
	printf("Program usage: %s <n. babybirds> <n. food portions> <n. refills>\n", argv[0]);
	exit(-1);
    }
else {
	B = atoi(argv[1]);
	F = atoi(argv[2]);
	R = atoi(argv[3]);
	}
printf("\nSimulation started\n");

// a preencher com o seu código:

// criar thread checker (também SEM passar argumentos!)
pthread_t ct;
pthread_create(&ct, NULL, checker, NULL);

// criar thread parent bird
pthread_t pt;
int pworking = 0;
parentarg parg = {F, R, &pworking};
pthread_create(&pt, &parg, parent, NULL);
// criar threads baby birds
pthread_t &bta =  malloc(B * sizeof(pthread_t);
for(int i = 0; i<B, i++) pthread_create(bta[i], NULL, baby, NULL);

// esperar por thread parent
pthread_join(pt, NULL);
// esperar por threads baby

// NÃO esperar pelo thread checker, pois é "detached"!

printf("\nSimulation finished\n");

exit (0);

} // main()


void *parent(void *arg) {	// parent bird thread
printf ("\n\tParent starting");

printf ("\n\tParent finishing");
return NULL;
}


void *baby(void *arg){	// baby thread

printf ("\n   Baby bird beginning");

printf ("\n   Baby bird finishing");
return (NULL);
}

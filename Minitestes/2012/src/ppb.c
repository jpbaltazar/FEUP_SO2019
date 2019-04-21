/* ppb.c
 *  The Hungry Birds Problem - pass arguments to threads and receive values from them when they finish!

Program invocation:
	./ppb <n. babybirds> <n. food portions> <n. refills>

Invocation example:
     ./ppb 3 5 10000
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#define MAXBABIES 100

int finish = 0;	// termination of simulation (flagged by parent bird)
int foodbits = 0;	// is the current number of bits of food in the "food-teat"

typedef struct _checkerarg {	// conveys info to checker
	int f;	// number of bits of food of each refill
	long r;	// number of refills - parent bird can then retire!
	int *working;	// ptr to binary state of parent bird
	int *eating;	// ptr to number of babies that are eating at a time
	pthread_mutex_t *mut; // for overall concurrency control to shared data
}checkerarg;
typedef struct _parentarg {	// conveys info to parent bird
	int f;	// number of bits of food of each refill
	long r;	// number of refills - parent bird can then retire!
	int *working;	// ptr to binary state of parent bird
}parentarg;
typedef struct babyarg {	// conveys info to baby birds
	int id;	// baby identification
	int *eating;	// ptr to number of babies that are eating at a time
}babyarg;

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
	parentarg pa;	// conveys info to parent bird (and checker!)
	checkerarg ca;	// conveys info to parent bird (and checker!)
	babyarg ba[MAXBABIES];	// conveys baby identification
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

// preparar args e criar thread checker (aqui, pôr o membro mut a NULL!)
ca = (checkerarg){F, R, &working, &eating};
if(pthread_create(&tchecker, NULL, checker, &ca) != 0) return -1;

// preparar args e criar thread parent bird
pa = (parentarg){F, R, &working};
pthread_create(&tparent, NULL, parent, &pa);
// preparar args e criar threads baby birds
for(int i = 0; i<B; i++){
	ba[i] = (babyarg){i, &eating};
	if(pthread_create(tbaby + i, NULL, baby, ba + i) != 0) return -1;
}


// esperar por thread parent
pthread_join(tparent, NULL);

// esperar por threads baby e recolher os seus resultados. Usar:
long *pbits_eaten;	// get baby bird's eating statistics
for(int i = 0; i < B; i++)
{
	pthread_join(tbaby[i], (void **)&pbits_eaten);
	printf ("\nNumber of bits of food eaten by baby %d / total of bits: %ld / %ld ", ba[i].id, *pbits_eaten, (R * F));
	free(pbits_eaten);
}


// Usar: printf ("\nNumber of bits of food eaten by baby %d / total of bits: %ld / %ld ", ? , ?, ? );


// NÃO esperar pelo thread checker, pois é "detached"!

printf("\nSimulation finished\n");

exit (0);
} // main()


void *parent(void *arg) {	// parent bird thread
	parentarg pa;
printf ("\n\tParent starting");
	pa = *((parentarg*)arg);
printf("\n\tParent received args f (%d), r (%ld), working (%d)", pa.f, pa.r , pa.working);
// a preencher com o seu código:

// Usar: printf ("\n\tParent received args f (%d), r (%ld), working (%d)", ? , ? , ? );



printf ("\n\tParent finishing");
return NULL;
} // parent()


void *baby(void *arg){	// baby thread
	babyarg ba;
	ba = *((babyarg*)arg);
	printf ("\n   Baby bird %d beginning", ba.id);
	printf("\n   Baby received args id (%d), eating (%d)", ba.id, ba.eating);
	long *res = malloc(sizeof(long));
	*res = 0;

// a preencher com o seu código:

// Usar: printf ("\n   Baby bird %d beginning",? );

// Usar: printf ("\n   Baby received args id (%d), eating (%d)", ? , ? );

// Usar: printf ("\n   Baby bird %d finishing", ? );
printf ("\n   Baby bird %d finishing", ba.id);
// Usar: return (?);
return res;
} // baby()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/time.h>

#include "err.h"
//#include "algoritmos.h"

typedef void(*SortFuncPtr)(void*,size_t,size_t,int(*)(const void*,const void*));

struct hipo
{
  int chave;
  int resto[100000]; // 100 mil posições
};

/*int type, size, alg;

void (*ptalgs[8])(Item, int, int, int);

int (*p)(Item, Item);*/

char *appName;


int intComp(const int *i1, const int *i2)
{
	return *i2-*i1;
}

int hipoComp(const struct hipo *s1,const struct *s2)
{
	return s2->chave - s1->chave;
}


void err(int errCode, char file[], int line)
{
	fprintf(stderr,"\n\nError: %s[%s:%i]\n\n",errStrings[errCode],file,line);
	exit(errCode);
}

struct _st1 {
	SortFuncPtr func;
	char *name;
	char *description;
} Algs[] = 
	{
		{qsort, "QuickSort LIBC", "LIBC(bult-in) implementation of QuickSort"},
		{NULL, NULL, NULL}
	};

/* Nomes de algoritimo para argumento do programa */
struct algoNames {
	char *name;
	SortFuncPtr algo;
} AlgNames [] = 
	{
		{"qsort",qsort},
		{"quicksortclib",qsort},
		{NULL, NULL}
	};


/*
Item *gerarandomico(){
    Item ran(){
        int i;
        i = rand()%size;
        if ( type == 0 ) return (Item)i;
        hp h = malloc(sizeof(hipo));
        if ( h == NULL ) return (Item)NULL;
        h->chave = i;
        return (Item)h;
    }
    Item *v;
    v = (Item*) calloc(size,sizeof(Item));
    if ( v == NULL ) return NULL;
    int i;
    for ( i = 0; i < size; ++i)
        v[i] = ran();
    return v;
}

void analisa(int argc, char** argv){
    int i = 1;
    for ( ; i < argc; ++i){
        if ( !(strcmp(argv[i],"-x3") ) )
            type = 1;
        if ( !(strcmp(argv[i],"-t") ) )
            size = atoi(argv[i+1]);
        if ( !(strcmp(argv[i],"-a") ) )
            alg = atoi(argv[i+1]);
    }
    if ( type == 1 )
        p = comp;
    else 
        p = compara;
}

void printKeys(Item vet[], int tam){
    void printItem(Item a){
        if ( type == 0 ){
            int i = (int) a;
            printf("%d ",i);
        }else{
            hp i = (hp) a;
            printf("%d ",i->chave);
        }
    }
    int i;
    for( i = 0; (i < tam) && (i < 20); ++i){
        printItem(vet[i]);
    }
    printf("\n");
}*/


void usage (int status)
{
	int i;

	if(!status)
	{
		fprintf(stderr,"Usage: %s [-a alg] -t tam [-x3]\n", appName);
		fprintf(stderr,"\nWhere:\ttam is the test vector size. Use tam<0 for defaults testes\n");
		fprintf(stderr,"\tx3 runs experiment 3. Without it runs experiments 1 and 2\n");
		fprintf(stderr,"\tAlg is the algorithm name. These's the disponible ones:\n");
		for( i=0 ; AlgNames[i].name ; ++i )
			fprintf(stderr,"\t\t%s\n",AlgNames[i].name);
		fputs("\n",stderr);
	}
	
	if(status==-3)
		fprintf(stderr,"The argument \"-t value\" is bounden\nCall %s with no arguments to see usage\n",appName);
}

int main(int argc, char *argv[])
{
	int i,c;
	static int x3=0;
	SortFuncPtr algo;
	static int tam[] = {0,0};

	static struct option const long_options[] =
	{
		{"x3", no_argument, &x3, 1},
		{"help", no_argument, 0, 'h'},
		{NULL, 0, NULL, 0}
	};
	
	appName = argv[0];


	if(argc<=1)
	{
		usage(0);
		return 0;
	}

	int optIndex = 0;	
	while ( (c=getopt_long(argc, argv,"a:t:h",long_options, &optIndex)) != -1)
		switch(c)
		{
			case 't':
				*tam = atoi(optarg);
				break;

			case 'a':
				for(i=0;AlgNames[i].name;++i)
					if(!(strcmp(optarg,AlgNames[i].name)))
					{
						algo = AlgNames[i].algo;
						break;
					}
				break;
			
			case 'h':
				usage(0);
				return 0;

/* Esse case '?' eu tirei de um ultilitario GNU */
			case '?':
				if (optopt == 'a' || optopt == 't')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr,"Unknown option character `\\x%x'.\n", optopt);
				return -2;
		}

	if(!*tam)
	{
		usage(-3);
		return -3;
	}

	if(x3)
	{
		if(*tam<0) *tam = 500;
		experimento(tamVet, hipoFill, hipoComp);
	}
	else
	{
		if(*tam<0) tem = NULL;
		experimento( 
	}
	




	return 0;
}


void intRandFill(void *v, size_t num)
{
	register int i;
	int vet* = (int*)v;

	for(i=0; i<num ; ++i)
		vet[i]= rand();
}

void intOrdFill(void *v, size_t num)
{
	register int i;
	int vet* = (int*)v;

	for(i=0; i<num ; ++i)
		vet[i]= i;
}

void hipoFill(void *v, size_t num)
{
	register int i;
	int vet* = (struct hipo*)v;

	for(i=0; i<num ; ++i)
		vet[i].chave = rand();
}

void ex1()
{
	return experimento(NULL, intRandFill, intComp);
}

int  ex2()
{
	return experimento(NULL, IntOrdFill, intComp);
}

int ex3()
{
	static int tamVet[] = {500,0};
	
}

/*
Arg1: Vetor com tamnhos dos testes a ser realizado. Termina com 0. Null usa vetor padrão
Arg2: Ponteiro de função que preenche os vetores
Arg3: Ponteiro para a função que compara 2 elementos do vetor

*/
int experimento(const int *tamVet,void(*fill)(void*) ,int(*comp)(const void*,const void*))
{
	static int DefaultTamVet[] = {5000,10000,20000,40000,0};
	

	if(!tamVet) tamVet = DefaultTamVet;


/*
int main(int argc, char** argv){
    void preenche(){
        size = type = 0;
        alg = -1;
        ptalgs[0] = selectionsort;
        ptalgs[1] = insertionsort;
        ptalgs[2] = insertionSent;
        ptalgs[3] = bolhaS;
        ptalgs[4] = bolhaCPA;
        ptalgs[5] = shellsort;
        ptalgs[6] = quick;
        analisa(argc, argv);
    }
    if ( argc == 1 ){
        printf("Usage: %s [-a <alg>] -t <tam> [-x3]\n",argv[0]);
        printf("Where 'a' is a number that represents one of these algorithms (all of them 'll be executed if you do not wants to specify):\n");
        printf(" 0 for SELECTION SORT\n 1 for INSERTION SORT\n 2 for INSERTION SORT (with Sentinel)\n 3 for BUBBLE SORT\n");
        printf(" 4 for BUBBLE SORT (early stopping)\n 5 for SHELL SORT\n 6 for QUICK SORT\n");
        return 1;
    }
    preenche();
    int i;
    if ( type == 1 ){
        typedef hp Item;
    }
    if ( alg == (-1) ){
        Item **vet = (Item**) calloc(8,sizeof(Item*));
        if ( vet == NULL ){
            printf("Memória cheia.\n");
            free(vet);
            return 1;
        }
        for ( i = 0; i < 8; ++i) vet[i] = (Item*) gerarandomico();
        printf("Antes:\n");
        for( i = 0; i < 7; ++i){
            printKeys(vet[i],size);
        }
        printf("\nDepois:\n");
        if ( !( vet == NULL ) ){
            ptalgs[0]((Item)vet[0], 0, size-1, (int)p);
            ptalgs[1]((Item)vet[1], 0, size-1, (int)p);
            ptalgs[2]((Item)vet[2], 0, size-1, (int)p);
            ptalgs[3]((Item)vet[3], 0, size-1, (int)p);
            ptalgs[4]((Item)vet[4], 0, size-1, (int)p);//bolhaCPA
            ptalgs[5]((Item)vet[5], 0, size-1, (int)p);
            ptalgs[6]((Item)vet[6], 0, size-1, (int)p);//quick
            for( i = 0; i < 7; ++i){
                printKeys(vet[i],size);
                free(vet[i]);
            }
            printf("The End.\n");
            free(vet);
            return 0;
        }
    }
    if ( alg > 6 ){
        printf("Digitou um numero incorreto para o algoritmo.\n");
        return 1;
    }
    Item *v = (Item*) malloc(sizeof(Item));
    if ( v == NULL ){
        printf("Memória cheia.\n");
        free(v);
        return 1;
    }
    v = (Item*) gerarandomico();
    printf("Antes:\n");
    printKeys(v,size);
    ptalgs[alg]((Item)v, 0, size-1, (int)p);
    printf("\nDepois:\n");
    printKeys(v,size);
    return 1;
}

*/
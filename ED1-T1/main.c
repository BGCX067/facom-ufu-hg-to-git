#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "algoritmos.h"
#include "err.h"

int type, size, alg;

void (*ptalgs[8])(Item, int, int, int);

int (*p)(Item, Item);

void err(int errCode, char file[], int line)
{
	fprintf(strerr,"\n\nError: %s[%s:%i]\n\n",errStrings[errCode],file,line);
	exit(errCode);
}

struct algoritimo {
	int(*func)(void *base, size_t num, size_t size, int(*comp)(const void*,const void*)),
	char name[50],
	char description[0x200]
} Algs[] = 
{
	{qsort, "QuickSort LIBC","LIBC implementation of QuickSort"},
	{NULL, NULL, NULL}
};


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
}


int main(int argc, char *argv[])
{
	
}


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


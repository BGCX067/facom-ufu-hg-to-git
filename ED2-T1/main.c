/* Copyright (C) 1988, 1990-1991, 1995-2010 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <sys/time.h>

#include "err.h"
#include "algoritmos.h"


void intRandFill(void *v, size_t num);
void intOrdFill(void *v, size_t num);
void hipoFill(void *v, size_t num);


typedef void(*SortFuncPtr)(void*,size_t,size_t,int(*)(const void*,const void*));


char *appName;
FILE *out;



char *errStrings[]=
{
	"Sucess",			/*  0 */
	"Unknow error",		/* -1 */
	"Generic error",	/* -2 */
	"Memory allocation error", /* -3 */
	"Ordenation function fails", /* -4 */
	"Pointer to a function not know", /* -5 */
	NULL
};

struct hipo
{
  int chave;
  int resto[100000]; // 100 mil posições
};


struct Algoritmos {
	SortFuncPtr func;
	char *name;
	char *description;
} AlgsGlobal[] = 
	{
		{qsort, "QuickSort LIBC", "LIBC(bult-in) implementation of QuickSort"},
		{selectionsort, "SelectionSort", "Generic SelectionSort implementation"},
		{insertionsort, "InsertionSort", "Generic InsertionSort implementation"},
		{insertionSent, "InsertionSort with Sentinel", "Generic InsertionSort implementation (with Sentinel)"},
		{bolhaS, "BubbleSort", "Generic BubbleSort implementation"},
		{bolhaCPA, "BubbleSort with early stop", "Generic BubbleSort implementation (with early stop)"},
    	{shellsort, "ShellSort", "Generic ShellSort implementation"},
    	{quicksortRecursive,"Quick Sort Recursive","QuickSort Recursive (Generic)"},
    	{stacksort,"StackSort","Stacksort algorithm (Generic)"},
		{NULL, NULL, NULL}
	};


/* Nomes de algoritmo para argumento do programa */
struct algoNames {
	char *name;
	SortFuncPtr algo;
} AlgNames [] = 
	{
		{"qsort",qsort},
		{"quicksortclib",qsort},
		{"insert", insertionsort},
		{"insertS", insertionSent},
		{"selec", selectionsort},
		{"bubble", bolhaS},
		{"bubbleCPA", bolhaCPA},
    	{"shell", shellsort},
    	{"quicksort", quicksortRecursive},
    	{"stack",stacksort},
		{NULL, NULL}
	};


struct fillFuncs {
	void (*fillFunc)(void*,size_t);
	char *name;
} fillFuncNames[] = 
{
	{intRandFill, "Inteiros Aleatorios"},
	{intOrdFill, "Inteiros Ordenados"},
	{hipoFill, "Estrutura hipo (chaves Aleatorias)"},
	{NULL, NULL}
};

////////////////////////////////////////////////////////////////////////

void err(int errCode, char file[], int line)
{
	fprintf(stderr,"\n\nError: %s[%s:%i]\n\n",errStrings[abs(errCode)],file,line);
	exit(errCode);
}

int intComp(const int *i1, const int *i2)
{
	return *i1-*i2;
}

int hipoComp(const struct hipo *s1, const struct hipo *s2)
{
	return s1->chave - s2->chave;
}

void intRandFill(void *v, size_t num)
{
	register int i;
	int *vet = (int*)v;

	for(i=0; i<num ; ++i)
		vet[i]= rand();
}

void intOrdFill(void *v, size_t num)
{
	register int i;
	int *vet = (int*)v;

	for(i=0; i<num ; ++i)
		vet[i]= i;
}

void hipoFill(void *v, size_t num)
{
	register int i;
	struct hipo *vet = (struct hipo*)v;

	for(i=0; i<num ; ++i)
		vet[i].chave = rand();
}

void printElemInt(const int *e)
{
	printf("%i\n",*e);
}

void printElemHipo(const struct hipo *e)
{
	printf("%i\n",e->chave);
}

/*
Arg1: int com tamnho dos teste a ser realizado.
Arg2: int com tamanho de cada elemento do vetor.
Arg3: Ponteiro de função que preenche os vetores
Arg4: Ponteiro para função q imprime o elemento
Arg5: Ponteiro para a função que compara 2 elementos do vetor
Arg6: Vetor da struct algoritmos com as função de ordenação a serem usadas. Termina com NULLs
*/
int experimento(const int tamVet, const int size, void(*fill)(void*,size_t), void(*printElem)(const void*), int(*comp)(const void*,const void*), struct Algoritmos Algs[])
{
	int i;
	register int k;
	struct timeval t1,t2;
	char * vet[3];
	void *p;

	/* vet[0] : vetor original */
	if(!(vet[0] = malloc(tamVet * size * 3)))
		err(ERR_ALLOC,__FILE__,__LINE__);

	vet[1] = vet[0] + size*tamVet; /*Vetor para ordenar */
	vet[2] = vet[1] + size*tamVet; /*Vetor para conferir ordenacao */

	fill(vet[0], tamVet);

	puts("Before:");
	for( k=0,p=vet[0] ; k<20 && k<tamVet ; ++k , p = vet[0]+(k*size) )
		printElem(p);
	puts("\n");

	for( k=0 ; fillFuncNames[k].name ; ++k )
		if(fillFuncNames[k].fillFunc == fill)
			break;
	if(!fillFuncNames[k].name)
		err(ERR_UNKNOWFUNCTION,__FILE__,__LINE__);


	fprintf(out, "TipoDeDado: \"%s\"\tSize: %i\tTamVet: %i\n", fillFuncNames[k].name, size, tamVet);
	fprintf(out, "Algoritmo\tTempoSeg\tTempouseg\n");
	for( i=0 ; Algs[i].func ; ++i )
	{
		memcpy(vet[1], vet[0], tamVet * size);
	
		
	
		gettimeofday(&t1, NULL);
		Algs[i].func(vet[1], tamVet, size, comp);
		gettimeofday(&t2, NULL);


		printf("Afer (%s):\n",Algs[i].name);
		for( k=0,p=vet[1] ; k<20 && k<tamVet ; ++k , p = vet[1]+(k*size) )
			printElem(p);
		puts("\n");

		/* Verifica se a função fez tudo certo */
		memcpy(vet[2], vet[1], tamVet * size);
		qsort(vet[2], tamVet, size, comp);
		for( k=0 ; k <tamVet * size ; ++k)
			if(vet[1][k] != vet[2][k])
				err(ERR_ORDFUNC,__FILE__,__LINE__);
				/* |->Função com erros */

		fprintf(out,"%s\t%li\t%li\n",Algs[i].name, t2.tv_sec - t1.tv_sec, t2.tv_usec - t1.tv_usec);
		
	}

	fputs("\n",out);
	free(vet[0]);
	
}






void usage (int status)
{
	int i;

	if(!status)
	{
		fprintf(stderr,"Usage: %s [-a alg] -t tam [-xn]\n", appName);
		fprintf(stderr,"\nWhere:\t-t tam\tThe test vector size. Use tam<0 for defaults vector testes\n");
		fprintf(stderr,"-s --seed\tThe seed for srand. seed<0 will take the time. Dafualt is 0\n");
		fprintf(stderr,"\t-xn\tRuns experiment n. Without it runs experiments 1 and 2\n");
		fprintf(stderr,"\t-aAlg\tAlg is the algorithm name. These's the disponible ones:\n");
		for( i=0 ; AlgNames[i].name ; ++i )
			fprintf(stderr,"\t\t%s\n",AlgNames[i].name);
		fputs("\n",stderr);
	}
	
	if(status == -3)
		fprintf(stderr,"The argument \"-t value\" is bounden\nCall %s with no arguments to see usage\n",appName);
}





int main(int argc, char *argv[])
{
	int i,j,c;
	static int tam=0, x3=0, seed=0;
	static int DefaultTamVet[] = {5000,10000,20000,40000,0};
	static struct timeval tod;
	static struct Algoritmos *Algs, Alg[] = {{NULL, NULL, NULL}, {NULL, NULL, NULL}};

	static struct option const long_options[] =
	{
		{"x3", no_argument, &x3, 1},
		{"help", no_argument, 0, 'h'},
		{"seed", required_argument, 0, 's'},
		{NULL, 0, NULL, 0}
	};



	appName = argv[0];
	out = stderr;


	if(argc<=1)
	{
		usage(0);
		return 0;
	}

	int optIndex = 0;	
	while ( (c=getopt_long(argc, argv,"a:t:S:hx:",long_options, &optIndex)) != -1)
		switch(c)
		{
			case 't':
				tam = atoi(optarg);
				break;

			case 'a':
				for(i=0 ; AlgNames[i].name ; ++i)
					if(!(strcmp(optarg,AlgNames[i].name)))
					{
						for( j=0 ; AlgsGlobal[j].func ; ++j )

							if(AlgsGlobal[j].func == AlgNames[i].algo)
							{
								Alg[0].func = AlgsGlobal[j].func;
								Alg[0].name = AlgsGlobal[j].name;
								Alg[0].description = AlgsGlobal[j].description;
								break;
							}
						if(!AlgsGlobal[j].func)
							err(ERR_UNKNOWFUNCTION,__FILE__,__LINE__);
						break;
					}
				if(!AlgNames[i].name)
					err(ERR_UNKNOWFUNCTION,__FILE__,__LINE__);
				break;

			case 's':
				seed = atoi(optarg);
				if(seed < 0 )
				{
					gettimeofday(&tod,NULL);
					seed = tod.tv_usec;
				}
				break;

			case 'x':
				x3 = 1;
				break;
			
			case 'h':
				usage(0);
				return 0;

/* Esse case '?' eu tirei de um ultilitario GNU */
			case '?':
				if (optopt == 'a' || optopt == 't' || optopt == 's')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr,"Unknown option character `\\x%x'.\n", optopt);
				return -2;
		}

	if(!tam)
	{
		usage(-3);
		return -3;
	}

	if(Alg[0].func)
		Algs = Alg;
	else
		Algs = AlgsGlobal;

	srand(seed);





	if(x3)
	{
		if(tam<=0) tam = 500;
		experimento(tam, sizeof(struct hipo), hipoFill, (void(*)(const void*))printElemHipo, (int(*)(const void*,const void*))hipoComp, Algs);
	}
	else
	{
		if(tam>0)
		{
			DefaultTamVet[0] = tam;
			DefaultTamVet[1] = 0;
		}
		for( i=0 ; DefaultTamVet[i] ; ++i )
		{
			experimento(DefaultTamVet[i], sizeof(int), intRandFill, (void(*)(const void*))printElemInt, (int(*)(const void*,const void*))intComp, Algs);
			experimento(DefaultTamVet[i], sizeof(int), intOrdFill, (void(*)(const void*))printElemInt, (int(*)(const void*,const void*))intComp, Algs);
		}
	}
	

	return 0;
}

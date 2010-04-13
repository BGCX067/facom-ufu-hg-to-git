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
//#include "algoritmos.h"


void intRandFill(void *v, size_t num);
void intOrdFill(void *v, size_t num);
void hipoFill(void *v, size_t num);


typedef void(*SortFuncPtr)(void*,size_t,size_t,int(*)(const void*,const void*));


char *appName;
FILE *out;





struct hipo
{
  int chave;
  int resto[100000]; // 100 mil posições
};


struct Algoritimos {
	SortFuncPtr func;
	char *name;
	char *description;
} AlgsGlobal[] = 
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






int intComp(const int *i1, const int *i2)
{
	return *i2-*i1;
}

int hipoComp(const struct hipo *s1, const struct hipo *s2)
{
	return s2->chave - s1->chave;
}

void err(int errCode, char file[], int line)
{
	fprintf(stderr,"\n\nError: %s[%s:%i]\n\n",errStrings[errCode],file,line);
	exit(errCode);
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



/*
Arg1: int com tamnho dos teste a ser realizado.
Arg2: int com tamanho de cada elemento do vetor.
Arg3: Ponteiro de função que preenche os vetores
Arg4: Ponteiro para a função que compara 2 elementos do vetor
Arg5: Vetor da struct algoritimos com as função de ordenação a serem usadas. Termina com NULLs
*/
int experimento(const int tamVet, const int size, void(*fill)(void*,size_t), int(*comp)(const void*,const void*), struct Algoritimos Algs[])
{
	int i;
	register int k;
	struct timeval t1,t2;
	char * vet[3];

	/* vet[0] : vetor original */
	if(!(vet[0] = malloc(tamVet * size * 3)))
		err(ERR_ALLOC,__FILE__,__LINE__);

	vet[1] = vet[0] + size*tamVet; /*Vetor para ordenar */
	vet[2] = vet[1] + size*tamVet; /*Vetor para conferir ordenacao */

	fill(vet[0], tamVet);

	for( k=0 ; fillFuncNames[k].name ; ++k )
		if(fillFuncNames[k].fillFunc == fill)
			break;
	if(!fillFuncNames[k].name)
		err(ERR_UNKNOWFUNCTION,__FILE__,__LINE__);


	fprintf(out, "TipoDeDado: \"%s\"\tSize: %i\tTamVet: %i\n", fillFuncNames[k].name, size, tamVet);
	fprintf(out, "Algoritimo\tTempoSeg\tTempouseg\n");
	for( i=0 ; Algs[i].func ; ++i )
	{
		memcpy(vet[1], vet[0], tamVet * size);
	
		gettimeofday(&t1, NULL);
		Algs[i].func(vet[1], tamVet, size, comp);
		gettimeofday(&t2, NULL);

		/* Verifica se a função fez tudo certo */
		memcpy(vet[2], vet[1], tamVet * size);
		qsort(vet[3], tamVet, size, comp);
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
		fprintf(stderr,"Usage: %s [-a alg] -t tam [-x3]\n", appName);
		fprintf(stderr,"\nWhere:\ttam is the test vector size. Use tam<0 for defaults testes\n");
		fprintf(stderr,"\tx3 runs experiment 3. Without it runs experiments 1 and 2\n");
		fprintf(stderr,"\tAlg is the algorithm name. These's the disponible ones:\n");
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
	SortFuncPtr algo;
	static int DefaultTamVet[] = {5000,10000,20000,40000,0};
	static struct timeval tod;
	static struct Algoritimos *Algs = {{NULL, NULL, NULL}, {NULL, NULL, NULL}};

	static struct option const long_options[] =
	{
		{"x3", no_argument, &x3, 1},
		{"help", no_argument, 0, 'h'},
		{"seed", required_argument, 0, 's'},
		{NULL, 0, NULL, 0}
	};



	appName = argv[0];
	out = stdout;


	if(argc<=1)
	{
		usage(0);
		return 0;
	}

	int optIndex = 0;	
	while ( (c=getopt_long(argc, argv,"a:t:S:hx::",long_options, &optIndex)) != -1)
		switch(c)
		{
			case 't':
				tam = atoi(optarg);
				break;

			case 'a':
				for(i=0 ; AlgNames[i].name ; ++i)
					if(!(strcmp(optarg,AlgNames[i].name)))
					{
					
						algo = AlgNames[i].algo;
						for( j=0 ; AlgsGlobal[j].func ; ++j )

							if(AlgsGlobal[j].func == AlgNames[i].algo)
							{
								Algs[0].func = AlgsGlobal[j].func;
								Algs[0].name = AlgsGlobal[j].name;
								Algs[0].description = AlgsGlobal[j].description;
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

	if(!Algs[0].func)
		Algs = AlgsGlobal;

	srand(seed);





	if(x3)
	{
	puts("alksjdlasjdkll");
		if(tam<=0) tam = 500;
		experimento(tam, sizeof(struct hipo), hipoFill, hipoComp, Algs);
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
			experimento(DefaultTamVet[i], sizeof(int), intRandFill, intComp, Algs);
			experimento(DefaultTamVet[i], sizeof(int), intOrdFill, intComp, Algs);
		}
	}
	

	return 0;
}

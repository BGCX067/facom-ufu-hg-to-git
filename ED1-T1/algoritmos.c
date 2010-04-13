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

#include <stdlib.h>
#include <string.h>
#include "algoritmos.h"
#include "err.h"
//#include "pilha.h"


void swap(void * e1, void *e2, size_t size)
{
	void *aux;
	
	if(!(aux=malloc(size)))
		err(ERR_ALLOC,__FILE__,__LINE__);

	memcpy(aux,e1,size);
	memcpy(e1,e2,size);
	memcpy(e2,aux,size);
}


void selectionsort(void *base, size_t num, size_t size, int(*less)(const void*,const void*))
{
    size_t a, b, pos;
    void *menor = malloc(size);
    for ( a = 0; a < num*size; a+=size)
    {
        memcpy(menor,(base+a),size);
        b = pos = a + size;
        while ( b < num*size )
        {
            if ( less(base+b,menor) < 0 )
            {
                memcpy(menor,base+b,size);
                pos = b;
            }
            b += size;
        }
        if ( memcmp(menor,base+a,size) < 0 )
            swap(base+a,base+pos,size);
    }
}

void insertionsort(void *base, size_t num, size_t size, int (*less)(const void*, const void*))
{
    size_t i, k;
    void *index = malloc(size);
	for ( i = 0; i < num*size; i+=size)
	{
		k = i;
		memcpy(index,base+i,size);
		while( ( k != 0 ) && ( less(base+(k-size),index) > 0 ) )
		{
			memcpy(base+k,base+(k-size),size);
			k-=size;
		}
		memcpy(base+k,index,size);
	}
}

void insertionSent(void *base, size_t num, size_t size, int (*less)(const void*, const void*))
{
	size_t i, k;
	void *index = malloc(size);
	for (i = size*(num-1); 0 > i; i-=size)
	{
		if ( memcmp(base+i,base+(i-size),size) == 0 )
		    swap(base+i,base+(i-size),size);
	}
	for ( i = 0; i < num*size; i+=size)
	{
		k = i;
		memcpy(index,base+i,size);
		while( ( k != 0 ) && ( less(base+(k-size),index) > 0 ) )
		{
			memcpy(base+k,base+(k-size),size);
			k-=size;
		}
		memcpy(base+k,index,size);
	}
}

void bolhasort(void *base, size_t num, size_t size, int(*comp)(const void*,const void*))
{
	register int i, j;


	for (i = 0; i <= num; ++i)
		for (j = i+1; j<= num; ++j)
			if ( !comp(base+(j-1)*size,base+j*size) )
				swap(base+(j-1)*size,base+j*size);
}

void bolhaCPA(void *base, size_t num, size_t size, int (*less)(const void*, const void*))
{
    int troca;
	size_t i, j;
	for (i = 0, troca = 0; i < size*num; i+=size)
	{
		for (j = size; j< num*size; j+=size){
			if ( less(base+(j-size),base+j) > 0 )
			{
       		    swap(base+(j-size),base+j,size);
                troca = 1;
			}
		}
		if (troca == 0) break;
	}
}

void shellsort(void *base, size_t num, size_t size, int (*less)(const void*, const void*))
{
    int h;
    size_t i,j;
    void *v = malloc(size);
    for( h = 1; h < (num*size)/9; h = (3*h) + 1);
    for( ; h > 0; h /= 3)
        for ( i = h*size; i < num*size; i+=size)
        {
            j = i;
            memcpy(v,base+i,size);
            while( (j >= h*size) && (less(v, base+(j-(h*size))) < 0))
            {
                memcpy(base+j,base+(j-(h*size)),size);
                j -= (h*size);
            }
            memcpy(base+j,v,size);
        }
}

/*void stacksort(int *vet, int tam, int (*less)(int,int)){
    int a, b, pos;
    int menor;
    pilha p;
    start(&p);
    for (a = 0; a < tam - 1; ++a){
        menor = vet[a];
        b = a + 1;
        while ( b < tam ){
            if ( less(vet[b],menor) ){
                if ( vet[a] != menor )
                    push(&p, menor, pos);
                menor = vet[b];
                pos = b;
            }
            b++;
        }
        if ( menor != vet[a] ){
            int temp = vet[a];
            vet[a] = menor;
            vet[pos] = temp;
        }
    }
}*/

int partition(void *base, size_t num, size_t size, int(*comp)(const void*,const void*))
{
    int i = l - 1;
    int j = r;
    Item v = a[r];
    for( ; ; ){
        while( less(a[++i], v) );
        while( less(v, a[--j]) )
            if ( j == l ) break;
        if ( i >= j ) break;
        Item c = a[i];
        a[i] = a[j];
        a[j] = c;
    }
    Item c = a[i];
    a[i] = a[r];
    a[r] = c;
    return i;
}


void quicksortRecursive(void *base, size_t num, size_t size, int(*comp)(const void*,const void*))
{
    int i;

    if ( num > 1 ) {
        i = partition(base,num,size,comp);
        quicksortRecursive(base,i-1,size,comp);
        quicksortRecursive(base+i*size,num-i-1,size,comp);
    }
}


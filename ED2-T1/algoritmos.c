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
#include "pilha.h"


void swap(void * e1, void *e2, size_t size)
{
	void *aux;
	
	if(!(aux=malloc(size)))
		err(ERR_ALLOC,__FILE__,__LINE__);

	memcpy(aux,e1,size);
	memcpy(e1,e2,size);
	memcpy(e2,aux,size);
	free(aux);
}

void selectionsort(void *base, size_t num, size_t size, int(*less)(const void*,const void*))
{
    size_t a, b, pos;
    void *menor;
    if( !(menor=malloc(size)) )
		err(ERR_ALLOC,__FILE__,__LINE__);
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
        if ( less(menor,base+a) < 0 )
            swap(base+a,base+pos,size);
    }
   	free(menor);
}

void stacksort(void *base, size_t num, size_t size, int (*less)(const void*, const void*))
{
    size_t a, b, pos;
    void *menor;
    if( !(menor=malloc(size)) )
		err(ERR_ALLOC,__FILE__,__LINE__);
    pilha p;
    start(&p);
    for (a = 0; a < num*size; a+=size)
    {
        memcpy(menor,(base+a),size);
        b = pos = a + size;
        while ( b < num*size )
        {
            if ( less(base+b,menor) < 0 ){
                if ( !(less(base+a, menor) == 0) )
                    push(&p, menor, size, (pos/size));
                memcpy(menor,base+b,size);
                pos = b;
            }
            b+=size;
        }
        if ( less(menor,base+a) < 0 )
            swap(base+a,base+pos,size);
    }
}

void insertionsort(void *base, size_t num, size_t size, int (*less)(const void*, const void*))
{
    size_t i, k;
    void *index;
    if ( !(index = malloc(size) ) )
        err(ERR_ALLOC,__FILE__,__LINE__);
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
	free(index);
}

void insertionSent(void *base, size_t num, size_t size, int (*less)(const void*, const void*))
{
	size_t i, k;
	void *index;
	if ( !(index = malloc(size) ) )
        err(ERR_ALLOC,__FILE__,__LINE__);
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
	free(index);
}

void bolhaS(void *base, size_t num, size_t size, int(*less)(const void*,const void*))
{
	size_t i, j;
	for (i = 0; i < num*size; i+=size)
		for (j = size; j< num*size; j+=size)
			if ( less(base+(j-size),base+j) > 0 )
				swap(base+(j-size),base+j,size);
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
    void *v;
    if ( !(v = malloc(size) ) )
        err(ERR_ALLOC,__FILE__,__LINE__);
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
    free(v);
}

int partition(void *base, size_t num, size_t size, int(*less)(const void*,const void*))
{
    int i = -1;
    int j = (int)num-1;
    void *v;
    if ( !( v = malloc(size) ))
        err(ERR_ALLOC, __FILE__, __LINE__);
    memcpy(v,base+((num-1)*size),size);
    for( ; ; ){
        while( less(base+((++i)*size), v) );
        while( less(v, base+((--j)*size)) )
            if ( j == 0 ) break;
        if ( i >= j ) break;
        swap(base+(i*size),base+(j*size),size);
    }
    swap(base+(i*size),base+((num-1)*size),size);
    free(v);
    return i;
}


void quicksortRecursive(void *base, size_t num, size_t size, int(*less)(const void*,const void*))
{
    int i;
    if ( num > 1 ) {
        i = partition(base,num,size,less);
        quicksortRecursive(base,i-1,size,less);
        quicksortRecursive(base+i*size,num-i-1,size,less);
    }
}

/*
int partition(void *base, size_t num, size_t size, int(*less)(const void*,const void*))
int partition(Item a[], int l, int r)
{
	int i = l-1, j = r;
	void *v;
	
	if(!(v=malloc(size)))
		err(ERR_ALLOC,__FILE__,__LINE__);

	memcpy(v, base+(num-1)*size, size);
	for (;;)
	{
		for()
		while (less(a[++i], v)) ;

		while (less(v, a[--j])) if (j == l) break;
		if (i >= j) break;
		exch(a[i], a[j]);
	}
	exch(a[i], a[r]);
	return i;
}

void quicksortRecursive(void *base, size_t num, size_t size, int(*less)(const void*,const void*))
void quicksort(Item a[], int l, int r)
{
	int i;

	if (num <= 0) return;
	i = partition(base, num, size, less);
	quicksort(a, l, i-1);
	quicksort(a, i+1, r);
}

*/

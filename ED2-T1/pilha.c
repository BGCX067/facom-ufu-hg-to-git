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
#include "pilha.h"

void start(pilha *p)
{
	p->topo = MAX;
}

int isEmpty(pilha *p)
{
	if ( p->topo == MAX )
		return 1;
	return 0;
}

int isFull(pilha *p)
{
	if( p->topo == (-1) )
		return 1;
    return 0;
}

int push(pilha *p, int e1, int e2)
{
	if ( isFull(p) )
		return 0;
	else
	{	
		p->topo--;
		p->vet[p->topo][0] = e1;
		p->vet[p->topo][1] = e2;
		return 1;
	}
}

int pop(pilha *p, int *e1, int *e2)
{
	if( isEmpty(p) )
		return 0;
	else
	{
		*e1 = p->vet[p->topo][0];
    	*e2 = p->vet[p->topo][1];
		p->topo++;
		return 1;
	}
}

int peek(pilha *p, int *e1, int *e2)
{
	if( isEmpty(p) )
		return 0;
	else
	{
		*e1 = p->vet[p->topo][0];
    	*e2 = p->vet[p->topo][1];
		return 1;
	}
}

void print(pilha *p)
{
	int i = p->topo;
	printf("[ ");
	for( ; i < MAX; i++)
		printf("(%d ^ %d)| ",p->vet[i][0],p->vet[i][1]);
	printf(" ].\n");
}


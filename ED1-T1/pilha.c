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


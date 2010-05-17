
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
#include "lista.h"

/**** Função crialista(void)
    * Retorna um ponteiro pra uma nova lista.
    */

lista crialista(void)
{
    return NULL;
}

/**** Função vazia(lista p)
    * Verifica se a lista p é ou não vazia, retornando 1 para sim e 0 para nao.
    */

int vazia(lista p)
{
    if ( p == NULL)
        return 1;
    return 0;
}

/**** Função insere(plista list, int dest, char tarefa[], int peso)
    * Dada uma lista, um destino, uma tarefa e um peso, insere na lista um novo elemento que engloba os três últimos,
    * retornando 1 caso for possivel inserir e 0 caso não for possível fazê-lo.
    */

int insere(plista list, int dest, char tarefa[], int peso)
{
    lista p,p1;
    if ( !(p = malloc(sizeof(no))))
        return 0;
    p->dest = dest;
    p->peso = peso;
    p->tarefa = malloc((strlen(tarefa)-1)*sizeof(char));
    if ( strcmp(tarefa,"DUMMY!") )
        memcpy(p->tarefa ,tarefa, strlen(tarefa));
    else
        strcpy(p->tarefa,"DUMMY!");
    p->prox = NULL;
    if ( vazia(*list) )
    {
        *list = p;
    }else
    {
        p1 = *list;
        while( !vazia(p1->prox) )
            p1 = p1->prox;
        p1->prox = p;
    }
    return 1;
}

/**** Função imprime(lista list)
    * Imprime a lista elemento a elemento, onde cada elemento é o conjunto formado pela união de destino, peso e tarefa.
    */

void imprime(lista list)
{
    if ( vazia(list) )
        printf("[]");
    else
    {
        printf("[ ");
        lista p;
        for (p = list; p != NULL; p = p->prox)
            printf("(d: %d,p: %d,t: %s) ",p->dest, p->peso, p->tarefa);
        printf("]");
    }
    printf("\n");
}

/**** Função removeE(plista list, int dest)
    * Dada uma lista e um destino, caso for possível remover o elemento com esse destino, o faz e retorna 1, caso contrário, retorna 0.
    */

int removeE(plista list, int dest)
{
    if ( vazia(*list) ) 
        return 1;
    lista p1 = *list;
    if ( p1->dest == dest )
    {
        *list = p1->prox;
        free(p1);
        return 1;
    }
    while ( (p1->prox != NULL) && (p1->prox->dest != dest) )
        p1 = p1->prox;
    if ( vazia(p1->prox) ) 
        return 0;
    lista p2 = p1->prox;
    p1->prox = p2->prox;
    free(p2);
    return (removeE(&p1,dest));
}

/**** Função getTam(plista l)
    * Dada uma lista, retorna o tamanho da mesma.
    */

int getTam(plista l)
{
    if ( vazia(*l) ) 
        return 0;
    int ct = 0;
    lista p = (*l);
    while( p != NULL )
    {
        ++ct;
        p = p->prox;
    }
    return ct;
}

/**** Função copy(plista p)
    * Dada uma lista, retorna um ponteiro para outra lista que contém os mesmos elementos da primeira (é cópia dela).
    */

lista copy(plista p)
{
    lista p1 = NULL;
    p1 = crialista();
    lista p2 = *p;
    for ( ; p2 != NULL; p2 = p2->prox)
        insere(&p1,p2->dest, p2->tarefa, p2->peso);
    return p1;
}

/**** Função destroy(plista p)
    * Dada uma lista, libera o espaço ocupado pela mesma, desalocando elemento a elemento.
    */

void destroy(plista p)
{
    if ( !vazia(*p))
    {
        lista p1;
        for ( p1 = *p; !vazia(p1); p1 = (*p))
        {
            (*p) = p1->prox;
            free(p1);
        }
    }
}

/**** Função getDest(lista l, char tarefa[])
    * Dada uma lista e uma tarefa, retorna o destino do elemento (aresta) cuja tarefa é igual à de entrada.
    */

int getDest(lista l, char tarefa[])
{
    lista p = l;
    while ( !vazia(p) )
    {
        if ( !strcmp(tarefa,p->tarefa) ) 
            return p->dest;
        p = p->prox;
    }
    return 0;
}

/**** Função getPeso(lista l, int v)
    * Dada uma lista l e um destino v, retorna o peso do elemento (aresta) cuja destino é igual ao de entrada.
    */

int getPeso(lista l, int v)
{
    lista p = l;
    while( !vazia(p) )
    {
        if ( p->dest == v ) 
            return p->peso;
        p = p->prox;
    }
    return -1;
}



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
   
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "pilha.h"

/**** Função start(pilha *p)
    * Dada um ponteiro de uma pilha, inicia-a com o valor default.
    */

void start(pilha *p)
{
    *p = NULL;
}

/**** Função empty(pilha *p)
    * Verifica se a pilha passada como argumento é vazia, retornando 1 para sim e 0 para não.
    */

int empty(pilha *p)
{
    return ( *p == NULL )?1:0;
}

/**** Função push(pilha *p, int e)
    * Verifica se é possível inserir na pilha e faz-o com o parâmetro e, retornando 1 para sim, ou não o faz, caso nao for possível, retornando 0.
    */

int push(pilha *p, int e)
{
    pilha p1 = malloc(sizeof(node));
    if ( p1 == NULL ) return 0;
    p1->prox = *p;
    p1->local = e;
    *p = p1;
    return 1;
}

/**** Função pop(pilha *p, int *e)
    * Verifica se é possível remover da pilha e faz-o com o parâmetro e, retornando 1 para sim, ou não o faz, retornando 0.
    */

int pop(pilha *p, int *e)
{
    if ( empty(p) ) return 0;
    pilha p1 = *p;
    *e = p1->local;
    *p = p1->prox;
    free(p1);
    return 1;
}

/**** Função peek(pilha *p, int *e)
    * Caso tenha elementos na pilha, copia o topo para o elemento de entrada e retorna 1, caso contrário, retorna 0.
    */

int peek(pilha *p, int *e)
{
    if ( empty(p) ) 
        return 0;
    *e = (*p)->local;
    return 1;
}


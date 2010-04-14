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

void start(pilha *p)
{
    *p = NULL;
}

int vazia(pilha *p)
{
    if ( *p == NULL )
        return 1;
    return 0;
}

int cheia(pilha *p)
{
    if ( vazia(p) )
        return 0;
    return 1;
}

int push(pilha *p, void *e, size_t size, int pos)
{
    pilha p1 = malloc(sizeof(no));
    if ( p1 == NULL ) return 0;
    p1->prox = *p;
    p1->local = pos;
    p1->info = malloc(size);
    memcpy( p1->info, e, size);
    *p = p1;
//    if ( size == sizeof(char) ) p1->t = 0;
//    else p1->t = 1;
    return 1;
}

int pop(pilha *p, void *e, size_t size, int *pos){
    if ( vazia(p) ) return 0;
    pilha p1 = *p;
    memcpy( e, (p1->info), size);
    *pos = p1->local;
    *p = p1->prox;
    free(p1);
    return 1;
}

int peek(pilha *p, void *e){
    if ( vazia(p) ) return 0;
    memcpy(e, (*p)->info, sizeof((*p)->info));
    return 1;
}


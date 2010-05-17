
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
#include "pilha.h"

typedef struct edge
{
    int v;
    int w;
    int peso;
} Edge;

typedef struct graph
{
    int V;
    int E;
    plista adj;
}graph, *Graph;

Graph GRAPHinit( int n);

void GRAPHinsertE(Graph g, Edge e, char tarefa[]);

void GRAPHremoveE(Graph g, Edge e);

void GRAPHedges(Edge *a, Graph g);

Graph GRAPHcopy(Graph g);

void GRAPHdestroy(Graph g);

void traverse_d(Graph g, int k, void (*visit)(Graph, int));

void traverse_dr(Graph g, int k);

void visitar(Graph g, int v);

void printAdjacence(Graph g);


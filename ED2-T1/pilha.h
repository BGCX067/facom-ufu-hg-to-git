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

# define MAX 1000000

typedef struct no{
	int topo;
	int vet[MAX][2];
}pilha;

void start(pilha *p);

int isEmpty(pilha *p);

int isFull(pilha *p);

int push(pilha *p, int e1, int e2);

int pop(pilha *p, int *e1, int *e2);

int peek(pilha *p, int *e1, int *e2);

void print(pilha *p);

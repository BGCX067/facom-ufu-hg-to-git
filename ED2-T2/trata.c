
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

#include "trata.h"

/**** Função **separa(char s[], char c)
    * Dada uma string de entrada, representada por char s[], separa-a em strings, de acordo com o caractere de separação c.
    */
    
extern int usados, 
            *visited, 
            *visitados, 
            *critico, 
            tcritico, 
            ct, 
            flags, 
            maximo;

char **separa(char s[], char c)
{
    int i, j, n;
    char **pch, sn[2], *stemp = malloc(strlen(s)*sizeof(char));
    n = count(s,c)+1;
    pch = malloc(n*sizeof(char*));
    strcpy(stemp,s);
    sprintf(sn,"%c",c);
    for ( j = 0; j < n; ++j)
    {
        i = strcspn(stemp,sn) + 1;
        if ( i != 0 )
        {
            pch[j] = malloc(i*sizeof(char));
            memcpy(pch[j],stemp,i-1);
        }else
        {
            pch[j] = malloc(strlen(stemp)*sizeof(char));
            memcpy(pch[j],stemp,strlen(stemp)-1);
        }
        strcat(pch[j],"");
        stemp += i;
    }
    return pch;
}

/**** Função insereDummy(int a, int b, Graph g)
    * Dados dois vértices pertencentes a um grafo e o grafo, insere uma aresta dummy(com peso 0) entre os mesmos.
    */

void insereDummy(int a, int b, Graph g)
{
    Edge e;
    e.v = a;
    e.w = b;
    e.peso = 0;
    GRAPHinsertE(g,e,"DUMMY!");
}

/**** Função analisa(Graph g)
    * Dado um grafo de entrada, procura por vértices que não tem adjacência e insere uma tarefa dummy deste vértice para o vértice de maior número no grafo.
    */

void analisa(Graph g)
{
    int i, j, k;
    i = j = k = 0;
    for ( ; i < g->V; ++i)
    {
        for ( j = i + 1; j < g->V; ++j)
        {
            k = getTam(&g->adj[i]);
            if ( (k == 0 ) && (i != (g->V -1)))
                insereDummy(i,usados,g);
        }
    }
}

/**** Função getTime(char s[], Graph g)
    * Dada precedência de uma tarefa (em s) e um grafo g, encontra e retorna a melhor posição para inserir a aresta no grafo.
    */

int getTime(char s[], Graph g)
{
    if ( strcmp(s,"-") == 0 )
        return 0;
    int i, k, r, n, mx, ot;
    i = k = r = mx = ot = 0;
    n = count(s,',') + 1;
    char **pch = separa(s,',');
    if (n != 1)
    {
    	for ( i = 0; i < n; ++i){
    		for ( r = 0; r < g->V; ++r)
                k = (getDest(g->adj[r],pch[i]) > k)?getDest(g->adj[r],pch[i]):k;
			insereDummy(k,usados+1,g);
    	}
    	usados++;
    	mx = usados;
    }else
    {
        for ( i = 0; i < usados; ++i)
        {
            ot = getDest(g->adj[i], pch[0]);
            mx = (ot>mx)?ot:mx;
        }
    }
    return mx;
}

/**** Função monta(char s[], Graph g)
    * Dada uma atividade e um grafo, encontrar o melhor lugar para inserí-la e efetivamente fazer isso.
    */

void monta(char s[], Graph g)
{
    int i, j, k, l;
    char *pt1, *pt2, *pt3;
    i = j = k = 0;
    i = strcspn(s,";") + 1;
    pt1 = malloc(i*sizeof(char));
    memcpy(pt1,s,i-1);
    pt1[i-1] = '\0';
    s += i;
    j = strcspn(s,";") + 1;
    pt2 = malloc(j*sizeof(char));
    memcpy(pt2,s,j-1);
    pt2[j-1] = '\0';
    s += j;
    k = strcspn(s,";") + 1;
    pt3 = malloc(k*sizeof(char));
    memcpy(pt3,s,k-1);
    pt3[k-1] = '\0';
    s = s - i - j;
    Edge e;
    l = getTime(pt3,g);
    e.v = l;
    e.w = usados+1;
    e.peso = atoi(pt2);
    GRAPHinsertE(g,e,pt1);
    usados++;
    free(pt1);
    free(pt2);
    free(pt3);
}

/**** Função count(char *s, char c)
    * Conta e retorna a quantidade de ocorrências do caractere c na string s.
    */

int count(char *s, char c)
{
    int i, k = 0;
    for ( i = 0; s[i] != '\0'; ++i)
        if ( s[i] == c ) ++k;
    return k;
}

/**** Função recebe(char *s, Graph g)
    * Dada uma lista de atividades e um grafo, separa-a em partes (divididas pelo caractere '\n') e usa do método monta para inserí-las no grafo.
    */

void recebe(char *s, Graph g)
{
    int i, j, n;
    i = j = 0;
    n = count(s,'\n')+1;
    char **vetor = separa(s,'\n');
    for ( i = 0; i < n; ++i)
    {
        monta(vetor[i],g);
        free(vetor[i]);
    }
    g->V = usados+1;
    g->adj = realloc(g->adj,(usados+1)*sizeof(int));
    free(vetor);
    analisa(g);
}


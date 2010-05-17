
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

#define OBJ "Implementacao de grafos direcionados atraves de lista de adjacencias.\n"
#include "grafo.h"

int usados, 
    *visited, 
    *visitados, 
    *critico, 
    tcritico = 0, 
    ct = 0, 
    flags = 0, 
    maximo = 0;

/**** Função GRAPHinit(int n)
    * Cria um grafo, dado um numero de vertices.
    */

Graph GRAPHinit(int n)
{
    Graph g;
    if ( !(g = malloc(sizeof(graph))))
        return NULL;
    g->E = 0;
    g->V = n;
    if ( !(g->adj = malloc(n*sizeof(lista))))
        return NULL;
    return g;
}

/**** Função GRAPHinsertE(Graph g, Edge e, char tarefa[])
    * Insere no grafo recebido a aresta e cujo nome de tarefa também é parâmetro de entrada.
    */

void GRAPHinsertE(Graph g, Edge e, char tarefa[])
{
    insere(&g->adj[e.v],e.w, tarefa, e.peso);
    g->E++;
}

/**** Função GRAPHremoveE(Graph g, Edge e)
    * Remove do grafo recebido a aresta e (caso a mesma exista).
    */

void GRAPHremoveE(Graph g, Edge e)
{
    removeE(&g->adj[e.v],e.w);
    --g->E;
}

/**** Função GRAPHcopy(Graph g)
    * Retorna o endereço do grafo que é cópia do grafo de entrada.
    */

Graph GRAPHcopy(Graph g)
{
    Graph g1;
    if ( !(g1=malloc(sizeof(graph))))
        return NULL;
    if ( !(g1->adj = malloc(g->V*sizeof(plista))))
        return NULL;
    int i;
    for ( i = 0; i < g->V; ++i)
        g1->adj[i] = copy(&g->adj[i]);
    g1->V = g->V;
    g1->E = g->E;
    return g1;
}

/**** Função GRAPHdestroy(Graph g)
    * Remove o conteúdo da memória gasto pelo grafo de entrada, desalocando também as listas que representam as adjacências dos vértices.
    */

void GRAPHdestroy(Graph g)
{
    int i;
    for ( i = 0; i < g->V; ++i)
        destroy(&g->adj[i]);
    free(g->adj);
    free(g);
}

/**** Função printgrafo(Graph g)
    * Imprime o grafo representado pelo vetor de listas de adjacências.
    */

void printgrafo(Graph g)
{
    int i = 0;
    printf("  VERTICES\t[(destino,peso,tarefa)...]\t\t\t     (Vertice 0 representado por INICIO)\n");
    for ( ; i < g->V; ++i)
    {
        if ( i == 0)
            printf("[  INICIO ]\t|-> ");
        else
            printf("[Vertice %d]\t|-> ",i);
        if ( vazia(g->adj[i]))
            printf("FIM\n");
        else
            imprime(g->adj[i]);
    }
}

/**** Função visitou(Graph g, char menos[])
    * Imprime um caminho no grafo.
    */

void visitou(Graph g, char menos[])
{
    printf("%s\nCaminho:\tINICIO",menos);
    int conta, mx,i;
    conta = mx = i = 0;
    for ( i = 1; i < ct; ++i)
        printf(" -> %d",visitados[i]);
    for ( i = 1; i < ct; ++i)
        conta += getPeso(g->adj[visitados[i-1]],visitados[i]);
    printf(" -> FIM\nPeso total: %d\n",conta);
    if ( conta > maximo )
    {
        maximo = conta;
        memcpy(critico,visitados,ct*sizeof(int));
        tcritico = ct;
    }
}

/**** Função traverse_dr(Graph g, int k)
    * Faz a busca em profundidade no grafo g (método recursivo), começando pelo vértice k.
    */

void traverse_dr(Graph g, int k)
{
    char menos[] = "<------------------------------------------------------------------------------------------------------->";
    printf("\033[2J%s\n|\t\t\t\t\t\tGRAFO\t\t\t\t\t\t\t|\n%s\n",menos,menos);//esse printf imprime o caracter '\n' até que, na linha de comando,
    printgrafo(g);                                              /// os dados anteriores sejam apagados
    int i = 0;
    auto void traverse_deep(Graph g, int k,void (*visit)(Graph, char[]))
    {
        lista t;
        visitados[ct++] = k;
        flags = 1;   
        for ( t = g->adj[k]; !vazia(t); t = t->prox)
                traverse_deep(g,t->dest,visit);
        if ( flags )
        {
            (*visit)(g,menos);
            flags = 0;
        }
        --ct;
    }
    visited = calloc(g->V,sizeof(int));
    visitados = calloc(g->V, sizeof(int));
    critico = calloc(g->V,sizeof(int));
    printf("%s\n|\t\t\t\t\tCAMINHOS POSSIVEIS\t\t\t\t\t\t|\n",menos);
    if ( g == NULL )
        printf("Impossivel fazer busca em profundidade em um grafo vazio.\n");
    else
        traverse_deep(g,k,&visitou);
    printf("%s\n\tMenor tempo previsto para conclusao do projeto: %d\n\tCaminho critico: ",menos,maximo);
    for ( ; i < tcritico; ++i)
        printf(" ->%d",critico[i]);
    printf("\n");
}

/**** Função traverse_d(Graph g, int k)
    * Faz a busca em profundidade no grafo g (metodo iterativo), começando pelo vértice k.
    */

void traverse_d(Graph g, int k, void (*visit)(Graph, int))
{
    printf("Fazendo busca em profundidade no grafo (metodo iterativo), a partir do vertice %d.\n",k);
    printgrafo(g);
    auto void traverse_deep(Graph g, int k, void (*visit)(Graph, int))
    {
        int i;
        pilha p;
        lista t;
        start(&p);
        push(&p,k);
        while( !empty(&p) )
        {
            pop(&p,&i);
            if ( !visited[i] )
            {
                visit(g,i);
                visited[i] = 1;
                for ( t = g->adj[i]; !vazia(t); t = t->prox)
                    if (!visited[t->dest])
                        push(&p,t->dest);
            }
        }
    }
    visited = calloc(g->V,sizeof(int));
    if ( g == NULL )
        printf("Impossivel fazer busca em profundidade em um grafo vazio.\n");
    else
        traverse_deep(g,k,visit);
}

/**** Função visitar(Graph g, int v)
    * Imprime o número de vértices adjacentes ao vértice v no grafo g.
    */

void visitar(Graph g, int v)
{
    printf("O vertice %d tem %d vertices adjacentes.\n",v,getTam(&(g->adj[v])));
}

/**** Função printAdjacence(Graph g)
    * Imprime todas as adjacências dos vértices do grafo g.
    */

void printAdjacence(Graph g)
{
    int i = 0;
    for ( ; i < g->V; ++i)
    {
        printf("Vertice: %d ",i);
        imprime(g->adj[i]);
    }
}



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
#include "trata.h"

/**** Função *ledarquivo(char s[])
    * Dado um arquivo de entrada, caso for possível lê-lo, retorna um ponteiro que é um vetor contendo os caracteres do arquivo. 
    * Caso contrário, imprime mensagens de erro e finaliza a execução do programa.
    */

char *ledarquivo(char s[])
{
    FILE * pFile;
    int lSize,j, i;
    i = j = 0;
    char *buffer,b;
    pFile = fopen ( s , "r+" );
    if (pFile==NULL) 
    {
	    fprintf(stderr,"File error.\n");
	    exit (1);
    }
    fseek (pFile , 0 , SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);
    buffer = (char*) malloc (sizeof(char)*2*lSize);
    while( fscanf(pFile, " %c",&b) != EOF)
    {
        buffer[i] = b;
        ++i;
        if ( b == ';')
        {
            ++j;
            if ( j == 3 )
            {
                j = 0;
                buffer[i] = '\n';
                ++i;
            }
        }
    }
    buffer[lSize-1] = '\0';
    return (buffer);
}

/**** Função menu(char s[])
    * Dado os caracteres de um arquivo de entrada, monta um grafo de atividades e calcula caminho crítico e tempo total do projeto por ele representado.
    */

void menu(char s[])
{
    int num;
    num = count(s,'\n')+1;
    Graph g = GRAPHinit(num+1);
    recebe(s,g);
    traverse_dr(g,0);
    GRAPHdestroy(g);
}

/**** Função main(int argc, char** argv)
    * Dada uma quantidade de parâmetros e o vetor contendo-os, verifica a possibilidade de ser um arquivo de projeto e executa, caso possível, a função menu.
    */

int main(int argc, char** argv)
{
    if ( (argc < 2) || (argc > 2) )
    {
        printf("Parametros incorretos. Para inicializar, voce deve passar um arquivo de entrada.\n");
        printf("Exemplos: %s entrada.txt\n\t  %s entrada2.txt\n",argv[0],argv[0]);
        return 1;
    }
    menu(ledarquivo(argv[1]));
    return 0;
}


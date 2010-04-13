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

typedef Item;

int compara(int a, int b);

int comp(hp a, hp b);

void selectionsort(void *base,size_t num,size_t size,int(*less)(const void*,const void*));

void insertionsort(void *base,size_t num,size_t size,int(*less)(const void*,const void*));

void insertionSent(void *base,size_t num,size_t size,int(*less)(const void*,const void*));

void bolhaS(void *base,size_t num,size_t size,int(*comp)(const void*,const void*));//ponteiro deveria chamar less, tambem nao alterei esta implementacao

void bolhaCPA(void *base,size_t num,size_t size,int(*less)(const void*,const void*));

void shellsort(void *base,size_t num,size_t size,int(*less)(const void*,const void*));

void stacksort(void *base,size_t num,size_t size,int(*less)(const void*,const void*));

void quick(void *base,size_t num,size_t size,int(*less)(const void*,const void*));


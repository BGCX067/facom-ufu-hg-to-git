#include "algoritmos.h"
//#include "pilha.h"

int compara(int a, int b){
    if ( a < b) return 1;
    return 0;
}

int comp(hp a, hp b){
    if ( a->chave < b ->chave ) return 1;
    return 0;
}

void selectionsort(void *base,size_t num,size_t size,int(*)(const void*,const void*))
{
    int a, b, pos;
    Item menor;
    for (a = l; a <= r; ++a){
        menor = vet[a];
        b = a + 1;
        while ( b <= r ){
            if ( less(vet[b],menor) ){
                menor = vet[b];
                pos = b;
            }
            b++;
        }
        if ( menor != vet[a] ){
            Item temp = vet[a];
            vet[a] = menor;
            vet[pos] = temp;
        }
    }
}

void insertionsort(Item *vet, int l, int r, int (*less)(Item, Item)){
    int i, k;
    Item index;
	for ( i = l; i <= r; i++){
		k = i;
		index = vet[i];
		while( ( k != 0 ) && ( !less(vet[k-1],index) ) ){
			vet[k] = vet[k-1];
			k--;
		}
		vet[k] = index;
	}
}

void insertionSent(Item *vet, int l, int r, int (*less)(Item,Item)){
	int i, k;
	Item index, b;
	for (i = r; i >= l; i--){
		if ( vet[i] == vet[i-1] ){
			b = vet[i];
			vet[i] = vet[i-1];
			vet[i-1] = b;
		}
	}
	for ( i = l; i <= r; i++){
		k = i;
		index = vet[i];
		while( ( k != 0 ) && ( !less(vet[k-1],index) ) ){
			vet[k] = vet[k-1];
			k--;
		}
		vet[k] = index;
	}
}

void bolhaS(Item *vet, int l, int r, int (*less)(Item,Item)){
	int i, j;
	Item b;
	for (i = l; i <= r; i++){
		for (j = l+1; j<= r; j++){
			if ( !less(vet[j-1],vet[j]) ){
			   b = vet[j-1];
			   vet[j-1] = vet[j];
			   vet[j] = b;
			}
		}
	}
}

void bolhaCPA(Item *vet, int l, int r, int (*less)(Item,Item)){
	int i, j, troca;
	Item b;
	for (i = l, troca = 0; i <= r; i++){
		for (j = l+1; j<= r; j++){
			if ( !less(vet[j-1],vet[j]) ){
			   b = vet[j-1];
			   vet[j-1] = vet[j];
			   vet[j] = b;
			   troca = 1;
			}
		}
		if (troca == 0) break;
	}
}

void shellsort(Item *a, int l, int r, int (*less)(Item, Item)){
    int i,j,h;
    for( h = 1; h <= (r-1)/9; h = (3*h) + 1);
    for( ; h > 0; h /= 3)
        for ( i = l+h; i <= r; ++i){
            j = i;
            Item v = a[i];
            while( j >= l + h && less(v, a[j-h]) ){
                a[j] = a[j - h];
                j -= h;
            }
            a[j] =v;
        }
}

void stacksort(int *vet, int tam, int (*less)(int,int)){
    int a, b, pos;
    int menor;
    pilha p;
    start(&p);
    for (a = 0; a < tam - 1; ++a){
        menor = vet[a];
        b = a + 1;
        while ( b < tam ){
            if ( less(vet[b],menor) ){
                if ( vet[a] != menor )
                    push(&p, menor, pos);
                menor = vet[b];
                pos = b;
            }
            b++;
        }
        if ( menor != vet[a] ){
            int temp = vet[a];
            vet[a] = menor;
            vet[pos] = temp;
        }
    }
}

int partition(void *base, size_t num, size_t size, int(*comp)(const void*,const void*))
{
    int i = l - 1;
    int j = r;
    Item v = a[r];
    for( ; ; ){
        while( less(a[++i], v) );
        while( less(v, a[--j]) )
            if ( j == l ) break;
        if ( i >= j ) break;
        Item c = a[i];
        a[i] = a[j];
        a[j] = c;
    }
    Item c = a[i];
    a[i] = a[r];
    a[r] = c;
    return i;
}


void quicksortRecursive(void *base, size_t num, size_t size, int(*comp)(const void*,const void*))
{
    int i;

    if ( num > 1 ) {
        i = partition(base,num,size,comp);
        quicksortRecursive(base,i-1,size,comp);
        quicksortRecursive(base+i*size,num-i-1,size,comp);
    }
}


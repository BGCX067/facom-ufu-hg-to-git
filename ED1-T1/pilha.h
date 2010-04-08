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


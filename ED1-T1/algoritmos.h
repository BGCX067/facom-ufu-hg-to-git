

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


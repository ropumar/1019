#define _GNU_SOURCE

#include <assert.h>
#include <unistd.h>
#include <stdio.h>

//o seguinte programa aumenta a memória do heap em 100*4 bytes, e escreve dois inteiros, um no inicío da nova área(*p = 1) e outro na sua última posição(*(p+100) = 2). Então, ele usa assert para verificar que os valores foram gravados e lidos corretamente, e por último desaloca a memória.

int main(void) {

    int pg;
    void *b = sbrk(0);
    int *p = (int *)b;
    
    pg = getpagesize();
    printf("%d\n", pg);
    
    /* Move it 100 ints forward */
    brk(p + 100); 
    
    *p = 1;
    *(p + 100) = 2;
    
    assert(*p == 1);
    assert(*(p + 100) == 2);
    
    /*Desaloca voltando ao endereço anterior b */
    brk(b); 
    
    printf("Erfolgreich\n");
    return 0;
}

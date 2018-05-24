#define _GNU_SOURCE

#include <assert.h>
#include <unistd.h>
#include <stdio.h>
void *myallocate( int n);
void initmemorypool(void);
void resetmemorypool(void);
void *memorypool;
void *a;

int main(void) {


    initmemorypool();
    int *p = (int*) memorypool;
    a=myallocate (p + 300);
    printf("memory pool %p \n",memorypool);
    printf("a %p \n",a);
    a=myallocate (p + 100);
    printf("memory pool %p \n",memorypool);
    printf("a %p \n",a);

    resetmemorypool();

    return 0;
}

void *myallocate( int n)
{
    return sbrk(n);
}
void initmemorypool(void) {
    memorypool = sbrk(0);
}
void resetmemorypool(void){
 brk(memorypool);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
	int status;
	char* const parameters[] = {NULL};
	printf("pidPai: %d  meuPid: %d \n",getppid() , getpid());
	execv("alomundo", parameters);
	printf("pidPai: %d  meuPid: %d \n",getppid() , getpid());
    return 0;
}

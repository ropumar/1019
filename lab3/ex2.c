#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


void killHandler(int signal)
{
	printf("cheguei aqui\n");
}

int main(void) {
	void (*p)(int);// ponteiro para função que recebe int como parâmetro 
	p = signal(SIGKILL, killHandler);
	printf("inicio\n");
	while(1);
	printf("final\n");
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
	int var = 0;
	int status;

	if (fork() != 0) { // Codigo Pai
		for (int i=1;i<=50;i++)
		{
			var=i;
			printf("var: %d \n", var);
			sleep(2);
		}
		printf("Processo Pai vai morrer  		pidPai: %d  meuPid: %d \n",getppid() , getpid());

	}
	else if (fork()!=0)
	{ // Codigo Filho
		printf(" 	Filho 1 foi Criado pidPai: %d  meuPid: %d \n",getppid() , getpid());
		for (int i=100;i<=200;i++)
		{
			var=i;
			printf("	var: %d \n", var);
			sleep(1);
		}
		printf(" 	Filho 1 vai morrer 	pidPai: %d  meuPid: %d \n",getppid() , getpid());

	}else { // Codigo Neto
		printf(" 		Neto 1 foi criado pidPai: %d  meuPid: %d \n",getppid() , getpid());
		for (int i=300;i<=350;i++)
		{
			var=i;
			printf("		var: %d \n", var);
			sleep(2);
		}
		printf("  		Neto 1 vai morrer 		pidPai: %d  meuPid: %d \n",getppid() , getpid());
	}
	return 0;
}

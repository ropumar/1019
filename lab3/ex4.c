#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void childhandler(int sinal);
#define EVER ;;

int main(int argc, char *argv[]) 
{ 
	pid_t pid1, pid2;
	int i, processo, ntrocas;
	processo = 1;
	if((pid1 = fork()) < 0) 
	{ 
		fprintf(stderr, "Erro ao criar filho\n");
		 
		exit(-1); 
	} 
	if(pid1 == 0) /*Filho 1 */
	{
		for (EVER){
			printf("Filho 1 sendo executado\n");
			sleep(1); //Sleep para facilitar a visualizacao
		}
	} 

	if((pid2 = fork()) < 0) 
	{ 
		fprintf(stderr, "Erro ao criar filho\n");
		 
		exit(-1); 
	} 
	if(pid2 == 0) /*Filho 2 */
	{
		for (EVER){
			printf("Filho 2 sendo executado\n");
			sleep(1); //Sleep para facilitar a visualizacao
		}
	} 
	kill(pid1, SIGSTOP); //para filhos
	kill(pid2, SIGSTOP); //para filhos
	for(i=0; i<10; i++){ // 10 loops para fazer a troca entre filhos
		if(processo == 1){
			kill(pid2, SIGSTOP);
    		kill(pid1, SIGCONT);
    		printf("Troca %d\n",i+1);
    		processo = 2;
		}
		else if(processo == 2){
			kill(pid1, SIGSTOP);
    		kill(pid2, SIGCONT);
    		printf("Troca %d\n",i+1);
    		processo = 1;
		}
		sleep(1); 
	}

	//Processo pai mata os processos filhos
	kill(pid1, SIGKILL); 
	kill(pid2, SIGKILL); 
	return 0; 
}


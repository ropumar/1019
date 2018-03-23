#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {

	int seg=0; 
	int tam_string=141;
	char msg[tam_string],*mensagem_dia;
	int pid;
	char* const parameters[] = {NULL};
	int tamanho = sizeof(char)*tam_string;

	printf("Insira mensagem do dia\n");
	scanf(" %140[^\n]",msg);

	seg = shmget (8752, tamanho, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); 

	if (seg == -1) {
		puts ("Erro na criação de segmento de memoria compartilhada.");
		exit(1);
	}
	mensagem_dia = (char *) shmat (seg, 0, 0);
	strcpy(mensagem_dia,msg);
	shmdt (mensagem_dia); 
	execv("ex2b", parameters);
	return 0;
}

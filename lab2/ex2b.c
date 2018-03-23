#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>


int main () {

	int seg=0; 
	char *mensagem_dia;
	int tam_string=141;
	int tamanho = sizeof(char)*tam_string;
	seg = shmget (8752, tamanho, S_IRUSR |  S_IWUSR);
	if (seg == -1) {
		printf("Erro segmento\n");
		exit(1);
	}
	mensagem_dia = (char *) shmat (seg, 0, 0);

	printf("Mensagem do dia: %s\n",mensagem_dia);

	shmdt (mensagem_dia); 
	shmctl (seg, IPC_RMID, 0); 

	return 0;	

}
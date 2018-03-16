#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
	int status;
	int pidPai = getpid();

	if (fork() != 0) { // Codigo Pai
		printf("Processo pai:\n");
		printf("meu pid: %d\n", pidPai);
		waitpid(-1, &status, 0);
		printf("Pai finalizado\n");
	}
	else { // Codigo Filho
		printf("	Processo filho\n");
		printf("	pid: %d\n", getpid()); //pega este pid
		printf("	pid pai: %d\n", getppid()); //pega pid pai
		printf("	Filho finalizado\n");
		exit(0);
	}

    return 0;
}
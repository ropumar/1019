#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
	int var = 0;
	int status;

	if (fork() != 0) { // Codigo Pai
		var += 50;
		printf("Pai %d - %d -end %p \n", getpid(), var, &var);

		waitpid(-1, &status, 0);
		printf("Pai %d - %d -end %p \n", getpid(), var, &var);
	}
	else { // Codigo Filho
		var += 10;
		printf("	Filho %d - %d - end %p \n", getpid(), var, &var);
	}
	return 0;
}

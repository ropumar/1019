#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

void preenche_m1(int *m,int nlinhas, int ncolunas) {
	int i,j;
	for (i=0; i < nlinhas; i++) {
		for (j=0; j < ncolunas; j++) {
			m[i*ncolunas+j] = 2*i+3*j;
		}
	}
}
void preenche_m2(int *m,int nlinhas, int ncolunas) {
	int i,j;
	for (i=0; i < nlinhas; i++) {
		for (j=0; j < ncolunas; j++) {
			m[i*ncolunas+j] = 3*i+2*j;;
		}
	}
}

void imprime_m(int *m,int nlinhas, int ncolunas) {
	int i,j;
	for (i=0; i < nlinhas; i++) {
		for (j=0; j < ncolunas; j++) {
			printf("%d ",m[i*ncolunas+j]);
		}
		printf("\n");
	}
}

int main() {
	int i, j;
	int nlinha = 3;
	int ncol =4;
	int seg1, seg2, seg3;
	int *m1, *m2, *m3;
	int nforks;
	int pid;
	int status;
	seg1 = shmget (IPC_PRIVATE, sizeof (int)*nlinha*ncol, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); 
	if (seg1 == -1) {
		puts ("Erro na criação de segmento de memoria compartilhada.");
		exit(1);
	}
	m1 = (int *) shmat (seg1, 0, 0);

	seg2 = shmget (IPC_PRIVATE, sizeof (int)*nlinha*ncol, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); 
	if (seg2 == -1) {
		puts ("Erro na criação de segmento de memoria compartilhada.");
		exit(1);
	}
	m2 = (int *) shmat (seg2, 0, 0);

	seg3 = shmget (IPC_PRIVATE, sizeof (int)*nlinha*ncol, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); 
	if (seg3 == -1) {
		puts ("Erro na criação de segmento de memoria compartilhada.");
		exit(1);
	}
	m3 = (int *) shmat (seg3, 0, 0);
	
	preenche_m1(m1,nlinha, ncol);
	preenche_m2(m2,nlinha, ncol);
	printf("M1: ");
	imprime_m(m1,nlinha,ncol);
	printf("M2: ");
	imprime_m(m2,nlinha,ncol);


	for (nforks = 0; nforks < nlinha; nforks++) {
		pid = fork();
		if (pid < 0) { 
			puts ("Erro na criação do novo processo"); 
			exit (-2); 
		} 
		if (pid == 0) {
			printf ("    Processo filho \n");
			int j, indice = nforks*ncol;
			for (j = 0; j < ncol; j++) {
				m3[indice] = m1[indice] + m2[indice];
				indice++;
			}
			break;
		}
	}
	if (pid != 0) {
		printf ("Processo Pai \n");
		for(i=0;i<nforks;i++){
			waitpid(-1,&status,0);
		}
		printf("Terceira matriz\n");
		imprime_m(m3,nlinha,ncol);
	}

	shmdt (m1); 
	shmctl (seg1, IPC_RMID, 0); 
	shmdt (m2); 
	shmctl (seg2, IPC_RMID, 0); 
	shmdt (m3); 
	shmctl (seg3, IPC_RMID, 0);

	return 0;
}

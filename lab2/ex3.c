#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#define TAMANHO 12

int main(){
    int status;
    int valor_procurado=7;
    int *vetor;
    int pid;
    int v[TAMANHO]= {3,5,1,9,10,7,8,6,4,0,11,2};
	int seg1 = shmget (IPC_PRIVATE, sizeof (int)*TAMANHO, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR); 
	if (seg1 == -1) {
		puts ("Erro na criação de segmento de memoria compartilhada.");
		exit(1);
	}
	vetor = (int *) shmat (seg1, 0, 0);
    printf("vetor:");
    for (int i = 0; i < TAMANHO; i++) {
		vetor[i] = v[i];
        printf("%d ",vetor[i]);
	}
    printf("\n");
    
    for(int i=0; i<TAMANHO; i=i+3){
        pid=fork();
        if (pid==0){
            printf("Filho : %d\n", getpid());
            printf("Filho de %d a %d\n", i,i+3);
            int found = 0;
            for(int j = 0;j < 3;j++) {
                if (vetor[i+j] == valor_procurado) {
                    found = 1;
                    printf("Filho %d Encontrou na posicao %d do vetor o valor procurado %d \n",getpid() ,i+j, vetor[i+j]);
                }
            }
            if (found != 1)
                printf("Não encontrou ocorrência do valor no filho %d \n", getpid());
            exit(1);
        }else{
            printf("Pai : %d\n", getpid());
            waitpid(-1,&status,0);
        }
    }
    shmdt (vetor); 
	shmctl (seg1, IPC_RMID, 0); 
    return 0;
}

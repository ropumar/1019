#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/mman.h> 
#include <math.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/sem.h>

union semun { 
	int val; 
	struct semid_ds *buf; 
	ushort *array; 
};

int setSemValue(int semId) { 
	union semun semUnion; 
	semUnion.val = 1; 
	return semctl(semId, 0, SETVAL, semUnion); 
}

void delSemValue(int semId) { 
	union semun semUnion; 
	semctl(semId, 0, IPC_RMID, semUnion); 
}

//perguntar sobre esses troço loko aqui em baixo

int semaforoP(int semId) { 
	struct sembuf semB; 
	semB.sem_num = 0; 
	semB.sem_op = -1; 
	semB.sem_flg = SEM_UNDO; 
	semop(semId, &semB, 1); 
	return 0; 
}

int semaforoV(int semId) { 
	struct sembuf semB; 
	semB.sem_num = 0; 
	semB.sem_op = 1; 
	semB.sem_flg = SEM_UNDO; 
	semop(semId, &semB, 1); 
	return 0; 
}

int main(void)
{
	//vetor memory map
	char *p;
	//controle do semáforo
	int semId;
	//descritor de arquivo
	int fd;
	int i;
	struct stat sb;
	
	// O semáforo. NÃO CRIA
	semId = semget (8600, 1, 0666); 
	
	//arquivo sendo aberto. NÃO CRIA
	fd = open("file.txt", O_RDWR);
	if (fd == -1){
   		perror ("open"); exit(1);
   	} 
   	
   	if (fstat(fd, &sb)== -1){
   		perror ("fstat"); exit(1);
   	}     
	
	//memory mapping
	p = mmap (0, sb.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	 if (p == MAP_FAILED){
   		perror ("mmap"); exit(1);
   	}
   	printf("lendo:\n");
   	for(i = 0; i < 10; i++)
   	{
   		semaforoP(semId); /* down */
   		printf("%c\n", p[i]);		
   		semaforoV(semId);/* up */
   	}
   	printf("lendo:\n");
   	
   	//limpa semaforo e desmapeia memoria
   	delSemValue(semId);
   	if (munmap  (p, sb.st_size) == -1){
   		perror ("munmap"); exit(1);
   	}      
   	close(fd);
   	
   	return 0;
   	
   	
   	
 
   	
}

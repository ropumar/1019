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
#include <string.h>

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
	int i, size;
	struct stat sb;
	char mens[] = "mensagem";
	
	// O semáforo. CRIA
	semId = semget (8600, 1, 0666 | IPC_CREAT); 
	setSemValue(semId);
	
	//arquivo sendo criado. CRIA
	fd = open("file.txt", O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	if (fd == -1){
   		perror ("open"); exit(1);
   	}      
   	
   	//magia negra
   	lseek(fd, strlen(mens),SEEK_SET);
   	
   	write(fd, "", sizeof(char));
   	
   	if (fstat(fd, &sb)== -1){
   		perror ("fstat"); exit(1);
   	}
	
	printf("%ld\n", sb.st_size);
	
	//memory mapping
	p = mmap (0, strlen(mens), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	 if (p == MAP_FAILED){
   		perror ("mmap"); exit(1);
   	}
   	printf("escrevendo:\n");
   	for(i = 0; i < 10; i++)
   	{
   		semaforoP(semId); /* down */
   		p[i] = 'A' + (char)i;
   		msync(p, getpagesize(), MS_SYNC);   
   		sleep(1);		
   		semaforoV(semId); /* up */
   		
   	}
   	printf("fim leitura:\n");
   	
   	
   	//limpa semáforo e desmapeia memória
   	
   	delSemValue(semId);
   	 if (munmap  (p, strlen(mens)) == -1){
   		perror ("munmap"); exit(1);
   	}       
   	
   	close(fd);
   	
   	return 0;
   	
   	
   	
   	
   	
}

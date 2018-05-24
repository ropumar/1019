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
#include <string.h>




int main(void)
{
	//vetor memory map
	char *p;
	
	//descritor de arquivo
	int fd;
	struct stat sb;
	char mens[] = "Jorge";
	

	//arquivo sendo criado. CRIA
	fd = open("carta.txt", O_RDWR, S_IRUSR|S_IWUSR);
	if (fd == -1){
   		perror ("open"); exit(1);
   	}    
   	
   	if (fstat(fd, &sb)== -1){
   		perror ("fstat"); exit(1);
   	}
	   	
   	
   	lseek(fd, strlen(mens)-1,SEEK_END);
   	  	
   	write(fd, "", sizeof(char));
	
	//memory mapping
	p = mmap (0, sb.st_size + strlen(mens), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	 if (p == MAP_FAILED){
   		perror ("mmap"); exit(1);
   	}
   	printf("escrevendo:\n");
   	
	
	strcpy(&p[sb.st_size], mens);
	msync(p, strlen(mens) + sb.st_size, MS_SYNC);
	 
	
   		
   	
   	printf("fim escrita:\n");
   	
   	
   	//desmapeia memória
   	
   	
   	if (munmap  (p, strlen(mens)) == -1){
   		perror ("munmap"); exit(1);
   	}       
   	
   	//fechar arquivo
   	close(fd);
   	return 0;	
   	
   	
   	
}

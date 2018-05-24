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
#include <utime.h>

#define _GNU_SOURCE

//map-exemplo.c alterado:


int main (int argc, char *argv[]){

	struct stat sb;

	
	struct timeval stop, start;
	
	//do stuff
	
	off_t len;
	char *p;   
	char c;
	int fd, pArq;
	long int t1, t2;
	//FILE *pArq;
	


   	if (argc < 2){
	   	fprintf (stderr, "usage: %s <file>\n", argv[0]);
	   	exit(1);
   	}

	fd = open (argv[1], O_RDONLY);

   	if (fd == -1){
   		perror ("open"); exit(1);
   	}                 

   	if (fstat(fd, &sb)== -1){
   		perror ("fstat"); exit(1);
   	}

   	if (!S_ISREG (sb.st_mode)){
	   	fprintf (stderr, "%s is not a file\n", argv[1]);
	   	exit(1);
   	}

	//mapeamento do arquivo para a memória principal. 
	gettimeofday(&start, NULL);
   	p = mmap (0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
   	gettimeofday(&stop, NULL);
   	if (fstat(fd, &sb)== -1){
   		perror ("fstat"); exit(1);
   	}
   	

   	if (p == MAP_FAILED){
   		perror ("mmap"); exit(1);
   	}

   	if (close (fd) == -1){
   		perror ("close"); exit(1);
   	}
   	
   	t1 = stop.tv_usec - start.tv_usec;

	//printando o arquivo que foi mapeado diretamente da memória.
   	printf("Memória Principal:\n");
   	for (len = 0; len < sb.st_size; len++){
   		putchar (p[len]);
   	}

	fflush(stdout);
	
   	if (munmap  (p, sb.st_size) == -1){
   		perror ("munmap"); exit(1);
   	}       
   	
 	//repetindo a impressão diretamente da memória
 	
 	pArq = open (argv[1], O_RDONLY);

   	if (fd == -1){
   		perror ("open"); exit(1);
   	}                 

   	if (fstat(fd, &sb)== -1){
   		perror ("fstat"); exit(1);
   	}

   	if (!S_ISREG (sb.st_mode)){
	   	fprintf (stderr, "%s is not a file\n", argv[1]);
	   	exit(1);
   	}
   	//imprimindo diretamente do disco
   	printf("DISCO:\n");
   	gettimeofday(&start, NULL);
   	for(len = 0; len < sb.st_size; len++)
   	{
   		read(pArq, (void*) &c, sizeof(char));
   		putchar(c);
   	}
   	gettimeofday(&stop, NULL);
   	close(pArq);
   	
   	t2 = stop.tv_usec - start.tv_usec;
   	
   	printf("Tempo Memory Map: %ld\n", t1);
   	printf("Tempo Disco: %ld\n", t2);
   	
   	
   	//calcula quantidade de página usadas = ceil(tamanho do arquivo carregado / tamanho da página) 
   	printf("páginas usadas: %ld \n", (long int)ceil(((double)sb.st_size / (double)getpagesize())));

   	return 0;
}

#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/mman.h> 
#include <math.h>

#define _GNU_SOURCE

//map-exemplo.c alterado:

//

int main (int argc, char *argv[]){

	struct stat sb, sm, sn;

	off_t len;
	char *p, *out;   
	//descritores de: arquivo a ser lido, arquivo escrito através de memory map e arquivo escrito diretamente
	int fd, fm, fn;
	


   	if (argc < 2){
	   	fprintf (stderr, "usage: %s <file>\n", argv[0]);
	   	exit(1);
   	}
	//arquivo de leitura
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
   	
   	/*
   	
   	//arquivo de escrita através de memory map
   	fm = open ("saidaMM.txt", O_WRONLY|O_CREAT|O_TRUNC);
   	
   	if (fm == -1){
   		perror ("open"); exit(1);
   	}                 

   	if (fstat(fm, &sb)== -1){
   		perror ("fstat"); exit(1);
   	}
   	
   	//arquivo de escrita direta
   	fn = open ("saidaD.txt", O_WRONLY|O_CREAT|O_TRUNC);
   	
   	if (fn == -1){
   		perror ("open"); exit(1);
   	}                 

   	if (fstat(fn, &sb)== -1){
   		perror ("fstat"); exit(1);
   	}

*/

	//mapeamento do arquivo para a memória principal. 
   	
   	p = mmap (0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);

   	if (p == MAP_FAILED){
   		perror ("mmap"); exit(1);
   	}

   
	
	//printando o arquivo que foi lido para arquivo de saída direta e medindo o tempo
   	
   	//abrindo arquivo
   	fn = open ("saidaD.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
   	
   	if (fn == -1){
   		perror ("open"); exit(1);
   	}                 

   	if (fstat(fn, &sn)== -1){
   		perror ("fstat"); exit(1);
   	}
   	
   	//out = mmap (0, sb.st_size, PROT_READ, MAP_SHARED, fm, 0);
   	
   	for (len = 0; len < sb.st_size; len++){
   		 write(fn, p[len],sizeof(char));
   	}
  
   	
   	
   	if (close (fn) == -1){
   		perror ("close"); exit(1);
   	}
   	
   	//printando o arquivo que foi lido para arquivo de saída MM e medindo o tempo
   	
   	
   	
	if (close (fd) == -1){
	perror ("close"); exit(1);
	}
   		
   	
	//desalocando mapas
   	if (munmap  (p, sb.st_size) == -1){
   		perror ("munmap"); exit(1);
   	}
   	
   //	if (munmap  (out, sb.st_size) == -1){
 //  		perror ("munmap"); exit(1);
  // 	}    
   	
   	//calcula quantidade de página usadas = ceil(tamanho do arquivo carregado / tamanho da página) 
   	printf("páginas usadas: %ld \n", (long int)ceil(((double)sb.st_size / (double)getpagesize())));

   	return 0;
}

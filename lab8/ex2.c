#include <stdio.h> 
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/mman.h> 

#define _GNU_SOURCE

//map-exemplo.c:
//o programa a seguir lê o que está escrito no arquivo e printa isso na saída padrão. A novidade está em que é usado um memory map: o conteúdo do arquivo é carregado inteiramente para o heap do programa, e é então lido e printado diretamente da memória principal.

int main (int argc, char *argv[])
{
 struct stat sb;
 off_t len;
 char *p; int fd;
 if (argc < 2) { fprintf (stderr, "usage: %s <file>\n",argv[0]); exit(1); }
 fd = open (argv[1], O_RDONLY);
 if (fd == -1) { perror ("open"); exit(1); }
 if (fstat(fd, &sb)== -1) { perror ("fstat"); exit(1); }
 if (!S_ISREG (sb.st_mode)) { fprintf (stderr, "%s is nota file\n", argv[1]); exit(1);}
 p = mmap (0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
 if (p == MAP_FAILED) { perror ("mmap"); exit(1); }
 if (close (fd) == -1) { perror ("close"); exit(1); }
 for (len = 0; len < sb.st_size; len++) putchar (p[len]);
 if (munmap (p, sb.st_size) == -1) {perror ("munmap");
exit(1); }
 return 0;
}

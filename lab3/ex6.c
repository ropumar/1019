#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int tempo = 0;
int centavos = 0;

void initHandler (int sinal);
void quitHandler (int sinal);

int main (void){
	signal(SIGUSR1, initHandler);
	signal(SIGUSR2, quitHandler);
	printf("Pronto para Receber Ligacoes no processo\n");
	printf("Para Iniciar Ligacao:\n");
	printf("kill -s USR1 %d\n", getpid());
	printf("Para Terminar Ligacao:\n");
	printf("kill -s USR2 %d\n", getpid());
	printf("digite\n");
	pause();
	return 0;
}

void initHandler (int sinal){

	printf("Ligação iniciada.\n");
	while (1){
		sleep(1);
		tempo++;
		if(tempo <= 60) centavos = centavos + 2;
		else centavos++;
	}
}

void quitHandler (int sinal){
	printf("Ligacao Terminada.\n");
	printf("Tempo gasto: %d segundos\nPreco: R$%d,%02d\n", tempo, centavos/100, centavos%100 );
	return;
}

/*

Explicação:

O programa é iniciado em backgroud e fica esperando o inicio de uma ligação.

A ligação é feita através do sinal initHandler, que é chamado pelo sinal SIGUSR1.
O usuário manda o sinal através do comando "kill -s USR1 3004" (levando em conta que 3004 é o pid do processo),
e assim a ligação é iniciada.

O mesmo é feito para terminar uma ligação através do quitHandler, que é chamado pelo sinal SIGUSR2.
Este sinal é chamado no terminal pelo comando "kill -s USR1 3004" (levando em conta que 3004 é o pid do processo).
A função quitHandler diz a duração da chamada, o preço da mesma e termina o programa.

Exempĺo 1: menos de 1 minuto.

[paranapanema.grad.inf.puc-rio.br:~/Documents/inf1019/Lab4] ./ex6 &
[14] 3315
[paranapanema.grad.inf.puc-rio.br:~/Documents/inf1019/Lab4] Preparado

[paranapanema.grad.inf.puc-rio.br:~/Documents/inf1019/Lab4] kill -s USR1 3315
Ligação iniciada.
[paranapanema.grad.inf.puc-rio.br:~/Documents/inf1019/Lab4] kill -s USR2 3315
Terminado.
Tempo gasto: 6 segundos
Preco: 12 centavos


Exemplo 2: mais de 1 minuto.

[paranapanema.grad.inf.puc-rio.br:~/Documents/inf1019/Lab4] ./ex6 &
[14] 3374
[paranapanema.grad.inf.puc-rio.br:~/Documents/inf1019/Lab4] Preparado

[paranapanema.grad.inf.puc-rio.br:~/Documents/inf1019/Lab4] kill -s USR1 3374
Ligação iniciada.
[paranapanema.grad.inf.puc-rio.br:~/Documents/inf1019/Lab4] kill -s USR2 3374
Terminado.
Tempo gasto: 84 segundos
Preco: 144 centavos

*/

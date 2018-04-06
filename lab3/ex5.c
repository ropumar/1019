#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void FPEhandler (int sinal);

int main (void) {
	int x,y;
	signal(SIGFPE, FPEhandler);
	printf("Digite o primeiro numero: ");
	scanf("%d", &x);
	printf("Digite o segundo numero: ");
	scanf("%d", &y);
	printf("\nAdição: %d + %d = %d \nSubtração: %d - %d = %d \nDivisão: %d/%d = %d \nMultiplicação: %d x %d = %d \n", x, y, x+y, x, y, x-y, x, y, x/y, x, y, x*y);
	return 0;

}

void FPEhandler (int sinal) {

	printf ("Erro de Floating point exception\n");
	exit(0);
}

/*

Explicação:

Quando executamos o programa sem digitar o zero no segundo número, o programa não tenta uma divisão por zero.
Assim não há erro de floating number, então o sinal não é enviado e a função handler não é utilizada.

Já quando colocamos o segundo número como zero, na parte da divisão entre dois números, o númerador sendo zero cai no erro de
floating point. O programa automaticamente envia o sinal, gerando um código de erro default. Ao registrar o handler para este
sinal com "signal(SIGFPE, handler);", o tratamento de erro muda e a função handler é chamada.

Exemplo 1: sem zero no divisor.

[paranapanema.grad.inf.puc-rio.br:~/Documents/inf1019/Lab4] ./ex5
Digite o 1 numero: 1
Digite o 2 numero: 5
Adição: 1 + 5 = 6 
 Subtração: 1 - 5 = -4 
 Divisão: 1/5 = 0 
 Multiplicação: 1 x 5 = 5 

Exemplo 2: sem o registro do handler.

[paranapanema.grad.inf.puc-rio.br:~/Documents/inf1019/Lab4] ./ex5
Digite o 1 numero: 1
Digite o 2 numero: 0
Floating exception (core dumped)

Exemplo 3: com o registro do handler.

[paranapanema.grad.inf.puc-rio.br:~/Documents/inf1019/Lab4] ./ex5
Digite o 1 numero: 1
Digite o 2 numero: 0
Erro de floating point. Signal : 8

*/

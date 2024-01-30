//VAMOS CRIAR UM PROGRAMA QUE TESTAS AS ROTINAS CRIADAS NO ARQUIVO primes_sum_of_square.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o primes_sum_of_square primes_sum_of_square.c -lm

//Cabeçalho
#include"primes_sum_of_square.h"


//Função principal
int main(){
//Variáveis locais
int64_t prime;

//Procedimentos

//Recebendo input do usuário
printf("Digite um inteiro p primo:");
scanf("%li", &prime);

//Testedo algoritmo que expressaprimos em termos de formas quadrá
prime_sum_of_square(prime);

//Finalizando a aplicação
return 0;
          }

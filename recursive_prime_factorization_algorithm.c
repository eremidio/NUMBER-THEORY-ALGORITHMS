//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA AS ROTINAS CRIADAS NO ARQUIVO recursive_prime_factorization_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o recursive_prime_factorization_algorithm recursive_prime_factorization_algorithm.c -lm -O2

//Cabeçalho
#include"recursive_prime_factorization_algorithm.h"

//Função principal
int main(){
//Variáveis locais
uint64_t number;

//Procedimentos
//Recebendo input do usuário
printf("Digite um número inteiro a ser fatorado: ");
if(scanf("%lu", &number)!=1)
return 0;

//Fatorando o número em questão
elias_rowland_factorization_algorithm(number);

//Finalizando a aplicação
return 0;
          }

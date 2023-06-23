//VAMOS IMPLEMENTAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE SELFRIDGE PARA TESTAR SE UM NÚMERO É PRIMO OU NÃO
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o selfridge_prime_test selfridge_prime_test.c

/*
O TESTE DE SELFRIDGE É BASEADO EM UMA CONJECTURA QUE AFIRMA QUE UM NÚMERO p É PRIMO SE E SOMENTE SE:
1. f(p+1) = 0 mod(p). ONDE f(p+1) É O (p+1)-ÉSIMO NÚMERO NA SEQUÊNCIA DE FIBONACCI.
2. 2^(p-1)= 1 mod(p).

ESTE É UM REASULTADO AINDA NÃO COMPROVADO, EMBORA FUNCIONE RAZOALMENTE BEM EM CÁLCULOS PRÁTICOS.

*/

//********************************************************************************************************************
//CABEÇALHO
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"mod_bin_exponentiation.h"


//********************************************************************************************************************
//FUNÇÕES

//Função que calcula o n-ésimo número na sequência de Fibonacci a menos de uma congruência
long long int fibonacci_module(long long int n, long long int p){
//Definição
if(n==1 || n==2)
return 1;
else
return (fibonacci_module(n-1, p)+fibonacci_module(n-2, p))%p;
                                                                };

//Teste de primalidade
bool selfridge_test(long long int n){
if(fibonacci_module(n+1, n)==0 && mod_pow(2, n-1, n)==1)
return true;
else 
return false;
                                    };

//********************************************************************************************************************
//FUNÇÃO PRINCIPAL

int main(){
//Váriaveis
long long int number, i;
//Procedimentos
//Recebendo input do usuário
printf("Digite um limitante superior para a sequência de possíveis números:\n");
scanf("%lli", &number);

//Executando o teste
printf("Eis sua sequência de prováveis números primos:\n2, 3, 5, ");

for(i=7; i<=number; ++i){
if(selfridge_test(i)==true)
printf("%lli, ", i);
                        };
printf("...\n");

//Finalizando a aplicação
return 0;
          }



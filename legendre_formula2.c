//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO legendre_formula2.h 
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o legendre_formula2 legendre_formula2.c -lm -O2


//Cabeçalho
#include"legendre_formula2.h"
#include<stdio.h>


//Função principal
int main(){
 //Variáveis locais
 int32_t limit;

 //Procedimentos
  //Recebendo input do usuário
  printf("Limite superior para a contagem de primos: ");
  if(scanf("%i", &limit)!=1) return 0;

  //Contagem de primos
  printf("Número de primos até %i: %i.\n", limit, legendre_sieve_prime_counting(limit));

 //Finalizando a aplicação
 return 0;

}

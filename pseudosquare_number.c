//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS DESENVOLVIDAS NO ARQUIVO pseudosquare_number.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o pseudosquare_number pseudosquare_number.c -O3




//Cabeçalho
#include"pseudosquare_number.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  uint64_t number,lp;
  int small_prime;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro primo impar inferior a 300: ");
    if(scanf("%i", &small_prime)!=1) return 0;

    printf("Digite um número inteiro cuja primalidade será testada: ");
    if(scanf("%lu", &number)!=1) return 0;


    //Computando classe residual pseudoquadrática módulo primo ímpar
    lp=find_least_pseudosquare(small_prime);
    printf("Menor classe residual pseudoquadrática módulo %i: %lu\n", small_prime, lp);

    //Teste de primalidade
    if(pseudosquare_primality_testing(number)) printf("%lu é primo (ou potência de um número primo).\n", number);
    else printf("%lu é composto.\n", number);    


  //Finalizando a aplicação
  return 0;


}

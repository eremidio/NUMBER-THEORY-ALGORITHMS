//VAMOS CRIAR UM PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO aks_prime_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o aks2 aks2.c -lm -O3


//Cabeçalho
#include"aks_prime_test.h"
#include<stdint.h>
#include<stdbool.h>
#include<stdio.h>


//Função principal 
int main(){

  //Variáveis locais
  uint64_t number;

  //Procedimentos
    //Recebendo o input
    printf("Número a ser testado: ");
    if(scanf("%lu", &number)!=1)  return 0;


    //Usando o teste de primalidade AKS
    if(aks_primality_test(number, Yes)==true)
      printf("O número em questão é primo.\n");
    else
      printf("O número em questão é composto.\n");


  //Finalizando a aplicação
  return 0;

} 

//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO miller_rabin_gauss_euler_combined_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o miller_rabin_gauss_euler_combined_test miller_rabin_gauss_euler_combined_test.c -lm -O2


//Cabeçalho
#include"miller_rabin_gauss_euler_combined_test.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  uint64_t number;

  //Procedimentos
    //Recebendo o input
    printf("Número a ser testado: ");
    if(scanf("%lu", &number)!=1)  return 0;


    //Usando o teste de Miller-Rabin para inteiros de 128 bits
    if(mr_ge_combined_test(number)==true)
      printf("O número em questão é primo.\n");
    else
      printf("O número em questão é composto.\n");


  //Finalizando a aplicação
  return 0;

}

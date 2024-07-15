//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO strong_fermat_primality_test.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o strong_fermat_primality_test strong_fermat_primality_test.c -lm -O2

//Cabeçalho
#include"strong_fermat_primality_test.h"
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
    if(strong_fermat_primality_test(number)==true)
      printf("O número em questão é primo.\n");
    else
      printf("O número em questão é composto.\n");


  //Finalizando a aplicação
  return 0;

}

//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO HEADER mobius_function.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o mobius_function mobius_function.c -lm

//Cabeçalho
#include<stdio.h>
#include"mobius_function.h"


//Função principal
int main(){

 //Variáveis locais
 uint64_t number;

 //Procedimentos
  //Recebendo input do usuário
  printf("Usuário digite um número inteiro: ");
  scanf("%lu", &number);

  //Calculando as funções de Möbius e as funções de Mertens
  printf("μ(%lu) = %d\n", number, mobius_function(number));
  printf("M(%lu) = %li\n", number, mertens_function(number));

 //Finalizando a aplicação
 return 0;

          };

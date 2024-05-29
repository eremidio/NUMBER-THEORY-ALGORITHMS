//VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS CRIADAS NO ARQUIVO lehman_factorization_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o lehman_factorization_algorithm lehman_factorization_algorithm.c -lm

//Cabeçalho
#include"lehman_factorization_algorithm.h"
#include<stdio.h>

//Função principal
int main(){

  //Váriaveis
  uint64_t number;


  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número que será testado:\n");
    scanf("%lu", &number);

    //Executando o teste
    lehman_factorization_algorithm(number);

//Finalizando a aplicação
return 0;
          }

//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO sophie_german_primes.h
//COMPILAR ESTE PROGRAMA COMO COMANDO: g++ -o sophie_german_primes sophie_german_primes.c -lm


//Cabeçalho
#include"sophie_german_primes.h"
#include<stdio.h>


//Função principal
int main(){

  //Váriaveis locais
  uint64_t number;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número que será testado:\n");
    scanf("%lu", &number);

    //Executando o teste
    if(is_sophie_germain_prime(number)==true)
      printf("Primo de Sophie Germain encontrado!\n");
    else
      printf(" O número em questão não é um primo de Sophie-Germain.\n");

  //Finalizando a aplicação
  return 0;


}

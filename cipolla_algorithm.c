//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO cipolla_algorithm.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o cipolla_algorithm cipolla_algorithm.c -lm

//Cabeçalho
#include"cipolla_algorithm.h"
#include<stdio.h>

//Função principal
int main(){

  //Variáveis locais
  int64_t n, sqrt_n, prime;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um inteiro: ");
    scanf("%li", &n);
    printf("Digite um inteiro primo ímpar: ");
    scanf("%li", &prime);

    //Algoritmo de Cipolla
    sqrt_n=cipolla_algorithm(n, prime);
    printf("√%li (mod %li)= %li\n", n, prime, sqrt_n);

  //Finalizando a aplicação
  return 0;

}

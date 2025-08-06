//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO integer_partition.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o integer_partition integer_partition.c -lm

//Cabeçalho
#include<stdio.h>
#include"integer_partition.h"


//Função principal
int main(){

  //Variáveis locais
  int number;

  //Procedimentos
    //Recebendo input do usuário
    printf("Digite um número inteiro: ");
    scanf("%i", &number);

    //Cálculo da função de partição e da função soma de divisores
    __int128_t partition=partition_function(number);
    printf("Soma dos divisores de %i: %i\n", number, sum_of_divisors(number));
    printf("Número de partições de %i: ", number); printf128(partition);


  //Finalizando a aplicação
  return 0;

}

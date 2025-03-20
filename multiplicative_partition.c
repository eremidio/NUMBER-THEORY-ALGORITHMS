//VAMOS CRIAR UM PROGRAMA PARATESTAR AS ROTINAS CRIADAS NO ARQUIVO multiplicative_partition.h
//COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o multiplicative_partition multiplicative_partition.c -O2 -lm


//Cabeçalho
#include"multiplicative_partition.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  int32_t n;

  //Procedimentos
    //Recebendo input dos usuários
    printf("[Inteiro] n: ");
    if(scanf("%i", &n)!=1) return 0;

    //Computando o coeficiente binomial C(n, m)
    multiplicative_partitions(n);


  //Finalizando a aplicação
  return 0;

}

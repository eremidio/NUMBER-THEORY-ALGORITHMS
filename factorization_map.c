//VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO factorization_map.h
//COMPILAR ESTE PROGRAMA COM OS COMANDO: gcc -o  factorization_map factorization_map.c -lm -O2


//Cabeçalho
#include"factorization_map.h"
#include<stdio.h>


//Função principal
int main(){

  //Variáveis locais
  uint64_t prime_factors[30];
  int prime_powers[30];
  uint64_t n;


  //Procedimentos
    //Recebendo input do usuário
    printf("Número a ser fatorado: ");
    if(!scanf("%lu", &n))
      return 0;

    //Fatorando o número em questão
    factorization_map(n, prime_factors, prime_powers);

    printf("Relatório de execução do algoritmo:\n");
    for(int i=0; prime_factors[i]>1; ++i)
      printf("Fator: %lu  Multiplicidade: %d\n", prime_factors[i], prime_powers[i]);



  //Finalizando a aplicação
  return 0;



          }

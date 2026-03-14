//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O CRIVO DE SUNDARAM PARA GERAR NÚMEROS PRIMOS ATÉ UM DETERMINADO LIMITE

/*

PARA MAIORES INFORMAÇÕES: https://canonica.ai/page/Sieve_of_Sundaram

*/


//***********************************************************************************************************************************
//CABEÇALHO
#ifndef SUNDARAM_SIEVE_H
#define SUNDARAM_SIEVE_H
#include<stdint.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>


//***********************************************************************************************************************************
//DECLRAÇÕES DE FUNÇÕES
bool* fill_prime_array_sieve(int64_t);
void sundaram_sieve(int64_t);


//***********************************************************************************************************************************
//FUNÇÕES
//Função que prenche um array de booleanos usados para computar números primos em um intervalo
bool* fill_prime_array_sieve(int64_t n){

  //Variáveis locais
  bool* prime_array = calloc((n+1), sizeof(bool));
  int64_t index=0, k=0;


  //Procedimentos
    //Loop principal
    for(int64_t i=1; (i*i)<=n; ++i){
    
      k=i;
      while(1){
        index=i+k+2*i*k;
        if(index>n) break;
        prime_array[index]=true;
        k++;
      }

   }


  //Resultado
  return prime_array;

};

//Função que implementa o crivo de sundaram
void sundaram_sieve(int64_t n){

  //Variáveis locais
  int64_t array_size=((n-2)>>1), value=0;
  bool* prime_array=fill_prime_array_sieve(array_size);// 0--> indexa números primos, 1 -->indexa números compostos; n=(2*index)+1


  //Procedimentos
    //Exibindo o resultado do algoritmo
    printf("Lista de números primos encontrados até %li: 2, ", n);

    for(int64_t i=1; i<=array_size; ++i){
    
      if(prime_array[i]==false){
        value = (2*i)+1;
        printf("%li, ", value);
      }

    }

    printf("...\n");


    //Limpando o cachê de memória
    if(prime_array){
      free(prime_array); prime_array=NULL;
    }

};

//***********************************************************************************************************************************
//FIM DO HEADER
#endif

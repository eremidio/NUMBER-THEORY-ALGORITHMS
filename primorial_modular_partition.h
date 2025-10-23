//VAMOS CRIAR UM PROGRAMA PARA COMPUTAR PARTIÇÕES DE INTEIROS A MENOS DE UMA CONGRUÊNCIA MÓDULO PRIMOS 

/*

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/primorial_prime_sieve_setup.h

*/


//********************************************************************************************
//CABEÇALHO
#ifndef PRIMORIAL_MODULAR_PARTITION_H
#define PRIMORIAL_MODULAR_PARTITION_H
#include"primorial_prime_sieve_setup.h"
#include<stdio.h>


//CONSTANTES GLOBAIS
int small_prime_residue_classes[15];


//********************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
void primorial_prime_sieve_setup();
void compute_primorial_partition(uint64_t);


//********************************************************************************************
//FUNÇÕES
//Função que pré-computa valores usados no algoritmo principal
void primorial_sieve_setup(){
  compute_primorial_sequence();
  compute_Tnk_prime_generating_sequence();
};


//Função que computa uma partição de um inteiro a menos de congruência módulo um primorial
void compute_primorial_partition(uint64_t n){

  //Variáveis locais
  int prime_index=0;
  uint64_t sum=0;
  bool is_mod=false;


  //Procedimento
    //Calculando o menor m tal que #m<n<#(m+1)
    while(n>small_primorials[prime_index]) prime_index++;
    prime_index--;

    //Computando classes residuais módulo primos pequenos
    for(int i=0; i<15; ++i){
      small_prime_residue_classes[i]=n%small_primes[i];
    }

    //Checando se um inteiro podeexpandindo em termos da sequência OEISA240673
    restart:
    for(int i=0; i<=prime_index; ++i) sum+= small_prime_residue_classes[i]*Tnk_prime_generating_sequence[prime_index][i];
    if(sum>n) sum%=small_primorials[prime_index];


    if(sum==n){
      printf("%lu = ", n);
      for(int i=0; i<prime_index; ++i)
        printf(" %ix%lu +", small_prime_residue_classes[i], Tnk_prime_generating_sequence[prime_index][i]);

      if(is_mod) 
        printf(" %ix%lu (mod %lu)\n", small_prime_residue_classes[prime_index],
               Tnk_prime_generating_sequence[prime_index][prime_index], small_primorials[prime_index]);
      else
        printf(" %ix%lu\n", small_prime_residue_classes[prime_index], Tnk_prime_generating_sequence[prime_index][prime_index]);
      return;
    }

    if(prime_index>14){
      printf("Erro...\n");
      return;
    }
    if(sum<n){
      prime_index++;
      is_mod=true;
      sum=0;
      goto restart;
    }
  


};

//********************************************************************************************
//FIM DO HEADER
#endif

//VAMOS CRIAR UM PROGRAMA PARA TESTAR O GRAU DE SEGURANÇA ASSOCIADO A UM NÚMERO PRIMO

/*

UM NÚMERO PRIMO q É DITO SER UM NÚMERO PRIMO SEGURO SE q=2p+1, COM p PRIMO TAMBÉM. TAL DEFINIÇÃO
PROVÉM DO FATO DE MUITOS ALGORITMOS PARA FATORAR INTEIROS E PARA COMPUTAR LOGARITMOS DISCRETOS 
EXPLORAREM O FATO DE COMPUTAÇÕES EM GF(q) SÃO EXTREMAMENTE SIMPLIFICADAS SE (p-1) TIVER FATORES
PRIMOS "PEQUENOS", POR EXEMPLO, OS ALGORITMOS p-1 DE POLLARD (SIMILARMENTE O ALGORITMO DE CURVAS
ELÍPTICAS) PARA FATORAR NÚMEROS INTEIROS E O ALGORITMO DE POHLIG-HELLMAN PARA O CÁLCULO DO
LOGARITMO DISCRETO SÃO MUITO EFICIENTES SE (p-1) TIVER APENAS FATORES PRIMOS PEQUENOS.

PARA MAIORES INFORMAÇÕES: https://scispace.com/pdf/primality-criterion-for-safe-primes-3fkxq9br5u.pdf
                          https://en.wikipedia.org/wiki/Safe_and_Sophie_Germain_primes

PARA GENEREALIZAÇÕES DO PRESENTE ALGORITMO: https://arxiv.org/pdf/2207.12407


*/


//*******************************************************************************************************************
//CABEÇALHO
#ifndef SAFE_PRIMES_H
#define SAFE_PRIMES_H
#include"sophie_german_primes.h"
#include<stdio.h>


//*******************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool terzic_safe_prime_test(uint64_t);


//*******************************************************************************************************************
//FUNÇÕES
//Função que testa a primalidade de inteiros da forma q=2p+1 se p=5 (mod 6) com p primo
bool terzic_safe_prime_test(uint64_t p){

  //Restrição
  if((p%6)!=5){
    printf("Teste inconclusivo!\n");
    return false;
  };


  //Variáveis locais
  uint64_t q=(p<<1)+1;
  uint64_t t=mod_bin_pow(3, p, q);


  //Análise do resultado
  if(t==1) return true;
  else return false;


};


//*******************************************************************************************************************
//FIM DO HEADER
#endif

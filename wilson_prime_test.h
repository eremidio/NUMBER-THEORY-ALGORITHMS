//VAMOS CRIAR UM PROGRAMA QUEM IMPLEMENTA O TESTE DE PRIMALIDADE BASEADO NO CRITÉRIO DE WILSON

/*
O CHAMADO TEOREMA DE WILSON AFIRMA QUE UM NÚMERO p É PRIMO SE E SOMENTE SE (p-1)!=(p-1) mod(p).
ESTE TEOREMA FORNECEUM TESTE EXTREMAMENTE BÁSICO PARA TESTAR A PRIMALIDADE DE UM NÚMERO.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Wilson%27s_theorem

*/ 


//**************************************************************************************************************************
//CABEÇALHO
#ifndef WILSON_PRIME_TEST_H
#define WILSON_PRIME_TEST_H
#include"mod_bin_exponentiation.h"
#include<stdbool.h>

//**************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
bool wilson_prime_test(uint64_t);

//**************************************************************************************************************************
//FUNÇÕES
bool wilson_prime_test(uint64_t n){
  
  //Casos bases:
  if(n<2) return false;
  if(n==2 || n==3) return true;
  if(!(n&1)) return false;//Descartando números pares

  //Etapa 1: pré-seleção de acordo com o critério p² (mod 6)=1 válidos para primos superiores a 5
  if(mul_mod(n, n, 6)!=1) return false;

  //Etapa 2: aplicando o teorema de Wilson checando a congruência (p-1)! mod p=(p-1)
    //Variáveis locais
    uint64_t result=1;

    //Procedimentos
     //Loop principal
      for(uint64_t a=2; a<n; ++a) result=mul_mod(result, a, n);

  //Resultado
  if(result==(n-1)) return true;
  else return false;


}

//**************************************************************************************************************************
//FIM DO HEADER
#endif

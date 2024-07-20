//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE STRASSEN POLLARD PARA FATORAR NÚMEROS INTEIROS 

/*

O ALGORITMO DE STRASSEN (POLLARD) É O ALGORITMO MAIS RÁPIDO PARA FATORAR NÚMEROS INTEIROS CUJA COMPLEXIDADE E TEMPO DE EXECUÇÃO SÃO RIGOROSAMENTE DETERMINADOS EM NOTAÇÃO
BIG-O SUA COMPLEXIDADE É O(n^(1/4)log(n)).

O ALGORITMO É EXTREMAMENTE SIMPLES E BASEIA-SE NA OBSERVAÇÃO DE QUE UM NÚMERO COMPOSTO TEM PELO MENOS UM FATOR PRIMO INFERIOR A n^(1/2) SENDO d=n^(1/4), ENTÃO 
mmc(d²! mod n, n)>1. 

NESTE CASO d²! mod n =b(0)b(1)...b(d-1), ONDE DEFINE-SE PARA i INTEIRO b(i)=(i.d+1)(i.d+2)...(i.d+d) mod n

PARA MAIORES INFORMAÇÕES: https://web.maths.unsw.edu.au/~davidharvey/talks/factoring.pdf

*/

//*****************************************************************************************************************************************************************
//CABEÇALHO
#ifndef STRASSEN_POLLARD_FACTORIZATION_H
#define STRASSEN_POLLARD_FACTORIZATION_H
#include"int128.h"
#include"binary_multiplication.h"
#include"sqrt128.h"

//*****************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
__int128_t gcd128(__int128_t, __int128_t);
__int128_t generate_divisor(__int128_t, __int128_t, __int128_t);
void strassen_pollard_factorization(__int128_t);

//*****************************************************************************************************************************************************************
//FUNÇÕES

//Algoritmo de Euclides para inteiros de 128 bits
__int128_t gcd128(__int128_t a, __int128_t b){

  
  //Variáveis locais
  int bit_shift=0;

  //Procedimentos
    //Caso trivial
    if(b==a || b==0)
      return a;
    if(a==0)
      return b;


    //Invertendo os argumentos da função se a<b
    if(a<b)
      return gcd128(b, a);


    //Removendo fatores 2 em comum
    while(!(a&1) && !(b&1)){
      a>>=1; b>>=1;
      bit_shift++;
    }

    //Loop principal
    while(a>b || a<b){

      if(a>b){
        a-=b;
        while(!(a&1)) a>>=1;
      }

      if(a<b){
        b-=a;
        while(!(b&1)) b>>=1;
      }

    }

  //Em caso de falha
  return (b<<bit_shift);
                                             };


//Função que calcula um número que contém possíveis divisores de um inteiro a ser fatorado
__int128_t generate_divisor(__int128_t multiplier, __int128_t bound, __int128_t number){

  //Variáveis locais
  __int128_t temp=1, result=1, tester;
  __int128_t lower=binary_multiplication(multiplier, bound);
  __int128_t upper=lower+bound+1;


  //Procedimentos
    //Loop principal
    for(__int128_t i=lower; i<upper; ++i){
      temp=result;
      result=binary_multiplication(temp, i)%number;
    };


  //Resultado
  return result;
                                                                                       };




//Função que implementa o algoritmo de Strassen-Pollard
void strassen_pollard_factorization(__int128_t number){


  //Variáveis locais
  __int128_t d=sqrt128(sqrt128(number));
  __int128_t factor1, factor2, tester;


  //Procedimentos
    //Loop principal
    for(__int128_t i=(d+2); i>=0; --i){

      //Condição que determina a primalidade do número em questão
      if(i==0){
        printf("O número em questão é primo.\n");
        return;
      };


      //Cálculo de possíveis fatores primos
      tester=generate_divisor(i, d, number);

      factor1=gcd128(tester, number);
      if(factor1>1){
        factor2=number/factor1;
        break;
      };


    };


  //Resultado da execução do algoritmo
  printf("Fatores encontrados:\n");
  printf128(factor1);
  printf128(factor2);

};

//*****************************************************************************************************************************************************************
//FIM DO HEADER
#endif

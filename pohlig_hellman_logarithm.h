//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE POHLIG HELLMAN E BAY-STEP-GIANT-STEP PARA O CÁLCULO DE LOGARITMO DISCRETO

/*
DADO UM NÚMERO INTEIRO, UM TEOREMA GARANTE QUE O MESMO POSSUI UMA EXPANSÃO ÚNICA EM POTÊNCIA DE FATORES PRIMOS. O ALGORITMO DE POHLIG-HELLMAN É USADO PARA CALCULAR 
LOGARITMOS DISCRETOS NOS CASOS EM QUE A ORDEM DO GRUPO CÍCLICO EM QUESTÃO É COMPLETAMENTE FATORADA EM RELAÇÃO A UMA PEQUENA BASE DE NÚMEROS PRIMOS. O ALGORITMO DE
POHLIG-HELLMAN PERMITE COMPUTAR A ORDEM DE VÁRIOS SUBGRUPOS CÍCLICOS DE ORDEM p(i)^k(i), ONDE p(i) É UM FATOR PRIMO DA ORDEM n DO GRUPO EM QUESTÃO. MEDIANTE UMA
EXPANSÃO DO VALOR DO LOGARITMO DISCRETO EM POTÊNCIAS DE p(i). O RESULTADO PARA O GRUPO ORIGINAL É RECUPERADO VIA TEOREMA DO RESÍDUO CHINÊS.

PARA MAIORES INFORMAÇÕES: https://risencrypto.github.io/PohligHellman/
                          https://en.wikipedia.org/wiki/Pohlig–Hellman_algorithm
                          https://www-ee.stanford.edu/~hellman/publications/28.pdf
                          https://archive.org/details/handbookofapplie0000mene/page/108/mode/2up
*/


//*******************************************************************************************************************************************************************
//CABEÇALHO
#ifndef POHLIG_HELLMAN_LOGARITHM_H
#define POHLIG_HELLMAN_LOGARITHM_H
#include"baby_step_giant_step_binary.h"
#include"mod_bin_exponentiation128.h"
#include"factorization_map.h"
#include"chinese_remainder_theorem.h"
#include<stdlib.h>


//*******************************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int64_t modular_inverse(int64_t, int64_t);
int64_t pohlig_hellman_logarithm_power_prime_order(int64_t, int64_t, int64_t, int64_t);
int64_t pohlig_hellman_logarithm_generalized(int64_t, int64_t, int64_t);

//*******************************************************************************************************************************************************************
//FUNÇÕES AUXIARES
//Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de euclides
int64_t modular_inverse(int64_t a, int64_t n){

  //Variáveis locais
  int64_t  r0,r1, x0, x1, r2, x2;


  //Procedimentos 
    //Ajuste de variáveis
    r0=a;
    r1=n;
    r2=1;
    x0=1;
    x1=0;

    //Calculando os valores finais coeficientes recursivamente
    while(r2>0){
      int64_t quotient= r0/r1;
      r2=r0-quotient*r1;
      x2=x0-quotient*x1;


    //Atualizando variáveis para a próxima iteração
    if(r2>0){
      r0=r1;
      r1=r2;
      x0=x1;
      x1=x2;
            };

              };
  

  //Resultado
  if(x1<0)
    return(x1+n);
  else
    return x1;
                                             };



//*******************************************************************************************************************************************************************
//FUNÇÕES 
//Função que implementa o algoritmo de Pohlig-Helmann para grupos cíclicos cuja ordem é potência de um número primo
int64_t pohlig_hellman_logarithm_power_prime_order(int64_t g, int64_t h, int64_t prime, int64_t power){

  //Variáveis locais
  int64_t x0=0, x1=0;
  int64_t k, dk, hk, gxk;
  int64_t prime_power=bin_pow(prime, power);
  int64_t prime_power2=prime_power/prime;
  int64_t gamma=mod_bin_pow(g, prime_power2, prime_power);


  //Procedimentos
    //Loop principal
    for(k=0; k<power; ++k){
      gxk=modular_inverse(bin_pow(g, x1), prime_power);
      int64_t temp=(prime_power2-k);
      hk=mod_bin_pow((gxk*h), temp, prime_power);
      dk=baby_step_giant_step_binary(gamma, hk, prime);

     x1=(x0+bin_pow(prime, k)*dk)%prime_power;
     x0=x1;

    };
  

  //Resulatdo
  return x1;

};


//Função que implementa o algoritmo de Pohlig-Hellman para o caso mais geral quando a ordem do grupo cíclico é decomposável em uma pequena base de primos
int64_t pohlig_hellman_logarithm_generalized(int64_t g, int64_t h, int64_t m){

  //Variáveis locais
  int64_t * logs_array=NULL;
  int64_t * prime_power_array=NULL;
  uint64_t prime_factors[30];
  int prime_powers[30];
  int index=0;
  int64_t ord=(m-1);
  int64_t gi, hi;
  int64_t x;
  

  //Procedimentos
    //Decomposição da ordem  do grupo em fatores primos
    factorization_map(ord, prime_factors, prime_powers);

    //Loop principal: resolvendo o problema do log discreto nos subgrupos cíclicos de ordem de potência de primos
    for(int k=0; prime_factors[k]>0; ++k){
      index++;
      logs_array=(int64_t*)realloc(logs_array, index*sizeof(int64_t));
      prime_power_array=(int64_t*)realloc(prime_power_array, index*sizeof(int64_t));
      
      prime_power_array[index-1]=bin_pow(prime_factors[k], prime_powers[k]);
      int64_t exponent=ord/prime_power_array[index-1];
      gi=mod_bin_pow(g, exponent, ord);
      hi=mod_bin_pow(h, exponent, ord);
      logs_array[index-1]=pohlig_hellman_logarithm_power_prime_order(gi, hi, prime_factors[k], prime_powers[k]);
      
    }

    //Calculando o resultado final via teorema do resto chinês
    x=chinese_remainder_theorem(logs_array, prime_power_array, index);


  //Resultado e limpeza do cachê de memória
  if(logs_array) free(logs_array);
  if(prime_power_array) free(prime_power_array);
    
  return x;

};


//*******************************************************************************************************************************************************************
//FIM DO HEADER
#endif

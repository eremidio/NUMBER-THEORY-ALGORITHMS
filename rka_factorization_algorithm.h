//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO RKA (RABIN-KARP-ADLEMAN) PARA FATORAR NÚMEROS INTEIROS DE 64 BITS


/*
O ALGORITMO RKA CONVERTE O PROBLEMA DE FATORAR NÚMEROS INTEIROS EM UM PROBLEMA ANÁLOGO AO
DE SE COMPUTAR LOGARITMOS DISCRETOS. É UM MÉTODO QUE GUARDA SIMILARIDADES COM O ALGORITMO
DE FERMAT, SENDO PARTICULARMENTE EFICIENTE QUANDO A DIFERENÇA ENTRE FATORES PRIMOS É 
SUFICIENTEMENTE PEQUENA.

ARITGO DISPONÍVEL EM: https://eprints.qut.edu.au/16142/1/Yousef_Bani_Hammad_Thesis.pdf

VAMOS IMPLEMENTAR AQUI A VARIANTE MAIS SIMPLES DO ALGORITMO, UMA VERSÃO MAIS ROBUSTA ESTÁ
DISPONÍVEL NO ARTIGO ACIMA.
*/


//****************************************************************************************************************************************
//CABEÇALHO
#ifndef RKA_FACTORIZATION_ALGORITHM_H
#define RKA_FACTORIZATION_ALGORITHM_H
#include"mod_bin_exponentiation128.h"
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdio.h>

//****************************************************************************************************************************************
//DECLARAÇÃO DE ROTINAS AUXILIARES
__int128_t modular_inverse(__int128_t, __int128_t);
uint64_t gcd_rka(uint64_t, uint64_t);

//****************************************************************************************************************************************
//ROTINAS AUXILIARES
// Função que calcula o inverso modular de um número inteiro a (mod n) usando o algoritmo extendido de Euclides
__int128_t modular_inverse(__int128_t a, __int128_t n) {
  // Variáveis locais
  __int128_t r0, r1, x0, x1, r2, x2;

  // Procedimentos
  // Ajuste de variáveis
  r0 = a;
  r1 = n;
  r2 = 1;
  x0 = 1;
  x1 = 0;

  // Calculando os valores finais dos coeficientes recursivamente
  while (r2 > 0) {
    __int128_t quotient = r0 / r1;
    r2 = r0 - quotient * r1;
    x2 = x0 - quotient * x1;

    // Atualizando variáveis para a próxima iteração
    if (r2 > 0) {
      r0 = r1;
      r1 = r2;
      x0 = x1;
      x1 = x2;
    };
  };

  // Resultado
  if (x1 < 0)
    return (x1 + n);
  else
    return x1;
};

//Função que implementa o algoritmo de Euclides
uint64_t gcd_rka(uint64_t a, uint64_t b){

  if(b==0) return a;
  else return gcd_rka(b, (a%b));

};


//****************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void rka_factorization_algorithm(uint64_t);

//****************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo RKA para fatorar números inteiros de 64 bits
void rka_factorization_algorithm(uint64_t n){

  //Variáveis locais
  __int128_t  h_, c;
  uint64_t* A=NULL;
  uint64_t A_size=0;
  uint64_t e=floor(log(n)/log(2));
  uint64_t k, x, h, z,  m=1, a=2;
  uint64_t factor, cofactor, root=sqrt(n);


  //Procedimentos
    //Précomputação de parâmetros usados no algoritmo
    k=((n+1)/2)-(floor(sqrt(n))+1);
    c=mod_bin_pow(4, k, n);
    if(c==1){
      x=k;
      goto factor_computation;
    };

    for(z=0; z<=(e*e); ++z){
      A_size++;
      A=(uint64_t*)realloc(A, A_size*sizeof(uint64_t));
      A[A_size-1]=mod_bin_pow(4, z, n);

    }

    for(uint64_t i=1; i<(e*e); ++i){
      if(c==A[i]){
        z=i;
        x=k-z;
        goto factor_computation;
                 }
    }


    h_=bin_pow(4, (e*e));
    h=modular_inverse(h_, n);

    //Fase iterativa: refinando os valores dos parâmetros usados no algoritmos
    while(1){
      c=(c*h)%n;
      for(uint64_t i=1; i<(e*e); ++i){
        if(c==A[i]){
          z=i;
          x=k-(m*e*e)-z;
          goto factor_computation;
                   }
      }

      m++; //Ajuste de variáveis

    }


    //Computando fatores primos
    factor_computation:
  
    while(!(x&1) && mod_bin_pow(4, x, n)==1) x>>=1;
    if(mod_bin_pow(4, x, n)!=1) x<<=1;
  
    while(a<root){
      factor=gcd_rka((mod_bin_pow(a, x, n)-1), n);
      if(factor>1 && factor<n) break;
      factor=gcd_rka((mod_bin_pow(a, x, n)+1), n);
      if(factor>1 && factor<n) break;
      a++;

    }

    //Exibindo o resultado da execução do algoritmo
    cofactor=n/factor;
    printf("Fatores de %lu: %lu e %lu\n", n, factor, cofactor);

    //Limpando o cachê de memória
    if(A) free(A);  

};


//****************************************************************************************************************************************
//FIM DO HEADER
#endif


// VAMOS CRIAR UM PROGRAMA QUEEMPREGA O ALGORITMO DE FATORAÇÃO DE HART PARA
// FATORAR INTEIROS DE ATÉ 64 BITS

/*
O ALGORITMO DE HART É UMA APRIMORAMENTO DO ALGORTIMO DE FERMAT PARA FATORAR
NÚMEROS INTEIROS.

PARA MAIORES INFORMAÇÕES: http://selmer.warwick.ac.uk/onelinefactor.pdf
                          The Joy Of Factoring by Samuel Wagstaff Jr

*/

//***********************************************************************************************************************************************************************
// CABEÇALHO
#ifndef HART_FACTORIZATION_H
#define HART_FACTORIZATION_H
#include"prime_power_detection.h"
#include <stdio.h>


//***********************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
int64_t gcd_s64(int64_t, int64_t);
void trial_division(int64_t*, int64_t);
void hart_factorization(int64_t);

//***********************************************************************************************************************************************************************
// FUNÇÕES
//Função que implementa o algoritmo de Euclides para inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t b){

  if(b==0) return a;
  else return gcd_s64(b, (a%b));

};


// Função que performa tentativa por divisão até a raiz cúbica do número a ser fatorado
void trial_division(int64_t* n, int64_t cbrt_n) {
  // Variáveis locais
  int64_t N=(*n);
  int64_t i;

  // Procedimentos
   // Fatores 2 e 3
    while (!(N&1)) {
      N/= 2;
      printf("2, ");
    };

    while ((N % 3) == 0) {
      N/= 3;
      printf("3, ");
    };

    // Loop principal
    for (i = 5; i < (cbrt_n + 100); i += 6) {
      while ((N % i) == 0) {
        N /= i;
        printf("%li, ", i);
      };

      while ((N % (i + 2)) == 0) {
        N /= (i + 2);
        printf("%li, ", (i + 2));
      };
    };

    //Atualizando variáveis
    (*n)=N;

};



// Função que implementa o algoritmo de Hart
void hart_factorization(int64_t n) {
  // Variáveis locais
  int64_t n_ = n;
  int64_t cbrt_n = cbrt(n_);
  int64_t i, s, t, m, factor;

  // Procedimentos
    // Etapa 1: teste por divisão até a raíz cúbica do número a ser fatora do (caso o número em questão tenha mais de dois fatores primos)
    trial_division(&n_, cbrt_n);

    if (n_ == 1) {
      printf("...\n");
      return;
    };

  
    // Etapa 2: loop principal
    for(i = 1; i <= cbrt_n; ++i){
      s=ceil(sqrt(n*i));
      m=(s*s)%n;
      if(fast_square_detection(m, &t)==true) break;
  
    }
    
    factor=gcd_s64((s-t), n_);    



    // Printando o resultado da execução da segunda etapa do algoritmo na tela
    if(factor>1 && factor<n_)
      printf("Fatores de %li encontrados na segunda etapa do algoritmo: %li, %li, ...\n", n, factor, (n_ / factor));
    else printf("%li é primo\n", n_);

};

//***********************************************************************************************************************************************************************
// FIM DO HEADER
#endif

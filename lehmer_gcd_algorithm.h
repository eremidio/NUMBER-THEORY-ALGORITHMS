//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE LEHMER PARACACALCULAR OMDC DE DOIS INTEIROS DE 128 BITS

/*
O ALGORITMO DE LEHMER ÉUMA INTERESSANTE VARIANTE DO ALGORITMO DE EUCLIDES
USANDO OPERAÇÕES DE PRECISÃO SIMPLES NO LUGAR DE OPERAÇÕES DE PRECISÃO
MÚLTIPLA QUANDO TRABALHANDO COM GRANDES VALORES.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Lehmer%27s_GCD_algorithm
                          A Course In Computational Algebraic Number Theory by Henri Cohen

*/


//****************************************************************************************************************
//CABEÇALHO
#ifndef LEHMER_GCD_ALGORITHM_H
#define LEHMER_GCD_ALGORITHM_H
#include<math.h>
#include"int128.h"


//CONSTANTES GLOBAIS
const int64_t M=4611686018427387904;//2^62


//****************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
int64_t gcd_s64(int64_t, int64_t);
__int128_t gcd_s128(__int128, __int128_t);
__int128_t lehmer_gcd_s128(__int128, __int128_t);

//****************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Euclides para inteiros de 64 bits
int64_t gcd_s64(int64_t a, int64_t b){

  if(b==0) return a;
  else return gcd_s64(b, (a%b))  ;

};

//Função que implementa o algoritmo de Euclides para inteiros de 128 bits
__int128_t gcd_s128(__int128 a, __int128_t b){

  //Variáveis locais
  __int128_t r=(a%b);

  //Procedimentos
    //Ajuste de variáveis
    a=b; b=r;

    //Calculando o gcd usando operações simples
    if(b==0) return a;
    else{
      int64_t a_=a; int64_t b_=b;
      return gcd_s64(a_, b_);  //Operações de divisão de precisão simples
    }

};

//Função que implementa o algoritmo de Lehmer para calcular o gcd de dois números inteiros
__int128_t lehmer_gcd_s128(__int128 a, __int128_t b){
  
  //Restrição
  if(a < b){
    __int128_t temp = a;
    a = b;
    b = temp;
  };

  //Variáveis locais
  __int128_t t, r;
  int64_t a_, b_;
  int64_t A=1, B=0, C=0, D=1, T=0, q=0;


  //Procedimentos
    //Loop principal
    while (b >= M){

      //Ajuste de variáveis
      a_ = a >> 62;//Computando o digito mais signficativo de a
      b_ = b >> 62;//Computando o digito mais signficativo de b
      A = 1; B = 0; C = 0; D = 1;

      //Loop euclidiano
      while (1) {
        q = (a_ + A) / (b_ + C);
        if (q != (a_ + B) / (b_ + D)) break;

        T = A - (q * C); A = C; C = T;
        T = B - (q * D); B = D; D = T;
        T = a_ - (q * b_); a_ = b_; b_ = T;
      }
  
      //Etapa de precisão múltipla
      if (B == 0) {
        t = a % b;
        a = b;
        b = t;
      }
      else {
        t = (A * a) + (B * b);
        r = (C * a) + (D * b);
        a = t;
        b = r;
      }
    }

  //Resultado
  return gcd_s128(a, b);

};


//****************************************************************************************************************
//FIM DO HEADER
#endif

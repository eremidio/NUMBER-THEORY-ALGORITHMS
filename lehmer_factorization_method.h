// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O MÉTODO DE LEHMER PARA FATORAR NÚMEROS INTEIROS

/*
O MÉTODO DE LEHMER É UM EFICIENTE MÉTODO PARA FATORAR NÚMEROS SEMIPRIMOS (n=pq,
COM p, q PRIMOS) ATÉ ~ 10^25 , ~ 10^30.

ESTE ALGORITMO USA FORMAS QUADRÁTICAS DO TIPO λN = x²-Dy², COM λ = -1, 1, 2 E D
= -1, 1, 2, -2, 3, -3, 6, -6; PARA COMPUTAR NÚMEROS PRIMOS. SE DUAS SOLUÇÕES
INTEIRAS (x1, y1) (x2, y2) FOREM ENCONTRADAS PARA UMA DAS FORMAS QUADRÁTICAS EM
QUESTÃO ENTÃO UM POSSÍVEL FATOR PRIMO É OBTIDO CALCULANDO-SE mdc(n,
|x1y2-x2y1|).

O MÉTODO CONSISTE EM TESTAR MÚLTIPLOS VALORES DE y DENTRO DE LIMITES BEM
ESTABELECIDOS USANDO-SE CRITÉRIOS BASEADOS NOS PARÂMETROS λ, D E TESTANDO SE x É
QUADRADO PERFEITO. A ESCOLHA DA FORMA QUADRADA ADEQUADA É FEITAS BASEADO NA
RELAÇÃO DE CONGRUÊNCIA r = n (mod 24).

PARA REFERÊNCIAS:
https://www.ams.org/journals/mcom/1974-28-126/S0025-5718-1974-0342458-5/S0025-5718-1974-0342458-5.pdf

*/

//******************************************************************************************************************************************
// CABEÇALHO
#ifndef LEHMER_FACTORIZATION_METHOD_H
#define LEHMER_FACTORIZATION_METHOD_H
#include <math.h>
#include <stdbool.h>
#include "int128.h"
#include "sqrt128.h"


//CONSTANTES GLOBAIS
const int q11[11]={1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0};
const int q63[63]={1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
const int q64[64]={1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0};
const int q65[65]={1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1};


//******************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
bool fast_square_detection(__int128_t, __int128_t*);
void select_quadratic_form_coefficients(__int128_t, signed[], signed[]);
void set_y_bounds(double*, double*, __int128_t, signed, signed);
__int128_t gcd128(__int128_t, __int128_t);
bool find_quadratic_representation(__int128_t, __int128_t, __int128_t, signed,
                                   signed, __int128_t[], __int128_t[]);
void lehmer_factorization_method(__int128_t);

//******************************************************************************************************************************************
// FUNÇÕES
//Função que determina se um número é um quadrado perfeito
bool fast_square_detection(__int128_t number, __int128_t* root){

  //Variáveis locais
  __int128_t t=(number%64), r;

  //Procedimentos
    //Testes rápidos para detecção de não quadrados perfeitos
      //Teste 1:
      if(q64[t]==0) return false;

      //Ajuste de variáveis
      r=(number%45045);  
      //Teste 2:
      if(q63[r%63]==0) return false;
      //Teste 3:
      if(q65[r%65]==0) return false;
      //Teste 4:
      if(q11[r%11]==0) return false;

      //Teste 5:
      r=sqrt128(number);
      if((r*r)==number){
        (*root)=r;
        return true;      
      }
      else return false;

};

// Função que determina os coefficients λ, D das formas quadráticas λN = x²-Dy² a serem usadas no algoritmo
void select_quadratic_form_coefficients(__int128_t number,
                                        signed lambda_array[],
                                        signed D_array[]) {
  // Variáveis locais
  __int128_t residue = (number % 24);

  // Procedimentos
  if (residue == 1) {
    lambda_array[0] = 1;
    lambda_array[1] = 1;
    lambda_array[2] = 1;
    D_array[0] = (-2);
    D_array[1] = (-3);
    D_array[2] = 6;
  };

  if (residue == 5) {
    lambda_array[0] = 1;
    lambda_array[1] = 2;
    lambda_array[2] = (-1);
    D_array[0] = (-1);
    D_array[1] = (-6);
    D_array[2] = 6;
  };

  if (residue == 7) {
    lambda_array[0] = 1;
    lambda_array[1] = 1;
    lambda_array[2] = 1;
    D_array[0] = 2;
    D_array[1] = (-3);
    D_array[2] = (-6);
  };

  if (residue == 11) {
    lambda_array[0] = 1;
    lambda_array[1] = (-1);
    lambda_array[2] = 2;
    D_array[0] = (-2);
    D_array[1] = 3;
    D_array[2] = (-6);
  };

  if (residue == 13) {
    lambda_array[0] = 1;
    lambda_array[1] = 1;
    lambda_array[2] = 1;
    D_array[0] = (-1);
    D_array[1] = (-3);
    D_array[2] = 3;
  };

  if (residue == 17) {
    lambda_array[0] = 1;
    lambda_array[1] = 1;
    lambda_array[2] = 1;
    D_array[0] = (-1);
    D_array[1] = (-2);
    D_array[2] = 2;
  };

  if (residue == 19) {
    lambda_array[0] = 1;
    lambda_array[1] = 1;
    lambda_array[2] = 1;
    D_array[0] = (-2);
    D_array[1] = (-3);
    D_array[2] = 6;
  };

  if (residue == 23) {
    lambda_array[0] = 1;
    lambda_array[1] = (-1);
    lambda_array[2] = (-1);
    D_array[0] = 2;
    D_array[1] = 3;
    D_array[2] = 6;
  };
};

// Função que determina intervalos de possíveis valores para y na representação via forma quadrática λN = x²-Dy²
void set_y_bounds(double* upper, double* lower, __int128_t number,
                  signed lambda, signed D) {
  // Variáveis locais
  unsigned D_abs = (D > 0) ? D : ((-1) * D);
  unsigned lambda_abs = (lambda > 0) ? lambda : ((-1) * lambda);
  unsigned D_root = sqrt(D_abs);
  unsigned T = 1;
  unsigned lambda_root = sqrt(lambda_abs);
  __int128_t root = sqrt128(number);

  // Procedimentos
  // Cálculo do parâmetro T solução da equação de Pell T²-DU²=1
  if (D < 0) T = 1;
  if (D == 2) T = 3;
  if (D == 3) T = 7;
  if (D == 6) T = 49;

  // Cálculo dos valores mínimos e máximos de y
  // Caso 1
  if (D < 0) {
    (*upper) = (1.0 * root * lambda_root) / D_root;
    (*lower) = 0;
  };

  // Caso 2
  if (D > 1 && lambda > 0) {
    (*upper) = (1.0 * root * lambda_root * sqrt((T - 1) / 2.0)) / D_root;
    (*lower) = 0;
  };

  // Caso 3
  if (D > 1 && lambda < 0) {
    (*upper) = (1.0 * root * lambda_root * sqrt((T + 1) / 2.0)) / D_root;
    (*lower) = (1.0 * root * lambda_root) / D_root;
  };
};

// Função que implementa o algoritmo de Euclides para inteiros de 128 bits
__int128_t gcd128(__int128_t a, __int128_t b) {
  if (b == 0)
    return a;
  else
    return gcd128(b, (a % b));
};

// Função que calcula uma representação de um inteiro a ser fatorado como uma
// forma quadrática  λN = x²-Dy²
bool find_quadratic_representation(__int128_t number, __int128_t upper,
                                   __int128_t lower, signed lambda, signed D,
                                   __int128_t x_array[], __int128_t y_array[]) {
  __int128_t x, y, x_squared;
  short matches = 0;

  // Procedimentos
  // Loop principal
  for (y = lower; y <= upper; y++) {
    x_squared = (lambda * number) + (D * y * y);
    if(fast_square_detection(x_squared, &x)==false) continue;

    if ((lambda * number) == ((x * x) - (D * y * y))) {
      x_array[matches] = x;
      y_array[matches] = y;
      matches++;
    };

    if (matches > 1) return true;
  };

  // Resultado
  return false;
};

// Função que implementa o algoritmo de Lehmer para fatorar números inteiros
void lehmer_factorization_method(__int128_t number) {
  // Variáveis locais
  double upper_y = 0.0, lower_y = 0.0;
  __int128_t x_array[2], y_array[2];
  __int128_t factor = 1, cofactor = 1;
  __int128_t x1y2 = 0, x2y1 = 0;
  signed lambda_array[3], D_array[3];
  signed lambda, D;
  bool factor_test;

  // Procedimentos
  // 1: Cálculo dos parâmetros λ, D das formas quadráticas λN = x²-Dy² a serem
  // usadas no algoritmo
  select_quadratic_form_coefficients(number, lambda_array, D_array);

  // 2: Loop principal: calculando rprtesentações de N usando formas quadráticas
  // λN = x²-Dy²
  for (int q_form = 0; q_form < 3; q_form) {
    lambda = lambda_array[q_form];
    D = D_array[q_form];

    // Calculando valores de intervalo para y
    set_y_bounds(&upper_y, &lower_y, number, lambda, D);

    // Determinando representações de N via formas quadráticas λN = x²-Dy²
    factor_test = find_quadratic_representation(number, (__int128_t)upper_y,
                                                (__int128_t)lower_y, lambda, D,
                                                x_array, y_array);

    // Cálculo dos fatores primos do número em questão
    if (factor_test == true) {
      x1y2 = x_array[0] * y_array[1];
      x2y1 = x_array[1] * y_array[0];

      if (x2y1 > x1y2) {
        factor = gcd128((x2y1 - x1y2), number);
        cofactor = number / factor;
      };

      if (x2y1 < x1y2) {
        factor = gcd128((x1y2 - x2y1), number);
        cofactor = number / factor;
      };

      // Resultado da execução do algoritmo
      if (factor > 1 && cofactor > 1 && factor < number && cofactor < number) {
        printf("Fatores primos encontrados:\n");
        printf128(factor);
        printf128(cofactor);
        return;
      };
    };

  };  // Loop sobre as formas quadráticas

  printf("O algoritmo não foi capaz de fatorar o número em questão.\n");
};

//******************************************************************************************************************************************
// FIM DO HEADER
#endif

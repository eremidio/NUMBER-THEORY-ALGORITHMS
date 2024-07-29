// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE CHAKRAVALA PARA
// RESOLVER DIOFANTINAS QUADRÁTICAS IRREDUTÍVEIS DO TIPO x²-Ny²=1, COM N INTEIRO

/*
O ALGORITMO DE CHAKRAVALA É UM EFICIENTE ALGORITMO PARA RESOLVER EQUAÇÕES
DIOFANTINAS DO TIPO x²-Ny²=1 (EQUAÇÃO DE PELL), COM N INTEIRO.

A IDEIA BÁSICA DO ALGORITMO USA A IDENTIDADE DE BRAHMAGUPTA
(a²-nb²)(c²-nd²)=(ac-nbd)²-n(ad-bc)². A IDEIA BÁSICA É FAZER A COMPOSIÇÃO DE UMA
TRIPLA (a,b,k) QUE OBDEDECE A a²-Nb²=k COM A TRIPLA TRIVIAL(m, 1, m²-N) QUE
RESULTA EM (am+Nb, a+bm, k(m²-N)), REDUÇÃO DESTA TRIPLA ORDENADA PELO FATOR k É
REALIZADA ATÉ SE OBTER UM CASO COM k= 1, -1, 2, -2, 4, -4.  NESTA SITUAÇÃO
PODEMOS USAR O PROCEDIMENTO CHAMADO COMPOSIÇÃO DE BRAHMAGUPTA QUE SEMPRE CONDUZ
A UMA SOLUÇÃO DA EQUAÇÃO ORIGINAL.

A SUBSTITUIÇÃO ACIMA TRANSFORMA a²-Nb²=k EM
[(am+Nb)/|k|]²-N[(a+bm)/|k|]²=[(m²-N)/k], A IDEIA É ENCONTRAR UM VALOR DE m TAL
QUE [(a+bm)/|k|] SEJA INTEIRO. O MÉTODO DEFINE O VALOR IDEAL DE m COMO O QUE
MINIMIZA m²-N. É POSSÍVEL PROVAR QUE ESTE ALGORITMO SEMPRE FORNECE UMA SOLUÇÃO
PARA O PROBLEMA ORIGINAL.

PARA MAIORES INFORMAÇÕES:
https://en.wikipedia.org/wiki/Chakravala_method#The_method
                          https://en.wikipedia.org/wiki/Bhaskara%27s_lemma
                          https://en.wikipedia.org/wiki/Brahmagupta%27s_identity

*/

//**********************************************************************************************************************************************************************
// CABEÇALHO
#ifndef CHAKRAVALA_ALGORITHM_H
#define CHAKRAVALA_ALGORITHM_H
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//**********************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
void brahmagupta_composition(int64_t, int64_t, int64_t, int64_t*, int64_t*);
void chakravala_algorithm(int64_t, int64_t, int64_t*, int64_t*);

//**********************************************************************************************************************************************************************
// FUNÇÕES
// Função que implementa o método de composição de Brahmagupta para encontrar x, y satisfazendo x²=Ny²+1 dado a²=Nb²+k, com  k= 1, -1, 2, -2, 4, -4
void brahmagupta_composition(int64_t a, int64_t b, int64_t k, int64_t* x,
                             int64_t* y) {
  // Caso 1: k= 1
  if (k == 1) {
    (*x) = ((2 * a * a) - 1);
    (*y) = (2 * a * b);
  };

  // Caso 2: k= (-1)
  if (k * (-1) == 1) {
    (*x) = ((2 * a * a) + 1);
    (*y) = (2 * a * b);
  };

  // Caso 3: k= 2
  if (k == 2) {
    (*x) = ((a * a) - 1);
    (*y) = (a * b);
  };

  // Caso 4: k= (-2)
  if (k * (-1) == 2) {
    (*x) = ((a * a) + 1);
    (*y) = (a * b);
  };

  // Caso 5: k=4
  if (k == 4) {
    // Caso 5.1: a é par
    if ((a % 2) == 0) {
      (*x) = (((a * a) - 2) / 2);
      (*y) = ((a * b) / 2);
    };
    // Caso 5.2: a é ímpar
    if ((a % 2) == 1) {
      (*x) = ((a * a) - 3);
      (*x) = (*x) * a;
      (*x) = (*x) / 2;
      (*y) = ((a * a) - 1);
      (*y) = (*y) * b;
      (*y) = (*y) / 2;
    };
  };

  // Caso 6: k=(-4)
  if (k * (-1) == 4) {
    (*x) = ((a * a) + 2);
    (*x) = (*x) * ((((a * a) + 1) * ((a * a) + 3)) - 2);
    (*x) = (*x) / 2;
    (*y) = ((((a * a) + 1)) * (((a * a) + 3)) * a * b);
    (*y) = (*y) / 2;
  };
};

// Função que implementa o algoritmo de Chakravala
void chakravala_algorithm(int64_t N, int64_t a, int64_t* x, int64_t* y) {
  // Variáveis locais
  int64_t b, k, abs_k;
  int64_t m, root, ord;
  int64_t a_temp, b_temp, k_temp;
  int64_t x_temp, y_temp;

  // Procedimentos
  // Ajuste de variáveis
  b = 1;
  k = (a * a) - (b * b * N);
  if (k < 0)
    abs_k = (-1) * k;
  else
    abs_k = k;
  root = sqrt(N);

  // TESTES USAR UM // APÓS O MESMO
  // printf("a:%li, b:%li, k:%li, |k|=%li\n", a, b, k, abs_k);

  // Loop principal
  while (true) {
    // Condição que determina se o parâmetro k é aplicável a composição de
    // Brahmagupta
    if (k == 1 || (-1) * k == 1 || k == 2 || (-1) * k == 2 || k == 4 ||
        (-1) * k == 4)
      break;

    // Cálculo do parâmetro m adequado
    for (int64_t i = 0;; ++i) {
      m = (root - i);
      if (m > 0 && ((a + (m * b)) % abs_k) == 0) break;
      m = (root + i);
      if (m > 0 && ((a + (m * b)) % abs_k) == 0) break;
    };


    // Atualizando variáveis para a próxima iteração
    a_temp = ((a * m) + (N * b)) / abs_k;
    b_temp = (a + (m * b)) / abs_k;
    k_temp = ((m * m) - N) / k;

    a = a_temp;
    b = b_temp;
    k = k_temp;
    if (k < 0)
      abs_k = (-1) * k;
    else
      abs_k = k;


  };

  // Calculando os valores de x e y usando a composição de Brahmagupta
  brahmagupta_composition(a, b, k, &x_temp, &y_temp);
  (*x) = x_temp;
  (*y) = y_temp;
};

//**********************************************************************************************************************************************************************
// FIM DO HEADER
#endif

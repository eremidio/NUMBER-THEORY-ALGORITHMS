//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE LEGENDRE PARA COMPUTAR A FUNÇÃO  π(x) DE CONTAGEM DE NÚMEROS PRIMOS

/*
O ALGORITMO DE MAPES É UM EFICIENTE ALGORITMO QUE CONTABILIZA A FUNÇÃO π(x) PARA
A CONTAGEM DE PRIMOS. DADO UM DETERMINADO INTERVALO {1, 2,..., x}, CONTENDO
PRIMOS {p(1), ..., p(a)} O PRINCÍPIO DE INCLUSÃO-EXCLUSÃO AFIRMA QUE:
π(x)=|_x_|-|_x/p(i)_|+|_x/p(i)p(j)_|-|_x/p(i)p(j)p(k)_|+.... (AQUI |_x_| DENOTA
O INTEIRO MENOR MAIS PRÓXIMO DE x).

É POSSÍVEL MOSTRAR QUE O SOMATÓRIO ACIMA PODE SER REESCRITO COMO
π(x)-π(√x)-1=φ(x, π(√x)) ONDE φ(m, n) É UMA FUNÇÃO QUE CONTABILIZA O NÚMERO DE
INTEIROS MENORES QUE m NÃO DIVISÍVEIS PELOS n-ÉSIMOS PRIMEIROS NÚMEROS PRIMOS. A
FUNÇÃO φ(m, n) PODE SER COMPUTADA RECURSIVAMENTE POR MEIO DAS RELAÇÕES:
φ(m, 0)=|_m_| E φ(m, n)=φ(m, (n-1))-φ(m/p(n), (n-1)).

ALGORITMOS MAIS SOFISTICADOS COMO O ALGORITMO DE MEISSEL-LEHMER CONSISTEM EM
REELABORAÇÕES DO SOMATÓRIO ORIGINAL PARA REDUZIR O ESPAÇO USADO PARA ALOCAR UMA
LISTA PRÉ-COMPUTADA DE PRIMOS E PARA REDUZIR A CHAMADAS RECURSIVAS NO CÁLCULO DA
FUNÇÃO φ(m, n).

PARA MAIORES REFERÊNCIAS:
https://en.wikipedia.org/wiki/Prime-counting_function#The_Meissel–Lehmer_algorithm

*/

//****************************************************************************************************************************************************
// CABEÇALHO
#ifndef LEGENDRE_FORMULA_H
#define LEGENDRE_FORMULA_H
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//****************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
int64_t* prime_sieving_counting(int64_t, int64_t*);
int64_t small_counting(int64_t);
int64_t phi_mn(int64_t, int64_t, int64_t[]);
int64_t prime_counting_function(int64_t);

//****************************************************************************************************************************************************
// FUNÇÕES

// Função que contabiliza números primos primos até a raíz quadrada de um limite
// especificado pelo usuário e preenche um buffer de números primos
int64_t* prime_sieving_counting(int64_t n, int64_t* root_counter) {
  // Variáveis locais
  int64_t* prime_array = NULL;
  int64_t prime_index = 0;
  int64_t counter = 0;
  int64_t root = sqrt(n);
  bool sieve_array[root + 100];
  int64_t i, j;

  // Procedimentos

  // Inicializando o array de booleanos
  for (i = 2; i < (root + 100); ++i) sieve_array[i] = true;

  // Peneirando os números primos no intervalo 0, 1, 2,..., n^(1/2)+100
  for (i = 0; (i * i) < (root + 100); i++) {
    if (sieve_array[i] == true) {
      for (j = (i * i); j < (root + 100); j += i) sieve_array[j] = false;
    };
  };

  // Computando o número de primos no intervalo até n^1/2
  for (i = 0; i < (root + 100); ++i) {
    if (sieve_array[i] == true) {
      if (i <= root) counter++;
      prime_index++;
      prime_array =
          (int64_t*)realloc(prime_array, prime_index * sizeof(int64_t));
      prime_array[prime_index - 1] = i;
    };
  };

  // Resultado
  (*root_counter) = counter;
  return prime_array;
};

// Função de contagem de números primos até 100
int64_t small_counting(int64_t n) {
  // Variáveis locais
  int64_t small_primes[168] = {
      2,   3,   5,   7,   11,  13,  17,  19,  23,  29,  31,  37,  41,  43,
      47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97,  101, 103, 107,
      109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181,
      191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263,
      269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
      353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433,
      439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521,
      523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613,
      617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701,
      709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
      811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887,
      907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997};
  int64_t counter = 0;

  // Procedimentos
  for (int i = 0; i < 168; ++i) {
    if (n >= small_primes[i]) counter++;
  };

  // Resultado
  return counter;
};

// Função auxiliar Φ(m, n)
int64_t phi_mn(int64_t m, int64_t n, int64_t prime_array[]) {
  // Resultado
  if (n == 0)
    return floor(m);
  else if (prime_array[n - 1] > m)
    return 1;
  else
    return phi_mn(m, (n - 1), prime_array) -
           phi_mn(m / prime_array[n - 1], (n - 1), prime_array);
};

// Função que implementa o algoritmo de Legendre para a função de contagem de primos
int64_t prime_counting_function(int64_t n) {
  // Caso base
  if (n <= 1000) return small_counting(n);

  // Variáveis locais
  int64_t* prime_array = NULL;
  int64_t prime_root_counter = 0;
  int64_t phi, result;

  // Procedimentos
  // Preenchendo um buffer de primos e computando onúmero de primos  até a raíz
  // quadrada do limite desejado
  prime_array = prime_sieving_counting(n, &prime_root_counter);

  // Computando a função auxiliar Φ(m, n)
  phi = phi_mn(n, prime_root_counter, prime_array);

  // Computando a contagem de primos até o limite especificado pelo usuário
  result = (prime_root_counter + phi - 1);

  // Limpando o cachê de memória e retornando o resultado
  if (prime_array) free(prime_array);
  return result;
};

//****************************************************************************************************************************************************
// FIM DO HEADER
#endif

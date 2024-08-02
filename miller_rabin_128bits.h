// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE MILLER-RABIN PARA INTEIROS DE 128 BITS

/*

O TESTE DE MILLER-RABIN, A PRINCÍPIO, É UM TESTE PROBABILÍSTICO PARA TESTAR A
PRIMALIDADE DE UM NÚMERO INTEIRO. PORÉM ELE PODE SE TORNAR UM TESTE EXATO SE UMA
BASE SUFICIENTEMENTE GRANDE DE PRIMOS FOR USADAS NO TESTE, TAL AFIRMAÇÃO É
CONDICIONAL A HIPÓTESE DE RIEMANN. DO PONTO DE VISTA PRÁTICO, RESULTADOS
ACUSANDO A COMPOSIÇÃO DE UM INTEIRO SÃO CORRETOS, E A CHANCE DE UM FALSO PRIMO
SER DETECTADO É BEM BAIXA (~25%), SE CERTAS CONJECTURAS FOREM COMPROVADAS UM
NÚMERO MINIMO DE BASES DA ORDEM log2(n) É SUFICIENTEPARA ASSEGURAR A PRIMALIDADE
DE UM INTEIRO.

PARA INTEIROS DE 64 BITS PODEMOS USAR AS BASSE {2, 3, 5, 7, 11, 13, 17, 19, 23,
29, 31, 37}. PARA INTEIRO DE 32 BITS A BASE {2, 3, 5, 7} É SUFICIENTE PARA
ASSEGURAR A PRIMALIDADE DO NÚMERO EM QUESTÃO. PARA INTEIROS DE 128 BITS USAREMOS
AS BASES {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67}.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Miller–Rabin_primality_test

*/

//***********************************************************************************************************************************************************
// CABEÇALHO
#ifndef MILLER_RABIN_128BITS_H
#define MILLER_RABIN_128BITS_H
#include <math.h>
#include <stdbool.h>
#include "int128.h"
#include "mod_bin_exponentiation128.h"

//***********************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
__int128_t gcd128(__int128_t, __int128_t);
bool miller_rabin128(__int128_t);

//***********************************************************************************************************************************************************
// FUNÇÕES

// Algoritmo de Euclides para inteiros de 128 bits
__int128_t gcd128(__int128_t a, __int128_t b) {
  if (b == 0)
    return a;
  else
    return gcd128(b, (a % b));
};

// Teste de Miller-Rabin para inteiro de 128bits
bool miller_rabin128(__int128_t n) {
  // Variáveis locais
  __int128_t prime_seed[25] = {2,  3,  5,  7,  11, 13, 17, 19, 23,
                               29, 31, 37, 41, 43, 47, 53, 59, 61,
                               67, 71, 73, 79, 83, 89, 97};
  __int128_t s, d, x, n_even;
  __int128_t tester;
  bool result = false;

  // Procedimentos
  // Testes com primos inferiores a 100
  for (int i = 0; i < 25; ++i) {
    if (n == prime_seed[i]) return true;
    if ((n % prime_seed[i]) == 0) return false;
  };

  // Cálculo dos parâmetros s e d usados no algoritmo
  n_even = (n - 1);
  s = 0;

  while ((n_even % 2) == 0) {
    n_even = n_even / 2;
    s++;
  };

  d = n_even;

  // Loop principal
  for (int i = 0; i < 25; ++i) {
    __int128_t a = prime_seed[i];

    if (a >= n) break;

    __int128_t x = mod_bin_pow(a, d, n);

    if (x == 1 || x == (n - 1)) continue;

    bool prime = false;

    for (int j = 0; j < s - 1; ++j) {
      x = mod_bin_pow(x, 2, n);

      if (x == (n - 1)) {
        prime = true;
        break;
      };
    };

    if (!prime) return false;
  };

  // Caso não passe nos testes acima o número é declarado primo
  return true;
};

//***********************************************************************************************************************************************************
// FIM DO HEADER
#endif

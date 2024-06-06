// VAMOS CRIAR UM PROGRAMA QUE COMPUTA A ORDEM MULTIPLICATIVA DE UM INTEIRO
// MÓDULO OUTRO INTEIRO COPRIMO PARA INTEIROS DE 64 BITS

/*
A ORDEM MULTIPLICATIVA DE UM INTEIRO a MÓDULO UM INTEIRO n DENOTADA POR ord(a) É
DEFINIDA COMO O MENOR INTEIRO x TAL QUE a^x=1 (mod n).

PARA O GRUPOS DE INTEIROS A MENOS DE UMA CONGRUÊNCIA O SEGUINTE TEOREMA DEVIDO A
EULER É ÚTIL PARA COMPUTAR A ORDEM MULTIPLICATIVA DE UM INTEIRO: SE a,n SÃO DOIS
INTEIROS COPRIMOS ENTÃO a^φ(n)=1 (mod n), ONDE φ(n) É A FUNÇÃO TOTIENTE DE
EULER.

TAL TEOREMA PROVIDO DA FATORAÇÃO DE φ(n) PROVÊ UM EFICIENTE MÉTODO DE SE
CALCULAR A ORDEM MULTIPLICATIVA DE UM INTEIRO. A RECIPROCA É VERDADEIRA ord(a) É
EQUIVALENTE A FATORAR n, ESSA É A PARTE CLÁSSICA DO ALGORITMO DE SHOR (QUE USA
TRANSFORMADA DE FOURIER E SUPERPOSIÇÃO DE ESTADOS QUÂNTICOS PARA DETERMINAR
ord(a) DE FORMA EFICAZ), SE a^x=1 (mod n) E x FOR PAR ENTÃO SE (a^x)-1 = 0 (mod n),
PORTANTO [a^(x/2)-1][a^(x/2)+1] = 0 (mod n).

ALGORITMOS MAIS EFICAZES PERMITEM REAGRUPRAR OS FATORES PRIMOS DE φ(n),
REDUZINDO ASSIM O NÚMERO DE EXPONENCIAÇÔES NECESSÁRIAS PARA COMPUTAR ord(a).

PARA MAIORES INFORMAÇÕES: A Course In Computational Number Theory by H. Cohen


*/

//*************************************************************************************************************************************************************
// CABEÇALHO
#ifndef MULTIPLICATIVE_ORDER_H
#define MULTIPLICATIVE_ORDER_H
#include <stdio.h>
#include"factorization_map.h"
#include "euler_totient_function.h"
#include "mod_bin_exponentiation128.h"

//*************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
uint64_t multiplicative_order(uint64_t, uint64_t);

//*************************************************************************************************************************************************************
// FUNÇÕES

// Função que calcula a ordem multiplicativa de um inteiro congruente a um número coprimo
uint64_t multiplicative_order(uint64_t a, uint64_t n) {

  // Restrição: o algoritmo se aplica apenas quando n é coprimo com a
  if (gcd_euclides(a, n) > 1) {
    printf(
        "%lu e %lu não coprimos, o algoritmo não se aplica a estes "
        "parâmetros.\n",
        a, n);
    return 0;
  };

  // Variáveis locais
  uint64_t primes[30];
  int multiplicities[30];
  uint64_t totient = euler_totient_function(n);
  uint64_t M = totient, lowest = totient;

  // Procedimentos
  // Fatorando φ(n)
  factorization_map(totient, primes, multiplicities);

  // Teste sobre os fatores primos de φ(n): determinando o menor x tal que a^x=1
  // (mod n)
  for (int k = 0; k < 30; ++k) {
    if (primes[k] == 0) break;

    // Ajuste de variáveis
    uint64_t reducer= bin_pow(primes[k], multiplicities[k]);
    if(reducer<=0) continue;
    M = totient /reducer;

    // Testando se o expoente φ(n) pode ser reduzido
    for (int l = multiplicities[k]; l >= 0; --l) {
      if (mod_bin_pow(a, M, n) == 1 && M < lowest)
        lowest = M;
      else
        M *= primes[k];
    }
  };

  // Resultado
  return lowest;
};

//*************************************************************************************************************************************************************
// FIM DO HEADER
#endif

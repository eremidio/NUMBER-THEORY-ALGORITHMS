// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE SELFRIDGE PARA TESTAR SE UM NÚMERO É PRIMO OU NÃO

/*
O TESTE DE SELFRIDGE É BASEADO EM UMA CONJECTURA QUE AFIRMA QUE UM NÚMERO p =
2,3 (mod 5)É PRIMO SE E SOMENTE SE:
1. f(p-δ) = 0 mod(p). ONDE f(p) É O (p)-ÉSIMO NÚMERO NA SEQUÊNCIA DE
FIBONACCI E δ=(p|5) É O SÍMBOLO DE LEGENDRE.
2. 2^(p-1)= 1 mod(p).

ESTE É UM RESULTADO AINDA NÃO COMPROVADO, EMBORA FUNCIONE RAZOALMENTE BEM EM
CÁLCULOS PRÁTICOS, SENDO RAZOÁVEL PARA GERAÇÃO DE NÚMEROS PRIMOS ELEVADOS DA
ORDEM 10^100. EXISTEM GENERALIZAÇÕES DESTES ALGORITMO ENVOLVENDO CLASSES
RESIDUAIS DOS CHAMADOS POLINÔMIOS DE FIBONACCI F(x) AVALIADOS PARA O ARGUMENTO
x=1.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Primality_test#Heuristic_tests
                          https://en.wikipedia.org/wiki/Fibonacci_polynomials

*/

//****************************************************************************************************************************************************************
// CABEÇALHO
#ifndef SELFRIDGE_PRIME_TEST_H
#define SELFRIDGE_PRIME_TEST_H
#include <stdbool.h>
#include"fast_lucas_sequence.h"
#include"legendre_symbol.h"
#include "mod_bin_exponentiation128.h"

//****************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
bool selfridge_prime_test(uint64_t);

//****************************************************************************************************************************************************************
// FUNÇÕES
// Função que executao teste de primalidade de Selfridge
/*
NOTA: Impondo-se a condição n=2,3 (mod 5) garante que o resultado tenha maior confiabilidade. Sem contra-exemplos no momento.
*/

bool selfridge_prime_test(uint64_t n) {

  //Casos bases:
  if(n<2) return false;
  if(n==2 || n==3 || n==5) return true;
  if((n % 2) == 0 || (n % 3) == 0 || (n % 5) == 0) return false;

  // Variáveis locais
  __int128_t u,v;

  // Procedimentos
  // Teste 1: teste de Fermat na base 2,3,5
  if (mod_bin_pow(2, (n - 1), n) != 1 || mod_bin_pow(3, (n - 1), n) != 1 || mod_bin_pow(5, (n - 1), n) != 1)
    return false;

  // Teste 2: teste da sequência de Fibonacci F(n)=U(n) para P=1, Q=(-1)
  fast_modular_lucas_sequence(1, (-1), (n-legendre(n, 5)), n, &u, &v);
  if (u != 0) return false;

  // Caso passe nos testes acima um primo foi encontrado
  return true;
};

//****************************************************************************************************************************************************************
// FIM DO HEADER
#endif

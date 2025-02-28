// VAMOS IMPLEMENTAR A FUNÇÃO DE MÖBIUS μ

/*
Α FUNÇÃO DE MÖBIUS É UMA FUNÇÃO MULTIPLICATIVA QUE É DEFINIDA PARA TODO INTEIRO
n:

μ(n)={ 0, SE n CONTÉM ALGUM FATOR PRIMO REPETIDO
     { +1, SE n CONTÉM UM NÚMERO PAR DE FATORES PRIMOS
     { -1, SE n CONTÉM UM NÚMERO ÍMPAR DE FATORES PRIMOS

A FUNÇÃO DE MÖBIUS É MULTIPLICATIVA SE m E n SÃO RELATIVAMENTE PRIMOS ENTRE SI:
μ(nm) = μ(n).μ(m)

A APLICAÇÃO MAIS IMPORTANTE DA FUNÇÃO DE MÖBIUS É A CHAMADA FÓRMULA DE INVERSÃO:
SEJAM f E g DUAS FUNÇÕES ARITMÉTICA TAIS QUE g(n)= Σf(d), ONDE n É UM INTEIRO
QUALQUER E d REPRESENTA O CONJUNTO DOS DIVISORES DE n ENTÃO VALE A RELAÇÃO:
f(n)= Σμ(d)g(n/d).

A FÓRMULA DE INVERSÃO É UM CASO PARTICULAR DE UMA CONVOLUÇÃO DE DIRICHLET.
ALGUMAS GENERALIZAÇÕES DA FUNÇÃO DE MÖBIUS SÃO TAMBÉM DENOTADAS POR μ(n).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Möbius_inversion_formula
                          https://en.wikipedia.org/wiki/Möbius_function#cite_note-FOOTNOTEBostConnes1995411–457-6
                          https://en.wikipedia.org/wiki/Dirichlet_convolution

*/

//*************************************************************************************************************************
// CABEÇALHO
#ifndef MOBIUS_FUNCTION_H
#define MOBIUS_FUNCTION_H
#include"prime_power_detection.h"
#include <math.h>

// CONSTANTES GLOBAIS
const unsigned int MOBIUS_BOUND = 100000;

//*************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
int mobius_small_integer(uint64_t);
int mobius_large_integer(uint64_t);
int mobius_function(uint64_t);
int64_t mertens_function(uint64_t);
uint64_t gcd_mob(uint64_t, uint64_t);

//*************************************************************************************************************************
// FUNÇÕES
// Função de Möbius para pequenos valores
int mobius_small_integer(uint64_t n) {
  
   // Caso trivial: n=1
   if (n == 1) return 1;

  // Variáveis locais
  uint64_t root = sqrt(n);
  int prime_factor_number = 0;
  int result = 1;

  // Procedimentos
  // Testando a divisibilidade por 2 e 3
  if ((n % 2) == 0) {
    n /= 2;
    prime_factor_number++;

    if (n == 1) goto end;
    if ((n % 2) == 0) return 0;
  };

  if ((n % 3) == 0) {
    n /= 3;
    prime_factor_number++;

    if (n == 1) goto end;
    if ((n % 3) == 0) return 0;
  };

  // Testando a divisibilidade por números primos ímpares até n^(1/2)
  for (uint64_t i = 5; i < (root + 1); i += 6) {
    if ((n % i) == 0) {
      n /= i;
      prime_factor_number++;

      if (n == 1) goto end;
      if ((n % i) == 0) return 0;
    };

    if ((n % (i + 2)) == 0) {
      n /= (i + 2);
      prime_factor_number++;

      if (n == 1) goto end;

      if ((n % (i + 2)) == 0) return 0;
    };
  };

  // Fator primo superior a n^(1/2)
  if (n > 1) prime_factor_number++;

// Resultado
end:
  if ((prime_factor_number &1) == 1) return (-1) * result;
  else return result;
};

// Função que implementa o algoritmo de Euclides para se calcular o mdc de dois inteiros
uint64_t gcd_mob(uint64_t a, uint64_t b) {
  if (b == 0)
    return a;
  else
    return gcd_mob(b, a % b);
};

// Função de Möbius para grandes valores
int mobius_large_integer(uint64_t n) {
  // Variáveis locais
  int64_t root, prime;
  int result = 1;

  // Procedimentos
  // Caso 1: quadrados perfeitos
  if (fast_square_detection(n, &root) == true) return 0;

  // Caso2 : números primos
  if (baillie_psw_test(n) == true) return (-1) * result;

  // Caso3 : potências de números primos
  if (fast_prime_power_detection(n, &prime) == true) return 0;

  // Caso 4: explorando a propriedade multiplicativa da função de Möbius
  // Variáveis
  uint64_t factor1, factor2;
  uint64_t sqrt_n = sqrt(n);

  // Procedimentos
  // Loop principal encontrando fatores relativamente primos entre si
  for (uint64_t i = (sqrt_n - 1); i > 1; --i) {
    if ((n % i) == 0) {
      factor1 = i;
      factor2 = n / i;

      if (gcd_mob(factor1, factor2) == 1) break;
    };

    if ((n % (sqrt_n - i)) == 0 && (sqrt_n - i) >= 2) {
      factor1 = (sqrt_n - i);
      factor2 = n / (sqrt_n - i);

      if (gcd_mob(factor1, factor2) == 1) break;
    };
  };

  // Resultado
  if (factor1 > MOBIUS_BOUND && factor2 <= MOBIUS_BOUND)
    return (mobius_large_integer(factor1) * mobius_small_integer(factor2));
  if (factor1 <= MOBIUS_BOUND && factor2 > MOBIUS_BOUND)
    return (mobius_small_integer(factor1) * mobius_large_integer(factor2));
  else
    return (mobius_small_integer(factor1) * mobius_small_integer(factor2));
};

// Função de Möbius
int mobius_function(uint64_t n) {
  if (n <= MOBIUS_BOUND)
    return mobius_small_integer(n);
  else
    return mobius_large_integer(n);
};

//*************************************************************************************************************************
// APLICAÇÃO NO CÁLCULO DA FUNÇÃO DE MERTENS

int64_t mertens_function(uint64_t n) {
  // Variáveis locais
  int64_t result = 0;
  int64_t bound=floor(n/3.0);  

  // Procedimento:loop principal
  for (uint64_t i = 1; i <=bound; ++i) result += (floor((n-i)/(2.0*i))*mobius_function(i));

  // Resultado
  return (-1)*result;
};

//*************************************************************************************************************************
// FIM DO HEADER
#endif

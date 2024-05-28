// VAMOS IMPLEMENTAR UMA FUNÇÃO QUE CALCULA O SÍMBOLO DE JACOBI

/*
O CHAMADO SÍMBOLOS DE JACOBI SÃO UMA GENERALIZAÇÃO DOS SÍMBOLOS DE LEGENDRE.
O SÍMBOLO DE LEGENDRE (a/b) É DEFINIDO COMO:
       { 0 SE a = 0 mod(b)
(a/b)= { +1 SE a ≠ 0 mod(b) E PARA ALGUM x SE VERIFICA A RELAÇÃO a = x² mod(b)
       { -1 SE a ≠ 0 mod(b) E PARA NENHUM x SE VERIFICA A RELAÇÃO a = x² mod(b)

OS SÍMBOLOS DE JACOBI SÃO CALCULADOS MULTIPLICANDO-SE OS REPECTIVOS SÍMBOLOS DE
LEGENDRE DOS FATORES PRIMOS UM DADO NÚMERO ELEVADO AO SEU NÚMERO DE OCORRÊNCIA
DE CADA FATOR NESTE NÚMERO. PARA NÚMEROS PRIMOS AMBOS DOS SÍMBOLOS SÃO IGUAIS.

UMA SÉRIE DE RELAÇÕES RECURSIVAS PERMITE OBTER O SÍMBOLO DE JACOBI DE FORMA
SIMPLES. UMA GENERALIZAÇÃO SIMPLES EXTENDE A DEFINIÇÃO PARA O CASO EM QUE a<0.
O SÍMBOLO DE JACOBI É UM CASO ESPECIAL CARACTÉRE DE DIRICHLET A MENOS DE UMA
RELAÇÃO DE CONGRUÊNCIA.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Jacobi_symbol
                          https://en.wikipedia.org/wiki/Dirichlet_character

*/

//********************************************************************************************************************
// CABEÇALHO
#ifndef JACOBI_SYMBOL_H
#define JACOBI_SYMBOL_H
#include <assert.h>
#include <stdint.h>

// Protótipo de funções
int64_t euclides_check(int64_t, int64_t);
int jacobi(int64_t, int64_t);
int jacobi_symbol_extension(int64_t, int64_t);

//********************************************************************************************************************
// Função que implementa o algoritmo de Euclides para se calcular o mdc de dois
// inteiros
int64_t euclides_check(int64_t a, int64_t b) {
  if (b == 0)
    return a;
  else
    return euclides_check(b, a % b);
};

// Função que calcula o símbolo de Jacobi
int jacobi(int64_t a, int64_t b) {
  // Restrições para o cálculo
  assert(a > 0 && (b % 2) == 1);

  // Variáveis locais
  int j = 1;     // Resultado
  int64_t temp;  // Variável temporária

  // Procedimentos

  // Loop principal (tentaremos obter o numerador a=1)
  while (a != 1) {
    // Reduzindo fatores pares no numerador
    while (a % 2 == 0) {
      a /= 2;
      if (b % 8 == 3 || b % 8 == 5) j *= (-1);
      if (b % 8 == 1 || b % 8 == 7) continue;
    };

    // Caso trivial:numerador e denominador não são relativamente primos
    if (euclides_check(a, b) != 1) return 0;

    // Lei da reciprocidade quadrática
    temp = a;
    a = b;
    b = temp;

    if (a % 4 == 3 && b % 4 == 3) j *= (-1);

    // Reduzindo o numerador
    a %= b;

    // Caso geral
    if (b == 1) return j;
  };

return j;

};

// Função que extende o simbolo de jacobi para números negativos (a<0)
int jacobi_symbol_extension(int64_t a, int64_t n) {
  // Restrição
  assert(a < 0);

  // Variáveis locais
  int64_t positive_a = (-1) * a;
  int64_t power2 = 0;
  int result;

  // Procedimentos
  // Determinando a paridade do numerador
  while ((positive_a % 2) == 0) {
    positive_a /= 2;
    power2++;
  };

  // Definindo o símbolo de jacobi para |a|>0
  result = jacobi(positive_a, n);

  // Determinando o sinal do resultado
  // Caso 1: |a| é ímpar
  if (power2 > 0 && (power2 % 2) == 1) result = (-1) * jacobi(positive_a, n);
  // Caso 2: |a| é par
  if (power2 > 0 && (power2 % 2) == 0) return result;

  // Caso 2: |a| não contém fatores 2
  if (power2 == 0) result = (-1) * jacobi(positive_a, n);

  // Resultado
  return result;
};

//********************************************************************************************************************
// FIM DO HEADER
#endif

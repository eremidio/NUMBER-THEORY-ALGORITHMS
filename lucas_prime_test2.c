// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O TESTE DE PRIMALIDADE DE LUCAS PARA
// TESTAR A PRIMALIDADE DE UM NÚMERO INTEIRO COMPILAR ESTE PROGRAMA COM O
// COMANDO: gcc -o lucas_prime_test2 lucas_prime_test2.c -lm

/*
O TESTE DE LUCAS CONSISTE EM UM ALGORITMO PARA PROVAR A PRIMALIDADE DEUM NÚMERO
INTEIRO PRODUZINDO UM CERTIFICADO (CERTIFICADO DE PRATT)QUE ASSEGURA QUE O
NÚMERO EM QUESTÃO É PRIMO. O ALGORITMO SE BASEIA NA SEGUINTE PROPOSIÇÃO: DADO UM
INTEIRO POSITIVO n, n É PRIMO SE E SOMENTE SE EXISTIR UM INTEIRO a, TAL QUE
1<a<n, a^(n-1)=1 (mod n) E PARA CADA FATOR PRIMO p DE (n-1) a^{(n-1)/p}≠1 (mod
n).

ESTE É O MAIS SIMPLES DOS ALGORITMOS QUE SE BASEIAM NA ORDEM DE UM GRUPO PARA
TESTAR A PRIMALIDADE DE UM INTEIRO E UMA VARIANTE DASEGUINTE PROPOSIÇÃO GERAL:
DADO UM INTEIRO n E DOIS INTEIROS a, s,  TAL QUE a^s=1 (mod n) E PARA CADA
DIVISOR PRIMO p DE s a^(s/p) ≠ 1 (mod n); SE s>n^(1/2) ENTÃO n É PRIMO.

ALGORITMO MAIS MODERNOS USAM TÉCNICAS SIMILARES PARA REDUZIR A ORDEM DE
GRANDEZAS DOS VALORES A SEREM TESTADOS PARA CHECAR A PRIMALIDADE DE UM NÚMERO.
ESTE É O CASO DOS ALGORITMOS DE CURVAS ELÍPTICAS E DO ALGORITMO DE POCKLINGTON
(DIRETAMENTE LIGADO A ESTE PORÉM REQUERINDO APENAS UMA FATORAÇÃO PARCIAL DE
(n-1)). A PRIMALIDADE DE UM DADO INTEIRO É REDUZIDA A TESTES ENVOLVENDO NÚMEROS
MENORES.

PARA MAIORES INFORMAÇÕES:
https://en.wikipedia.org/wiki/Pocklington_primality_test
                          https://en.wikipedia.org/wiki/Lucas_primality_test

*/

//*********************************************************************************************************************************************************************
// CABEÇALHO
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "gcd_euclides_fast.h"
#include "mod_bin_exponentiation.h"

enum show_lucas_pratt_certificate { Yes, No };

//*********************************************************************************************************************************************************************
// FUNÇÕES
// Função que fatora um número inteiro e estoca os elementos em um array
void factor(uint64_t prime_array[], uint64_t number) {
  // Varíaveis locais
  uint64_t limit = sqrt(number);
  uint64_t limit2 = sqrt(limit);
  uint64_t i, k = 0;

  // Procedimentos
  // Testando a divisibilidade por 2 e 3
  if ((number % 2) == 0) {
    prime_array[k] = 2;
    ++k;
    while ((number % 2) == 0) number /= 2;
  };

  if ((number % 3) == 0) {
    prime_array[k] = 3;
    ++k;
    while ((number % 3) == 0) number /= 3;
  };

  // Loop principal
  for (i = 5; i <= limit; i += 6) {
    if ((number % i) == 0) {
      prime_array[k] = 2;
      ++k;
      while ((number % i) == 0) number /= i;
    };

    if ((number % (i + 2)) == 0) {
      prime_array[k] = 2;
      ++k;
      while ((number % (i + 2)) == 0) number /= (i + 2);
    };
  };

  // Fatores  superiores a n^(1/2)
  if (number > 1) prime_array[k] = number;
};

// Teste de Lucas
bool lucas_test(uint64_t n, enum show_lucas_pratt_certificate x) {
  // Variáveis locais
  uint64_t exponent = (n - 1), exponent2;
  uint64_t bound = sqrt(n) * sqrt(sqrt(n));
  uint64_t prime_array[65];
  uint64_t a = 2;
  uint64_t i, k = 0;

// Procedimentos
// Teste de Fermat
first_part:
  if (mod_bin_pow(a, exponent, n) == 1)
    goto second_part;
  else {
    if (a < n) printf("%lu certifica a composição de %lu\n", a, n);

    if (a == n) {
      printf("Primo encontrado\n");
      return true;
    } else
      return false;
  };

  // Fatorando o expoente
  factor(prime_array, exponent);

second_part:
  // Testando os expoentes
  for (i = 0; i < 65; ++i) {
    if (prime_array[i] > 0) exponent2 = exponent / prime_array[i];

    if (mod_bin_pow(a, exponent2, n) == 1) {
      if (x == Yes) printf("%lu certfica a primalidade de %lu\n", a, n);
      break;
    };
  };

  // Atualizando variáveis
  if (a == 2)
    a++;
  else
    a += 2;
  goto first_part;

  // Caso o número falhe nos teste acima
  return true;
};

//*********************************************************************************************************************************************************************
// FUNÇÃO PRINCIPAL
int main() {
  // Váriaveis
  uint64_t number;
  bool result;
  // Procedimentos
  // Recebendo input do usuário
  printf("Digite um número que será testado:\n");
  scanf("%lu", &number);

  // Executando o teste
  result = lucas_test(number, Yes);

  // Finalizando a aplicação
  return 0;
}

// VAMOS CRIAR UM PROGRAMA QUE IMPLMENTA O ALGORITMO DE MILLER-RABIN PARA
// TESTAR A PRIMALIDADE DE UM NÚMERO INTEIRO COMPILAR ESTE PROGRAMA COM O
// COMANDO: gcc -o miller_rabin2 miller_rabin2.c
/*
O TESTE DE MILLER RABIN A PRINCÍPIO É UM TESTE PROBALÍSTICO PARA TESTAR A
PRIMALIDADE DE UM NÚMERO INTEIRO.PORÉM ELE PODE SE TORNAR UM TESTE EXATO SE UMA
BASE SUFICIENTEMENTE GRANDE DE PRIMOS FOR USADAS NO TESTE.

PARA INTEIROS DE 64 BITS PODEMOS USAR A BASE {2, 3, 5, 7, 11, 13, 17, 19, 23,
29, 31, 37}. PARA INTEIRO DE 32 BITS A BASE {2, 3, 5, 7} É SUFICIENTE PARA
ASSEGURAR A PRIMALIDADE DO NÚMERO EM QUESTÃO.
*/

//********************************************************************************************************************
// CABEÇALHO
#include "mod_bin_exponentiation.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//********************************************************************************************************************
// FUNÇÕES

// Função que implementa o algoritmo de Euclides para se calcular o mdc de dois
// inteiros
uint64_t
gdc_euclides (uint64_t a, uint64_t b)
{
  if (b == 0)
    return a;
  else
    return gdc_euclides (b, a % b);
};

// Função que executa o teste para um dado número inteiro
bool
test (uint64_t n, uint64_t a)
{
  // Números pares estão excluídos do teste
  if (n % 2 == 0)
    return false;

  // Definindo uma semente para geração de números aleatórios
  srand (time (NULL));

  // Variáveis locais
  uint64_t s, r, d, x, n_even;

  // Procedimentos

  // Definindo valores de s, d
  s = 0;          // Ajuste de variáveis
  n_even = n - 1; // Ajuste devariáveis

  while (n_even % 2 == 0)
    {
      n_even /= 2;
      s++;
    };
  d = n_even;

  // Teste 1: a^(d)=1 mod(n)
  if (mod_pow (a, d, n) == 1)
    return true;

  // Teste 2: a^(2^(r)d)=1 mod(n) para r no intervalo 1, 2,..., s-1
  for (r = 0; r < s; ++r)
    {
      x = mod_pow (a, bin_pow (2, r) * d, n);
      if ((x * x) % n == 1)
        return true;
    };
  // Caso haja falhas no teste acima
  return false;
};

// Teste de Miller-Rabin
bool
miller_rabin_test (uint64_t n)
{
  // Variáveis locais
  bool prime_check;
  int i;
  uint64_t base[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
  // Realizando o teste de Miller na base de primos acima
  for (i = 0; i < 12; ++i)
    {
      prime_check = test (n, base[i]);
      if (prime_check == false)
        return false;
    };
  // Se o número passar no teste acima ele é declarado primo.
  return true;
};

//********************************************************************************************************************
// FUNÇÃO PRINCIPAL

int
main ()
{
  // Váriaveis
  uint64_t number;
  int k;
  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um número que será testado:\n");
  scanf ("%lu", &number);

  // Executando o teste
  if (miller_rabin_test (number) == true)
    printf ("Primo encontrado!\n");
  else
    printf ("Número composto.\n");

  // Finalizando a aplicação
  return 0;
}

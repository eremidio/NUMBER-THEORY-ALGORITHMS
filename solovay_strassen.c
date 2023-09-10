// VAMOS CRIAR UM PROGRAMA QUE IMPLMENTA O TESTE DE SOLOVAY STRASSEN PARA
// CHECAR A PRIMALIDADE DE UM NÚMERO COMPILAR ESTE PROGRAMA COM O COMANDO: gcc
// -o solovay_strassen solovay_strassen.c

/*
O ALGORITMO DE SOLOVAY-STRASSEN É BASEADO NA SEGUINTE RELAÇÃO:
PARA n INTEIRO NEGATIVO n É PRIMO SE E SOMENTE a^((n-1)/2)= (a/n) mod(n)
ONDE (a/n) DENOTA O SÍMBOLO DE LEGENDRE.

*/

//********************************************************************************************************************
// CABEÇALHO
#include "jacobi_symbol.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//********************************************************************************************************************
// FUNÇÕES
// Função que calcula a exponencial modular a^b mod(n)
int64_t
mod_pow (int64_t a, int64_t b, int64_t n)
{
  // Variáveis locais
  int64_t result = 1;
  int64_t i; // Variável de iteração

  // Procedimento
  for (i = 0; i < b; ++i)
    result = (result * a) % n;

  return result;
};

// Função que executa um teste unitário
bool
test (int64_t n)
{
  // Semente de geração de números aleatórios
  srand (time (NULL));

  // Caso trivial
  if (n % 2 == 0)
    return false;

// Gerando um número aleatório coprimo como número a ser testado
pick:
  int64_t a = 2 + rand () % (n - 4);

  if (euclides_check (a, n) != 1)
    goto pick;

  // Variáveis usadas no teste
  int64_t power_result = mod_pow (a, (n - 1) / 2, n);
  int j_symbol = jacobi (a, n);
  // Realizando teste
  if (j_symbol == 0 && power_result == 0)
    return true;
  else if (j_symbol == 1 && power_result == 1)
    return true;
  else if (j_symbol == (-1) && power_result == (n - 1))
    return true;
  else
    return false;
};

// Teste de Solovay-Strassen
bool
solovay_strassen (int64_t n, int k)
{
  // Variáveis locais
  int i;
  int p_results = 0;
  int f_results = 0; // Variável de iteração e contagem de acertos e erros

  // Teste
  for (i = 0; i <= k; ++i)
    {
      if (test (n) == false)
        ++f_results;
      else if (test (n) == true)
        p_results++;
    };

  if (f_results >= p_results)
    return false;
  if (f_results < p_results)
    return true;
};

//********************************************************************************************************************
// FUNÇÃO PRINCIPAL
int
main ()
{
  // Váriaveis
  int64_t number;
  int k;
  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um número que será testado:\n");
  scanf ("%li", &number);
  printf (
      "Digite um número que define a precisão do teste a ser realizado:\n");
  scanf ("%d", &k);

  // Executando o teste
  if (solovay_strassen (number, k) == true)
    printf ("Provável primo encontrado!\n");
  else
    printf ("Número composto.\n");

  // Finalizando a aplicação
  return 0;
}

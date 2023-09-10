// VAMOS CRIAR UM PROGRAMA QUE IMPLMENTA O TESTE DE PRIMALIDADE PARA NÚMEROS DE
// PROTH COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o proth_prime_test
// proth_prime_test.c

/*
UM NÚMERO DE PROTH É UM INTEIRO POSITIVO ÍMPAR DA FORMA k.2^r+1, ONDE k É ÍMPAR
E k<2^r. PARA NÚMEROS NESTA CATEGORIA, O TEOREMA DE PROTH GARANTE QUE ELE É
PRIMO SE E SOMENTE SE: 2^((p-1)/2)= -1 mod(p). PARA MAIORES INFORMAÇÕES:
https://en.wikipedia.org/wiki/Proth%27s_theorem

*/

//********************************************************************************************************************
// CABEÇALHO
#include "mod_bin_exponentiation.h"
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//********************************************************************************************************************
// FUNÇÕES

// Função que calcula um quadrado não residual a mesno de uma relação de
// congruência
/*Um número é denominado um resíduo quadrático a menos de uma congruência se
existe um inteiro x tal que: x²= q mod(x). Se não existir tal número o número
em questão é dito um quadrado não residual. Um teste heurístico probabilístico
consite em usar os chamados símbolos de Legendre.
*/

uint64_t
get_quadratic_non_residue (uint64_t n)
{
  // Restrição a números ímpares
  assert (n % 2 == 1);

  // Semente para geração de números aleatórios
  srand (time (NULL));
  // Variáveis locais
  uint64_t trials = 0, a = 2;
// Procedimento
// Gerando um número aleatório
pick:
  trials++;

  // Limitando as buscas
  if (trials > 1000)
    return a;

  a = 2 + rand () % (n - 3);
  // Verificando se o número em questão é um quadrado não residual módulo n
  if (mod_bin_pow (a, ((n - 1) / 2), n) == (n - 1))
    return a;
  else
    goto pick;
};

// Função que determina se um número é um número de Proth ou não
bool
is_proth (uint64_t n)
{
  // Variáveis locais
  uint64_t k = 1;
  uint64_t i, power2, tester2;
  uint64_t tester = n - 1;

  // Procedimentos
  for (k = 1; k < (n + 1) / 2; ++k)
    {
      power2 = 2;
      tester2 = tester / k;

      if (tester2 % 2 == 1)
        continue;

      for (i = 0; i < k; ++i)
        {
          if (tester2 == power2 && k < power2)
            return true;
          else if (tester2 > power2)
            power2 *= 2;
          else if (tester2 < power2)
            break;
        };
    };

  return false;
};

// Função que realiza o teste de Proth
// Para quadrados não residuais o teste é exato, caso contráio apenas
// probabilístico
bool
proth_test (uint64_t n)
{
  // Testando se número é um número de Proth
  if (is_proth (n) == false)
    {
      printf ("O teste é inconclusivo. O número em questão não é um número de "
              "Proth!\n");
      return false;
    };
  // Procedimentos
  // Obtendo um quadrado não residual módulo n
  uint64_t a = get_quadratic_non_residue (n);
  // Aplicando o teste
  if ((mod_bin_pow (a, ((n - 1) / 2), n) + 1) % n == 0)
    return true;
  else
    return false;
};

//********************************************************************************************************************
// FUNÇÃO PRINCIPAL
int
main ()
{
  // Váriaveis
  uint64_t number;
  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um número que será testado:\n");
  scanf ("%lu", &number);

  // Executando o teste
  if (proth_test (number) == true)
    printf ("Provável primo encontrado!\n");
  else
    printf ("Número composto.\n");

  // Finalizando a aplicação
  return 0;
}

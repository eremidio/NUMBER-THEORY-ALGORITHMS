// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A CLASSE DOS NÚMEROS DE FERMAT E O
// TESTE DE PÉPIN PARA A PRIMALIDADE DOS TESTE DE FERMAT COMPILAR ESTE PROGRAMA
// COM O COMANDO: gcc -o fermat_number fermat_number.c

/*
UM NÚMERO DE FERMAT É UM NÚMERO INTEIRO DA FORMA: F(n)=2^(2^n)+1.

VÁRIAS RELAÇÕES DE RECORRÊNCIA EXISTEM ENVOLVENDO ESTES NÚMEROS, POR EXEMPLO:
PARA n>1: F(n)=(F(n-1)-1)²+1 E F(n)=F(0).F(1)...F(n-1)+2

O CHAMADO TESTE DE PÉPIN PODE SER USADO PARA DETERMINAR SE UM NÚMERO DE FERMAT
É PRIMO OU NÃO. ESTE TEOREMA BASICAMENTE AFIRMA QUE PARA UM NÚMERO DE FERMAT
SER PRIMO ELE TEM DE SATISFAZER A RELAÇÃO: 3^((F(n)-1)/2)=(F(n)-1) mod(F(n))

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Pépin%27s_test
                          https://en.wikipedia.org/wiki/Fermat_number

*/

//***************************************************************************************************************************
// CABEÇALHO
#include "mod_bin_exponentiation.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
//***************************************************************************************************************************
// FUNÇÕES
// Função que determina se um número inteiro positivo é um número de Fermat
bool
is_fermat_number (uint64_t n)
{
  // Variáveis locais
  uint64_t i, tester;
  // Procedimentos
  for (i = 0;; ++i)
    {
      tester = bin_pow (2, bin_pow (2, i)) + 1;
      if (tester == n)
        return true;
      if (tester > n)
        return false;
    };
};

// Teste de Pépin para testar a primalidade de um número
void
pepin_test (uint64_t n)
{
  // Checando se o número em questão é um número de Fermat
  bool test1 = is_fermat_number (n);

  if (test1 == false)
    {
      printf ("O número em questão não é um número de Fermat!\n");
      return;
    };

  // Teste de primalidade
  uint64_t exponent = (n - 1) / 2;
  uint64_t tester = mod_pow (3, exponent, n);

  if (tester == (n - 1))
    printf ("O número em questão é primo.\n");
  else
    printf ("O número em questão não é primo.\n");
};

//***************************************************************************************************************************
// FUNÇÃO PRINCIPAL
int
main ()
{
  // Variáveis locais
  uint64_t n;

  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um número inteiro: ");
  scanf ("%lu", &n);

  // Aplicando o teste de Pépin
  pepin_test (n);
  // Finalizando a aplicação
  return 0;
}

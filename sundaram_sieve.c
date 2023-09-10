// VAMOS IMPLEMENTAR O ALGORITMO DA PENEIRA DE SUNDARAM  PARA CALCULAR NÚMEROS
// PRIMOS ARTÉ UM CERTO LIMITE COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o
// sundaram_sieve sundaram_sieve.c

/*CABEÇALHO*/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Função que determina se um  número é quadrado perfeito
bool
perfect_square_check (int64_t n)
{
  // Variáveis locais
  int64_t odd = 1;
  // Procedimentos
  while (n > 0)
    {
      n -= odd;
      odd += 2;
      if (n < 0)
        return false;
    };

  return true;
};

// FUNÇÃO QUE APLICA A PENEIRA DE SUNDARAM PARA UMA SEQUÊNCIA DE INTEIROS ATÉ
// UM DADO VALOR
void
sundaram_sieve (int64_t n)
{
  // VARIÁVEIS LOCAIS
  bool number_list[n + 1];
  int64_t i, j, k;

  // PROCEDIMENTOS
  // INICIALIZANDO A LISTA DE BOOLEANOS
  for (k = 0; k < n + 2; ++k)
    number_list[k] = true;

  // APLICANDO A PENEIRA DE SUNDARAM A LISTA DE BOOLEANOS
  for (j = 1; j < n; ++j)
    {
      for (i = 1; i < j; ++i)
        {
          if ((i + j + 2 * i * j) < n)
            number_list[i + j + 2 * i * j] = false;
        };
    };

  // PRINTANDO A LISTA DE NÚMEROS PRIMOS
  printf ("2, 3, ");
  for (k = 2; (2 * k + 1) < n; ++k)
    {
      if (number_list[k] == true
          && perfect_square_check ((2 * k + 1)) == false)
        printf ("%li, ", (2 * k + 1));
    };
};

// FUNÇÃO PRINCIPAL
int
main ()
{
  // DEFINIÇÃO DE VARIÁVEIS
  int64_t n;
  // RECEBENDO INPUT DO USUÁRIO E EXIBINDO OS NÚMEROS PRIMOS
  printf ("Vamos calcular os números primos até um certo valor usando a "
          "peneira de Sundaram.\n");
  printf ("Usuário digite um número inteiro:\n");
  scanf ("%li", &n);
  sundaram_sieve (n);
  printf ("\n");

  // FINALIZANDO A APLICAÇÃO
  return 0;
}

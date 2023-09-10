// VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS DESENVOLVIDAS NO ARQUIVO
// bernoulli_numbers.h COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o
// bernoulli_numbers bernoulli_numbers.c -lm

// Cabeçalho
#include "bernoulli_numbers.h"
#include <stdio.h>

// Função principal
int
main ()
{
  // Variáveis locais
  int n;
  // Recebendo input do usuário
  printf ("Digite um número inteiro: ");
  scanf ("%d", &n);

  // Calculando o  n-ésimo número de Bernoulli
  printf ("B(%d) = %f (cálculo explícito).\n", n,
          bernoulli_number_generator1 (n));
  printf ("B(%d) = %f (cálculo recursivo).\n", n,
          bernoulli_number_generator2 (n));

  // Finalizando a aplicação
  return 0;
}

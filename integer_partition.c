// VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO
// integer_partition.h COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o
// integer_partition integer_partition.c -lm

// Cabeçalho
#include "integer_partition.h"
#include <stdio.h>

// Função principal
int
main ()
{
  // Variáveis locais
  unsigned int number;

  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um número inteiro: ");
  scanf ("%u", &number);

  // Teste de funções
  // Função de partição
  printf ("Soma dos divisores de %u: %u\n", number, sum_of_divisors (number));
  printf ("Número de partições de %u: %u\n", number,
          partition_function (number));

  // Finalizando a aplicação
  return 0;
}

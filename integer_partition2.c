// VAMOS CRIAR UM PROGRAMA QUE TESTA A ROTINA CRIADA NO ARQUIVO
// integer_partition2.h COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o
// integer_partition2 integer_partition2.c

// Cabeçalho
#include "integer_partition2.h"
#include <stdio.h>

// Função principal
int
main ()
{
  // Variáveis locais
  int number;
  // Procedimentos
  // Recebendo input do usuário
  printf ("Usuário digite um número inteiro:\n-> ");
  scanf ("%d", &number);
  // Cálculo das partições de um inteiro
  generate_partition (number, Yes);

  // Finalizando a aplicação
  return 0;
}

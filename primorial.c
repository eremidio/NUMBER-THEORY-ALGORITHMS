// VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO
// primorial.h COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o primorial
// primorial.c -lm

// Cabeçalho
#include "primorial.h"
#include <stdint.h>
#include <stdio.h>

// Função principal
int
main ()
{
  // Variáveis locais
  uint64_t n;

  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um número inteiro: ");
  scanf ("%lu", &n);

  // Calculando o primorial de um número
  printf ("%lu# = %lu\n", n, primorial (n));

  // Finalizando a aplicação
  return 0;
}

// VAMOS CRIAR UM PROGRAMA PARA TESTAR AS ROTINAS CRIADAS NO ARQUIVO
// legendre_symbol.h COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o legendre
// legendre.c -lm

// Cabeçalho
#include "legendre_symbol.h"
#include <stdio.h>

// Função principal
int
main ()
{
  // Variáveis locais
  uint64_t prime, number;

  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um inteiro positivo: ");
  scanf ("%lu", &number);
  printf ("Digite um inteiro ímpar e primo: ");
  scanf ("%lu", &prime);

  // Calculando o símbolo de Legendre
  printf ("(%lu/%lu) = %i\n", number, prime, legendre (number, prime));

  // Finalizando a aplicação
}

// VAMOS CRIAR UM PROGRAMA PARA TESTAR A ROTINA NO ARQUIVO gcd_euclides_fast.h
// COMPILAR ESTE PROGRAMA COM: gcc -o gcd_euclides_fast gcd_euclides_fast.c

// Cabeçalho
#include "gcd_euclides_fast.h"
#include <stdint.h>
#include <stdio.h>

// Função principal
int
main ()
{
  // Variáveis locais
  int64_t a, b;

  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um inteiro: ");
  scanf ("%li", &a);
  printf ("Digite um inteiro: ");
  scanf ("%li", &b);

  // Calculando o mdc de a e b
  printf ("mdc(%li, %li)=%li\n", a, b, binary_gcd (a, b));

  // Finalizando a aplicação
  return 0;
}

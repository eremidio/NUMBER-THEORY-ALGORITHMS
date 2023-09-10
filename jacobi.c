// UM PROGRAMA PARA TESTAR A FUNÇÃO QUE CALCULA OS SÍMBOLOS DE JACOBI
// COMPILAR  ESTE PROGRAMA COM O COMANDO: gcc -o jacobi jacobi.c

// Cabeçalho
#include "jacobi_symbol.h"
#include <stdint.h>
#include <stdio.h>

// Função principal
int
main ()
{
  // Variáveis locais
  int64_t a, b;

  // Procedimento
  // Recebendo input
  printf ("Digite um número inteiro: ");
  scanf ("%li", &a);
  printf ("Digite um número inteiro: ");
  scanf ("%li", &b);
  // Calculando o símbolo de Jacobi
  printf ("(%li/%li)= %d\n", a, b, jacobi (a, b));
  // Finalizando a aplicação
  return 0;
}

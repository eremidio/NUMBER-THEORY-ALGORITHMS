// VAMOS CRIAR UM PROGRAMA QUE TESTA AS ROTINAS DEFINIDAS NO HEADER
// modular_square_root.h COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o
// modular_square_root modular_square_root.c

// Cabeçalho
#include "modular_square_root.h"
#include <stdio.h>

// Função principal
int
main ()
{
  // Variáveis locais
  uint64_t n, p, root;
  // Procedimentos
  // Recebendo input do usuário
  printf ("Digite um número primo ímpar: ");
  scanf ("%lu", &p);
  printf ("Digite um número inteiro: ");
  scanf ("%lu", &n);

  // Calculando raíz quadrada a menos de uma relação de congruência
  root = modular_sqrt (n, p);

  if (root == 0)
    printf ("Não foram em contradas raízes quadradas de %lu (mod %lu)\n", n,
            p);
  else
    printf ("Raíz quadrada de %lu (mod %lu)=%lu.\n", n, p, root);

  // Finalizando a aplicação
  return 0;
}

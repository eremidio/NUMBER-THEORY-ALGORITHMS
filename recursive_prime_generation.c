// VAMOS CRIAR PROGRAMA PARA TESTAR AS RORINAS CRIADAS NO ARQUIVO
// recursive_prime_generation.h COMPILAR ESTE PROGRAMA COM COMANDO: gcc -o
// recursive_prime_generation recursive_prime_generation.c

// Cabeçalho
#include "recursive_prime_generation.h"
#include <stdint.h>
#include <stdio.h>

// Função principal
int
main ()
{
  // Variáveis
  uint64_t seed, iterations;

  // Procedimentos
  // Recebendo inputdo usuário
  printf (
      "Digite um valor inicial para iniciar a sequência de números primos: ");
  scanf ("%lu", &seed);
  printf ("Digite quantas iterações serão usadas neste experimento: ");
  scanf ("%lu", &iterations);

  // Gerando a lista de primos
  printf (
      "Primos gerados usando-se a relação R(n) = R(n-1)+mdc(n, R(N-1)):\n");
  recursive_prime_generation (seed, iterations);

  // Finalizando a aplicação
  return 0;
}

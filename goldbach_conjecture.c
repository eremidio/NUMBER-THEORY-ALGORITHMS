// VAMOS CRIAR UM PROGRAMA QUE TESTA A CONJECTURA DE GOLDBACH
// COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o goldbach_conjecture
// goldbach_conjecture.c -lm

/*

A CONJECTURA DE GOLDBACH AFIRMA QUE TODO INTEIRO PAR n>3 PODE SER ESCRITO COMO
A SOMA DE DOIS NÚMEROS PRIMOS. PARA MAIORES INFORMAÇÕES:
https://en.wikipedia.org/wiki/Goldbach%27s_conjecture

*/

//**************************************************************************************************************************
// CABEÇALHO
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//**************************************************************************************************************************
// FUNÇÕES
// Função que calcula se um número é primo ou não (usaremos uma otimização
// 6k+1)
bool
is_prime (uint64_t n)
{
  // Casos triviais
  // 0,1
  if (n <= 1)
    return false;

  // Casos básicos
  if (n == 2 || n == 3)
    return true;
  if ((n % 2) == 0 || (n % 3) == 0)
    return false;

  // Loop principal
  for (uint64_t i = 5; i < sqrt (n); i += 6)
    {
      if ((n % i) == 0 || (n % (i + 2)) == 0)
        return false;
    };

  // Caso fatores primos não sejam encontrados
  return true;
};

// Função que testar a conjectura de Goldbach
void
goldbach_conjecture (uint64_t n)
{
  // Variáveis locais
  uint64_t i, factor1, factor2;
  bool test1, test2;
  // Procedimentos
  // Detectando se o número em questão é par
  if ((n % 2) == 1)
    {
      printf ("O número emq uestão é impar a conjectura de Golbbach não se "
              "aplica.\n");
    };
  // Loop principal
  for (i = 2; i <= n / 2; ++i)
    {
      factor1 = i;
      factor2 = (n - factor1);
      test1 = is_prime (factor1);
      test2 = is_prime (factor2);

      if (test1 == true && test2 == true)
        {
          printf ("Fatores primos encontrados satisfazendo a conjectura: %lu "
                  "= %lu + %lu\n",
                  n, factor1, factor2);
          return;
        };
    };

  printf ("Não foram encontrados fatores primos satisfazendo a conjectura de "
          "Goldbach.\n");
};

//**************************************************************************************************************************
// FUNÇÃO PRINCIPAL
int
main ()
{
  // Variáveis locais
  uint64_t n;
  // Procedimento
  // Recebendo input do usuário
  printf ("Usuário digite um número inteiro: ");
  scanf ("%lu", &n);
  // Testando a conjectura de Goldbach
  goldbach_conjecture (n);
  // Finalizando a aplicação
  return 0;
}

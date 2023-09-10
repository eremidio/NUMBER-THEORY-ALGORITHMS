// VAMOS IMPLEMENTAR O ALGORITMODE FERMAT PARA FATORAR NÚMEROS INTEIROS GRANDES
// COMPILAR ESTE PROGRAMA COM O COMANDO: gcc -o fermat_factorization
// fermat_factorization.c -lm
/*
ESTE ALGORITMO USA O FATODE QUE PARA NÚMEROS INTEIROS ÍMPARES PODEM SER
ESCRITOS COMO A DIFERENÇA DE DOIS QUADRADOS. SEJA n UM INTEIRO COMPOSTO ÍMPAR,
TEMOS QUE n=a²-b², ONDE a>n^(1/2) E b<n^(1/2). PARA NÚMEROS PARES n UMA
DECOMPOSIÇÃO TRIVIAL É n/2, 2.
*/

// CABEÇALHO
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// FUNÇÕES
// Função que calcula um valor limite usado no algoritmo de  Fermat
uint64_t
limit (uint64_t number)
{
  return floor (sqrt (number));
};

// Função que executa o algoritmo de Fermat
void
fermat_algorithm (uint64_t number)
{
  // Variáveis locais
  uint64_t i, j; // Variáveis de  iteração
  uint64_t temp1, temp2, fermat_root, fermat_factor1, fermat_factor2;
  // Procedimento
  // Calculando um limitante
  fermat_root = limit (number);

  // Caso trivial, o npumero a ser fatorado é um quadrado perfeito
  if (fermat_root * fermat_root == number)
    {
      fermat_factor1 = fermat_root;
      fermat_factor2 = fermat_root;
      printf ("Fator1: %li\n Fator2: %li\n", fermat_factor1, fermat_factor2);
      return;
    };
  // Ajuste de variáveis
  i = fermat_root;

  // Encontrando valores de a e b tais que n=a²-b²
  while (true)
    {
      ++i;

      for (j = 1; j < fermat_root; j++)
        {

          // TESTE USE UM // APÓS OS MESMOS
          // printf("fermat_root=%li\n", fermat_root);
          // printf("i=%li\n", i);
          // printf("j=%li\n", j);
          // printf("i²-j²=%li\n", (i*i)-(j*j));

          if (((i * i) - (j * j)) == number)
            {
              fermat_factor1 = (i + j);
              fermat_factor2 = number / fermat_factor1;
              printf ("Fator1: %li\n Fator2: %li\n", fermat_factor1,
                      fermat_factor2);
              return;
            };
        };

      if (i > pow (number, 4))
        {
          printf ("O algoritmo não encontrou fatores do número em questão "
                  "dentro do limite definido.\n");
          break;
        };
    };
};

// FUNÇÃO PRINCIPAL
int
main ()
{
  // Variáveis locais
  uint64_t num;
  // Procedimento
  // Recebendo input do usuário
  printf ("Digite um número inteiro:");
  scanf ("%li", &num);

  // TESTE USE UM // APÓS OS MESMOS
  // printf("%li\n", limit(122));

  // Aplicando o algoritmo de Fermat
  fermat_algorithm (num);
  // Encerrando a aplicação
  return 0;
}

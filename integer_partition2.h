// VAMOS CRIAR UM PROGRAMA QUE GERA DIAGRAMAS DE YOUNG E AS RESPECTIVAS
// PARTIÇÕES DE UM NÚMERO INTEIRO

/*

PARA MAIORES INFORMAÇÕES:
https://jeromekelleher.net/generating-integer-partitions.html
                          https://www.tutorialspoint.com/cplusplus-program-to-perform-partition-of-an-integer-in-all-possible-ways

*/

//***************************************************************************************************************************
// CABEÇALHO
#ifndef INTEGER_PARTITION2_H
#define INTEGER_PARTITION2_H
#include <stdbool.h>
#include <stdlib.h>

// CONSTANTES GLOBAIS
enum show
{
  No,
  Yes
};

//***************************************************************************************************************************
// FUNÇÕES

// Função que printa uma partição de um número inteiro
void
print_partition (int array[], int size)
{
  // Variáveis locais
  int i;
  // Procedimento
  for (i = 0; i < size; ++i)
    {
      if (i == 0 && array[0] > 0)
        printf ("%d", array[0]);
      if (i > 0 && array[i] > 0)
        printf ("+%d", array[i]);
    };
  printf ("\n");
};

// Função que printa os diagramas de Young associado a um número inteiro
void
print_young_diagram (int array[], int size)
{
  // Variáveis locais
  int i, j, k;
  // Procedimento
  for (i = 0; i < size; ++i)
    {
      if (i == 0)
        {
          // Parte superior
          printf ("+");
          for (j = 0; j < array[i]; ++j)
            printf ("---+");
          printf ("\n");
          // Paredes laterais
          printf ("|");
          for (j = 0; j < array[i]; ++j)
            printf ("   |");
          printf ("\n");
          // Parte inferior
          printf ("+");
          for (j = 0; j < array[i]; ++j)
            printf ("---+");
          printf ("\n");
        };

      if (i > 0)
        {
          // Paredes laterais
          printf ("|");
          for (j = 0; j < array[i]; ++j)
            printf ("   |");
          printf ("\n");
          // Parte inferior
          printf ("+");
          for (j = 0; j < array[i]; ++j)
            printf ("---+");
          printf ("\n");
        };
    };
};

// Função que calcula as partições de um inteiro
void
generate_partition (int m, enum show x)
{
  // Definição e ajuste de variáveis locais
  int partition[m];
  int k = 0;
  partition[k] = m;

  // Loop principal
  while (true)
    {
      print_partition (partition, k + 1);
      if (x == Yes)
        print_young_diagram (partition, k + 1);

      int remainder = 0;

      while (k >= 0 && partition[k] == 1)
        {
          remainder += partition[k];
          k--;
        };
      // Fim do loop principal
      if (k < 0)
        return;

      // Ajuste de variáveis
      partition[k]--;
      remainder++;

      while (remainder > partition[k])
        {
          partition[k + 1] = partition[k];
          remainder = remainder - partition[k];
          k++;
        };
      partition[k + 1] = remainder;
      k++;
    };
};

//***************************************************************************************************************************
// FIM DO HEADER
#endif

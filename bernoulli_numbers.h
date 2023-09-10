// VAMOR CRIAR UM ARQUIVO QUE CALCULA A SEQUÊNCIA DOS NÚMEROS DE BERNOULLI

/*
OS NÚMEROS DE BERNOULLI FORMAM UMA DAS SEQUÊNCIAS MAIS IMPORTANTES EM
MATEMÁTICA APARECENDO EM DIVERSOS CONTEXTOS COMO NA EXPANSÃO ANALÍTICA DE
CERTAS FUNÇÕES COMO A FUNÇÃO TANGENTE CIRCULAR E A TANGENTE HIPERBÓLICA, NA
FÓRMULA DO TEOREMA DE FAULHABER, EM DETERMINADAS EXPRESSÕES ENVOLVENDO A FUNÇÃO
ZETA DE RIEMANN, ENTRE OUTROS.

VÁRIAS FÓRMULAS EXISTEM PARA CALCULAR ESTES NÚMEROS TANTO RECURSIVAMENTE,
QUANTO EXPLICITAMENTE. USAREMOS AQUI A CONVENÇÃO MAIS MODERNA NA QUAL
B(1)=-1/2.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Bernoulli_number


*/

//****************************************************************************************************************************
// CABEÇALHO
#ifndef BERNOULLI_H
#define BERNOULLI_H
#include "combinatorics.h"
#include <math.h>
#include <stdint.h>
//****************************************************************************************************************************
// PROTOTIPOS DE FUNÇÕES
double bernoulli_number_generator1 (int n);
double bernoulli_number_generator2 (int n);
double bernoulli_number_generator_positive_sign (int n);

//****************************************************************************************************************************
// FUNÇÕES
// Gerando os números de Bernoulli usando uma fórmula explicita B-
double
bernoulli_number_generator1 (int n)
{
  // Variáveis locais
  int k, v;
  double bernoulli = 0.0;
  // Procedimentos
  for (k = 0; k <= n; ++k)
    {
      for (v = 0; v <= k; ++v)
        {
          if (v % 2 == 0)
            bernoulli += ((combination (k, v) * pow (v, n)) / (k + 1));
          if (v % 2 == 1)
            bernoulli -= ((combination (k, v) * pow (v, n)) / (k + 1));
        };
    };
  // Resultado
  return bernoulli;
};

// Gerando os números de bernoulli usando recursão
double
bernoulli_number_generator2 (int n)
{
  // Casos triviais
  if (n == 0)
    return 1;
  if (n == 1)
    return (-0.5);
  // Variável local
  int k;
  double bernoulli = 0.0;

  // Definindo os números de Bernoulli recursivamente
  for (k = 0; k < n; ++k)
    {
      bernoulli += (bernoulli_number_generator2 (k) * combination (n, k)
                    / (n - k + 1));
    };
  return (-1) * bernoulli;
};

// Sequência dos números de Bernoulli com sinal +
double
bernoulli_number_generator_positive_sign (int n)
{
  if (n == 1)
    return (-1) * bernoulli_number_generator2 (n);
  else
    return bernoulli_number_generator2 (n);
};

//****************************************************************************************************************************
// FIM DO HEADER
#endif

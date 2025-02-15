// VAMOS CRIAR UM ROTINA QUE IMPLEMENTA O CÁLCULO DAS CHAMADAS SOMAS DE
// RAMANUJAN

/*
AS CHAMADAS SOMAS DE RAMANUJAN CONSISTEM EM SOMATÓRIOS DAS RAÍZES DA UNIDADES,
ISTO É DE NÚMEROS COMPLEXOS DA FORMA c(q, n) = Σ exp(2πi(a/q)n) COM AS SEGUINTES
RESTRIÇÕES mmc(a, q)=1 E 1≲a≲q. AS SOMAS DE RAMANJUJAN PODEM SER EXPRESSAS COMO
COMBINAÇÕES ENVOLVENDO A FUNÇÃO COSSENO, POIS e^(ia)=cos(a)+isen(a).

MUITAS FUNÇÕES IMPORTANTES EM TEORIA DE NÚMEROS PODEM SER EXPANDIDAS EM SÉRIES
DE POTÊNCIAS DA FORMA f= Σ a(q)c(q, n). ESTAS SÃO AS CHAMADAS SÉRIES DE
RAMANUJAN. DE FATO AS SEGUINTES IDENTIDADES SÃO VÁLIDAS: c(1, n)=1; c(q,
1)=μ(q); c(q, q)=φ(q), c(q, n)=c(q, m) SE m = n (mod q). φ É A FUNÇÃO TOTIENTE
DE EULER E μ É A FUNÇÃO DE MÖBIUS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Ramanujan%27s_sum

*/

//******************************************************************************************************************************************
// CABEÇALHO
#ifndef RAMANUJAN_SUM_H
#define RAMANUJAN_SUM_H
#include <math.h>
#include <stdint.h>
#include "ramanujan_tau_function.h"

//******************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
int64_t ramanujan_sum(int64_t, int64_t);

//******************************************************************************************************************************************
// FUNÇÕES
int64_t ramanujan_sum(int64_t q, int64_t n) {
  // Chamada recursiva do algoritmo

  // Usando a propriedade multiplicativa de c(q, n)
  if (n > 25000) {
    int64_t factor1 = 0, factor2 = 0;
    int64_t  sqrt_n = sqrt(q);
   

    // Procedimento
    for (int64_t i = (sqrt_n - 1); i > 1; --i) {
      if ((n % i) == 0) {
        factor1 = i;
        factor2 = n / i;

        if (gcd_s64(factor1, factor2) == 1) break;
      };

      if ((n % (sqrt_n - i)) == 0 && (sqrt_n - i) >= 2) {
        factor1 = (sqrt_n - i);
        factor2 = n / (sqrt_n - i);

        if (gcd_s64(factor1, factor2) == 1) break;
      };
    };

    return ramanujan_sum(factor1, n) * ramanujan_sum(factor2, n);
  };

  // Usando a propriedade c(q, n)=c(q, m) se m = n (mod q)
  if (n > 5000 && q < n) {
    int64_t m = n % q;
    return ramanujan_sum(q, m);
  };

  // Caso geral
  // Variáveis locais
  const double pi = 4.0 * atan(1.0);
  int64_t a;
  double quotient;
  double sum = 0.0;

  // Procedimentos
  for (a = 1; a <= q; ++a) {
    if (gcd_s64(a, q) == 1) {
      quotient = (2.0 * pi * a * n) / q;
      sum += cos(quotient);
    };
  };

  // Resultado
  return round(sum);

};

//******************************************************************************************************************************************
// FIM DO HEADER
#endif

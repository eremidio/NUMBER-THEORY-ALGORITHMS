// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA O CÁLCULO DAS SOMAS GAUSSIANAS QUADRÁTICAS

/*
SOMAS GAUSSIANAS SÃO IMPORTANTES SOMAS ENVOLVENDO RAÍZES DA UNIDADE. SE χ FOR UM
HOMEOMORFISMO DO GRUPO DE UNIDADES R* NO CIRCULO UNITÁRIO (DEFINIDO COMO 0 PARA
ELEMENTOS NÃO UNITÁRIOS) E ψ FOR UM HOMEOMORFISMO DO GRUPO R+ NO CÍRCULO
UNITÁRIO, ENTÃO A FORMA MAIS GERAL DAS SOMAS GAUSSIANAS TEM A FORMA G(χ, ψ)=
Σχ(x)ψ(x).

SOMAS GAUSSIANAS SÃO OS ANÁLOGOS DISCRETOS PARA CORPOS DA FUNÇÃO GAMA E
SATISFAZEM IDENTIDADES SIMILARES.

EM PARTICULAR DE GRANDE INTERESSE SÃO AS SOMAS GAUSSIANAS PARA CARACTÉRES DE
DIRICHLET χ(a) QUE SÃO DEFINIDAS PELA EXPRESSÃO GERAL: G(χ)=Σχ(x)e^(2πia/n),
ONDE 1 ≲ a ≲ n. DIFERENTES CARACTÉRES LEVAM A DIFERENTES DEFINIÇÕES PARA A SOMA
DE GAUSS.

DE GRANDE INTERESSE PRÁTICO SÃO AS CHAMADAS SOMAS GAUSSIANAS QUADRÁTICAS DA
FORMA S(p,q) = Σ e^(2πir²p/q) COM 1 ≲ r < q. AS SOMAS GAUSSIANAS QUADRÁTICAS SÃO
FUNÇÕES MULTIPLICATIVAS, ISTO É, DADO a, b, c INTEIROS COM mmc(b, c)=1, ENTÃO
S(a,bc)=S(ab,c)S(ac,b).

A SOMA DE GAUSS QUADRÁTICA GENERALIZADA É DEFINIDA PELA RELAÇÃO S(p,q,r) = Σ
e^{2πi(r²p+qr)/r}

SOMAS GAUSSIANAS SÃO IMPORTANTES EM TEORIA DE NÚMEROS E ENCONTRAM MUITAS
APLICAÇÕES PRÁTICAS COMO NA TEORIA DE RECIPROCIDADE QUADRÁTICA, CÚBICA E
QUÁRTICA; CONTAGEM DE SOLUÇÕES DE EQUAÇÕES DIOFANTINAS, ENTRE OUTROS.

PARA UMA DADA SOMA GAUSSIANA E DOIS CARACTÉRES DE DIRICHLET χ'E χ AS SOMAS DE
JACOBI SÃO DEFINIDAS POR: J(χ', χ)= Σ χ'(a)χ(1-a). UM IMPORTANTE TEOREMA FORNECE
A SEGUINTE RELAÇÃO J(χ', χ)=G(χ')G(χ)/G(χ'χ), SE χ'χ FOR UM CARACTÉRE NÃO
TRIVIAL. ESTA É UMA FORMA ANÁLOGA A RELAÇÃO ENTRE FUNÇÕES BETA E FUNÇÕES GAMA.

SOMAS GAUSSIANAS E SOMAS DE JACOBI SÃO USADAS NO TESTE DE PRIMALIDADE APR_CL
(ADLEMAN-POMENRANCE-RUMEL-COHEN-LENSTRA), UM DOS MAIS EFICIENTES TESTES DE
PRIMALIDADE QUE EXISTEM.

NO PRESENTE PROGRAMA FAREMOS USO DA CLASSE DE NÚMEROS COMPLEXOS DISPONÍVEL NO
HEADER <complex.h>.

PARA MAIORES INFORMAÇÕES:
https://en.wikipedia.org/wiki/Dirichlet_character#3
https://en.wikipedia.org/wiki/Hecke_character
https://en.wikipedia.org/wiki/Character_sum
https://en.wikipedia.org/wiki/Root_of_unity
https://en.wikipedia.org/wiki/Unit_(ring_theory)#Group_of_units
https://en.wikipedia.org/wiki/Gauss_sum
https://en.wikipedia.org/wiki/Quadratic_Gauss_sum
https://mathworld.wolfram.com/GaussianSum.html
https://mathworld.wolfram.com/SchaarsIdentity.html
https://mathworld.wolfram.com/KloostermansSum.html

*/

//*******************************************************************************************************************************************************************
// CABEÇALHO
#ifndef GAUSSIAN_SUM_H
#define GAUSSIAN_SUM_H
#include <complex.h>
#include<stdint.h>
#include <math.h>
#include <stdio.h>


// CONSTANTES GLOBAIS
#define MAX_GAUSS 50000

//*******************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
int64_t gcd_s64(int64_t, int64_t);
void find_relative_prime_factors(int64_t, int64_t*, int64_t*);
double _Complex quadratic_gaussian_sum(int64_t, int64_t);

//*******************************************************************************************************************************************************************
// FUNÇÕES
// Função que implementa o algoritmo de Euclides
int64_t gcd_s64(int64_t a, int64_t b) {

  if(b==0) return a;
  else return gcd_s64(b, (a%b));

};

// Função que decompõe um inteiro em dois fatores relativamente primos
void find_relative_prime_factors(int64_t n, int64_t* factor1,
                                 int64_t* factor2) {
  // Variáveis locais
  int64_t sqrt_n = sqrt(n), i, temp1, temp2;

  // Procedimentos
  // Loop principal
  for (i = 2; i < sqrt_n; ++i) {
    if ((n % i) == 0) {
      temp1 = i;
      temp2 = n / i;

      if (gcd_s64(temp1, temp2) == 1) {
        (*factor1) = temp1;
        (*factor2) = temp2;
        return;
      };
    };
  };
};

// Função que calcula a soma de Gauss quadrática
/*
NOTA: Notações diferentes são encontradas na literatura. Usaremos a  notação
usada em https://en.wikipedia.org/wiki/Quadratic_Gauss_sum

*/

double _Complex quadratic_gaussian_sum(int64_t p, int64_t q) {
  //*************************
  // Recursão
  if (q > MAX_GAUSS) {
    // Variáveis locais
    int64_t factor1, factor2;
    // Procedimentos
    find_relative_prime_factors(q, &factor1, &factor2);
    return quadratic_gaussian_sum((p * factor1), factor2) *
           quadratic_gaussian_sum((p * factor2), factor1);
  };

  //*************************
  // Variáveis locais
  double _Complex result;
  double real_part = 0.0, imag_part = 0.0;
  const double pi = 4.0 * atan(1.0);
  int64_t i;

  // Procedimentos

  // Casos triviais
  // p = 0 mod q
  if ((p % q) == 0) {
    real_part = q;
    imag_part = 0;
    goto final_stage;
  };

  // p=1
  if (p == 1) {
    if ((q % 4) == 0) {
      real_part = sqrt(q);
      imag_part = sqrt(q);
    };

    if ((q % 4) == 1) {
      real_part = sqrt(q);
      imag_part = 0;
    };

    if ((q % 4) == 2) {
      real_part = 0;
      imag_part = 0;
    };

    if ((q % 4) == 3) {
      real_part = 0;
      imag_part = sqrt(q);
    };

    goto final_stage;
  };

  // Caso geral: loop principal
  for (i = 0; i < q; i++) {
    real_part += cos((2 * pi * i * i * p) / q);
    imag_part += sin((2 * pi * i * i * p) / q);
  };

// Resultado
final_stage:
  result = CMPLX(real_part, imag_part);
  printf("g(%li, %li)=%lf+(%lfi)\n", p, q, creal(result), cimag(result));
  return result;
};

//*******************************************************************************************************************************************************************
// FIM DO HEADER
#endif

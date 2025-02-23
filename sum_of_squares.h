// VAMOS CRIAR UM PROGRAMA PARA EXPRESSAR NÚMEROS INTEIROS COMO A SOMA DE QUADRADOS PERFEITOS

/*

A FUNÇÃO r(k,n) É UMA FUNÇÃO ARITMÉTICA QUE COMPUTA DE QUANTAS FORMAS DIFERENTES
UM INTEIRO n PODE SER EXPRESSO COMO A SOMA DE k QUADRADOS PERFEITOS
n=a(0)²+...+a(k)². FÓRMULAS EXPLICÍTAS EXISTEM PARA ALGUNS CASOS PARTICULARES
COMO k=2, 3, 4, 6, ENTRE OUTROS.

ALGUNS TEOREMAS IMPORTANTES DÃO CONDIÇÕES NECESSÁRIAS PARA QUE n SEJA EXPRESSO
COMO A SOMA DE QUADRADOS PERFEITOS E/OU DETERMINAM DE QUANTAS FORMAS DIFERENTES
ISSO PODE SER FEITO. EM PARTICULAR:

TEOREMA DA SOMA: UM NÚMERO PODE SER EXPRESSO COMO A SOMA DE DOIS QUADRADOS
n=a²+b², SE E SOMENTE SE EM SUA DECOMPOSIÇÃO EM FATORES PRIMOS NÃO HOUVER UM
FATOR p^k COM p=3 (mod 4) PRIMO E k ÍMPAR.

TEOREMA DE LEGENDRE: UM NÚMERO PODE SER EXPRESSO COMO A SOMA DE TRÊS QUADRADOS
n=a²+b²+c², SE E SOMENTE ELE NÃO FOR DA FORMA n=(4^m)(8n+7) COM m, n INTEIROS.

TEOREMA DE LANGRANGE: TODOS NÚMEROS NATURAIS n PODEM EXPRESSO COMO A SOMA DE QUATRO
QUADRADOS PERFEITOS n=a²+b²+c²+d².

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Sum_of_squares_function
                          https://en.wikipedia.org/wiki/Sum_of_two_squares_theorem
                          https://en.wikipedia.org/wiki/Legendre%27s_three-square_theorem
                          https://en.wikipedia.org/wiki/Lagrange%27s_four-square_theorem
                          https://en.wikipedia.org/wiki/Ideal_class_group#Properties

*/

//****************************************************************************************************************************************************************
// CABEÇALHO
#ifndef SUM_OF_SQUARES_H
#define SUM_OF_SQUARES_H
#include"prime_power_detection.h"
#include <stdio.h>

//****************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
bool is_square_summable(int64_t);
void write_square_sum(int64_t);

//****************************************************************************************************************************************************************
// FUNÇÕES
// Função que determina se um número é expressível como a soma de quadrados
bool is_square_summable(int64_t n) {

  // Variáveis locais
  int64_t limit = sqrt(n);
  int64_t n_ = n;
  int64_t i, prime3_counter;

  // Procedimentos
    // Removendo fatores dois do número a ser fatorado
    while ((n % 2) == 0) n /= 2;

    // Contando o número de fatores primos da forma p = 3 (mod 4)
    for (i = 3; i < limit; i+=2) {

      // Removendo fatores p = 1 (mod 4)
      if ((i % 4) == 1) {
        while ((n_ % i) == 0) n_ /= i;
      };


      // Removendo fatores p = 3 (mod 4)
      if ((i % 4) == 3 && (n_ % i) == 0) {
        prime3_counter = 0;

        while ((n_ % i) == 0) {
          prime3_counter++;
          n_ /= i;
        };

        // Resultado
        if (prime3_counter & 1) return false;
      };
    };


    // Testando fatores primos maiores que n^(1/2)
    if (n_ > 1 && (n_ % 4) == 3) return false;

    // Caso n passe os teste acimas
    return true;

};


// Função que escreve um inteiro como uma soma de quadrados
void write_square_sum(int64_t n) {

  // Restrições
  if (is_square_summable(n) == false) {
    printf(
        "O número em questão não é expressável como a soma de dois quadrados "
        "perfeitos.\n");
    return;
  };

  // Caso trivial
  if (n == 2) {
    printf("2=1²+1²\n");
    printf("2=(-1)²+1²\n");
    printf("2=1²+(-1)²\n");
    printf("2=(-1)²+(-1)²\n");
    return;
  };


  // Variáveis locais
  int64_t a, b, b_squared;
  int64_t limit = sqrt(n);


   //Procedimentos
    // Loop principal
    for (a = 1; a < limit; ++a) {
     b_squared = n - (a * a);
     if (fast_square_detection(b_squared, &b) == true) {
      printf("%li=%li²+%li²\n", n, a, b);
      printf("%li=(-%li)²+%li²\n", n, a, b);
      printf("%li=%li²+(-%li)²\n", n, a, b);
      printf("%li=(-%li)²+(-%li)²\n", n, a, b);
    };
  };
};

//****************************************************************************************************************************************************************
// FIM DO HEADER
#endif

// VAMOS CRIAR UM PROGRAMA QUE CALCULA A SEQUÊNCIA DE FIBONACCI USANDO
// EXPONENCIAÇÃO DE MATRIZES

/*
SEJA A MATRIZ A = |1  1|. A SEGUINTE EQUAÇÃO FORNECE UM EFICIENTE ALGORTIMO PARA
COMPUTAR O N-ÉSIMO TERMO DA SEQUÊNCIA DE FIBONACCI |1  0|

EM TEMPO POLINOMIAL: PARA n INTEIRO,  A^n=|F(n+1)    F(n)|
                                          |F(n)    F(N-1)|.


A EQUAÇÃO ACIMA PODE SER REESCRITA NA FORMA DAS RELAÇÕES RECURSIVAS:
F(2n+1)=F(n)[2F(n+1)-F(n)] e F(2n)=F²(n+1)+F²(n).


PARA MAIORES INFORMAÇÕES: https://www.nayuki.io/page/fast-fibonacci-algorithms
*/

//***********************************************************************************************************************************************
// CABEÇALHO
#ifndef FIBONACCI_MATRIX_H
#define FIBONACCI_MATRIX_H
#include<boost/multiprecision/cpp_int.hpp>
#include<boost/cstdint.hpp>
#include "int128.h"
#include "matrix_exponentiation.h"
using namespace boost::multiprecision;


//***********************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
cpp_int fibonacci_matrix(int);

//***********************************************************************************************************************************************
// FUNÇÕES

// Função que calcula o n-ésimo termo da sequência de Fibonacci usando rotinas
// de expoeneciação de Matrizes
cpp_int fibonacci_matrix(int n) {
  // Variáveis locais
  Matrix<cpp_int> fib_matrix1, fib_matrix2;

  // Procedimentos
  // Ajuste da matriz base usada no cálculo
  fib_matrix1.rows = 2;
  fib_matrix1.columns = 2;
  fib_matrix1.reshape(2, 2);
  fib_matrix1.matrix[0][0] = 1;
  fib_matrix1.matrix[0][1] = 1;
  fib_matrix1.matrix[1][0] = 1;
  fib_matrix1.matrix[1][1] = 0;

  // Cálculo do resultado final
  fib_matrix2 = matrix_pow<cpp_int, int>(fib_matrix1, n);

  // Resultado
  return fib_matrix2.matrix[0][1];
};

//***********************************************************************************************************************************************
// FIM DO HEADER
#endif

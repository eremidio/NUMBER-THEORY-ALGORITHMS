// VAMOS CRIAR UM PROGRAMA QUE REDUZ OS COEFICIENTES DE UMA MATRIZ A MENOS DE
// UMA RELAÇÃO DE CONGRUÊNCIA

//****************************************************************************************************************************************************
// CABEÇALHO
#ifndef MATRIX_MODULAR_REDUCTION_H
#define MATRIX_MODULAR_REDUCTION_H
#include "matrix.h"

//****************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
template <typename T, typename U>
Matrix<T> matrix_mod(Matrix<T>&, U);

//****************************************************************************************************************************************************
// FUNÇÕES
// Função que reduz os coeficientes de uma matriz a menos de uma relação de
// congruência
template <typename T, typename U>
Matrix<T> matrix_mod(Matrix<T>& m1, U modulus) {
  // Restrição a expoentes inteiros
  static_assert(std::is_integral<T>::value,
                "Elementos da matriz congruentes devem ser inteiros");
  static_assert(std::is_integral<U>::value,
                "Inteiros congruentes devem ser inteiros");

  // Variáveis locais
  Matrix<T> result = m1;

  // Procedimentos
  // Redução dos coeficientes de uma matriz
  for (int64_t i = 0; i < m1.rows; ++i) {
    for (int64_t j = 0; j < m1.columns; ++j) result.matrix[i][j] %= modulus;
  };

  // Resultado
  return result;
};

//****************************************************************************************************************************************************
// FIM DO HEADER
#endif

// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA RORTINAS PARA EXPONENCIAÇÃO E
// EXPONENCIAÇÃO MODULAR DE MATRIZES

//******************************************************************************************************************************************************
// CABEÇALHO
#ifndef MATRIX_EXPONENTIATION_H
#define MATRIX_EXPONENTIATION_H
#include <type_traits>

#include "matrix.h"

//******************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
template <typename T, typename U>
Matrix<T> matrix_pow(Matrix<T>&, U);

template <typename T, typename U>
Matrix<T> matrix_powmod(Matrix<T>&, U, U);

//******************************************************************************************************************************************************
// FUNÇÕES
// Função que calcula a exponencial de uma matriz
template <typename T, typename U>
Matrix<T> matrix_pow(Matrix<T>& m1, U exponent) {
  // Restrição a expoentes inteiros
  static_assert(std::is_integral<U>::value, "Expoentes devem ser inteiros");
  assert(m1.rows == m1.columns);

  // Caso bases:expoentes 0 e 1
  if (exponent == 0) {
    Matrix<T> unity_matrix(m1.rows, Identity);
    return unity_matrix;
  };

  if (exponent == 1) return m1;

  // Variáveis locais
  Matrix<T> result(m1.rows, Identity);
  Matrix<T> multiplier = m1;

  // Procedimentos
  // Loop sobre os bits do expoente
  while (exponent > 0) {
    if ((exponent & 1)) {
      Matrix<T> temp = result * multiplier;
      result = temp;
    }

    Matrix<T> temp2 = multiplier * multiplier;
    multiplier = temp2;
    exponent >>= 1;
  };

  // Resultado
  return result;
};

// Função que implementa a exponenciação de matrizes a menos de uma congruência
// módulo um inteiro
template <typename T, typename U>
Matrix<T> matrix_powmod(Matrix<T>& m1, U exponent, U modulus) {
  // Restrição a expoentes inteiros
  static_assert(std::is_integral<T>::value,
                "Elementos da matriz congruentes devem ser inteiros");
  static_assert(std::is_integral<U>::value,
                "Inteiros congruentes devem ser inteiros");
  assert(m1.rows == m1.columns);

  // Caso bases:expoentes 0 e 1
  if (exponent == 0) {
    Matrix<T> unity_matrix(m1.rows, Identity);
    return unity_matrix;
  };

  if (exponent == 1) return m1;

  // Variáveis locais
  Matrix<T> result(m1.rows, Identity);
  Matrix<T> multiplier = m1;

  // Procedimentos
  // Loop sobre os bits do expoente
  while (exponent > 0) {
    if ((exponent & 1)) {
      Matrix<T> temp = result * multiplier;
      result = temp;

      // Ajustando os elementos da matriz
      for (int64_t i = 0; i < m1.rows; ++i) {
        for (int64_t j = 0; j < m1.columns; ++j) result.matrix[i][j] %= modulus;
      };
    };

    Matrix<T> temp3 = multiplier * multiplier;
    multiplier = temp3;
    exponent >>= 1;

      // Ajustando os elementos da matriz
      for (int64_t i = 0; i < multiplier.rows; ++i) {
        for (int64_t j = 0; j < multiplier.columns; ++j) multiplier.matrix[i][j] %= modulus;
      };
   
  };

  // Resultado
  return result;
};

//******************************************************************************************************************************************************
// FIM DO HEADER
#endif

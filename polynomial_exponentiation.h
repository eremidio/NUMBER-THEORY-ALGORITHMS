// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ALGORITMOS PARA EXPONENCIAÇÃO E EXPONENCIAÇÃO MODULAR DE POLINÔMIOS

//**************************************************************************************************************************************************************
// CABEÇALHO
#ifndef POLYNOMIAL_EXPONENTIATION_H
#define POLYNOMIAL_EXPONENTIATION_H
#include <type_traits>
#include "polynomials.h"

//**************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
template <typename T>
polynomial<T> generate_unity_polynomial();

template <typename T>
polynomial<T> generate_zero_polynomial();

template <typename T, typename U>
polynomial<T> polynomial_bin_pow(polynomial<T>&, U);

template <typename T, typename U>
polynomial<T> polynomial_powmod(polynomial<T>&, polynomial<T>&, U);

//**************************************************************************************************************************************************************
// FUNÇÕES
// Função que gera a elemento neutro no anel de polinômios sobre os reais
template <typename T>
polynomial<T> generate_unity_polynomial() {
  // Variáveis locais
  polynomial<T> result;

  // Procedimentos
  // Ajuste dos polinômios
  result.degree = 0;
  result.polynomial_coefficients = {static_cast<T>(1)};
  result.polynomial_powers = {0};

  // Result
  return result;
};

// Função que gera o elemento neutro da adição no anel de polinômios sobre os reais
template <typename T>
polynomial<T> generate_zero_polynomial() {
  // Variáveis locais
  polynomial<T> result;

  // Procedimentos
  // Ajuste dos polinômios
  result.degree = 0;
  result.polynomial_coefficients = {static_cast<T>(0)};
  result.polynomial_powers = {0};

  // Result
  return result;
};

// Função que implementa a exponenciação binária para polinômios
template <typename T, typename U>
polynomial<T> polynomial_bin_pow(polynomial<T>& p1, U exponent) {
  // Restrição a expoentes inteiros
  static_assert(std::is_integral<U>::value, "Expoentes devem ser inteiros");
  static_assert(std::is_integral<T>::value,
                "Coeficientes de polinômios devem ser inteiros");

  // Caso triviais: expoentes 0 ou 1
  if (exponent == 0) {
    polynomial<T> unity_polynomial = generate_unity_polynomial<T>();
    return unity_polynomial;
  }

  if (exponent == 1) return p1;

  // Caso geral:
  // Variáveis locais
  polynomial<T> result = generate_unity_polynomial<T>();
  polynomial<T> multiplier = p1;

  // Procedimentos
  // Loop sobre os bits do expoente
  while (exponent > 0) {
    if ((exponent & 1)) {
      polynomial<T> temp = result * multiplier;
      result = temp;
    };

    // Atualizando variáveis para a proxima iteração
    polynomial<T> temp2 = multiplier * multiplier;
    multiplier = temp2;

    exponent >>= 1;
  };

  // Resultado
  return result;
};

// Função que implementa o algoritmo de exponenciação modular para polinômios sobre os reais
template <typename T, typename U>
polynomial<T> polynomial_powmod(polynomial<T>& p1, polynomial<T>& p2,
                                U exponent) {
  // Restrição a expoentes inteiros
  static_assert(std::is_integral<U>::value, "Expoentes devem ser inteiros");
  static_assert(std::is_integral<T>::value,
                "Coeficientes de polinômios devem ser inteiros");

  // Caso triviais: expoentes 0 ou 1
  if (exponent == 0) {
    polynomial<T> unity_polynomial = generate_unity_polynomial<T>();
    return unity_polynomial;
  }

  if (exponent == 1){
     polynomial<T> result=remainder(p1, p2);
     return result;
  }

  // Caso geral:
  // Variáveis locais
  polynomial<T> result = generate_unity_polynomial<T>();
  polynomial<T> multiplier = p1;

  // Procedimentos
  // Loop sobre os bits do expoente
  while (exponent > 0) {
    if ((exponent & 1)) {
      polynomial<T> temp = result * multiplier;
      result = temp;

      if (result.degree > p2.degree) {
        polynomial<T> temp2 = remainder(result, p2);
        result = temp2;
      };
    };

    // Atualizando variáveis para a proxima iteração
    polynomial<T> temp3 = multiplier * multiplier;
    multiplier = temp3;
    exponent >>= 1;
  };

  // Resultado
  return result;
};

//**************************************************************************************************************************************************************
// FIM DO HEADER
#endif

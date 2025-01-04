// VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA REDUZIR OS COEFICIENTES DE UM POLINÔMIO MÓDULO UM INTEIRO

//*************************************************************************************************************************************************************
// CABEÇALHO
#ifndef POLYNOMIAL_MODULUS_REDUCTION_H
#define POLYNOMIAL_MODULUS_REDUCTION_H
#include <type_traits>
#include "polynomial_exponentiation.h"

//*************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
template <typename T, typename U>
polynomial<T> polynomial_modulus_reduction(polynomial<T>&, U);

//*************************************************************************************************************************************************************
// FUNÇÕES

// Função que reduz os coeficientes de um polinômio a menos de uma relação de
// congruência
template <typename T, typename U>
polynomial<T> polynomial_modulus_reduction(polynomial<T>& p1, U modulus) {
  // Restrição a expoentes inteiros
  static_assert(std::is_integral<U>::value,
                "Fatores de redução devem ser inteiros");
  static_assert(std::is_integral<T>::value,
                "Coeficiente dos polinômios de redução devem ser inteiros");

  // Variáveis locais
  polynomial<T> p2 = p1;
  polynomial<T> result;

  // Procedimentos
  // Reduzindo os coeficientes dos polinômios
  for (auto& x : p2.polynomial_coefficients) x %= modulus;

  // Ajuste do resultado
  result.degree = 1;

  for (auto c : p2.polynomial_coefficients) {
    if (c == 0 && result.polynomial_coefficients.size() == 0) continue;

    result.polynomial_coefficients.push_back(c);
  };

  if (result.polynomial_coefficients.size() == 0) {
    result = generate_zero_polynomial<T>();
    return result;
  } else
    result.degree = (result.polynomial_coefficients.size() - 1);

  for (int64_t i = result.degree; i >= 0; --i)
    result.polynomial_powers.push_back(i);

  // Resultado
  return result;
};

//*************************************************************************************************************************************************************
// FIM DO HEADER
#endif

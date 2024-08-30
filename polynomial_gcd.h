// VAMOS CRIAR UM PROGRAMA QUE CALCULA O MDC DE DOIS POLINÔMIOS

//*****************************************************************************************************************************************************************
// CABEÇALHO
#ifndef POLYNOMIAL_GCD_H
#define POLYNOMIAL_GCD_H
#include "polynomial_cast.h"
#include "polynomial_monic.h"

//*****************************************************************************************************************************************************************
// DECLARAÇÃO DE FUNÇÕES
template <typename T>
bool is_zero_polynomial(polynomial<T>&);
template <typename T>
bool is_unity_polynomial(polynomial<T>&);
template <typename T>
bool is_equal_polynomial(polynomial<T>&, polynomial<T>&);
template <typename T>
polynomial<T> polynomial_gcd(polynomial<T>&, polynomial<T>&);

//*****************************************************************************************************************************************************************
// FUNÇÕES
// Função que determina se um polinômio tem todos seus coeficientes nulos
template <typename T>
bool is_zero_polynomial(polynomial<T>& p1) {
  // Resultado
  for (auto c : p1.polynomial_coefficients) {
    if (c != 0) return false;
  };

  return true;
};

// Função que determina se um polinômio é a identidade no anel de polinômios
template <typename T>
bool is_unity_polynomial(polynomial<T>& p1) {
  // Resultado
  if (p1.degree == 0) {
    for (auto c : p1.polynomial_coefficients) {
      if (c == 1) return true;
    }
  };

  return false;
};

// Função que determina se dois polinômios são iguais
template <typename T>
bool is_equal_polynomial(polynomial<T>& p1, polynomial<T>& p2) {
  // Resultado
  if (p2.degree == p1.degree &&
      p1.polynomial_coefficients == p2.polynomial_coefficients)
    return true;
  else
    return false;
};

// Função que calcula o mdc de dois polinômios
template <typename T>
polynomial<T> polynomial_gcd(polynomial<T>& p1, polynomial<T>& p2) {
  // Restrição
  if (p1.degree < p2.degree) return polynomial_gcd(p2, p1);

  // Procedimentos
  // Caso trivial: p2(x) divide p1(x)
  polynomial<T> remainder_polynomial = remainder<T>(p1, p2);

  if (is_zero_polynomial<T>(remainder_polynomial)) return p2;

  // Calculando

  // Caso geral: p2(x) não divide p1(x)
  // Variáveis locais
  polynomial<double> u = polynomial_cast<T, double>(
      p2);  // Aritmética será feita no domínio dos reais para evitar erros
            // devido a float point exceptions
  polynomial<double> v = polynomial_cast<T, double>(remainder_polynomial);

  while (1) {
    polynomial<double> temp = remainder<double>(u, v);

    if (is_zero_polynomial<double>(temp) ||
        is_equal_polynomial<double>(u, v) == true)
      break;
    else {
      u = v;
      v = make_monic_polynomial<double>(temp);
    };
  };

  // Fazendo o cast de polinômios para seu tipo original
  polynomial<T> result = polynomial_cast<double, T>(v);
  polynomial<T> monic_result = make_monic_polynomial<T>(result);

  // Resultado
  return monic_result;
};

//*****************************************************************************************************************************************************************
// FIM DO HEADER
#endif

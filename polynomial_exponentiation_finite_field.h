//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA EXPOENENCIAR POLINÔMIOS QUE TOMAM VALORES EM UM CORPO FINITO DO TIPO (INTEIROS A MENOS DE UMA CONGRUÊNCIA)

/*
ESTAS ROTINAS SERÃO USADAS PARA IMPLEMENTAR ALGORITMOS MAIS EFICIENTES ENVOLVENDO ARITMÉTICA
EM CORPOS FINITOS DO SEGUNDO TIPO CUJOS ELEMENTOS SÃO POLINÔMIOS IRREDUTÍVEIS COM
COEFICIENTES EM UM CORPO FINITO F(p) INTEIROS A MENOS DE UMA CONGRUÊNCIA MÓDULO UM PRIMO.

*/

//****************************************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_EXPONENTIATION_FINITE_FIELD_H
#define POLYNOMIAL_EXPONENTIATION_FINITE_FIELD_H
#include"polynomial_exponentiation.h"
#include"fast_polynomial_division_finite_field.h"

//****************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template <typename T, typename U>
polynomial<T> polynomial_bin_pow_finite_field(polynomial<T>&, U, U);

template <typename T, typename U>
polynomial<T> polynomial_powmod_finite_field(polynomial<T>&, polynomial<T>&, U, U);


//****************************************************************************************************************
//FUNÇÕES

// Função que implementa a exponenciação binária para polinômiossobre F(p)
template <typename T, typename U>
polynomial<T> polynomial_bin_pow_finite_field(polynomial<T>& p1, U exponent, U prime_base) {
  // Restrição a expoentes inteiros
  static_assert(std::is_integral<U>::value, "Expoentes devem ser inteiros");
  static_assert(std::is_integral<T>::value, "Coeficientes de polinômios devem ser inteiros");

  // Caso triviais: expoentes 0 ou 1
  if (exponent == 0) {
    polynomial<T> unity_polynomial = generate_unity_polynomial<T>();
    return unity_polynomial;
  }

  if (exponent == 1){
    polynomial<T> result=p1;
  
    //Ajuste dos coeficientes do resultado
    for(auto& c:result.polynomial_coefficients) c%= prime_base;

    //Resultado
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
        for(auto& c:result.polynomial_coefficients) c%= prime_base;
      };

      // Atualizando variáveis para a proxima iteração
      polynomial<T> temp2 = multiplier * multiplier;
      multiplier = temp2;
      for(auto& c1:multiplier.polynomial_coefficients) c1%= prime_base;
      exponent >>= 1;
    };

  
    //Ajuste final dos coeficientes do resultado final
    for(auto& c:result.polynomial_coefficients) c%= prime_base;

  // Resultado
  return result;
};


// Função que implementa o algoritmo de exponenciação modular para polinômios sobre F(p)
template <typename T, typename U>
polynomial<T> polynomial_powmod_finite_field(polynomial<T>& p1, polynomial<T>& p2/* p2 deve ser mônico*/,
                                U exponent, U prime_base) {
  // Restrição a expoentes inteiros
  static_assert(std::is_integral<U>::value, "Expoentes devem ser inteiros");
  static_assert(std::is_integral<T>::value, "Coeficientes de polinômios devem ser inteiros");

  // Caso triviais: expoentes 0 ou 1
  if (exponent == 0) {
    polynomial<T> unity_polynomial = generate_unity_polynomial<T>();
    return unity_polynomial;
  }

  if (exponent == 1){
     polynomial<T> result=remainder(p1, p2);

    //Ajuste dos coeficientes do resultado
    for(auto& c:result.polynomial_coefficients) c%= prime_base;

    //Resultado
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
        result = result * multiplier;

        if (result.degree > p2.degree) {
          polynomial<T> q, r;
          fast_polynomial_division_finite_field<T, U>(result, p2, q, r, prime_base);
          result=r;
        };

      };

      // Atualizando variáveis para a proxima iteração
      multiplier = multiplier * multiplier;
      if (multiplier.degree > p2.degree) {
          polynomial<T> q, r;
          fast_polynomial_division_finite_field<T, U>(multiplier, p2, q, r, prime_base);
          multiplier=r;
      };
      exponent >>= 1;
    };

    //Ajuste final dos coeficientes do resultado final
    if (result.degree > p2.degree) {
      polynomial<T> q, r;
      fast_polynomial_division_finite_field<T, U>(result, p2, q, r, prime_base);
      result=r;
    };

  // Resultado
  return result;

};

//****************************************************************************************************************
//FIM DO HEADER
#endif

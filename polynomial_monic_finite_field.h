//VAMOS CRIAR UM PROGRAMA QUE CONVERTE POLINÔMIOS COM COEFICIENTES EM UM CORPO FINITO DO PRIMEIRO TIPO EM POLINÔMIOS MÔNICOS

/*
ESTE ALGORITMO PODERÁ SER USADO COMO SUBROTINAS EM OUTROS ALGORITMOS MAIS SOFISTICADOS.
EM UM CORPO FINITO NO PRIMEIRO TIPO PARA REDUZIR UM POLINÔMIO f(x) A SUA FORMA MÔNICA, 
OS COEFICIENTES c DE f(x) DEVEM SER MULTIPLICADOS PELO INVERSO MULTIPLICATIVO 
m⁻¹ (mod p), ONDE m DENOTA O COEFICIENTE DO MONÔMIO DE MAIOR GRAU EM f(x).

*/

//*******************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_MONIC_FINITE_FIELD_H
#define POLYNOMIAL_MONIC_FINITE_FIELD_H
#include"polynomials.h"

//*******************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
T modular_inverse(T, T);

template<typename T>
polynomial<T> make_monic_polynomial_finite_field(polynomial<T>&, T);


//*******************************************************************************************
//FUNÇÕES
//Funções auxiliares: cálculo de inverso modular via algoritmo de Euclides
template<typename T>
T modular_inverse(T a, T n){

  //Variáveis locais
  T r0,r1, x0, x1, r2, x2;

  //Procedimentos 
    //Ajuste de variáveis
    r0=a;
    r1=n;
    r2=1;
    x0=1;
    x1=0;

    //Calculando os valores finais coeficientes recursivamente
    while(r2>0){
      T quotient= r0/r1;
  
      r2=r0-quotient*r1;
      x2=x0-quotient*x1;

      //Atualizando variáveis para a próxima iteração
      if(r2>0){
       r0=r1; r1=r2;
       x0=x1; x1=x2;
              };
    };

  //Resultado
  if(x1<0)
    return(x1+n);
  else
    return x1;

};


//Função que converte um polinômio em um polinômio mônico em um corpo finitodo primeiro tipo
template<typename T>
polynomial<T> make_monic_polynomial_finite_field(polynomial<T>& p1, T prime){

  // Restrição a coeficientes inteiros
  static_assert(std::is_integral<T>::value, "Coeficientes de polinômios devem ser inteiros");

  //Variáveis locais
  polynomial<T> monic_poly = p1;
  T lead_coefficient =  monic_poly.polynomial_coefficients[0];
  T ratio = modular_inverse<T>(lead_coefficient, prime);


  //Procedimento
    //Reduzindo os coeficientes do polinômio
    for(auto& c:monic_poly.polynomial_coefficients) c=(c*ratio)%prime;

  //Resultado
  return monic_poly;

};

//*******************************************************************************************
//FIM DO HEADER
#endif

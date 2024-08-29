//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O MÉTODO DE HORNERS PARA DETERMINAR O VALOR DE UM POLINÔMIO PARA UM DADO ARGUMENTO 

/*
PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Horner%27s_method
*/

//******************************************************************************************************************************************************
//CABEÇALHO
#ifndef HORNERS_EVALUATION_POLYNOMIAL_H
#define HORNERS_EVALUATION_POLYNOMIAL_H
#include<stdint.h>
#include"polynomials.h"

//******************************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T, typename U>
U horners_polynomial_evaluation(polynomial<T>, T);

template<typename T, typename U>
U horners_polynomial_evaluation(polynomial<T>, T, T);


//******************************************************************************************************************************************************
//FUNÇÕES
//Função que implementa o algoritmo de Horners para determinar o valor de um polinômio
template<typename T, typename U>
U horners_polynomial_evaluation(polynomial<T> poly1, T argument){

  //Variáveis locais
  std::vector<U> coefficients;
  U arg=static_cast<U>(argument);
  U result, current;

  //Procedimentos
    //Convertendo os coeficientes do polinômio
    for(auto coeff:poly1.polynomial_coefficients)
      coefficients.push_back(static_cast<U>(coeff));

    //Caso base: polinômios de grau 0 e 1
    if(poly1.degree==0) return coefficients[0];
    result=(coefficients[0]*arg)+coefficients[1];
    if(poly1.degree==1) return result;
  
    //Iterando sobre os demais coeficientes do polinômio    
    for(int64_t i=2; i<coefficients.size(); ++i){
      current=result;
      result=current*arg+coefficients[i];
    }


  //Resultado
  return result;


};


//Função que determina o valor de um polinômio para  um dado argumentoa menos de uma relação de congruência
template<typename T, typename U>
U horners_polynomial_evaluation(polynomial<T> poly1, T argument, T modulus){

  //Variáveis locais
  std::vector<U> coefficients;
  U arg=static_cast<U>(argument);
  U result, current;

  //Procedimentos
    //Convertendo os coeficientes do polinômio
    for(auto coeff:poly1.polynomial_coefficients)
      coefficients.push_back(static_cast<U>(coeff));

    //Caso base: polinômios de grau 0 e 1
    if(poly1.degree==0) return coefficients[0]%modulus;
    result=(coefficients[0]*arg)+coefficients[1];
    if(poly1.degree==1) return result%modulus;
  
    //Iterando sobre os demais coeficientes do polinômio    
    for(int64_t i=2; i<coefficients.size(); ++i){
      current=result%modulus;
      result=current*arg+coefficients[i];
    }


  //Resultado
  return result%modulus;


};

//******************************************************************************************************************************************************
//FIM DO HEADER
#endif

//VAMOS CRIAR UMA FUNÇÃO QUE É USADA PARA CONVERSÃO ENTRE POLINÔMIOS CUJOS COEFICIENTES SÃO DEFINIDOS EM CONJUNTOS DIFERENTES



//********************************************************************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_CAST_H 
#define POLYNOMIAL_CAST_H
#include"polynomials.h"

//********************************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T, typename U>
polynomial<U> polynomial_cast(polynomial<T>);


//********************************************************************************************************************************************
//FUNÇÕES

//Função de conversão de polinômios com diferentes argumentos templates
template<typename T, typename U>
polynomial<U> polynomial_cast(polynomial<T> p1){

 //Variáveis locais
 polynomial<U> cast_polynomial;


 //Procedimentos
  //Ajuste do grau e do array de expoentes
  cast_polynomial.degree=p1.degree;
  cast_polynomial.polynomial_powers=p1.polynomial_powers;



  //Ajuste do array de coeficientes
  for(auto c:p1.polynomial_coefficients)
   cast_polynomial.polynomial_coefficients.push_back(static_cast<U>(c));

 //Resultado                                  
 return cast_polynomial;
                                               };


//********************************************************************************************************************************************
//FIM DO HEADER
#endif

//VAMOS CRIARUM PROGRAMA QUE COMPUTA O GCD DE POLINÔMIOS DEFINIDOS SOBRE CORPOS FINITOS DO PRIMEIRO TIPO 

/*
ALGORITMO PARA SER USADO COMO SUBROTINA EM ALGORITMOS MAIS SOFISTICADOS.

*/

//*******************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_GCD_FINITE_FIELD_H
#define POLYNOMIAL_GCD_FINITE_FIELD_H
#include"polynomial_gcd.h"
#include"polynomial_modulus_reduction.h"
#include"polynomial_monic_finite_field.h"
#include"fast_polynomial_division_finite_field.h"

//*******************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> polynomial_gcd_finite_field(polynomial<T>&, polynomial<T>&, T);


//*******************************************************************************************
//FUNÇÕES
//Função que calcula o gcd de dois polinômios definidos sobre F(p)
template<typename T>
polynomial<T> polynomial_gcd_finite_field(polynomial<T>& p1, polynomial<T>& p2, T prime){

  //Restrição
  if(p2.degree>p1.degree) return polynomial_gcd_finite_field(p2, p1, prime);

  //Variáveis locais
  polynomial<T> u=p1, v=p2;
  polynomial<T> Q, R;



  //Procedimentos
    //Checando se p2(x) divide p1(x)
    fast_polynomial_division_finite_field(p1, p2, Q, R, prime);
    if (is_zero_polynomial<T>(R)) return p2;


    //Loop principal
    while(1){
      fast_polynomial_division_finite_field(u, v, Q, R, prime);
      if (is_zero_polynomial<T>(R) || is_equal_polynomial<T>(u, v) == true)
        break;
      else{
        u=v;
        v=make_monic_polynomial_finite_field<T>(R, prime);
      }

    }

  //Resultado  
  polynomial<T> monic_result = make_monic_polynomial_finite_field<T>(v, prime);
  return monic_result;

};

//*******************************************************************************************
//FIM DO HEADER
#endif

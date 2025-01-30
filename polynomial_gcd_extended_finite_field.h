//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA O ALGORITMO DE EUCLIDES EXTENDIDO PARA POLINÔMIOS COM COEFICIENTES EM CORPOS FINITOS DO PRIMEIRO TIPO

/*

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/ALGEBRA-FACILITIES/blob/main/polynomial_gcd_extended.h

*/


//*************************************************************************************************************
//CABEÇALHO
#ifndef POLYNOMIAL_EXTENDED_GCD_FINITE_FIELD_H
#define POLYNOMIAL_EXTENDED_GCD_FINITE_FIELD_H
#include"fast_polynomial_division_finite_field.h"
#include"polynomial_exponentiation.h"
#include"polynomial_monic_finite_field.h"
#include"polynomial_gcd.h"
#include"polynomial_modulus_reduction.h"
#include<type_traits>


//*************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
void polynomial_finite_field_extended_euclidean_algorithm(polynomial<T>&, polynomial<T>&, polynomial<T>&, polynomial<T>&, polynomial<T>&, T);

//*************************************************************************************************************
//FUNÇÕES
//Função que imeplementa o algoritmo de Euclides extendido para polinômios sobre GF(p) para polinômios mônicos
template<typename T>
void polynomial_finite_field_extended_euclidean_algorithm(polynomial<T>& p1, polynomial<T>& p2,
                                                          polynomial<T>& A, polynomial<T>& B, polynomial<T>& gcd_poly, T prime){

  //Restrição a coeficientes inteiros
  static_assert(std::is_integral<T>::value, "Coeficientes de polinômios devem ser inteiros");
  assert(p1.degree>=p2.degree);

  //Variáveis locais
  polynomial<T> r0=p1, r1=p2;
  polynomial<T> s0=generate_unity_polynomial<T>(), s1=generate_zero_polynomial<T>();
  polynomial<T> t0=generate_zero_polynomial<T>(), t1=generate_unity_polynomial<T>();
  polynomial<T> s2, t2;


  //Procedimentos
    //Loop principal
    while(1){
    
      //Calculando o quociente Euclidiano
      polynomial<T> quotient, remainder;  
      fast_polynomial_division_finite_field(r0, r1, quotient, remainder, prime);

      //Atualizando variáveis para a próxima iteração
      r0=r1;
      r1=remainder;
      r1=make_monic_polynomial_finite_field<T>(r1, prime);
      r1.adjust_degree();



      polynomial<T> temp1=quotient*s1;
      polynomial<T> temp2=quotient*t1;

      s2=s0-temp1;      
      t2=t0-temp2;

      s0=s1;
      s1=s2;
      t0=t1;
      t1=t2;

      r0=polynomial_modulus_reduction<T, T>(r0, prime);
      r1=polynomial_modulus_reduction<T, T>(r1, prime);
      s0=polynomial_modulus_reduction<T, T>(s0, prime);
      s1=polynomial_modulus_reduction<T, T>(s1, prime);
      t0=polynomial_modulus_reduction<T, T>(t0, prime);
      t1=polynomial_modulus_reduction<T, T>(t1, prime);


      //Fim do loop 
      if(is_zero_polynomial<T>(r1)  || r1.polynomial_coefficients.size()==0 || (r1.polynomial_coefficients[0]==0 && r1.degree==0))
        break;     


    }



  //Resultado da execusção do algoritmo
  gcd_poly=r0;
  A = s0; B=t0; 

};


//*************************************************************************************************************
//FIM DO HEADER
#endif

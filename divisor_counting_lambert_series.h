//VAMOS CRIAR UM PROGRAMA QUE CALCULA A FUNÇÃO DE CONTAGEM DE DIVISORES DE UM INTEIRO d(n) USANDO SÉRIES DE LAMBERT 

/*

PARA A FUNÇÃO DE CONTAGEM DE DIVISORES DE UM INTEIRO d(n) TEMOS A SEGUINTE IDENTIDADE: Σ{x^n}d(n)=Σ {x^n/(1-x^n)}
QUE PODE SER USADA PARA COMPUTAR RAPIDAMENTE VALORES DE d(n) EM UM INTERVALO.

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/sum_of_divisors_lambert_series.h
                          https://oeis.org/A000005
*/


//****************************************************************************************************
//CABEÇALHO
#ifndef DIVISOR_COUNTING_LAMBERT_SERIES_H
#define DIVISOR_COUNTING_LAMBERT_SERIES_H
#include"sparse_polynomials.h"



//****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> generate_divisorcounting_polynomial_factor(int64_t, int64_t);


template<typename T>
void compute_divisor_counting_function(int64_t);

//****************************************************************************************************
//FUNÇÕES
//Função que calcula uma soma parcial da Série de Lambert
template<typename T>
polynomial<T> generate_divisorcounting_polynomial_factor(int64_t bound, int64_t step){

  //Variáveis locais
  polynomial<T> multiplier1, multiplier2, result;
  univariate_monomial<T> poly_term;


  //Procedimentos
    //Inicializando o polinômio p(n, x)=(x^n)
    poly_term.coefficient=1;  poly_term.power=step;
    multiplier1.monomials.insert({poly_term.power, poly_term}); 

    //Inicializando o polinômio q(x) que aproxima a série  1/{1-x^n}=Σx^(kn) para |x|<1
      //1ºtermo
      poly_term.coefficient=1;  poly_term.power=0;
      multiplier2.monomials.insert({poly_term.power, poly_term});


      //Demais termos
      for(int64_t i=step; i<=bound; i+=step){
        poly_term.coefficient=1;  poly_term.power=i;
        multiplier2.monomials.insert({poly_term.power, poly_term});

      }


      //Ajuste do resultado
      result=multiplier1*multiplier2;



      //Removendo os termos de coeficientes elevados
      for(auto it=result.monomials.begin(); it!=result.monomials.end();){
        if((it->second.power)>bound)
          it = result.monomials.erase(it);
        else break;
      
      }


  //Resultado
  return result;

};


//Função que a função d(n) usando somas parciais de séries de Lambert
template<typename T>
void compute_divisor_counting_function(int64_t n){

  //Variáveis locais
  polynomial<T> lambert_series_polynomial;
  univariate_monomial<T> zero_monomial(0,0);

  
  //Procedimentos
    //Inicializando o polinômio que corresponde as somas parciais de séries de Lambert L(x)=0
    lambert_series_polynomial.monomials.insert({zero_monomial.power, zero_monomial});

    //Loop principal: computando as somas parciais de séries de Lambert L(x)=0
    for(int64_t i=1; i<=n; ++i){
      polynomial<T> partial_polynomial=generate_divisorcounting_polynomial_factor<T>(n, i);
      lambert_series_polynomial=lambert_series_polynomial+partial_polynomial;
    };


    //Exibindo o resultado da execução do algoritmo
    for(auto it=lambert_series_polynomial.monomials.begin(); it!=lambert_series_polynomial.monomials.end(); ++it)
      std::cout<<"d("<<it->second.power<<") = "<<it->second.coefficient<<", ";
    std::cout<<"...\n";


};


//****************************************************************************************************
//FIM DO HEADER
#endif 

//VAMOS CRIAR UM PROGRAMA QUE COMPUTA POLINÔMIOS CICLOTÔMICOS USANDO A CLASSE DE POLINÔMIOS ESPARSOS

/*

A SEGUINTE IDENTIDADE PODE SER USADA PARA COMPUTAR POLINÔMIOS CICLOTOMÔMICOS USANDO UM NÚMERO REDUZIDO
DE OPERAÇÕES DE DIVISÕES PARA PEQUENOS INDEXES:
  φ(n, x)=Π(1-x^(n/d))^μ(d), ONDE d SÃO OS DIVISORES DE n E μ(d) É A FUNÇÃO DE MÖBIUS.

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/cyclotomic_polynomials.hpp

*/


//******************************************************************************************************************
//CABEÇALHO
#ifndef CYCLOTOMIC_POLYNOMIALS2_H
#define CYCLOTOMIC_POLYNOMIALS2_H
#include"sparse_polynomials.h"
#include"mobius_function.h"
#include<vector>


//******************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
void compute_divisors_mobius_values(std::vector<int64_t>&, std::vector<int>&, int64_t);

template<typename T>
polynomial<T> compute_cyclotomic_factor(int64_t);

template<typename T>
polynomial<T> compute_cyclotomic_polynomial(int64_t);

//******************************************************************************************************************
//FUNÇÕES 
//Função que computa um divisor de um inteiro de 64 bits
void compute_divisors_mobius_values(std::vector<int64_t>& factors_vector, std::vector<int>& mobius_vector, int64_t n){

  //Variáveis locais
  int64_t d;

  //Procedimentos
    //Loop principal
    for(d=1; d<=n; ++d){
      if((n%d)==0){
        factors_vector.push_back(d);
        mobius_vector.push_back(mobius_function(d));

      }

    }

};


//Função que computa um fator p(x) usado no cálculo do n-ésimo polinômio ciclotômico
template<typename T>
polynomial<T> compute_cyclotomic_factor(int64_t q){

  //Variáveis locais
  polynomial<T> partial;
  univariate_monomial<T> poly_term;


  //Procedimentos
    //Adicionando termos no polinômio
    poly_term.coefficient=1;  poly_term.power=0;
    partial.monomials.insert({poly_term.power, poly_term});
    poly_term.coefficient=(-1);  poly_term.power=q;
    partial.monomials.insert({poly_term.power, poly_term});


  //Resultado
  return partial;

};


//Função que computa o n-ésimo polinômio ciclotômico
template<typename T>
polynomial<T> compute_cyclotomic_polynomial(int64_t n){

  //Variáveis locais
  polynomial<T> cyclotomic_polynomial;
  univariate_monomial<T> poly_term;
  std::vector<int64_t> factor_vector;
  std::vector<int> mobius_vector;
  int64_t quotient;


  //Procedimento
    //Definindo a identidade p(x)=1
    poly_term.coefficient=1;  poly_term.power=0;
    cyclotomic_polynomial.monomials.insert({poly_term.power, poly_term});
  

    //Calculando os divisores e a função de Möbius dos divisores de n
    factor_vector.resize(0); mobius_vector.resize(0);
    compute_divisors_mobius_values(factor_vector, mobius_vector, n);  
  

    //Calculando o n-ésimo polinômio ciclotômico
    for(size_t s=0; s<factor_vector.size(); ++s){

      quotient=n/factor_vector[s];
      if(mobius_vector[s]>0){
        polynomial<T> partial_poly= compute_cyclotomic_factor<T>(quotient);
        cyclotomic_polynomial=cyclotomic_polynomial*partial_poly;
        continue;
      }


    };//Fim do loop principal


    for(size_t s=0; s<factor_vector.size(); ++s){

      quotient=n/factor_vector[s];
      if(mobius_vector[s]<0){
        polynomial<T> partial_poly= compute_cyclotomic_factor<T>(quotient);
        cyclotomic_polynomial=cyclotomic_polynomial/partial_poly;
        continue;
      }



    };//Fim do loop principal



  //Resultado
  return cyclotomic_polynomial;

};


//******************************************************************************************************************
//FIM DO HEADER
#endif

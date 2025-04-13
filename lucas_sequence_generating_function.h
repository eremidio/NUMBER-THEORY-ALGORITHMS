//VAMOS CRIAR UM PROGRAMA QUE COMPUTA TERMOS DA SEQUÊNCIA DE LUCAS USANDO FUNÇÕES GERADORAS

/*

SEQUÊNCIAS DE LUCAS DO PRIMEIRO E SEGUNDO TIPO PODEM SER CALCULADAS USANDO-SE AS SEGUINTES FUNÇÕES GERADORAS:
Σ Un(P,Q){x^n}= {x}/{1-Px+Qx²}; Σ Vn(P,Q){x^n}={2-Px}/{1-Px+Qx²}.

TAIS IDENTIDADES PODEM SER DIRETAMENTE OBTIDAS A PARTIR DAS RELAÇÕES DE RECORRÊNCIA QUE DEFINEM ESSAS
SEQUÊNCIAS E SÃO ÚTEIS PARA COMPUTAR TERMOS DESTA SEQUÊNCIA EM UM INTERVALO.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Lucas_sequence#Generating_functions


*/ 


//*********************************************************************************************************
//CABEÇALHO
#ifndef LUCAS_SEQUENCE_GENERATING_FUNCTION_H
#define LUCAS_SEQUENCE_GENERATING_FUNCTION_H
#include"sparse_polynomials.h"
#include<algorithm>


//*********************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
std::vector<T> compute_lucas_sequence_first_kind(int64_t, int64_t, int64_t);

template<typename T>
std::vector<T> compute_lucas_sequence_second_kind(int64_t);


//*********************************************************************************************************
//FUNÇÕES
/*
  NOTA: Usaremos a relação formal 1/(1-Px+Qx²)=1/(1-f(x)) ~ 1+f(x)+f²(x)+f³(x)+...;
        com a função f(x)=Px-Qx², para computar somas parciais da série.

*/

//Função que computa sequências de Lucas do primeiro tipo usando funções geradoras
template<typename T>
std::vector<T> compute_lucas_sequence_first_kind(int64_t P, int64_t Q, int64_t n){

  //Variáveis locais
  polynomial<T> lucas_polynomial, q, multiplier;
  univariate_monomial<T> poly_term;
  std::vector<T> lucas_sequence_vector;


  //Procedimentos
    //Ajuste dos polinômios usados no cálculo
    poly_term.coefficient=1;  poly_term.power=1;
    lucas_polynomial.monomials.insert({poly_term.power, poly_term});//1º termo l(x)=x
    q.monomials.insert({poly_term.power, poly_term});

    poly_term.coefficient=P;  poly_term.power=1;
    multiplier.monomials.insert({poly_term.power, poly_term});//f(x)=Px-Qx²
    poly_term.coefficient=(Q*(-1));  poly_term.power=2;
    multiplier.monomials.insert({poly_term.power, poly_term});


    //Loop principal
    for(int64_t i =1; i<n; ++i){
      
      q=q*multiplier;
      lucas_polynomial=lucas_polynomial+q;

      //Removendo os termos de expoentes elevados
      if(q.degree()>(n+20)){
        for(auto it=q.monomials.begin(); it!=q.monomials.end();){
          if((it->first)>n)
            it = q.monomials.erase(it);
          else break;
        }
      }


    };//Fim do loop principal

    //Coletando os coeficientes do polinômio calculado
    for(auto it=lucas_polynomial.monomials.begin(); it!=lucas_polynomial.monomials.end();++it){
      T E=it->second.coefficient;
      lucas_sequence_vector.push_back(E);
    }

    lucas_sequence_vector.push_back(0);//1º termo da sequência
    std::reverse(lucas_sequence_vector.begin(), lucas_sequence_vector.end());


  //Resultado
  return lucas_sequence_vector;  

};


//Função que computa sequências de Lucas do segundo tipo usando funções geradoras
template<typename T>
std::vector<T> compute_lucas_sequence_second_kind(int64_t P, int64_t Q, int64_t n){

  //Variáveis locais
  polynomial<T> lucas_polynomial, q, multiplier;
  univariate_monomial<T> poly_term;
  std::vector<T> lucas_sequence_vector;


  //Procedimentos
    //Ajuste dos polinômios usados no cálculo
    poly_term.coefficient=2;  poly_term.power=0;
    lucas_polynomial.monomials.insert({poly_term.power, poly_term});//1º termo l(x)=2-Px
    q.monomials.insert({poly_term.power, poly_term});
    poly_term.coefficient=((-1)*P);  poly_term.power=1;
    lucas_polynomial.monomials.insert({poly_term.power, poly_term});//1º termo l(x)=2-Px
    q.monomials.insert({poly_term.power, poly_term});


    poly_term.coefficient=P;  poly_term.power=1;
    multiplier.monomials.insert({poly_term.power, poly_term});//f(x)=Px-Qx²
    poly_term.coefficient=(Q*(-1));  poly_term.power=2;
    multiplier.monomials.insert({poly_term.power, poly_term});


    //Loop principal
    for(int64_t i =1; i<n; ++i){
      
      q=q*multiplier;
      lucas_polynomial=lucas_polynomial+q;

      //Removendo os termos de expoentes elevados
      if(q.degree()>(n+20)){
        for(auto it=q.monomials.begin(); it!=q.monomials.end();){
          if((it->first)>n)
            it = q.monomials.erase(it);
          else break;
        }
      }


    };//Fim do loop principal

    //Coletando os coeficientes do polinômio calculado
    for(auto it=lucas_polynomial.monomials.begin(); it!=lucas_polynomial.monomials.end();++it){
      T E=it->second.coefficient;
      lucas_sequence_vector.push_back(E);
    }

    std::reverse(lucas_sequence_vector.begin(), lucas_sequence_vector.end());


  //Resultado
  return lucas_sequence_vector;  

};

//*********************************************************************************************************
//FIM DO HEADER
#endif

//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UMA ROTINA PARA COMPUTAR O NÚMERO DE PARTIÇÕES TRIANGULARES DE UM INTEIRO USANDO FUNÇÕES GERADORAS 

/*

A FUNÇÃO THETA DE RAMANUJAN É DEFINIDA COMO f(a, b) = Σ [a^{n(n+1)/2}][b^{n(n-1)/2}] COM n=-∞,..., (-2),(-1),0,1,2,3,..., ∞ E |ab|<1. TAIS CLASSES
DE FUNÇÕES SÃO GENERALIZAÇÕES DAS FUNÇÃO THETA DE JACOBI. ALGUNS CASOS PARTICULARES DE GRANDE IMPORTÂNCIA PARA A TEORIA DAS PARTIÇÕES SÃO
DEFINIDOS PELAS IDENTIDADES: φ(q)=f(q, q); ψ(q)=f(q, q³); f(-q)=f(-q, -q²).

A FUNÇÃO {φ(q)}^k É A FUNÇÃO GERADORA DA FUNÇÃO ARITMÉTICA DE REPRESENTAÇÃO DE UM INTEIRO n COMO A SOMA DE k QUADRADOS PEREFEITOS. DE FORMA SIMILAR
{ψ(q)}^k=  Σ t(k, n){q^n}, ONDE t(k, n) É A FUNÇÃO QUE COMPUTA DE QUANTAS FORMAS DISTINTAS UM INTEIRO PODE SER ESCRITO COMO A SOMA DE k NÚMEROS
TRIANGULARES DIFERENTES (DIFERENTES ORDENS CONTAM COMO PARTIÇÕES DIFERENTES). UM NÚMERO TRIANGULAR É UM INTEIRO DA FORMA t={n(n+1)/2}.

PARA MAIORES INFORMAÇÕES: Number Theory in the Spirit of Ramanujan by Bruce C. Berndt

*/


//************************************************************************************************************************
//CABEÇALHO
#ifndef TRIANGULAR_PARTITION_GENERATING_FUNCTION_H
#define TRIANGULAR_PARTITION_GENERATING_FUNCTION_H
#include"sparse_polynomials.h"
#include<vector>


//************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> generate_triangular_base_polynomial(int64_t);

template<typename T>
polynomial<T> compute_triangular_partition_generating_function(int64_t, int64_t);


template<typename T, typename U>
std::vector<U> compute_triangular_partition_function(polynomial<T>&, int64_t);


//************************************************************************************************************************
//FUNÇÕES
//Função que computa um polinômio base para computar a função geradora da sequência da função t(k, n)
template<typename T>
polynomial<T> generate_triangular_base_polynomial(int64_t n){

  //Variáveis locais
  polynomial<T> result;
  univariate_monomial<T> poly_term;


  //Procedimentros
    //Loop principal
    for(int64_t i=0; i<=n; ++i){
      int64_t t=((i+1)*i)/2;
  
      poly_term.coefficient=1;
      poly_term.power=t;
  
      if(t>n) break;
      result.monomials.insert({poly_term.power, poly_term});

    };//Fim do loop principal


  //Resultado
  return result;

};


//Função que computa a função geradora para a função de partição triangular
template<typename T>
polynomial<T> compute_triangular_partition_generating_function(int64_t n, int64_t k){

  //Variáveis locais
  polynomial<T> multiplier = generate_triangular_base_polynomial<T>(n);//ψ¹(q)
  polynomial<T> triangular_polynomial=multiplier;//ψ¹(q)


  //Procedimentos
     //Caso base:
     if(k==1) return triangular_polynomial;

    //Loop principal
    for(int64_t i=1; i<k; ++i){
      triangular_polynomial=triangular_polynomial*multiplier;

      if(triangular_polynomial.degree()>(5*n)){

        //Removendo os termos de expoentes elevados
        for(auto it=triangular_polynomial.monomials.begin(); it!=triangular_polynomial.monomials.end();){
          if((it->second.power)>n) it = triangular_polynomial.monomials.erase(it);
          else break;
        }

      }



    };//Fim do loop principal


    //Ajuste fino do resultado
    for(auto it=triangular_polynomial.monomials.begin(); it!=triangular_polynomial.monomials.end();){
      if((it->second.power)>n) it = triangular_polynomial.monomials.erase(it);
      else break;
    }


  //Resultado
  return triangular_polynomial;

};


//Função que computa a função aritmética t(k, n)
template<typename T, typename U>
std::vector<U> compute_triangular_partition_function(polynomial<T>& p1, int64_t n){

  //Variáveis locais
  std::vector<U> tk_vector;
  U zero=static_cast<U>(0);

  //Procedimento
    //Loop principal
    for(int64_t i=0; i<=n; ++i){

      auto found = p1.monomials.find(i);
      if(found != p1.monomials.end()){
        U tk= found->second.coefficient;
        tk_vector.push_back(tk);
      }
      else tk_vector.push_back(zero);

    };//Fim do loop principal


  //Resultado
  return tk_vector;

};






//************************************************************************************************************************
//FIM DO HEADER
#endif

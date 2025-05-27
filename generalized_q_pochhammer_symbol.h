//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA UAM VERSÃO GENERALIZADA DOS SÍMBOLOS DE Q-POCHHAMMER

/*

EM MUITAS MANIPULAÇÕES SÍMBOLICAS ENVOLVENDO Q-ANÁLOGOS TEM-SE DE AVALIAR EXPRESSÕES DO TIPO (a{q^n}; b{q^m})(∞) ONDE
a, b, n, m SÃO NÚMEROS INTEIROS. DE PARTICULAR INTERESSE SÃO EXPRESSÕES NAS QUAIS a=1, b=1.

VAMOS CRIAR UMA SUBROTINA QUE PODE SER USADO EM OUTROS ALGORITMOS ENVOLVENDO Q-ANÁLOGOS.

PARA MAIORES INFORMAÇÕES: Number Theory in the Spirit of Ramanujan by Bruce C. Berndt
                          https://mathworld.wolfram.com/q-Series.html
                          https://mathworld.wolfram.com/q-PochhammerSymbol.html
                          https://mathworld.wolfram.com/PochhammerSymbol.html

*/ 


//**************************************************************************************************************************
//CABEÇALHO
#ifndef GENERALIZED_Q_POCHHAMMER_SYMBOL_H
#define GENERALIZED_Q_POCHHAMMER_SYMBOL_H
#include"sparse_polynomials.h"



//**************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> compute_q_pochhammer_symbol_finite(int64_t, int64_t, int64_t, T, T);

template<typename T>
polynomial<T> compute_q_pochhammer_symbol_infinite(int64_t, int64_t, int64_t, T, T);


//**************************************************************************************************************************
//FUNÇÕES
//Função que computa o símbolo de q-Pochhammer
/*
NOTA: Usaremos a notação (a{q^n}; b{q^m})(∞) para os argumentos da função, q é apenas uma variável simbólica e
      k denota o limite o número de termos usados na expansão.
*/
template<typename T>
polynomial<T> compute_q_pochhammer_symbol_finite(int64_t n, int64_t m, int64_t k, T a, T b){

  //Variáveis locais
  polynomial<T> q_symbol;
  polynomial<T> qp_1, qp_2, qp_3;
  univariate_monomial<T> q_term;


  //Procedimentos
    //Definindo os termos bases usados no cálculo

    q_term.coefficient=1;  q_term.power=0;
    qp_1.monomials.insert({q_term.power, q_term});//f(x)=1

    q_term.coefficient=a;  q_term.power=n;
    qp_2.monomials.insert({q_term.power, q_term});//f(x)=a(x^n)

    q_term.coefficient=b;  q_term.power=m;
    qp_3.monomials.insert({q_term.power, q_term});//f(x)=b(x^m)



    q_symbol=qp_1-qp_2;//f(x)=1-a(x^n) (1º termo da expansão)


    //Calculando o símbolo de q_Pochhammer
    for(int64_t i=1; i<k; ++i){
          
      qp_2=qp_2*qp_3;            
      polynomial<T> q_partial=qp_1-qp_2;
      q_symbol=q_symbol*q_partial;
      
    }
    

  //Resultado
  return q_symbol;

};


//Função que computa o símbolo de q-Pochhammer
/*
NOTA: A série é truncada nos k primeiros termos.
*/
template<typename T>
polynomial<T> compute_q_pochhammer_symbol_infinite(int64_t n, int64_t m, int64_t k, T a, T b){

  //Variáveis locais
  polynomial<T> q_symbol;
  polynomial<T> qp_1, qp_2, qp_3;
  univariate_monomial<T> q_term;


  //Procedimentos
    //Definindo os termos bases usados no cálculo

    q_term.coefficient=1;  q_term.power=0;
    qp_1.monomials.insert({q_term.power, q_term});//f(x)=1

    q_term.coefficient=a;  q_term.power=n;
    qp_2.monomials.insert({q_term.power, q_term});//f(x)=a(x^n)

    q_term.coefficient=b;  q_term.power=m;
    qp_3.monomials.insert({q_term.power, q_term});//f(x)=b(x^m)



    q_symbol=qp_1-qp_2;//f(x)=1-a(x^n) (1º termo da expansão)


    //Calculando o símbolo de q_Pochhammer
    for(int64_t i=1; i<=k; ++i){
          
      qp_2=qp_2*qp_3;            
      polynomial<T> q_partial=qp_1-qp_2;
      q_symbol=q_symbol*q_partial;

      if(q_symbol.degree()>(2*k)){

        //Removendo os termos de expoentes elevados
        for(auto it=q_symbol.monomials.begin(); it!=q_symbol.monomials.end();){
          if((it->second.power)>(2*k)) it = q_symbol.monomials.erase(it);
          else break;
        }

      }

      
    };


    //Ajuste final do resultado
    for(auto it=q_symbol.monomials.begin(); it!=q_symbol.monomials.end();){
      if((it->second.power)>k)
        it = q_symbol.monomials.erase(it);
      else break;
    }

    

  //Resultado
  return q_symbol;

};

//**************************************************************************************************************************
//FIM DO HEADER
#endif 

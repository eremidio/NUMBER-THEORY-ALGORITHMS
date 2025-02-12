//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA ROTINAS PARA CALCULAR A FUNÇÃO TAU DE RAMANUJAN USANDO SÉRIES Q

/*

A FUNÇÃO TAU DE RAMANUJAN τ(n) PODE SER CALCULADA A PARTIR DA EXPANSÃO DA SÉRIE-Q ASSOCIADAS
A FUNÇÃO MODULAR DISCRIMINANTE Δ(z) PARA z COMPLEXO. A SEGUINTE IDENTIDADE É VÁLIDA:
Δ(z)= q Π {(1-(q^n))^24} = Σ {τ(n)(q^n)}, ONDE q=e^(2πiz), n=1,2,... 

TAL IDENTIDADE PODE SER FACILMENTE EMPREGADA PARA COMPUTAR VALORES DE τ(n) EM UM INTERVALO
PROVIDO EFICIENTES ROTINAS PARA ARITMÉTICA POLINOMIAL. ESTIMATIVAS RAZOÁVEIS ESTABELECEM QUE
τ(n)<(n^7).


PARA MAIORES INFORMAÇÕES: The Mathematical Legacy of Srinivasa Ramanujan by M. Ram Murty, V. Kumar Murty 
                          https://en.wikipedia.org/wiki/Ramanujan_tau_function

*/



//****************************************************************************************************
//CABEÇALHO
#ifndef RAMANUJAN_TAU_FUNCTION_QSERIES_H
#define RAMANUJAN_TAU_FUNCTION_QSERIES_H
#include"sparse_polynomials.h"


//****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
template<typename T>
polynomial<T> compute_tau_polynomial_factor(int64_t, int64_t);

template<typename T>
void compute_ramanujan_tau_function(int64_t);

//****************************************************************************************************
//FUNÇÕES
template<typename T>
polynomial<T> compute_tau_polynomial_factor(int64_t index, int64_t bound){

  //Variáveis locais
  polynomial<T> tau_polynomial, result;
  univariate_monomial<T> poly_term;
  

  //Procedimentos
    //Definindo o polinômio g(x)=1-(x^n)
    poly_term.coefficient=1; poly_term.power=0;
    tau_polynomial.monomials.insert({poly_term.power, poly_term});
    poly_term.coefficient=(-1); poly_term.power=index;
    tau_polynomial.monomials.insert({poly_term.power, poly_term}); 


    //Calculando t(x)=(1-(x^n))^24 (24=16+8)
    tau_polynomial=tau_polynomial*tau_polynomial; //g(x)^2
    tau_polynomial=tau_polynomial*tau_polynomial; //g(x)^4
    tau_polynomial=tau_polynomial*tau_polynomial; //g(x)^8
    result=tau_polynomial;
    tau_polynomial=tau_polynomial*tau_polynomial; //g(x)^16
    result=result*tau_polynomial;
   


    //Removendo os termos de coeficientes elevados
    for(auto it=result.monomials.begin(); it!=result.monomials.end();){
      if((it->second.power)>(bound+1))
        it = result.monomials.erase(it);
      else break;
      
    }

  
  //Resultado
  return result;

};



//Função que computa a função τ(n) usando séries q
template<typename T>
void compute_ramanujan_tau_function(int64_t n){

  //Variáveis locais
  polynomial<T> ramanujan_tau_polynomial=compute_tau_polynomial_factor<T>(1, n);
  polynomial<T> identity;
  univariate_monomial<T> poly_term;

  
  //Procedimentos
    //Ajuste de variáveis
    poly_term.coefficient=1; poly_term.power=1;
    identity.monomials.insert({poly_term.power, poly_term});//f(q)=q




    //Loop principal
    for(int64_t i=2; i<=n; ++i){

      //Calculando parciais da série q da função τ(n)
      polynomial<T> factor_poly=compute_tau_polynomial_factor<T>(i, n);
      ramanujan_tau_polynomial=ramanujan_tau_polynomial*factor_poly;


      //Removendo os termos de coeficientes elevados
      if(i%10==0){
        for(auto it=ramanujan_tau_polynomial.monomials.begin(); it!=ramanujan_tau_polynomial.monomials.end();){
          if((it->second.power)>(n+1))
            it = ramanujan_tau_polynomial.monomials.erase(it);
          else break;
        }
      }
  

    };//Fim do loop principal


    //Ajuste fino do resultado
    for(auto it=ramanujan_tau_polynomial.monomials.begin(); it!=ramanujan_tau_polynomial.monomials.end();){
      if((it->second.power)>n)
        it = ramanujan_tau_polynomial.monomials.erase(it);
        else break;
    };
  
    ramanujan_tau_polynomial=ramanujan_tau_polynomial*identity;


    //Exibindo o resultado da execução do algoritmo
    for(auto it=ramanujan_tau_polynomial.monomials.begin(); it!=ramanujan_tau_polynomial.monomials.end(); ++it)
      std::cout<<"τ("<<it->second.power<<") = "<<it->second.coefficient<<", ";
    std::cout<<"...\n";

  



};


//****************************************************************************************************
//FIM DO HEADER
#endif

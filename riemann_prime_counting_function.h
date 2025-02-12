//VAMOS CRIAR UM PROGRAMA QUE IMPLEMENTA A  FUNÇÃO DE CONTAGEM DE PRIMOS DE RIEMANN Ri(x)

/*

A FUNÇÃO Π(x) DE RIEMANN É DEFINIDA PELO SOMATÓRIO Π(x)= Σ(1/e), NO QUAL O SOMATÓRIO É
REALIZADO SOBRE TODOS OS NÚMEROS DA FORMA n=p^e COM p PRIMO.

TAL FUNÇÃO SATISFAZ A RELAÇÃO Π(x)=Σ {π(x^(1/n))/n}, ONDE π(x) É A FUNÇÃO DE CONTAGEM DE
NÚMEROS PRIMOS INFERIORES A x E O SOMÁRTORIO É REALIZADO PARA n = 1,..., log2(x). USANDO-SE
A FÓRMULA DE INVERSÃO DE MÖBIUS TEM-SE QUE: π(x) = Σ{μ(n)/n}Π(x^(1/n), ONDE μ(n) É A
FUNÇÃO DE MÖBIUS.

A FUNÇÃO Π(x) É  RELACIONADA A FUNÇÃO ZETA DE RIEMANN ζ(x) POR MEIO DE UMA TRANSFORMAÇÃO DE
MELLIN. UMA EXPRESSÃO EXATA PARA Π(x) EXISTE EM TERMOS DA FUNÇÃO LOGARÍTMICA INTEGRAL li(x),
ENVOLVENDO OS ZEROS NÃO TRIVIAIS DA FUNÇÃO ζ(x).

A FUNÇÃO DE CONTAGEM DE PRIMOS DE RIEMANN Ri(x) É UMA FUNÇÃO QUE USADA PARA APROXIMAR A FUNÇÃO
π(x) DE CONTAGEM DE NÚMEROS COM ALTA PRECISÃO. ELA PODE SER APROXIMADA POR MEIO DA SÉRIE:
Ri(x)=Σ{μ(n)/n}li(x^(1/n).

EXISTEM IMPORTANTES RELAÇÕES FUNCIONAIS ENVOLVENDO AS FUNÇÕES Ri(x) COM AS FUNÇÕES ζ(x) (VIA
SÉRIES DE GRAM) E A FUNÇÃO π(x).


PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/RiemannPrimeCountingFunction.html
                          Prime Numbers And Computer Methods For Factorization, by Hans Riesel  


*/ 


//***********************************************************************************************
//CABEÇALHO
#ifndef RIEMANN_PRIME_COUNTING_FUNCTION_H
#define RIEMANN_PRIME_COUNTING_FUNCTION_H
#include"mobius_function.h"
#include"logarithmic_integral_continued_fraction.h"
#include"prime_table_reading.h"



//***********************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
double riemann_pi_weight_function(uint64_t, uint64_t[]);
double riemann_prime_counting_function(double);


//***********************************************************************************************
//FUNÇÕES
//Programa que calcula a função Π(x)
double riemann_pi_weight_function(uint64_t n, uint64_t prime_list[]){

  //Variáveis locais
  double result=0.0;
  uint64_t prime_power, e;


  //Procedimentos
    //Loop sobre números primos estocados em uma lista
    for(uint64_t i=0; prime_list[i]<=n ; ++i){
 
        prime_power=prime_list[i];
        e=1; result+= (1.0/e);

        while(1){
          prime_power*=prime_list[i];
          e++;          
          if(prime_power<=n) result+= (1.0/e);
          else break;

        }

    };

  //Resultado
  return result;

};


//Função de contagem de primos de Riemann Ri(x)
double riemann_prime_counting_function(double x){

  //Variáveis locais
  double result=0.0;
  uint64_t index;


  //Procedimentos
    //Loop principal
    for(uint64_t n=1; ; ++n){
      double nth_root=pow(x, (1.0/n));
      if(nth_root<=2) break;
      else result+=((mobius_function(n)*logarithmic_integral_continued_fraction(nth_root))/n);
    }
  
  //Resultado
  return result;


};


//***********************************************************************************************
//FIM DO HEADER
#endif

//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A SÉRIE DE GRAM PARA APROXIMAR A FUNÇÃO DE CONTAGEM DE PRIMOS π(x) 

/*

A SÉRIE DE GRAM É UMA SÉRIE INFINITA QUE PODE SER USADA PARA APROXIMAR A FUNÇÃO DE CONTAGEM DE PRIMOS π(x) PARA VALORES
INTERMEDIÁRIOS DE x. TAL SÉRIE É DEFINIDA PELA EQUAÇÃO G(x)=1+Σ{ln(x)^k}/{k!kζ(k+1)}, ONDE ζ(x) É A FUNÇÃO ZETA DE 
RIEMANN E k=1,2,3,.... EXISTEM VARIAÇÕES DESTA SÉRIE E UMA REPRESENTAÇÃO INTEGRAL QUE SÃO ATRIBUIDAS A RAMANUJAN.

É POSSÍVEL MOSTRAR QUE TAL FUNÇÃO É EQUIVALENTE A FUNÇÃO Ri(x) DE RIEMANN PARA APROXIMAR π(x), EMBORA MUITAS VEZES SEJA
MAIS ADEQUADA PARA VALORES ATÉ A ORDEM 10^9. É POSSÍVEL MOSTRAR, NO ENTANTO, QUE G(x) TEM UM COMPORTAMENTO IRREGULAR NEM 
SEMPRE FORNECENDO APROXIMAÇÕES ACURADAS.

PARA MAIORES INFORMAÇÕES: https://math.stackexchange.com/questions/1506980/could-someone-explain-how-the-gram-series-relates-to-riemanns-function
                          https://mathworld.wolfram.com/GramSeries.html

*/


//**************************************************************************************************************************
//CABEÇALHO
#ifndef GRAM_SERIES_H
#define GRAM_SERIES_H
#include"riemann_zeta_series.h"
#include<stdint.h>


//CONSTANTES GLOBAIS
const double GRAM_MULTIPLIER=1e10;
const double GRAM_ERROR=1e-5;


//**************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
long double gram_factorial(int);
long double gram_series_approximation(int64_t);


//**************************************************************************************************************************
//FUNÇÕES
//Função que calcula a função fatorial de um inteiro
long double gram_factorial(int n){

  //Caso base:
  if(n==0) return 1.0;

  //Variáveis locais
  long double result=1.0;


  //Procedimento: loop principal
  for(int i=n; i>=1; --i) result*=i;

  
  //Resultado
  return result;

};


//Função que aproxima a função de contagem de primos usando séries de Gram
long double gram_series_approximation(int64_t n){

  //Variáveis locais
  long double sum=0.0;
  long double parcel=0.0;
  long double ln_x=log(n);
  long double fact=0.0, zeta=0.0;


  //Procedimento
    //Loop principal
    for(int k=1; ; ++k){

      parcel=GRAM_MULTIPLIER*pow(ln_x, k);
      fact=gram_factorial(k);
      zeta=riemann_zeta_asymptotic_series(k+1.0);
      parcel=parcel/(k*fact*zeta);
     

      if(parcel>=GRAM_ERROR) sum+=parcel;
      else break;

    };



  //Resultado
  return 1.0+(sum/GRAM_MULTIPLIER);

};

//**************************************************************************************************************************
//FIM DO HEADER
#endif

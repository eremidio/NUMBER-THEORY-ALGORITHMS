//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO ZETA PRIMO 

/*

A FUNÇÃO ZETA PRIMO P(s) É DEFINIDA PELA RELAÇÃO P(s) = Σ {p^(-s)}, ONDE A SOMA É FEITA SOBRE O CONJUNTO DE TODOS OS PRIMOS.
ESTA FUNÇÃO É UMA GENERALIZAÇÃO DA FUNÇÃO ZETA DE RIEMANN USUAL ζ(s), SENDO PARTICULARMENTE ÚTIL NA DETERMINAÇÃO DE 
DETERMINADAS CONSTANTES IMPORTANTES EM TEORIA ANÁLITICA DOS NÚMEROS. 

A FUNÇÃO ZETA PRIMO P(s) PODE SER COMPUTADA EM TERMOS DA FUNÇÃO ZETA DE RIEMANN USUAL PELA IDENTIDADE ENVOLVENDO A FÓRMULA 
DE INVERSÃO DE MÖBIUS P(s) = Σ{μ(k)/k} ln(ζ(ks)), COM k=1,2,... A FUNÇÃO ln(ζ(ks) PODE SER APROXIMADA USANDO-SE A SEGUINTE
FÓRMULA ln(ζ(ks)) ~ 2^(-ks)+ 3^(-ks)+(1/2){4^(-ks)}+5^(-ks)+7^(-ks)+... QUE PODE SER OBTIDA A PARTIR DA DEFINIÇÃO DA FUNÇÃO
ζ(s) E DA EXPANSÃO DA FUNÇÃO ln(1+x) EM SÉRIE DE TAYLOR.

A FUNÇÃO P(s) É UMA SÉRIE DE DIRICHLET QUE É A FUNÇÃO GERADORA DA FUNÇÃO CARACTERÍSTICA DOS NÚMEROS PRIMOS. A FUNÇÃO 
ζ(s)-1-P(s), POR SUA VEZ, É UMA SÉRIE DE DIRICHLET QUE É A FUNÇÃO GERADORA DA FUNÇÃO CARACTERÍSTICA DOS NÚMEROS COMPOSTOS.

ESTA FUNÇÃO APARECE EM UMA SÉRIE DE IDENTIDADES DE GRANDE INTERESSE TEÓRICO E ESTÁ RELACIONADA COM VÁRIAS CONSTANTES 
IMPORTANTES EM MATEMÁTICA.


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Prime_zeta_function
                          https://mathworld.wolfram.com/PrimeZetaFunction.html
                          https://mathworld.wolfram.com/ArtinsConstant.html
                          https://mathworld.wolfram.com/RiemannZetaFunction.html
                          Prime Numbers And Computer Methods For Factorization, by Hans Riesel

*/


//****************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_ZETA_FUNCTION_H
#define PRIME_ZETA_FUNCTION_H
#include"riemann_zeta_series.h"
#include"mobius_function.h"


//CONSTANTES GLOBAIS
const double PRIME_ZETA_EPSILON=1e-9;


//****************************************************************************************************************************
//DECLARAÇÕES DE FUNÇÕES
long double log_zeta_function(long double);
long double prime_zeta_function(long double);


//****************************************************************************************************************************
//FUNÇÕES
//Função que computa o valor aproximado de ln(ζ(ks))
long double log_zeta_function(long double power){

  //Variáveis locais
  const int base[12]={2,3,4,5,7,8,9,11,13,16,17,19};
  const double coeff[12]={1.0, 1.0, 0.5,1.0,1.0,(1.0/3.0),0.5,1.0,1.0,0.25,1.0,1.0};
  long double sum=0.0;


  //Procedimentos
    //Loop principal:
    for(int i=0; i<12; ++i){
      long double partial = (1.0/pow(base[i], power))*coeff[i];
      sum+=partial;

    }

  //Resultado
  return sum;

};


//Função que computa uma aproximação para a função zeta primo P(s)
long double prime_zeta_function(long double s){

  //Variáveis locais
  long double prime_zeta=0.0;
  uint64_t k=0;


  //Procedimentos
    //Loop principal
    for(k=1; ; k++){

      long double partial=0.0;
      long double ks=(k*s);

      if(ks<15) partial=log(riemann_zeta_asymptotic_series(ks));
      else partial=log_zeta_function(ks);
      partial=partial/k;

      if(partial<PRIME_ZETA_EPSILON)  break;
      else prime_zeta = prime_zeta + (mobius_function(k)*partial);


    };//Fim do loop principal


  //Resultado
  return prime_zeta;

};

//****************************************************************************************************************************
//FIM DO HEADER
#endif

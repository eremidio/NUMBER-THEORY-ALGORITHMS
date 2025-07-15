//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO DE CONTAGEM DE PRIMOS VIA CONVOLUÇÕES DE DIRICHLET

/*

SEJA 1p A FUNÇÃO CARACTERÍTICA DE NÚMEROS PRIMOS, ω(n) A FUNÇÃO DE CONTAGEM DE DISTINTOS FATORES PRIMOS DE UM INTEIRO E μ(n) A
FUNÇÃO DE MÖBIUS. A SEGUINTE RELAÇÃO ENVOLVENDO CONVOLUÇÕES DE DIRICHLET DESTAS TRÊS FUNÇÕES É VÁLIDA: ω*μ = 1p. DESTA FÓRMULA
É FACILMENTE OBSERVÁVEL QUE A FUNÇÃO π(x) DE CONTAGEM DE NÚMEROS PRIMOS PODE SER EXPRESSO POR MEIO DA SEGUINTE IDENTIDADE 
π(x)= Σ μ(d)M(|_x/d_|), ONDE |_x_| DENOTA A FUNÇÃO MENOR INTEIRO, M(n) É A FUNÇÃO DE MERTENS E d=1,2,...,n. TAL FÓRMULA APESAR
DE INEFICIENTE DO PONTO DE VISTA COMPUTACIONAL CONSTITUI UMA INTERESSANTE APLICAÇÃO DE CONVOLUÇÕES DE DIRICHLET EM TEORIA
ANÁLITICA DOS NÚMEROS.

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Dirichlet_convolution#Examples

*/


//*******************************************************************************************************************************
//CABEÇALHO
#ifndef PRIME_COUNTING_FUNCTION_DIRICHLET_CONVOLUTION_H
#define PRIME_COUNTING_FUNCTION_DIRICHLET_CONVOLUTION_H
#include"prime_omega_function.h"
#include"mobius_function_lambert_series.h"


//*******************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t prime_counting_function_dirichlet_convolution(int32_t, int32_t[], int8_t[]);


//*******************************************************************************************************************************
//FUNÇÕES

//Função que computa a função de contagem de números primos usando convoluções de Dirichlet
int32_t prime_counting_function_dirichlet_convolution(int32_t n, int32_t prime_omega_array[], int8_t mobius_array[]){

  //Váriáveis locais
  int32_t prime_counting=0;


  //Procedimentos
    //Loop principal: iterando sobre os elementos da soma
    for(int32_t d=1; d<=n; ++d){
      int64_t index=floor(n/d);
      int64_t M=0;
      for(int32_t k=1; k<=index; ++k) M=M+mobius_array[k];//Computando a função de Mertens 
      prime_counting=prime_counting+(prime_omega_array[d]*M);
    }


  //Resultado
  return prime_counting;

};


//*******************************************************************************************************************************
//FIM DO HEADER
#endif

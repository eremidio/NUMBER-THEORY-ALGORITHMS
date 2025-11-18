//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO TOTIENTE DE EULER USANDO CONVOLUÇÕES DE DIRICHLET

/*

SEJA Id(n)=n A FUNÇÃO IDENTIDADE, E 1(n)=1 A FUNÇÃO CONSTANTE, TAIS FUNÇÕES ESTÃO RELACIONADAS A FUNÇÃO TOTIENTE DE EULER
φ(n) PELA IDENTIDADE φ*1=Id, USANDO A FÓRMULA DE DIVISÃO DE MÖBIUS TEMOS QUE φ=Ιd*μ, EXPLICITAMENTE φ(n)=Σ Ιd(n/d)μ(d),
ONDE A SOMA É FEITA SOBRE OS DIVISORES d DE n. ESTA FÓRMULA É ÚTIL PARA COMPUTAR A FUNÇÃO TOTIENTE DE EULER EM PEQUENOS
INTERVALOS, PROVIDOS DE UM ARRAY DE VALORES DA FUNÇÃO DE MÖBIUS μ(n).

PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Dirichlet_convolution#Properties_and_examples
                          https://en.wikipedia.org/wiki/Euler%27s_totient_function#

*/ 


//*********************************************************************************************
//CABEÇALHO
#ifndef EULER_TOTIENT_FUNCTION_DIRICHLET_CONVOLUTION_H
#define EULER_TOTIENT_FUNCTION_DIRICHLET_CONVOLUTION_H
#include"mobius_function_lambert_series.h"


//*********************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t* compute_euler_totient_function_dirichlet_convolution(int32_t, int8_t[]);


//*********************************************************************************************
//FUNÇÕES
//Função que computa a função φ(n) usando convoluções de Dirichlet
int32_t* compute_euler_totient_function_dirichlet_convolution(int32_t n, int8_t mobius_array[]){

  //Ajuste de variáveis
  ++n;
 
  //Variáveis locais
  int32_t* euler_phi_array=(int32_t*) calloc((n+1), sizeof(int32_t));


  //Procedimentos
    //Computando os valores da função totiente em um intervalo
    for(int32_t i=1; i<n; ++i){
      for(int32_t j=i; j<n; j+=i){
        euler_phi_array[j]+=(j/i)*mobius_array[i];          
      }
    };//Fim do loop principal


  //Resultado
  return euler_phi_array;

};


//*********************************************************************************************
//FIM DO HEADER
#endif


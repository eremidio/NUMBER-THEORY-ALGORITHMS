//VAMOS CRIAR UM PROGRAMA QUE COMPUTA FUNÇÕES ARITMÉTICAS LOGARÍTMICAS USANDO SERIÉS DE LAMBERT

/*

A FUNÇÃO DE VON-MANGOLDT Λ(n) PODE SER CALCULANDO USANDO-SE A SEGUINTE IDENTIDADE ENVOLVENDO SÉRIES DE LAMBERT:
Σ {Λ(n)(x^n)}/{1-(x^n)}=Σ ln(n){(x^n)}.

TAL IDENTIDADE PODE SER USADA PARA COMPUTAR RAPIDAMENTE VALORES DAS FUNÇÃO Λ(n) E DAS FUNÇÕES DE CHEBYSHEV DO
PRIMEIRO E SEGUNDO TIPOS θ(n) E Ψ(n) EM UM INTERVALO. TAIS CLASSES DE FUNÇÕES SÃO EXTREMAMENTE IMPORTANTES EM
UMA SÉRIE DE TEOREMAS E IDENTIDADES ENVOLVENDO A DISTRIBUIÇÃO DE NÚMEROS PRIMOS DEVIDO A FORMA ASSINTÓTICA
LOGARÍTMICA DA FUNÇÃO DE CONTAGEM DE PRIMOS π(x).


PARA MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Lambert_series
                          https://en.wikipedia.org/wiki/Chebyshev_function
                          https://en.wikipedia.org/wiki/Von_Mangoldt_function#Exponential_series

*/


//**************************************************************************************************************
//CABEÇALHO
#ifndef LOGARITMIC_FUNCTIONS_LAMBERT_SERIES_H
#define LOGARITMIC_FUNCTIONS_LAMBERT_SERIES_H
#include<stdint.h>
#include<stdlib.h>
#include<math.h>


//**************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
double* generate_von_mangoldt_array(int64_t);
double* generate_chebyshev_second_array(int64_t, double[]);
double* generate_chebyshev_first_array(int64_t, double[]);


//**************************************************************************************************************
//FUNÇÕES
//Função que computa a função de von Mangoldt Λ(n) em um intervalo
double* generate_von_mangoldt_array(int64_t n){

  //Variáveis locais
  double* mangoldt_array=(double*)calloc((n+1), sizeof(double));

  
  //Procedimentos
    //Inicializando os array de valores de Λ(n)
    for(int64_t k=1; k<=n; ++k) mangoldt_array[k]=log(k);


    //Loop principal: calculando a função de von Mangoldt em um intervalo
    for(int64_t i=1; i<=(n/2); ++i){
      for(int64_t j=(2*i); j<=n; j+=i){
        mangoldt_array[j] = mangoldt_array[j]- mangoldt_array[i];
      }
    }


  //Resultado
  return mangoldt_array;

};


//Função que computa a função de Chebyshev do segundo tipo em um intervalo
double* generate_chebyshev_second_array(int64_t n, double mangoldt_array[]){

  //Variáveis locais
  double* chebyshev2_array=(double*)calloc((n+1), sizeof(double));

  //Procedimentos
    //Loop principal: calculando a função Ψ(n) em um intervalo
    for(int64_t i=1; i<=n; ++i){
      for(int64_t j=1; j<=i; ++j){
        if(mangoldt_array[j]>0) chebyshev2_array[i] = chebyshev2_array[i] + mangoldt_array[j];
      }
    }  
  

  //Resultado
  return chebyshev2_array;

};


//Função que computa a função de Chebyshev do primeiro tipo em um intervalo
double* generate_chebyshev_first_array(int64_t n, double mangoldt_array[]){

  //Variáveis locais
  double* chebyshev1_array=(double*)calloc((n+1), sizeof(double));
  int64_t p;


  //Procedimento
    //Zerando o valor de Λ(n) para números da forma p^k, com p primo e k≳2
    for(int64_t k=1; (k*k)<=n; ++k){

      if(mangoldt_array[k]==0.0) continue;
      else{
        p=(k*k);
        while(p<=n){
          mangoldt_array[p]=0.0;
          p*=k;
        }
      }

    };


    //Loop principal: calculando a função θ(n) em um intervalo
    for(int64_t i=1; i<=n; ++i){
      for(int64_t j=1; j<=i; ++j){
        if(mangoldt_array[j]>0) chebyshev1_array[i] = chebyshev1_array[i] + mangoldt_array[j];
      }
    }  
  

  //Resultado
  return chebyshev1_array;

};

//**************************************************************************************************************
//FIM DO HEADER
#endif

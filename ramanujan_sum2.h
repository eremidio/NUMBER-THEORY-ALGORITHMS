//VAMOS CRIAR UM PROGRAMA PARA CALCULAR A FUNÇÃO ARITMÉTICA SOMA DE RAMANUJAN

/*

A FUNÇÃO ARITMÉTICA c(q, n) = Σ exp(2πi(a/q)n) PODE SER COMPUTADA DE FORMA EFICIENTE EM UM INTERVALO USANDO-SE A FÓRMULA:
c(q, n)={φ(q)φ(γ)}μ(γ), ONDE γ=mdc(q, n). COMO φ(q)=Σμ(n/δ)δ, ONDE δ DENOTA OS DIVISORES DE q, TEMOS A FÓRMULA
ALTERNATIVA: c(q, n)=Σμ(q/δ)δ  ONDE δ DENOTA NESTE CASO OS DIVISORES DE γ=mdc(q, n). 

TAIS FÓRMULAS PERMITEM USAR TÉCNICAS SIMILARES AO CRIVO DE ERATÓSTENES PARA COMPUTAR A FUNÇÃO c(q, n).


PARA  MAIORES INFORMAÇÕES: https://en.wikipedia.org/wiki/Arithmetic_function#Prime-count_related

*/


//*************************************************************************************************************************
//CABEÇALHO
#ifndef RAMANUJAN_SUM2_H
#define RAMANUJAN_SUM2_H
#include"mobius_function_lambert_series.h"
#include"euler_totient_function_lambert_series.h"


//*************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t gcd_s32(int32_t, int32_t);
int32_t* compute_ramanujan_sum(int32_t, int32_t);


//*************************************************************************************************************************
//FUNÇÕES
//Função que computa o mdc de dois inteiros
int32_t gcd_s32(int32_t a, int32_t b){

  if(b==0) return a;
  else return gcd_s32(b, (a%b));

};


//Função que computa um array de valores da função soma de Ramanujan c(q, n)
int32_t* compute_ramanujan_sum(int32_t q, int32_t n){

  //Variáveis locais
  int32_t* ramanujan_array=(int32_t*) calloc((n+1), sizeof(int32_t));
  int8_t* mobius_array=compute_mobius_function(n);

  //Procedimentos
    //Computando os valores da função c(q, n) em um intervalo
     for(int32_t i=1; i<=n; ++i){

      int32_t index=gcd_s32(i, q);
      for(int32_t j=1; j<=index; ++j){
        if(index%j==0) ramanujan_array[i]=ramanujan_array[i]+mobius_array[i/j]*j;
      }
    }


    //Limpando o cachê de memória
    if(mobius_array) free(mobius_array); mobius_array=NULL;

  //Resultado 
  return ramanujan_array;

};

//*************************************************************************************************************************
//FIM DO HEADER
#endif

//VAMOS CRIAR UM PROGRAMA QUE COMPUTA A FUNÇÃO ARIMÉTICA DE VALÊNCIA TOTIENTE DE UM INTEIRO

/*

A FUNÇÃO DE VALÊNCIA TOTIENTE Nφ(n) COMPUTA O NÚMERO DE INTEIROS m TAL QUE φ(m)=n. POR CONTA DA NATUREZA MULTIPLICATIVA DA FUNÇÃO
TOTIENTE DE EULER φ(m) É FÁCIL OBSERVAR QUE EXCETO POR n=1, PARA TODOS OS VALORES ÍMPARES DE n TEM-SE SEMPRE Nφ(n)= 0.

A CONJECTURA DE SIERPIŃSKI (JÁ PROVADA) AFIRMA QUE Nφ(n) ASSUME TODOS OS VALORES INTEIROS MAIORES QUE 1. ALGUMAS CONJECTURAS
RELACIONADAS A FUNÇÃO Nφ(n) COMO A CONJECTURA DE CARMICHAEL, SEGUNDO A QUAL Nφ(n)≳2 (EXISTEM PELO MENOS DUAS SOLUÇÕES m PARA A
EQUAÇÃO φ(m)=n) PERMANECEM EM ABERTO. 


PARA MAIORES INFORMAÇÕES: https://mathworld.wolfram.com/TotientValenceFunction.html
                          https://mathworld.wolfram.com/CarmichaelsTotientFunctionConjecture.html
                          https://mathworld.wolfram.com/SierpinskisConjecture.html
                          https://mathworld.wolfram.com/SierpinskisConjecture.html
                          https://oeis.org/A014197
                          https://oeis.org/A005277

*/


//********************************************************************************************************************************
//CABEÇALHO
#ifndef TOTIENT_VALENCE_FUNCTION_H
#define TOTIENT_VALENCE_FUNCTION_H
#include"euler_totient_function_lambert_series.h"


//CONSTANTES GLOBAIS
const int VALENCE_PHI_MAX_FACTOR1=10;//Constantes que determinam o intervalo de checagem dos valores de φ(m)
const int VALENCE_PHI_MAX_FACTOR2=100;
const int VALENCE_PHI_MAX_FACTOR3=1000;
const int VALENCE_PHI_MAX_FACTOR4=100000;


//********************************************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t * compute_totient_valence_function(int32_t);


//********************************************************************************************************************************
//FUNÇÕES
//Função que computa a função Nφ(n) em um intervalo
/*
  NOTA: função ajustada para 10^7, para valores maiores um fator multiplicativo maior que define o tamanho do
        intervalo deve ser usado.

*/

int32_t * compute_totient_valence_function(int32_t n){

  //Variáveis locais
  int32_t* totient_array = compute_totient_function(n*VALENCE_PHI_MAX_FACTOR1);
  int32_t* totient_valence_array = (int32_t*) calloc((n+1), sizeof(int32_t));
  int32_t upper=0, lower=0, counter=0; 


  //Procedimentos
    //Ajuste do 1º elemento do array
    totient_valence_array[1]=2;//φ(n)=1 para n=1,2

    //Loop principal: computando a função Nφ(n) em um intervalo
    for(int32_t i=2; i<=n; i+=2){
      counter=0;
      upper=(i*VALENCE_PHI_MAX_FACTOR1); lower=i+1;

      for(int32_t j=lower; j<=upper; j++){
        if(totient_array[j]==i)
          counter++;
      }
        totient_valence_array[i]=counter;

    }


    //Limpando o cachê de memória
    if(totient_array) free(totient_array); totient_array=NULL;


  //Resultado
  return totient_valence_array;

};

//********************************************************************************************************************************
//FIM DO HEADER
#endif

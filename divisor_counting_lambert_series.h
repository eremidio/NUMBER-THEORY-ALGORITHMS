//VAMOS CRIAR UM PROGRAMA QUE CALCULA A FUNÇÃO DE CONTAGEM DE DIVISORES DE UM INTEIRO d(n) USANDO SÉRIES DE LAMBERT 

/*

PARA A FUNÇÃO DE CONTAGEM DE DIVISORES DE UM INTEIRO d(n) TEMOS A SEGUINTE IDENTIDADE: Σ{x^n}d(n)=Σ {x^n/(1-x^n)}
QUE PODE SER USADA PARA COMPUTAR RAPIDAMENTE VALORES DE d(n) EM UM INTERVALO.

PARA MAIORES INFORMAÇÕES: https://github.com/eremidio/NUMBER-THEORY-ALGORITHMS/blob/main/sum_of_divisors_lambert_series.h
                          https://oeis.org/A000005


*/


//****************************************************************************************************
//CABEÇALHO
#ifndef DIVISOR_COUNTING_LAMBERT_SERIES_H
#define DIVISOR_COUNTING_LAMBERT_SERIES_H
#include<stdint.h>
#include<stdlib.h>


//****************************************************************************************************
//DECLARAÇÃO DE FUNÇÕES
int32_t * compute_divisor_counting_function(int32_t);


//****************************************************************************************************
//FUNÇÕES
/*
  NOTA: O somatório do lado direito da identidade fundamental pode ser aproximado pela relação:
        (x^n)/{1-(x^n)} ~ {x^n+x^(2n)+x^(3n)+...}.
        O algoritmo em sua forma final consiste em uma modificação da peneira de Eratóstenes.

*/
int32_t * compute_divisor_counting_function(int32_t n){


  //Variáveis locais
  int32_t* divisor_counting_array=(int32_t*) calloc((n+1), sizeof(int32_t));


  //Procedimentos
    //Inicializando o array de coeficientes de somas parciais da séries de Lambert
    for(int32_t k=2; k<=n; ++k) divisor_counting_array[k]=2;//1 e n são divisores triviais de qualquer número


    //Computando os valores da função de contagem de divisores
    for(int32_t i=2; i<=(n/2); ++i){
      for(int32_t j=(2*i); j<=n; j+=i){
        divisor_counting_array[j]=divisor_counting_array[j]+1;

      }
    };
  
  
  //Resultado 
  return divisor_counting_array;


};

//****************************************************************************************************
//FIM DO HEADER
#endif 
